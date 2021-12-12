#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <math.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned long read_from_disk(char *FILENAME,int BLOCK_SIZE, long BLOCK_COUNT){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    int count = 0;
    unsigned long total_bytes_read = 0;
    while ((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0) {
        total_bytes_read += bytes_read;
        count++;
        if (count > BLOCK_COUNT){
            break;
        }
    }
    close(fd);
    return total_bytes_read;
}

int main(int argc, char *argv[]) {
    char * FILENAME;
    int BLOCK_SIZE;

    FILENAME = argv[1];
    BLOCK_SIZE = atoi(argv[2]);
    clock_t start,end;
    double wall_time;
    unsigned long FILESIZE = 0, PREV_FILE_SIZE = 0;
    long BLOCK_COUNT = 1;
    while(1){
        start = clock();
        FILESIZE = read_from_disk(FILENAME,BLOCK_SIZE,BLOCK_COUNT);
        end = clock();
        wall_time = (double)(end - start)/CLOCKS_PER_SEC;
        //printf("\nBlock Size : %d bytes \tWall Time : %f seconds \tSpeed : %f MiB/s\t\n",BLOCK_SIZE,wall_time,FILESIZE/(wall_time*1024*1024));
        if(wall_time > 5){
            printf("\n\nMax Filesize : %ld bytes\t| Final Block Count : %ld\n",FILESIZE,BLOCK_COUNT);
            break;
        }
        else if (PREV_FILE_SIZE == FILESIZE){
            printf("\n\nFile Read completely within 5 seconds!!! \nFilesize : %ld bytes\tFinal Block Count : %ld\n",FILESIZE,BLOCK_COUNT);
            break;
        }
        else{
            PREV_FILE_SIZE = FILESIZE;
            //printf("\n\nNew Filesize : %ld bytes\t| Block Count : %ld\n",BLOCK_SIZE*BLOCK_COUNT,BLOCK_COUNT);
            BLOCK_COUNT *= 2;
        }
    }
}