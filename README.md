# Portfolio

This portfolio is a collection of my programming projects. This README contains a brief description of each one. 

PROJECT ONE: Local Law-Based Image Classification (LLBIC) (done in Python): 

  This project aims to classify the MNIST dataset which contains images of digits ranging from 0 to 9. The images are represented as 28x28 pixel images with each pixel assigned a value between 0 and 1, 1 being the darkest and 0 being the lightest. The training set contains 50,000 instances, while the testing set contains 10,000. The code can be broken down into three sections: pre-processing, training, and classification.

  In the first section, pre-processing applies noise suppression, rotation, and centralization to the images. A filter of 0.2 is added to the images so that every pixel with a value of 0.2 or less is replaced with a value of 0. This is done to remove random disturbances in the image, such as random dots. Second, the images are centralized, this is done by calculating the center of mass of the image and placing this in the middle. Third the images are rotated to be as upright as possible. This is done by using a bounding box, and making this as thin and tall as possible. 
  The second section is training. This is where the algorithm learns to classifyi the testing images. 
  




