# CS-GY_6233_OperatingSystems
[CS-GY 6233 Operating Systems Final Project](https://kyall.notion.site/kyall/CS-GY-6233-Final-Project-f47fb948159e425da6a22ddfd318bb17)

## Members: 
1. [Ajinkya Sonawane](https://github.com/Ajinkya-Sonawane)
1. [Roshni Sen](https://github.com/rs7633)

## How to run
To compile all 6 parts and the fast.c file Run : `sh build.sh`

### Part 1 
- Program that can read and write a file from disk using the standard C/C++ library's open, read, write, and close functions.

#### How to execute : `./run FILE_NAME [-r | -w] BLOCK_SIZE BLOCK_COUNT`

![image](https://user-images.githubusercontent.com/21151348/145730580-153243f0-2827-4283-bd87-0e90520eb718.png)

### Part 2 
- Program to find a file size which can be read in "reasonable" time.

#### How to execute: `./run2 FILE_NAME BLOCK_SIZE`

![image](https://user-images.githubusercontent.com/21151348/145730623-52aca15b-539a-43af-a500-36939e50fd96.png)


### Part 3 
- Compare different block sizes and output the performance it achieved in MiB/s.

#### How to execute: `./run3 FILE_NAME`

![image](https://user-images.githubusercontent.com/21151348/145730646-f40fc4ce-148b-46fb-92ee-064f12e603db.png)
![image](https://github.com/Ajinkya-Sonawane/CS-GY_6233_OperatingSystems/blob/main/Part3/part_3.png)

### Part 4 
- Compare program with cached and non-cached data

#### How to execute: `./run4 FILE_NAME BLOCK_SIZE`

![image](https://github.com/Ajinkya-Sonawane/CS-GY_6233_OperatingSystems/blob/main/Part4/part_4.png)

### Part 5 
- Compare System calls for Block Size of 1 Byte, which will give number of system calls per second

#### How to execute: `./run5 FILE_NAME`

[READ vs LSEEK comparison](https://vast-baseball-750.notion.site/5178bbed585c4fb88bceffbd9f664c27?v=f527ddc7e8ab40a0ac918daba37c8551)
![image](https://github.com/Ajinkya-Sonawane/CS-GY_6233_OperatingSystems/blob/main/Part5/part_5.png)

### Part 6 
- Compare program performance with different block sizes and threads

#### How to execute: `./run6 FILE_NAME`

![image](https://user-images.githubusercontent.com/21151348/145730721-3b938077-7dbe-4ea8-a920-15565f09dea6.png)
(Partial O/P)

![part_6_diff_bnt](https://user-images.githubusercontent.com/21151348/145907288-66f8e65f-5636-413b-b850-89b49df86439.png)

<b>X-axis:</b> Number of Threads | <b>Y-axis:</b> Wall Time (seconds) | <b>Lines :</b> Block Size

### fast.c 
- Program to read in the fastest possible way using analysis from previous parts

#### How to execute : `./fast FILE_NAME`

![image](https://user-images.githubusercontent.com/21151348/145878999-89ac3349-6025-4bc4-bfe9-6589a94092ad.png)

