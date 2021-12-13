#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>

void howto() {
    printf("\rusage: ./os_project <FILENAME> [-r|-w] <BLOCK_SIZE> <BLOCK_COUNT>");
}

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

void read_from_disk(char *FILENAME,int BLOCK_SIZE, int BLOCK_COUNT){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    unsigned int xor = 0;
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    int count =0;
    while (((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0) && (count < BLOCK_COUNT)) {
        read_size = ceil(bytes_read/sizeof(unsigned int));
        xor ^= xorbuf(buf, read_size);
        count++;
    }
    printf("xor: %08x\n", xor);
    close(fd);
}

void write_to_disk(char *FILENAME, int BLOCK_SIZE, int BLOCK_COUNT){

    int fd = open(FILENAME, O_WRONLY | O_CREAT, 777);
    char buf[BLOCK_SIZE];
    char value = 'a';

    for(int i=0; i<BLOCK_COUNT;i++)
    {
        write(fd, buf, BLOCK_SIZE);
    }
    printf("File of size : %ld bytes created\n", (long)BLOCK_COUNT*BLOCK_SIZE);
    close(fd);
}

int main(int argc, char *argv[]) {
    char *FILENAME;
    char mode;
    unsigned int BLOCK_SIZE;
    unsigned int BLOCK_COUNT;

    FILENAME = argv[1];

    if (argc != 5) {
        howto();
    }
    if (strlen((argv[2])) != 2) {
        howto();
    }
    else {
        mode = argv[2][1];
    }

    BLOCK_SIZE = atoi(argv[3]);
    BLOCK_COUNT = atoi(argv[4]);

    clock_t start=0,end=0;
    start = clock();
    if (mode == 'r' || mode == 'R') {
        read_from_disk(FILENAME,BLOCK_SIZE,BLOCK_COUNT);
    }
    else if (mode == 'w' || mode == 'R') {

        write_to_disk(FILENAME,BLOCK_SIZE,BLOCK_COUNT);
    }
    end=clock();
    double wall_time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("File Size\t: %u\nTime taken\t: %f\n",BLOCK_SIZE*BLOCK_COUNT, wall_time);
}


