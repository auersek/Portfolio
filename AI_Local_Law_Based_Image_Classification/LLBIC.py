import numpy as np
import torch
import pickle
import gzip
import gc
from collections import defaultdict
import cv2
from scipy.ndimage import center_of_mass
from sklearn.decomposition import PCA
import random
import matplotlib.pyplot as plt



class Mnist_Loader:
    def load_data(self):
        """Load the MNIST dataset from a gzipped pickle file."""
        print("Loading MNIST data...")
        with gzip.open('./data/mnist.pkl.gz', 'rb') as f:
            training_data, validation_data, test_data = pickle.load(f, encoding='latin1')
        print("MNIST data loaded.")
        return training_data, validation_data, test_data

    def load_data_wrapper(self):
        """Prepare and return the MNIST dataset in a structured format."""
        print("Wrapping MNIST data...")
        training_data, validation_data, test_data = self.load_data()

        # Apply the 0.2 filter during the preparation phase
        training_data = self._prepare_data(training_data)
        validation_data = self._prepare_data(validation_data, label_vectorization=False)
        test_data = self._prepare_data(test_data)

        print("MNIST data wrapped.")
        return training_data, validation_data, test_data

    def _prepare_data(self, data, label_vectorization=True):
        """Helper function to reshape images, apply the 0.2 filter, and vectorize labels."""
        images = [self.apply_threshold(np.reshape(x, (28, 28))) for x in data[0]]  # Apply the filter during reshaping
        print("0.2 filter applied")
        labels = [self.vectorized_result(y) if label_vectorization else y for y in data[1]]
        return list(zip(images, labels))

    def apply_threshold(self, image, threshold=0.2):
        """Apply the 0.2 threshold filter to the image."""
        filtered_image = np.where(image < threshold, 0, image)
        return filtered_image

    def vectorized_result(self, j):
        """Convert a digit into a one-hot encoded vector."""
        vector = np.zeros((10, 1))
        vector[j] = 1.0
        return vector

    def centralize_image(self, image):
        """Centralize the image by shifting the bounding box of the non-zero pixels to the center of the image."""
        y, x = np.nonzero(image)  # Get coordinates of non-zero pixels
        if len(x) == 0 or len(y) == 0:  # If the image is completely empty, return as is
            return image

        # Calculate the bounding box of the non-zero pixels
        min_x, max_x = np.min(x), np.max(x)
        min_y, max_y = np.min(y), np.max(y)

        # Width and height of the bounding box
        bbox_width = max_x - min_x
        bbox_height = max_y - min_y

        # Calculate the center of the bounding box
        bbox_center_x = min_x + bbox_width // 2
        bbox_center_y = min_y + bbox_height // 2

        # Calculate shifts to move the bounding box center to the image center
        image_center_x = image.shape[1] // 2
        image_center_y = image.shape[0] // 2
        shift_x = image_center_x - bbox_center_x
        shift_y = image_center_y - bbox_center_y

        # Apply the translation (shifting) to the image
        translation_matrix = np.float32([[1, 0, shift_x], [0, 1, shift_y]])
        centralized_image = cv2.warpAffine(image, translation_matrix, (image.shape[1], image.shape[0]), borderMode=cv2.BORDER_CONSTANT, borderValue=0)

        return centralized_image


    def calculate_optimal_rotation(self, image, steps=36):
        """Find the rotation angle that makes the bounding box as narrow as possible and as tall as possible, within ±40 degrees."""
        best_angle = 0
        max_height = 0
        min_width = float('inf')

        # Ensure steps is at least 1 to avoid division by zero
        if steps < 1:
            steps = 1

        # Calculate the angle step size
        angle_step = 80 / steps

        for angle in range(-40, 41, int(angle_step)):
            rotated_image = self.rotate_image(image, angle)
            y, x = np.nonzero(rotated_image)  # Get the coordinates of non-zero pixels
            if len(x) == 0 or len(y) == 0:
                continue
            
            min_x, max_x = np.min(x), np.max(x)
            min_y, max_y = np.min(y), np.max(y)
            width, height = max_x - min_x, max_y - min_y

            # Prefer the rotation that maximizes the height and minimizes the width
            if width < min_width or (width == min_width and height > max_height):
                min_width = width
                max_height = height
                best_angle = angle

        return best_angle

    def rotate_image(self, image, angle):
        """Rotate the image by a specified angle."""
        h, w = image.shape
        center = (w / 2, h / 2)
        rotation_matrix = cv2.getRotationMatrix2D(center, angle, scale=1.0)
        rotated_image = cv2.warpAffine(image, rotation_matrix, (w, h), flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_CONSTANT, borderValue=0)
        return rotated_image

    def show_images(self, before, after):
        """Display images before and after rotation."""
        fig, ax = plt.subplots(1, 2, figsize=(8, 4))
        ax[0].imshow(before, cmap='gray')
        ax[0].set_title('Before Rotation')
        ax[0].axis('off')

        ax[1].imshow(after, cmap='gray')
        ax[1].set_title('After Rotation')
        ax[1].axis('off')

        plt.show()


    def standardize_images(self, images, labels):
        """Standardize a list of images by first centralizing and then rotating them."""
        standardized_images = []
        for image, _ in zip(images, labels):
            centralized_image = self.centralize_image(image)  # First centralize the image
            angle = self.calculate_optimal_rotation(centralized_image)  # Then calculate optimal rotation angle
            rotated_image = self.rotate_image(centralized_image, angle)  # Rotate by the calculated angle to adjust the orientation
            
            # Optionally display images before and after rotation
            # self.show_images(image, rotated_image)
            
            standardized_images.append(rotated_image)
        return standardized_images


class LLBIC:
    def __init__(self, no_of_instance=20000, no_of_classes=10, no_of_laws=196, H=2, device=torch.device('cpu')):
        print("Initializing LLBIC...")
        loader = Mnist_Loader()
        train_data, val_data, test_data = loader.load_data_wrapper()

        train_data = train_data[:no_of_instance]
        test_data = test_data[:10000]

        train_images, train_labels = zip(*train_data)
        test_images, test_labels = zip(*test_data)


        train_images_standardized = loader.standardize_images(np.array(train_images), np.array(train_labels))
        test_images_standardized = loader.standardize_images(np.array(test_images), np.array(test_labels))

        # Convert standardized images to tensors
        def convert_to_tensor(images, labels):
            print("Converting data to tensors...")
            if not images or not all(isinstance(img, np.ndarray) for img in images):
                raise ValueError("Images must be a list of numpy arrays.")
            inputs_tensor = torch.tensor(np.array(images).reshape(len(images), 784), dtype=torch.float32)
            classes_tensor = torch.tensor([np.argmax(label) for label in labels], dtype=torch.int64)
            print(f"Inputs tensor shape: {inputs_tensor.shape}")
            print(f"Classes tensor shape: {classes_tensor.shape}")
            return inputs_tensor, classes_tensor

        try:
            train_labels = [data[1] for data in train_data]
            test_labels = [data[1] for data in test_data]
            self.train_inputs, self.train_classes = convert_to_tensor(train_images, train_labels)
            self.test_inputs, self.test_classes = convert_to_tensor(test_images, test_labels)
        except ValueError as e:
            print(f"Error converting data to tensors: {e}")
            raise


        self.device = device
        self.train_inputs = self.train_inputs.to(self.device)
        self.train_classes = self.train_classes.to(self.device)
        self.test_inputs = self.test_inputs.to(self.device)
        self.test_classes = self.test_classes.to(self.device)

        self.no_of_classes = no_of_classes
        self.no_of_instance = no_of_instance
        self.no_of_laws = no_of_laws
        self.H = H
        self.features_matrix = torch.zeros((self.H, 196, self.no_of_classes), device=self.device)


    def _square_embed(self, instance_index, block_index):
        """ Extract a 2x2 block from the image and compute its symmetric matrix. """
        block_row = block_index // 14
        block_col = block_index % 14

        two_by_two_box = torch.zeros((2, 2), device=self.device)

        start_row = block_row * 2
        start_col = block_col * 2

        for i in range(2):
            for j in range(2):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    two_by_two_box[i, j] = self.train_inputs[instance_index, calculated_index]

        symmetric_matrix = torch.matmul( two_by_two_box.T, two_by_two_box)
        
        return symmetric_matrix

    def _square_embed_test(self, instance_index, block_index):
        """ Extract a 2x2 block from the image (test data) and compute its symmetric matrix. """
        block_row = block_index // 14
        block_col = block_index % 14

        two_by_two_box = torch.zeros((2, 2), device=self.device)

        start_row = block_row * 2
        start_col = block_col * 2

        for i in range(2):
            for j in range(2):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    two_by_two_box[i, j] = self.test_inputs[instance_index, calculated_index]

        symmetric_matrix = torch.matmul(two_by_two_box.T, two_by_two_box)
        
        return symmetric_matrix

    def count_non_zero_pixels_per_class(self):
        """Count the number of non-zero pixels and the number of instances for each class.
        Normalize the non-zero pixel counts by the number of instances and then by the maximum value."""
        
        non_zero_counts = torch.zeros(self.no_of_classes, dtype=torch.float32, device=self.device)
        class_counts = torch.zeros(self.no_of_classes, dtype=torch.int64, device=self.device)
        
        # Calculate non-zero pixel counts and class counts
        for i in range(self.no_of_instance): 
            label = self.train_classes[i]
            non_zero_pixels = torch.sum(self.train_inputs[i] > 0).item()
            non_zero_counts[label] += non_zero_pixels
            class_counts[label] += 1
        
        # Avoid division by zero for classes with no instances
        valid_classes = class_counts > 0
        non_zero_counts[valid_classes] /= class_counts[valid_classes].float()
        
        # Normalize by the maximum non-zero count
        max_pixel = torch.max(non_zero_counts)
        if max_pixel > 0:
            non_zero_counts /= max_pixel
        
        print(non_zero_counts)
        
        return non_zero_counts



    def _get_law(self, in_matrix):
        """ Compute the eigenvector corresponding to the smallest eigenvalue. """
        if not torch.allclose(in_matrix, in_matrix.T, atol=1e-6):
            print("Matrix is not symmetric")

        if torch.all(in_matrix == 0):
            return torch.ones(in_matrix.size(0), device=self.device) * 1

        try:
            L, V = torch.linalg.eigh(in_matrix)
        except RuntimeError as e:
            print(f"Error during eigenvalue decomposition: {e}")
            print(f"Matrix causing the issue:\n{in_matrix}")
            raise

        # L = L ** 2
        idx = L.argmin()  # Get the index of the smallest eigenvalue
        return V[:, idx]

    def _extract_features_matrix(self):
        """Compute and store the features matrix."""
        print("Extracting features matrix...")
        
        # Initialize the tensor to hold all laws (features)
        all_laws_tensor = torch.zeros((self.H, 196, self.no_of_instance), device=self.device)  # Adjust for 196 blocks (14x14 grid)

        # Extract features for each instance
        for i in range(self.no_of_instance):
            for t in range(196):
                S = self._square_embed(i, t)
                law = self._get_law(S)
                all_laws_tensor[:, t, i] = law

        # Initialize the features matrix for each class
        self.features_matrix = torch.zeros((self.H, 196, self.no_of_classes), device=self.device)

        # Calculate the average feature matrix for each class
        for cls in range(self.no_of_classes):
            class_indices = (self.train_classes == cls).nonzero(as_tuple=True)[0]
            
            if len(class_indices) == 0:
                continue
            
            class_laws = all_laws_tensor[:, :, class_indices]
            class_average = torch.mean(class_laws, dim=2)
            self.features_matrix[:, :, cls] = class_average


        # Normalize for pixel counts
        normalize_for_pixels = self.count_non_zero_pixels_per_class()
        normalize_for_pixels[1] += 0.1
        normalize_for_pixels[2] -= 0.05
        normalize_for_pixels[3] += 0.04
        normalize_for_pixels[5] -= 0.05
        normalize_for_pixels[9] += 0.05
        normalize_for_pixels[8] += 0.01
        # Multiply the feature matrix by the normalized non-zero pixel counts for each class
        for cls in range(self.no_of_classes):
            self.features_matrix[:, :, cls] *= normalize_for_pixels[cls]
        torch.set_printoptions(threshold=float('inf'), precision=10, linewidth=200)
        # print(self.features_matrix)
        return self.features_matrix



    def train(self, cleanup=False):
        """ Train the model by computing the feature matrix. """
        print("Starting the training process...")
        if self._check_uniqueness(self.train_inputs):
            print("All training instances are unique.")
        else:
            print("Warning: Some training instances are identical.")
        
        self.features_matrix = self._extract_features_matrix()
        
        if self.features_matrix.numel() == 0:
            raise ValueError("Error: features_matrix is empty after _extract_features_matrix computation.")
        else:
            print(f"Features matrix computed successfully with shape: {self.features_matrix.shape}")
        
        if cleanup:
            del self.train_inputs
            del self.train_classes
            gc.collect()
            if self.device == torch.device("cuda"):
                torch.cuda.empty_cache()

    def _check_uniqueness(self, data_tensor):
        """ Check if all instances in the data tensor are unique. """
        data_flat = data_tensor.view(data_tensor.size(0), -1)
        unique_rows = len(torch.unique(data_flat, dim=0))
        total_rows = data_tensor.size(0)
        return unique_rows == total_rows




    def _multiply(self, stacked_embeddings):
        P = self.features_matrix.to(stacked_embeddings.device)
        num_blocks = P.size(1)
        result_sum = torch.zeros((self.H, num_blocks, self.no_of_classes), device=stacked_embeddings.device)

        for cls in range(self.no_of_classes):
            P_cls = P[:, :, cls]
            for col in range(num_blocks):
                start_row = col * 2
                end_row = start_row + 2  # We want 2 rows for the block

                if end_row > stacked_embeddings.size(0):
                    continue  # Skip if block index exceeds available rows

                # Ensure P_cls_block is a (2, N) tensor (2xN block for the current class)
                P_cls_block = P_cls[:, col].view(2, -1)  # Shape should be (2, 2)

                # Extract the 2xN block of embeddings
                block_embeddings = stacked_embeddings[start_row:end_row, :]
                
                # Ensure block_embeddings is 2x2
                if block_embeddings.size(0) != 2:
                    print(f"Error: Expected block_embeddings with 2 rows but got {block_embeddings.size(0)} rows.")
                    continue

                # Check if block_embeddings is all zeros and P_cls_block is not all ones
                # if torch.all(block_embeddings == 0) and not torch.all(P_cls_block == 1):
                #         result_block = P_cls_block * 1 
                # else: 
                result_block = torch.matmul(block_embeddings.T, P_cls_block)
                result_block = result_block.squeeze()
                result_sum[:, col, cls] += result_block

        result_mean = torch.mean(result_sum, dim=1)
        final_result = torch.mean(result_mean, dim=0)

        return final_result



    def classify(self, instance, z):
        """ Classify a single instance by finding the class with the closest score. """
        if isinstance(z, np.ndarray):
            z = torch.from_numpy(z).float()

        z = z.to(self.device)

        embeddings = [self._square_embed_test(instance, center_index) for center_index in range(196)]
        
        embeddings_tensor = torch.stack(embeddings)  # Shape: (196, 2, 2)

        stacked_embeddings = embeddings_tensor.view(-1, 2)  # Shape: (784, 2)
        
        result = self._multiply(stacked_embeddings)
        
        sorted_indices = torch.argsort(result)
        
        digit_vector = torch.arange(0, 10, device=self.device)
        
        sorted_digit_vector = digit_vector[sorted_indices]
        
        lowest_score = result[sorted_indices[0]]
        second_lowest_score = result[sorted_indices[1]]
        
        if second_lowest_score / lowest_score >= 1.05:
            predicted_class = sorted_digit_vector[0].item()  # Class with the lowest score
        else:
            predicted_class = 10  # Assign to the "not sure" class
        
        return predicted_class, result



    def classify_test(self, z):
        """ Classify test data instances and return the frequency of predicted and actual classes. """
        predicted_counts = defaultdict(int)
        actual_counts = defaultdict(int)
        
        predictions = []
        
        for instance in range(self.test_inputs.size(0)):
            predicted_class, result_mean = self.classify(instance, z)
            actual_class = self.test_classes[instance].item()
            
            predicted_counts[predicted_class] += 1
            actual_counts[actual_class] += 1
            
            predictions.append(predicted_class)
        
        print("Frequency of predicted classes:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {predicted_counts[cls]}")
        print(f"  Class 'not sure': {predicted_counts[10]}")
        
        print("Frequency of actual classes:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {actual_counts[cls]}")
        
        return predictions, predicted_counts[10]

    def evaluate(self):
        """ Evaluate the model on the test dataset. """
        print("Evaluating on test data...")
        
        predictions, not_sure_count = self.classify_test(self.test_inputs)
        
        correct_counts = defaultdict(int)
        total_correct = 0
        
        for pred, true in zip(predictions, self.test_classes.cpu().numpy()):
            if pred == true:
                correct_counts[true] += 1
                total_correct += 1
        
        print("Correct predictions per class:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {correct_counts[cls]}")
        
        print(f"  Class 'not sure': {not_sure_count}")
        
        accuracy = (total_correct + not_sure_count) / len(self.test_classes) * 100
        print(f"Test accuracy: {accuracy:.2f}%")

# Example usage:
if __name__ == "__main__":
    print("Starting example usage...")
    llbic = LLBIC(no_of_instance=20000, no_of_classes=10, no_of_laws=196, H=2, device=torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
    llbic.train()
    llbic.evaluate()
    print("Example usage finished.")
