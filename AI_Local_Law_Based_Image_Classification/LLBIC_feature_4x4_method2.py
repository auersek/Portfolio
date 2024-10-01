"""Add an extra check on extract features that makes it so that it doesn't only check the new instance on the features of the same class
but also on other features from the other classes. If any of the other class features take the number lower than its own class laws then
you have to make a new feature of that instance since it isn't covered well in its own class. 
 """


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
        centralized_image = cv2.warpAffine(image, translation_matrix, (image.shape[1], image.shape[0]),
                                           borderMode=cv2.BORDER_CONSTANT, borderValue=0)

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
        rotated_image = cv2.warpAffine(image, rotation_matrix, (w, h), flags=cv2.INTER_CUBIC,
                                       borderMode=cv2.BORDER_CONSTANT, borderValue=0)
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
            rotated_image = self.rotate_image(centralized_image,
                                              angle)  # Rotate by the calculated angle to adjust the orientation

            # Optionally display images before and after rotation
            # self.show_images(image, rotated_image)

            standardized_images.append(rotated_image)
        return standardized_images

class LLBIC:
    def __init__(self, no_of_instance=200, no_of_classes=10, no_of_laws=49, H=16, device=torch.device('cpu')):
        print("Initializing LLBIC...")
        loader = Mnist_Loader()
        train_data, val_data, test_data = loader.load_data_wrapper()

        train_data = train_data[:no_of_instance]
        test_data = test_data[:1000]

        train_images, train_labels = zip(*train_data)
        test_images, test_labels = zip(*test_data)

        train_images_standardized = loader.standardize_images(np.array(train_images), np.array(train_labels))
        test_images_standardized = loader.standardize_images(np.array(test_images), np.array(test_labels))

        def convert_to_tensor(images, labels):
            print("Converting data to tensors...")
            inputs_tensor = torch.tensor(np.array(images).reshape(len(images), 784), dtype=torch.float32)
            classes_tensor = torch.tensor([np.argmax(label) for label in labels], dtype=torch.int64)
            return inputs_tensor, classes_tensor

        self.train_inputs, self.train_classes = convert_to_tensor(train_images, train_labels)
        self.test_inputs, self.test_classes = convert_to_tensor(test_images, test_labels)

        self.device = device
        self.train_inputs = self.train_inputs.to(self.device)
        self.train_classes = self.train_classes.to(self.device)
        self.test_inputs = self.test_inputs.to(self.device)
        self.test_classes = self.test_classes.to(self.device)

        self.no_of_classes = no_of_classes
        self.no_of_instance = no_of_instance
        self.no_of_laws = no_of_laws
        self.H = H

        # Initialize a list of lists to store feature matrices for each class
        self.features_matrix = {cls: [] for cls in range(no_of_classes)}

    def _square_embed(self, instance_index, block_index):
        block_row = block_index // 7
        block_col = block_index % 7

        two_by_two_vector = torch.zeros(4, device=self.device)

        start_row = block_row * 4
        start_col = block_col * 4

        for i in range(2):
            for j in range(2):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    vector_index = i * 2 + j
                    two_by_two_vector[vector_index] = self.train_inputs[instance_index, calculated_index]

        return two_by_two_vector

    def _square_embed_test(self, instance_index, block_index):
        block_row = block_index // 7
        block_col = block_index % 7

        two_by_two_vector = torch.zeros(4, device=self.device)

        start_row = block_row * 4
        start_col = block_col * 4

        for i in range(2):
            for j in range(2):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    vector_index = i * 2 + j
                    two_by_two_vector[vector_index] = self.test_inputs[instance_index, calculated_index]

        return two_by_two_vector

    def count_non_zero_pixels_per_pixel(self):
        non_zero_pixel_positions = torch.ones((self.no_of_classes, 49), dtype=torch.float32, device=self.device)
        class_counts = torch.zeros(self.no_of_classes, dtype=torch.int64, device=self.device)

        for i in range(self.no_of_instance):
            label = self.train_classes[i]
            class_counts[label] += 1

            for block_index in range(49):
                block_row = block_index // 7
                block_col = block_index % 7

                start_row = block_row * 4
                start_col = block_col * 4

                block_sum = 0
                for r in range(2):
                    for c in range(2):
                        row = start_row + r
                        col = start_col + c
                        if row < 28 and col < 28:
                            calculated_index = row * 28 + col
                            block_sum += (self.train_inputs[i, calculated_index] > 0).float()

                non_zero_pixel_positions[label, block_index] += block_sum

        valid_classes = class_counts > 0
        for c in range(self.no_of_classes):
            if valid_classes[c]:
                non_zero_pixel_positions[c][non_zero_pixel_positions[c] > 0] = \
                    1.0 / non_zero_pixel_positions[c][non_zero_pixel_positions[c] > 0]

        torch.set_printoptions(threshold=float('inf'), precision=10, linewidth=200)
        print(non_zero_pixel_positions)

        return non_zero_pixel_positions.T

    def count_non_zero_pixels_per_class(self):
        non_zero_counts = torch.zeros(self.no_of_classes, dtype=torch.float32, device=self.device)
        class_counts = torch.zeros(self.no_of_classes, dtype=torch.int64, device=self.device)

        for i in range(self.no_of_instance):
            label = self.train_classes[i]
            non_zero_pixels = torch.sum(self.train_inputs[i] > 0).item()
            non_zero_counts[label] += non_zero_pixels
            class_counts[label] += 1

        valid_classes = class_counts > 0
        non_zero_counts[valid_classes] /= class_counts[valid_classes].float()

        max_pixel = torch.max(non_zero_counts)
        if max_pixel > 0:
            non_zero_counts /= max_pixel

        print(non_zero_counts)

        return non_zero_counts

    def _get_law(self, instance_index, block_index):
        # Get the embedding for the given instance and block
        x = self._square_embed(instance_index, block_index)

        if torch.isnan(x).any():
            raise ValueError(f"Embedding x contains NaN values: {x}")

        # Generate a random tensor f and center it by subtracting its mean
        f = torch.randn(x.size(), device=self.device)
        f = f - f.mean()

        # Compute the dot product between f and x
        dot_product = torch.dot(f, x)

        # Compute the squared magnitude of x
        x_magnitude_squared = torch.norm(x).pow(2)

        if x_magnitude_squared == 0:
            # Set law to all ones if magnitude is zero
            law = torch.ones_like(x, device=self.device)
        else:
            # Calculate the projection of f onto x
            projection = dot_product / x_magnitude_squared
            # Compute the law
            law = f - (x * projection)

        # Check if any NaNs are produced
        if torch.isnan(law).any():
            raise ValueError(f"Computed law contains NaN values: {law}")
        return law
    

    def _update_feature_matrix(self, instance_index):
        """Update feature matrix for the class of a specific instance if needed."""
        instance_class = self.train_classes[instance_index].item()

        # Check if a feature matrix exists for the class; if not, create one immediately
        if not self.features_matrix[instance_class]:
            # Extract embeddings for the instance
            embeddings = [self._square_embed(instance_index, block_index) for block_index in range(49)]
            embeddings_tensor = torch.stack(embeddings)  # Shape: (49, 4)

            # Create and add the initial feature matrix for the class
            new_feature_matrix = torch.stack(
                [self._get_law(instance_index, block_index) for block_index in range(49)])
            self.features_matrix[instance_class].append(new_feature_matrix)
            print(f"Created initial feature matrix for class {instance_class}")
        
        # Extract embeddings for the instance again to ensure it's fresh
        embeddings = [self._square_embed(instance_index, block_index) for block_index in range(49)]
        embeddings_tensor = torch.stack(embeddings)  # Shape: (49, 4)

        # Calculate the result for the current instance against its own class
        current_result = self._multiply(embeddings_tensor, instance_class)
        current_min = current_result.min().item()  # Calculate the minimum for the current class

        feature_matrix_passed = False

        # Iterate through all classes to compare results
        for cls in range(self.no_of_classes):
            if cls == instance_class:  # Skip the current instance's class
                continue

            # Initialize a variable to track the minimum of the other class
            min_other_class = float('inf')

            # Multiply the embeddings with the feature matrices of the other classes
            for feature_matrix in self.features_matrix[cls]:
                result = self._multiply(embeddings_tensor, cls)
                min_result_other_class = result.min().item()  # Calculate the minimum for the other class
                min_other_class = min(min_other_class, min_result_other_class)  # Update to find the minimum

            # Check if the minimum of the other class is smaller than the current class minimum
            if min_other_class < current_min:
                feature_matrix_passed = True
                break

        # If no existing feature matrix passes and the current class minimum is above 0.1, create a new one
        if feature_matrix_passed:
            print(f"Instance {instance_index} not well covered in class {instance_class}, adding new feature.")
            new_feature_matrix = torch.stack(
                [self._get_law(instance_index, block_index) for block_index in range(49)])
            self.features_matrix[instance_class].append(new_feature_matrix)
        elif current_min >= 0.1:
            print(f"Instance {instance_index} well covered in class {instance_class}, but min is above 0.1.")


    def _extract_features_matrix(self):
        """Iterate over all training instances and update the feature matrices for each class."""
        # Initialize a tensor to store feature matrices (no_of_instance, 49, no_of_classes)
        feature_tensor = torch.zeros((self.no_of_instance, 49, self.no_of_classes), device=self.device)

        # Iterate over each training instance to update the feature matrix
        for instance_index in range(self.no_of_instance):
            self._update_feature_matrix(instance_index)

        print("Feature matrices extracted for all classes.")

        # Convert the dictionary of feature matrices into a tensor (if it’s not already a tensor)
        for cls in range(self.no_of_classes):
            if self.features_matrix[cls]:  # If feature matrix exists for the class
                stacked_matrices = torch.stack(self.features_matrix[cls])

                # Ensure the number of instances match
                num_instances_in_class = stacked_matrices.shape[0]
                # Reshape the stacked_matrices to fit into feature_tensor
                # Assuming feature_tensor expects a (no_of_instance, 49, no_of_classes) shape
                feature_tensor[:num_instances_in_class, :, cls] = stacked_matrices[:, :, 0]  # Choose appropriate dimension


        # Normalize based on the pixel counts per class
        normalize_for_class = self.count_non_zero_pixels_per_class()
        normalize_for_class[0] += 0.0
        normalize_for_class[1] -= 0.4
        # normalize_for_class[2] += 0.1
        normalize_for_class[3] += 0.5
        normalize_for_class[5] -= 0.01
        normalize_for_class[9] -= 0.01
        normalize_for_class[8] += 0.5

        # Normalize the feature tensor by non-zero pixel counts per class
        for cls in range(self.no_of_classes):
            # Normalize each class feature matrix by its corresponding non-zero pixel count
            if normalize_for_class[cls] > 0:
                feature_tensor[:, :, cls] *= normalize_for_class[cls]
            else:
                print(f"Warning: Class {cls} has zero non-zero pixels; skipping normalization for this class.")

        normalize_for_pixels = self.count_non_zero_pixels_per_pixel()

        # Apply per-block normalization
        for cls in range(self.no_of_classes):
            for block_index in range(49):
                feature_tensor[:, block_index, cls] *= normalize_for_pixels[block_index, cls]

        # Set print options for detailed output if needed
        torch.set_printoptions(threshold=float('inf'), precision=10, linewidth=200)
        
        print("Normalized feature matrix:")
        # print(feature_tensor)

        return feature_tensor

    def train(self):
        """Train the model by computing the feature matrix."""
        print("Starting the training process...")
        self._extract_features_matrix()
        print("Training complete.")

    def _check_uniqueness(self, data_tensor):
        """ Check if all instances in the data tensor are unique. """
        data_flat = data_tensor.view(data_tensor.size(0), -1)
        unique_rows = len(torch.unique(data_flat, dim=0))
        total_rows = data_tensor.size(0)
        return unique_rows == total_rows

    def _multiply(self, stacked_embeddings, class_index):
        feature_matrices = torch.stack(self.features_matrix[class_index]).to(stacked_embeddings.device)

        num_blocks = feature_matrices.size(1)  # Should be 49
        H = stacked_embeddings.shape[1]  # Number of features

        # Ensure the shape of stacked_embeddings is (49), H)
        if stacked_embeddings.shape[0] != num_blocks or stacked_embeddings.shape[1] != H:
            raise ValueError(f"Unexpected shape for stacked_embeddings: {stacked_embeddings.shape}")

        result_per_matrix = torch.zeros(len(self.features_matrix[class_index]), num_blocks,
                                        device=stacked_embeddings.device)

        for idx, P_cls in enumerate(feature_matrices):
            P_cls = P_cls.T
            # Ensure the shape of P_cls is (H, 49)
            if P_cls.shape[0] != H or P_cls.shape[1] != num_blocks:
                raise ValueError(f"Unexpected shape for P_cls: {P_cls.shape}")

            # Initialize result_row_vector
            result_row_vector = torch.zeros(num_blocks, device=stacked_embeddings.device)

            # Compute the element-wise multiplication and sum along the feature dimension
            for i in range(num_blocks):
                result_row_vector[i] = torch.sum(stacked_embeddings[i] * P_cls[:, i])

            # Ensure result_row_vector has shape (49,)
            if result_row_vector.shape[0] != num_blocks:
                raise ValueError(f"Unexpected shape for result_row_vector: {result_row_vector.shape}")

            result_per_matrix[idx] = result_row_vector

        average_result = torch.mean(result_per_matrix, dim=1)
        # print(average_result)
        return average_result

    def classify(self, instance, z):
        """Classify a single instance by finding the class with the closest score.
        Considers multiple feature matrices per class and uses the one that results in the best score.
        """
        if isinstance(z, np.ndarray):
            z = torch.from_numpy(z).float()

        z = z.to(self.device)

        # Extract 49 blocks of embeddings from the test instance
        embeddings = [self._square_embed_test(instance, center_index) for center_index in range(49)]
        embeddings_tensor = torch.stack(embeddings)  # Shape: (49, 16)

        # Initialize a list to store the results for each class
        class_results = []

        # Iterate through each class
        for class_index in range(self.no_of_classes):
            # For each class, get the score array from _multiply
            score_array = self._multiply(embeddings_tensor, class_index)

            # Compute the average score across all feature matrices for this class
            average_score = torch.mean(score_array).item()

            # Append the average score for the current class
            class_results.append(average_score)

        # Convert the results to a tensor
        result_tensor = torch.tensor(class_results, device=self.device)

        # Ensure result_tensor has the expected shape
        if result_tensor.shape[0] != self.no_of_classes:
            raise ValueError(f"Unexpected shape for result_tensor: {result_tensor.shape}")

        # Sort the results
        sorted_indices = torch.argsort(result_tensor)

        # Ensure that there are at least two classes to compare
        if self.no_of_classes < 2:
            raise ValueError("Number of classes must be at least 2 for comparison.")

        # Extract sorted digit vector and scores
        sorted_digit_vector = torch.arange(0, self.no_of_classes, device=self.device)[sorted_indices]
        lowest_score = result_tensor[sorted_indices[0]].item()
        second_lowest_score = result_tensor[sorted_indices[1]].item()

        # Check if the classification is confident enough
        # if second_lowest_score / lowest_score >= 1.02:
        predicted_class = sorted_digit_vector[0].item()  # Class with the lowest score
        # else:
        #     predicted_class = 10  # Assign to the "not sure" class

        return predicted_class, result_tensor

    def classify_test(self, z):
        """ Classify test data instances and return the frequency of predicted and actual classes. """
        predicted_counts = defaultdict(int)
        actual_counts = defaultdict(int)

        predictions = []

        for instance in range(self.test_inputs.size(0)):
            print(f"Classifying instance: {instance}")
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

        correct_counts = defaultdict(int)  # To track the number of correct predictions per class
        total_counts = defaultdict(int)  # To track the total occurrences of each class in the test set
        total_correct = 0

        # Count correct predictions and total occurrences of each class
        for pred, true in zip(predictions, self.test_classes.cpu().numpy()):
            total_counts[true] += 1  # Increment the count for the actual class

            if pred == true:  # If prediction is correct, increment correct count
                correct_counts[true] += 1
                total_correct += 1

        print("Correct predictions per class:")
        for cls in range(self.no_of_classes):
            correct = correct_counts[cls]
            total = total_counts[cls]
            percentage = (correct / total * 100) if total > 0 else 0.0
            print(f"  Class {cls}: {correct}/{total} correct ({percentage:.2f}%)")

        print(f"  Class 'not sure': {not_sure_count}")

        accuracy = (total_correct + not_sure_count) / len(self.test_classes) * 100
        print(f"Test accuracy: {accuracy:.2f}%")


if __name__ == "__main__":
    print("Starting example usage...")
    llbic = LLBIC(no_of_instance=200, no_of_classes=10, no_of_laws=49, H=4,
                  device=torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
    llbic.train()
    llbic.evaluate()
    print("Example usage finished.")
