import numpy as np
import torch
import pickle
import gzip
import gc
from collections import defaultdict
import cv2
from scipy.ndimage import center_of_mass
from sklearn.decomposition import PCA

class Mnist_Loader:
    def load_data(self):
        """Return the MNIST data as a tuple containing the training data, validation data, and test data."""
        print("Loading MNIST data...")
        with gzip.open('./data/mnist.pkl.gz', 'rb') as f:
            training_data, validation_data, test_data = pickle.load(f, encoding='latin1')
        print("MNIST data loaded.")
        return training_data, validation_data, test_data

    def load_data_wrapper(self):
        """Return a tuple containing (training_data, validation_data, test_data)."""
        print("Wrapping MNIST data...")
        tr_d, va_d, te_d = self.load_data()
        
        training_inputs = [np.reshape(x, (784, 1)) for x in tr_d[0]]
        training_results = [self.vectorized_result(y) for y in tr_d[1]]
        training_data = list(zip(training_inputs, training_results))
        validation_inputs = [np.reshape(x, (784, 1)) for x in va_d[0]]
        validation_data = list(zip(validation_inputs, va_d[1]))
        test_inputs = [np.reshape(x, (784, 1)) for x in te_d[0]]
        test_results = [self.vectorized_result(y) for y in te_d[1]]
        test_data = list(zip(test_inputs, test_results))
        print("MNIST data wrapped.")
        return training_data, validation_data, test_data

    def vectorized_result(self, j):
        """Return a 10-dimensional unit vector with a 1.0 in the jth position and zeroes elsewhere."""
        e = np.zeros((10, 1))
        e[j] = 1.0
        return e

class LLBIC:
    def __init__(self, no_of_instance=20000, no_of_classes=10, no_of_laws=196, H=2, device=torch.device('cpu')):
        print("Initializing LLBIC...")
        loader = Mnist_Loader()
        train_data, val_data, test_data = loader.load_data_wrapper()

        # Limit the dataset size as needed
        train_data = train_data[:no_of_instance]
        test_data = test_data[:10000]

        def convert_to_tensor(data):
            print("Converting data to tensors...")
            if not data or not all(isinstance(d, tuple) and len(d) == 2 for d in data):
                raise ValueError("Data must be an iterable of (input, label) tuples.")
            inputs = np.array([x for x, y in data])
            classes = np.array([np.argmax(y) for x, y in data])
            inputs_tensor = torch.tensor(inputs, dtype=torch.float32)
            classes_tensor = torch.tensor(classes, dtype=torch.int64)
            print(f"Inputs tensor shape: {inputs_tensor.shape}")
            print(f"Classes tensor shape: {classes_tensor.shape}")
            return inputs_tensor, classes_tensor

        try:
            self.train_inputs, self.train_classes = convert_to_tensor(train_data)
            self.test_inputs, self.test_classes = convert_to_tensor(test_data)
        except ValueError as e:
            print(f"Error converting data to tensors: {e}")
            raise

        # Apply the thresholding operation to the train and test inputs
        self.train_inputs[self.train_inputs < 0.2] = 0
        self.test_inputs[self.test_inputs < 0.2] = 0
        print("0.2 filter applied")

        self.device = device
        self.train_inputs = self.train_inputs.to(self.device)
        self.train_classes = self.train_classes.to(self.device)
        self.test_inputs = self.test_inputs.to(self.device)
        self.test_classes = self.test_classes.to(self.device)

        self.no_of_classes = no_of_classes
        self.no_of_instance = no_of_instance
        self.no_of_laws = no_of_laws
        self.H = H
        self.features_matrix = torch.zeros((self.H, 196, self.no_of_classes), device=self.device)  # 14x14 grid for 2x2 boxes

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
        
        # Normalize the symmetric matrix
        # symmetric_matrix = self.normalize_matrix(symmetric_matrix)
        
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
        
        # Normalize the symmetric matrix
        # symmetric_matrix = self.normalize_matrix(symmetric_matrix)
        
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

        # Multiply the feature matrix by the normalized non-zero pixel counts for each class
        for cls in range(self.no_of_classes):
            # Only multiply elements that are not equal to 1
            mask = self.features_matrix[:, :, cls] != 1
            self.features_matrix[:, :, cls][mask] *= normalize_for_pixels[cls]
        # torch.set_printoptions(threshold=float('inf'), precision=10, linewidth=200)
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
                if torch.all(block_embeddings == 0) and not torch.all(P_cls_block == 1):
                    result_block = 1 / P_cls_block  # Add (1 / P_cls_block) to result instead of P_cls_block
                else: 
                    # Perform matrix multiplication
                    result_block = torch.matmul(block_embeddings.T, P_cls_block)

                    # Reduce the dimension if needed (squeeze if it's 2D)
                    result_block = result_block.squeeze()

                    result_sum[:, col, cls] += result_block

        # Average results across blocks and classes
        result_mean = torch.mean(result_sum, dim=1)
        final_result = torch.mean(result_mean, dim=0)

        return final_result



    def classify(self, instance, z):
        """ Classify a single instance by finding the class with the closest score. """
        if isinstance(z, np.ndarray):
            z = torch.from_numpy(z).float()

        z = z.to(self.device)

        # Extract 196 embeddings, each of size 2x2
        embeddings = [self._square_embed_test(instance, center_index) for center_index in range(196)]
        
        # Convert the list of 2x2 tensors to a tensor of shape (196, 2, 2)
        embeddings_tensor = torch.stack(embeddings)  # Shape: (196, 2, 2)

        # Reshape to get a tensor of shape (784, 2) by concatenating the 2x2 blocks
        stacked_embeddings = embeddings_tensor.view(-1, 2)  # Shape: (784, 2)
        
        # Call _multiply with the reshaped tensor
        result = self._multiply(stacked_embeddings)
        
        # Sort the result to get class indices
        sorted_indices = torch.argsort(result)
        
        # Create a vector of digits 0-9
        digit_vector = torch.arange(0, 10, device=self.device)
        
        # Sort the digit vector according to the sorted indices
        sorted_digit_vector = digit_vector[sorted_indices]
        
        # Get the lowest and second-lowest scores
        lowest_score = result[sorted_indices[0]]
        second_lowest_score = result[sorted_indices[1]]
        
        # Check if the ratio between the lowest and second-lowest score is less than 1.2
        if second_lowest_score / lowest_score >= 1.02:
            predicted_class = sorted_digit_vector[0].item()  # Class with the lowest score
        else:
            predicted_class = 10  # Assign to the "not sure" class
        
        # Modify the prediction if it predicts class 8
        # if predicted_class == 8:
        #     predicted_class = sorted_digit_vector[1].item()  # Use the second-lowest value instead
        
        return predicted_class, result



    def classify_test(self, z):
        """ Classify test data instances and return the frequency of predicted and actual classes. """
        predicted_counts = defaultdict(int)
        actual_counts = defaultdict(int)
        
        predictions = []
        
        for instance in range(self.test_inputs.size(0)):
            predicted_class, result_mean = self.classify(instance, z)
            actual_class = self.test_classes[instance].item()
            
            # Update frequency counts
            predicted_counts[predicted_class] += 1
            actual_counts[actual_class] += 1
            
            # Append the predicted class        print
            predictions.append(predicted_class)
        
        # Print the frequencies
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
        
        # Get predictions and counts from classify_test
        predictions, not_sure_count = self.classify_test(self.test_inputs)
        
        # Initialize correct counts per class
        correct_counts = defaultdict(int)
        total_correct = 0
        
        # Iterate over predictions and actual classes
        for pred, true in zip(predictions, self.test_classes.cpu().numpy()):
            if pred == true:
                correct_counts[true] += 1
                total_correct += 1
        
        # Print out the number of correct predictions per class
        print("Correct predictions per class:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {correct_counts[cls]}")
        
        print(f"  Class 'not sure': {not_sure_count}")
        
        # Calculate and print the overall accuracy
        accuracy = (total_correct + not_sure_count) / len(self.test_classes) * 100
        print(f"Test accuracy: {accuracy:.2f}%")

# Example usage:
if __name__ == "__main__":
    print("Starting example usage...")
    llbic = LLBIC(no_of_instance=20000, no_of_classes=10, no_of_laws=196, H=2, device=torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
    llbic.train()
    llbic.evaluate()
    print("Example usage finished.")
