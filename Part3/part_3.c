#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <math.h>
#include<time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PART_3_FILENAME  "PART_3.csv"
#define MAX_BLOCK_SIZE 550000

void add_record_to_csv(char *record){
    FILE *fptr;
    fptr = fopen(PART_3_FILENAME,"a");
    fprintf(fptr,"%s",record);
    fclose(fptr);
}

void init_csv_file(){
    FILE *fptr;
    fptr = fopen(PART_3_FILENAME,"w");
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

int main(int argc, char *argv[]) {
    char * FILENAME;
    char *record;
    clock_t start,end;
    double wall_time;
    long total_bytes_read;
    FILENAME = argv[1];
    init_csv_file();
    for(long BLOCK_SIZE=1024;BLOCK_SIZE < MAX_BLOCK_SIZE; BLOCK_SIZE*=2){
        start = clock();
        total_bytes_read =  read_from_disk(FILENAME,BLOCK_SIZE);
        end = clock();
        wall_time = (double)(end - start)/CLOCKS_PER_SEC;


        record = (char*)malloc(50 * sizeof(char));
        sprintf(record, "\n%ld,%f,%f", BLOCK_SIZE, wall_time,total_bytes_read/(wall_time*1024*1024));

        add_record_to_csv(record);
        printf("\nBlock Size : %ld \tWall Time : %f \tSpeed : %f \t",BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024));
    }
}