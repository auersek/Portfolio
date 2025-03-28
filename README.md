# Portfolio

### This portfolio is a collection of my programming projects. This README contains a brief description of each one.

## PROJECT 1: Local Law-Based Image Classification (LLBIC) (done in Python):

This project aims to classify the MNIST dataset using a machine learning. The MNIST dataset contains images of digits ranging from 0 to 9, each digit is called a class. The images are represented as 28x28 pixel images with each pixel assigned a value between 0 and 1, 1 being the darkest and 0 being the lightest. The training set contains 50,000 instances, while the testing set 
contains 10,000. A relevant feature of the LLBIC is the ability to reflect on performance, primarily to detect anomalies. The code can be broken down into three sections: pre-processing, training, and classification. 

In the first section, pre-processing applies noise suppression, rotation, and centralization to the images. A filter of 0.2 is added to the images so that every pixel with a value of 0.2 or less is replaced with a value of 0. This is done to remove random disturbances in the images. Second, the images are centralized, this is done by calculating the center of mass of the image and placing this in the middle. Third the images are rotated between -35 to 35 degrees, to be as upright as possible. This is done by using a bounding box, and making the box as thin and tall as possible. 

The second section is training, this is where the algorithm learns to classify the testing images. The algorithm takes small sections of the image and embeds them into a square symmetric matrices. A law matrix for each instance is calculated by doing spectral decomposition for each of the embedded matrices. After all law matrices are calculated a variety of methods can be used to extract features. The goal is to find a feature for each digit. In this way the created feature tensor, has dimension n by m by 10, where 10 is the number of classes, n is the length of the embedded matrix and m is the number of embeddings. 

The third section of the code is classification. In this section the test set is embedded in the same way that the train instance is, however this time the embeddings are multiplied by the corresponding laws. If the embedded matrices are similar to the one the laws were derived from it should bring the product very close to zero, thereby signalling a similarity. The algorithm checks the product of the embedding with each feature matrix and picks the one that is on average closest to zero.

Further developments: Code for a complex gaussian system approach is in development.


## PROJECT 2: RISC-V CPU (done in System Verilog):

This project aims to build a functioning pipelined RISC-V CPU with cache in system verilog. 

I used pipelining to improve the performance of the CPU by increasing the number of instructions executed per unit of time. It allows the CPU to work on multiple instructions simultaneously, rather than completing one instruction before starting the next. In this RISC-V project, five stages are used: fetch, decode, execute, memory, and write-back. Four clocked flip-flops, one between each of these stages, are implemented to delay the signals, as shown below.

<img src="https://github.com/auersek/Portfolio/blob/main/Images/Screen%20Shot%202025-03-28%20at%206.12.54%20PM.jpg" width="850" height="550" alt="Pipeline 5 stages passed">


## PROJECT 3: C Compiler (done in C++):

This project aims to build a C compiler which translates C code into RISC-V assembly instructions. 







