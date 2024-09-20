"""
I am working with the MNIST database where each image represents a digit and is 28by28 pixels, it also has the corresponding class for each of the instances in the second dimension, which is 1by10 matrix where the corresponding class has the highest value and the others 0. A law vector for each instance should be calculated, creating a 28by1 matrix of laws. For each training instance after it is calculated it should be added to the tensor of laws, which would have dimensions 28*1*n where n is the number of instances. After all of the training instance law matrices are calculated, the law tensor should be partitioned so that each digit 0-9 have its own corresponding matrices grouped together. This is then averaged to create the features matrix, which should be a 28by1by10 tensor, where 28 is the length of the eigenvector, 1 is the number of laws, and  10 is the number of classes (digits 0-9). This feature matrix is to be used for classification. To classify each test instance multiply the matrix with each the feature matrices. Average the product into a single number and save this. The scale closest to zero on average should be the class that the test instance belongs to. Change the rest of the code so that it follows this method and the logic i just described:
"""

import numpy as np
import torch
import pickle
import gzip
import gc
from collections import defaultdict


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
    def __init__(self, no_of_instance=2000, no_of_classes=10, device=torch.device('cpu')):
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

        self.device = device
        self.train_inputs = self.train_inputs.to(self.device)
        self.train_classes = self.train_classes.to(self.device)
        self.test_inputs = self.test_inputs.to(self.device)
        self.test_classes = self.test_classes.to(self.device)

        self.no_of_classes = no_of_classes
        self.no_of_instance = no_of_instance
        self.features_matrix = torch.zeros((28, 1, self.no_of_classes), device=self.device)  # 28x1x10 tensor for features


    def _get_law(self, in_matrix):
        """Compute the law vector for a given instance, which is the eigenvector corresponding to the smallest non-zero eigenvalue."""
        # Ensure in_matrix is a 2D tensor
        if in_matrix.ndim != 2:
            raise ValueError("Input matrix must be 2D.")

        # Make the matrix symmetric
        sym_matrix = torch.matmul(in_matrix.T, in_matrix)

        try:
            # Perform eigenvalue decomposition
            L, V = torch.linalg.eigh(sym_matrix)
        except RuntimeError as e:
            print(f"Error during eigenvalue decomposition: {e}")
            print(f"Matrix causing the issue:\n{sym_matrix}")
            raise

        # print("Eigenvalues:", L)
        # print("Eigenvectors:", V)
        
        # Check for zero or very close to zero eigenvalues
        tolerance = 1e-10  # Define a small tolerance value
        non_zero_indices = L > tolerance

        if not non_zero_indices.any():
            raise ValueError("All eigenvalues are zero or very close to zero.")

        # Find the index of the smallest non-zero eigenvalue
        min_eigenvalue_idx = L[non_zero_indices].argmin()
        
        # Adjust index to get the original position in L
        min_eigenvalue_idx = non_zero_indices.nonzero(as_tuple=True)[0][min_eigenvalue_idx]
        
        law_vector = V[:, min_eigenvalue_idx]

        # Ensure law_vector is reshaped correctly for further processing
        return law_vector.view(in_matrix.size(0), 1)




    def train(self, cleanup=False):
        """Train the model by computing the feature matrix."""
        print("Starting the training process...")

        # Initialize law_tensor with dimensions (28, 1, no_of_instance)
        law_tensor = torch.zeros((28, 1, self.no_of_instance), device=self.device)

        for i in range(self.no_of_instance):
            # Reshape the instance to 28x28
            instance = self.train_inputs[i].view(28, 28)

            # Calculate the law vector for this instance
            law_vector = self._get_law(instance)

            # Add the law vector to the law_tensor
            # law_tensor.shape: (28, 1, no_of_instance), law_vector.shape: (28, 1)
            law_tensor[:, :, i] = law_vector

        # Compute the feature matrix
        self.features_matrix = torch.zeros((28, 1, self.no_of_classes), device=self.device)

        for cls in range(self.no_of_classes):
            # Get indices of instances belonging to the current class
            class_indices = (self.train_classes == cls).nonzero(as_tuple=True)[0]

            if len(class_indices) == 0:
                continue

            # Select the law vectors for the current class
            class_laws = law_tensor[:, :, class_indices]

            # Compute the average of the law vectors for this class
            self.features_matrix[:, :, cls] = torch.mean(class_laws, dim=2)

        # print(self.features_matrix)
        # print(f"Features matrix shape: {self.features_matrix.shape}")

        if cleanup:
            del self.train_inputs
            del self.train_classes
            gc.collect()
            if self.device == torch.device("cuda"):
                torch.cuda.empty_cache()



    def _multiply(self, instance):
        """Multiply the instance matrix with the features matrix for each class."""
        # Ensure the instance is on the same device as the features_matrix
        instance = instance.to(self.features_matrix.device)
        
        # Make sure the instance is a 28x28 matrix and symmetrize it
        instance = instance.view(28, 28)
        # torch.set_printoptions(precision=6, threshold=float('inf'))
        # print(instance)
        # Compute the symmetric matrix
        sym_instance = torch.matmul(instance.T, instance)  # Shape: (28, 28)
        
        # Initialize an empty tensor to hold the results for each class
        results = torch.zeros(self.no_of_classes, device=self.device)
        
        # Iterate over each class
        for cls in range(self.no_of_classes):
            P_cls = self.features_matrix[:, :, cls]
            # Perform matrix multiplication between the expanded symmetric instance and the class-specific feature matrix
            product = torch.matmul(sym_instance, P_cls) # Shape: (28,1)
            
            # Compute the mean across the 28 rows (dimension 0) to reduce the result to shape (1,)
            result_mean = torch.mean(product)  # Shape: (1,)
            
            # Assign the result to the appropriate index in the results tensor
            results[cls] = result_mean
        # print(results)
        
        return results

    def classify(self, instance):
        """ Classify a single instance by finding the class with the closest score. """
        if isinstance(instance, np.ndarray):
            instance = torch.from_numpy(instance).float()

        instance = instance.to(self.device)
        
        # Call _multiply with the reshaped tensor
        result = self._multiply(instance)
        
        # Get the class with the lowest score
        predicted_class = torch.argmin(result).item()
        
        # Check if the lowest score is significantly lower than the second-lowest score
        sorted_scores, sorted_indices = torch.sort(result)
        if len(sorted_scores) > 1 and sorted_scores[1] / sorted_scores[0] >= 2:
            predicted_class = 10  # Assign to the "not sure" class
        
        return predicted_class

    def classify_test(self):
        """ Classify test data instances and return the frequency of predicted and actual classes. """
        predicted_counts = defaultdict(int)
        actual_counts = defaultdict(int)
        
        predictions = []
        
        for instance in range(self.test_inputs.size(0)):
            predicted_class = self.classify(self.test_inputs[instance])
            actual_class = self.test_classes[instance].item()
            
            # Update frequency counts
            predicted_counts[predicted_class] += 1
            actual_counts[actual_class] += 1
            
            # Append the predicted class
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
        predictions, not_sure_count = self.classify_test()
        
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
    llbic = LLBIC(no_of_instance=2000, no_of_classes=10, device=torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
    llbic.train()
    llbic.evaluate()
