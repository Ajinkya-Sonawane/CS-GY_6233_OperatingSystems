#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PART_5_FILENAME "Part5/PART_5.csv"

void add_record_to_csv(char *record){
    FILE *fptr;
    fptr = fopen(PART_5_FILENAME,"a");
    fprintf(fptr,"%s",record);
    fclose(fptr);
}

void init_csv_file(){
    FILE *fptr;
    fptr = fopen(PART_5_FILENAME,"w");
    fprintf(fptr,"Block Size,Wall Time,Speed");
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

void lseek_file(char *FILENAME, int BLOCKSIZE){
    int fd = open(FILENAME, O_RDONLY);
    off_t end_position = lseek(fd, 0, SEEK_END);
    off_t old_position = lseek(fd, 0, SEEK_SET);
    // printf("\n%lld\n%lld\n",end_position,old_position);
    while(old_position < end_position) {
        old_position = lseek(fd, BLOCKSIZE, SEEK_CUR);
        // printf("\r%lld",old_position);
    }
}

int main(int argc, char *argv[]) {
    char *record;
    char *FILENAME;
    clock_t start,end;
    double wall_time;
    long total_bytes_read;
    FILENAME = argv[1];
    long BLOCK_SIZE = 1;

    //READ System Call
    start = clock();
    total_bytes_read = read_from_disk(FILENAME,BLOCK_SIZE);
    end = clock();
    wall_time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("\n\nREAD System Call:");
    printf("\nFile Size\t:\t%ld byte(s) \nBlock Size\t:\t%ld byte(s)\nWall Time\t:\t%f seconds\nSpeed\t\t:\t%f MiB/s | %f B/s\n\n",total_bytes_read,BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024),total_bytes_read/wall_time);

    // record = (char*)malloc(50 * sizeof(char));
    // sprintf(record, "%ld,%f,%f\n", BLOCK_SIZE, wall_time,total_bytes_read/(wall_time*1024*1024));

    //LSEEK System Call
    start = clock();
    lseek_file(FILENAME,BLOCK_SIZE);
    end = clock();
    wall_time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("\n\nLSEEK System Call:");
    printf("\nFile Size\t:\t%ld byte(s) \nBlock Size\t:\t%ld byte(s)\nWall Time\t:\t%f seconds\nSpeed\t\t:\t%f MiB/s | %f B/s\n\n",total_bytes_read,BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024),total_bytes_read/wall_time);
 
}