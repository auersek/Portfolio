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
