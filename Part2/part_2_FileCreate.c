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

void create_file_on_disk(char *FILENAME,long FILESIZE){    
    FILE *fp = fopen(FILENAME,"w");
    fseek(fp,FILESIZE,SEEK_SET);
    fputc('\0',fp);
    fclose(fp);
}

void read_from_disk(char *FILENAME,int BLOCK_SIZE){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    while ((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0) {
        continue;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    char * FILENAME = "PART2_FILE";
    int BLOCK_SIZE;

    BLOCK_SIZE = atoi(argv[1]);
    clock_t start,end;
    double wall_time;
    long FILESIZE = 10000;
    while(1){

        create_file_on_disk(FILENAME,FILESIZE);

        start = clock();
        read_from_disk(FILENAME,BLOCK_SIZE);
        end = clock();
        wall_time = (double)(end - start)/CLOCKS_PER_SEC;
        //printf("\nBlock Size : %d \tWall Time : %f\tSpeed : %f\t",BLOCK_SIZE,wall_time,FILESIZE/(wall_time*1024*1024));
        if(wall_time > 5){
            printf("\n\nMax Filesize : %ld bytes",FILESIZE);
            break;
        }
        else{
            //printf("\n\nNew Filesize : %ld bytes\t",FILESIZE);
            FILESIZE *= 2;
        }
    }
}