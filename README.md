# Portfolio

### This portfolio is a collection of my programming projects. This README contains a brief description of each one.

## PROJECT 1: Local Law-Based Image Classification (LLBIC) (Python):

This project aims to classify the MNIST dataset using a machine learning. The MNIST dataset contains images of digits ranging from 0 to 9, each digit is called a class. The images are represented as 28x28 pixel images with each pixel assigned a value between 0 and 1, 1 being the darkest and 0 being the lightest. The training set contains 50,000 instances, while the testing set 
contains 10,000. A relevant feature of the LLBIC is the ability to reflect on performance, primarily to detect anomalies. The code can be broken down into three sections: pre-processing, training, and classification. 

In the first section, pre-processing applies noise suppression, rotation, and centralization to the images. A filter of 0.2 is added to the images so that every pixel with a value of 0.2 or less is replaced with a value of 0. This is done to remove random disturbances in the images. Second, the images are centralized, this is done by calculating the center of mass of the image and placing this in the middle. Third the images are rotated between -35 to 35 degrees, to be as upright as possible. This is done by using a bounding box, and making the box as thin and tall as possible. 

The second section is training, this is where the algorithm learns to classify the testing images. The algorithm takes small sections of the image and embeds them into a square symmetric matrices. A law matrix for each instance is calculated by doing spectral decomposition for each of the embedded matrices. After all law matrices are calculated a variety of methods can be used to extract features. The goal is to find a feature for each digit. In this way the created feature tensor, has dimension n by m by 10, where 10 is the number of classes, n is the length of the embedded matrix and m is the number of embeddings. 

The third section of the code is classification. In this section the test set is embedded in the same way that the train instance is, however this time the embeddings are multiplied by the corresponding laws. If the embedded matrices are similar to the one the laws were derived from it should bring the product very close to zero, thereby signalling a similarity. The algorithm checks the product of the embedding with each feature matrix and picks the one that is on average closest to zero.

Further developments: Code for a complex gaussian system approach is in development.


## PROJECT 2: RISC-V CPU (System Verilog, RISC-V Assembly):

This project focused on designing and implementing a fully functional pipelined RISC-V CPU with cache in SystemVerilog. The goal was to create a processor capable of executing the RV32I instruction set while maintaining high performance and efficient hazard handling.

To improve throughput, I incorporated a five-stage pipeline—Fetch, Decode, Execute, Memory, and Write-Back—allowing the CPU to process multiple instructions simultaneously instead of sequentially. Clocked flip-flops were placed between each pipeline stage to synchronize signal flow and ensure proper timing, as shown below.


<img src="https://github.com/auersek/Portfolio/blob/main/Images/Screen%20Shot%202025-03-28%20at%206.12.54%20PM.jpg" width="850" height="550" alt="Pipeline 5 stages passed">

To address data and control hazards, I designed a dedicated hazard detection unit that performs stalling, flushing, and data forwarding when necessary. I also added support for JAL and JALR instructions by integrating jump and subroutine logic into the control path. For memory performance, I implemented a two-way set-associative cache with a write-through policy and LRU (Least Recently Used) replacement to handle cache misses efficiently.

The CPU was validated by running a wide range of RISC-V assembly programs to ensure full instruction-set functionality. As an extension, I wrote a Probability Distribution Function program, deployed it to an FPGA, and visualized the output on hardware, as shown below.

<img src="https://github.com/user-attachments/assets/64a0fcce-7148-4b86-b091-61f913ab8beb" width="50%">

## PROJECT 3: FPGA Video Game (Java, Verilog, FPGA, AWS):

This project involved designing an end to end motion controlled multiplayer game called Don’t Tilt, integrating FPGA sensor acquisition, real-time filtering, client server networking, and a Java-based game front end. The system captures tilt data from the DE10-Lite accelerometer, processes it through the Nios II soft-core processor, and streams it to a Java game, allowing players to control movement by physically tilting the FPGA board. A Python client manages local communication and relays data to a custom EC2 server, which distributes player states and maintains a persistent leaderboard via DynamoDB.

Accelerometer data was acquired via SPI, with an interrupt-driven design to minimize jitter and improve responsiveness. To suppress noise without sacrificing latency, raw samples were filtered using a 49-tap FIR filter, initially implemented in software and later migrated to a custom fixed-point hardware FIR module on the FPGA. This hardware filtering significantly reduced processing delay and allowed smooth real-time motion while maintaining stabilised sensor output. A clock-division module regulated the sampling rate to ~3.2 kHz to ensure consistent filtering and prevent overruns in the downstream pipeline.

For networking, the system uses a hybrid TCP + UDP architecture: TCP for reliable events such as combat setup and level completion, and UDP for high-frequency position updates. To further improve gameplay smoothness, each UDP packet included timestamps and velocity vectors, enabling out-of-order packet rejection and client-side motion prediction for remote player rendering. This reduced visual stutter when network latency introduced gaps between updates.

<img src="https://github.com/auersek/Portfolio/blob/main/Images/InfoprocArchitectureDiagram.jpg" width="750" height="550" alt="Communication architecture">

Multiplayer synchronization was managed through the EC2 game server, supporting parallel game sessions and maintaining fairness through level-completion gating, timeout handling, and scalable combat ID routing. A DynamoDB database stored user highscores, updated at the end of each game via TCP API calls. The final result was a fully integrated motion-based multiplayer game system running across FPGA hardware, Python middleware, cloud networking, and a Java client, optimized for responsiveness, real-time feedback, and low-latency user interaction.


## PROJECT 4: C Compiler (done in C++):

This project aims to build a C compiler which translates C90 code into RISC-V assembly instructions. 







