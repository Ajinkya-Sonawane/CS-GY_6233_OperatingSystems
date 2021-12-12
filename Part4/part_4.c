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

#define PART_4_FILENAME  "PART_4.csv"

void add_record_to_csv(char *record){
    FILE *fptr;
    fptr = fopen(PART_4_FILENAME,"a");
    fprintf(fptr,"%s",record);
    fclose(fptr);
}

long read_from_disk(char *FILENAME,int BLOCK_SIZE){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    long total_bytes_read;
    while ((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0) {
        total_bytes_read += bytes_read;
        continue;
    }
    close(fd);
    return total_bytes_read;
}

int main(int argc, char *argv[]) {
    char *record;
    char *FILENAME;
    clock_t start,end;
    double wall_time;
    long total_bytes_read;
    FILENAME = argv[1];
    long BLOCK_SIZE = atoi(argv[2]);
    start = clock();
    total_bytes_read = read_from_disk(FILENAME,BLOCK_SIZE);
    end = clock();
    wall_time = (double)(end - start)/CLOCKS_PER_SEC;

    record = (char*)malloc(50 * sizeof(char));
    sprintf(record, "%ld,%f,%f\n", BLOCK_SIZE, wall_time,total_bytes_read/(wall_time*1024*1024));

    printf("\n\nFile Size\t:\t%ld bytes \nBlock Size\t:\t%ld bytes\nWall Time\t:\t%f seconds\nSpeed\t\t:\t%f MiB/s\n\n",total_bytes_read,BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024));
}