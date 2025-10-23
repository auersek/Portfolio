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
    def __init__(self, no_of_instance=1000, no_of_classes=10, no_of_laws=4, H=14, device=torch.device('cpu')):
        print("Initializing LLBIC...")
        loader = Mnist_Loader()
        train_data, val_data, test_data = loader.load_data_wrapper()

        # Limit the dataset size as needed
        train_data = train_data[:no_of_instance]
        test_data = test_data[:2000]

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
            print("HELLO")
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
        self.no_of_laws = no_of_laws
        self.H = H
        self.features_matrix = torch.zeros((self.H, 4, self.no_of_classes), device=self.device)

    def _fourteen_by_fourteen_embed(self, instance_index, block_index):
        """ Extract a 14x14 block from the image and compute its symmetric matrix. """
        block_row = block_index // 2
        block_col = block_index % 2

        fourteen_by_fourteen_box = torch.zeros((14, 14), device=self.device)

        start_row = block_row * 14
        start_col = block_col * 14

        for i in range(14):
            for j in range(14):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    fourteen_by_fourteen_box[i, j] = self.train_inputs[instance_index, calculated_index]

        symmetric_matrix = torch.matmul(fourteen_by_fourteen_box, fourteen_by_fourteen_box.T)
        return symmetric_matrix

    def _fourteen_by_fourteen_embed_test(self, instance_index, block_index):
        """ Extract a 14x14 block from the image (test data) and compute its symmetric matrix. """
        block_row = block_index // 2
        block_col = block_index % 2

        fourteen_by_fourteen_box = torch.zeros((14, 14), device=self.device)

        start_row = block_row * 14
        start_col = block_col * 14

        for i in range(14):
            for j in range(14):
                row = start_row + i
                col = start_col + j
                if row < 28 and col < 28:
                    calculated_index = row * 28 + col
                    fourteen_by_fourteen_box[i, j] = self.test_inputs[instance_index, calculated_index]

        symmetric_matrix = torch.matmul(fourteen_by_fourteen_box, fourteen_by_fourteen_box.T)
        return symmetric_matrix

    def _extract_features_matrix(self):
        """ Compute and store the features matrix. """
        print("Extracting features matrix...")
        
        all_laws_tensor = torch.zeros((self.H, 4, self.no_of_instance), device=self.device)

        for i in range(self.no_of_instance):
            for t in range(4):
                S = self._fourteen_by_fourteen_embed(i, t)
                law = self._get_law(S)
                all_laws_tensor[:, t, i] = law

        self.features_matrix = torch.zeros((self.H, 4, self.no_of_classes), device=self.device)

        for cls in range(self.no_of_classes):
            class_indices = (self.train_classes == cls).nonzero(as_tuple=True)[0]
            
            if len(class_indices) == 0:
                continue
            
            class_laws = all_laws_tensor[:, :, class_indices]
            class_average = torch.mean(class_laws, dim=2)
            self.features_matrix[:, :, cls] = class_average

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


    def _get_law(self, in_matrix):
        """ Compute the eigenvector corresponding to the smallest eigenvalue. """
        if not torch.allclose(in_matrix, in_matrix.T, atol=1e-6):
            print("Matrix is not symmetric")

        if torch.all(in_matrix == 0):
            return torch.ones(in_matrix.size(0), device=self.device)  * 10

        try:
            L, V = torch.linalg.eigh(in_matrix)
        except RuntimeError as e:
            print(f"Error during eigenvalue decomposition: {e}")
            print(f"Matrix causing the issue:\n{in_matrix}")
            raise

        L = L ** 2
        idx = L.argmin()  # Get the index of the smallest eigenvalue
        return V[:, idx]

    def _multiply(self, stacked_embeddings):
        """ Multiply the embedded matrix with the feature matrices and return a 1x10 tensor. """
        P = self.features_matrix.to(stacked_embeddings.device)
        num_blocks = P.size(1)
        result_sum = torch.zeros((self.H, num_blocks, self.no_of_classes), device=stacked_embeddings.device)

        for cls in range(self.no_of_classes):
            P_cls = P[:, :, cls]
            for col in range(num_blocks):
                start_row = col * 4
                end_row = (col + 1) * 14
                end_row = min(end_row, stacked_embeddings.size(0))

                if start_row >= end_row:
                    continue  # Skip if the block index is out of range

                P_cls_block = P_cls[:, col].view(-1, 1)
                
                if end_row - start_row != P_cls_block.size(0):
                    print(f"Warning: Mismatch in dimensions for block column {col}. Expected rows: {P_cls_block.size(0)}, Found rows: {end_row - start_row}")

                result_block = torch.matmul(stacked_embeddings[start_row:end_row, :], P_cls_block)
                result_sum[:, col, cls] += result_block.squeeze()

        result_mean = torch.mean(result_sum, dim=1)
        final_result = torch.mean(result_mean, dim=0)

        return final_result

    def classify(self, instance, z):
        """ Classify a single instance by finding the class with the closest score. """
        if isinstance(z, np.ndarray):
            z = torch.from_numpy(z).float()

        z = z.to(self.device)
        embeddings = [self._fourteen_by_fourteen_embed_test(instance, center_index) for center_index in range(4)]
        stacked_embeddings = torch.stack(embeddings).view(-1, 14)
        
        result = self._multiply(stacked_embeddings)
        predicted_class = torch.argmin(result).item()
        
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
            
            # Append the predicted class
            predictions.append(predicted_class)
        
        # Print the frequencies
        print("Frequency of predicted classes:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {predicted_counts[cls]}")
        
        print("Frequency of actual classes:")
        for cls in range(self.no_of_classes):
            print(f"  Class {cls}: {actual_counts[cls]}")
        
        return predictions

    def evaluate(self):
        """ Evaluate the model on the test dataset. """
        print("Evaluating on test data...")
        predictions = self.classify_test(self.test_inputs)
        correct = sum(1 for pred, true in zip(predictions, self.test_classes.cpu().numpy()) if pred == true)
        accuracy = correct / len(self.test_classes) * 100
        print(f"Test accuracy: {accuracy:.2f}%")

# Example usage:
if __name__ == "__main__":
    print("Starting example usage...")
    llbic = LLBIC(no_of_instance=500, no_of_classes=10, no_of_laws=4, H=14, device=torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
    llbic.train()
    llbic.evaluate()
    print("Example usage finished.")
