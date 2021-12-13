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
    fprintf(fptr,"File Size,Wall Time,Speed (B/s),Speed (MiB/s)");
    fclose(fptr);
}

long read_from_disk(char *FILENAME,int BLOCK_SIZE,unsigned long EOF_bytes){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    long total_bytes_read;
    while ((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0 && total_bytes_read < EOF_bytes) {
        total_bytes_read += bytes_read;
        continue;
    }
    close(fd);
    return total_bytes_read;
}

void lseek_file(char *FILENAME, int BLOCKSIZE, unsigned long EOF_bytes){
    int fd = open(FILENAME, O_RDONLY);
    // off_t end_position = lseek(fd, 0, SEEK_END);
    off_t end_position = EOF_bytes;
    off_t old_position = lseek(fd, 0, SEEK_SET);
    // printf("\n%lld\n%lld\n",end_position,old_position);
    while(old_position < end_position) {
        old_position = lseek(fd, BLOCKSIZE, SEEK_CUR);
        // printf("\r%lld",old_position);
    }
}

unsigned int get_file_size_bytes(char *filename){
    unsigned int file_size_bytes = 0;
    int fd = open(filename,O_RDONLY);
    file_size_bytes = lseek(fd,0,SEEK_END);
    close(fd);
    return file_size_bytes;
}

int main(int argc, char *argv[]) {
    char *record;
    char *FILENAME;
    clock_t start,end;
    double wall_time;
    long total_bytes_read;
    FILENAME = argv[1];
    long BLOCK_SIZE = 1;

    unsigned long FILESIZE_BYTES = get_file_size_bytes(FILENAME);
    int ITERATION_SIZE_BYTES = ceil(FILESIZE_BYTES/10);    

    // Initialize the CSV File
    // init_csv_file();

    for(unsigned long CUR = 1; CUR <= 10; CUR++){
        //READ System Call
        start = clock();
        total_bytes_read = read_from_disk(FILENAME,BLOCK_SIZE,CUR*ITERATION_SIZE_BYTES);
        end = clock();
        wall_time = (double)(end - start)/CLOCKS_PER_SEC;
        printf("\n\nREAD System Call:");
        printf("\nFile Size\t:\t%ld byte(s) \nBlock Size\t:\t%ld byte(s)\nWall Time\t:\t%f seconds\nSpeed\t\t:\t%f MiB/s | %f B/s\n\n",CUR*ITERATION_SIZE_BYTES,BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024),total_bytes_read/wall_time);

        // record = (char*)malloc(100 * sizeof(char));
        // sprintf(record, "READ,%lu,%f,%f,%f\n",CUR*ITERATION_SIZE_BYTES, wall_time,(CUR*ITERATION_SIZE_BYTES)/(wall_time),(CUR*ITERATION_SIZE_BYTES)/(wall_time*1024*1024));
        // add_record_to_csv(record);

        //LSEEK System Call
        start = clock();
        lseek_file(FILENAME,BLOCK_SIZE,CUR*ITERATION_SIZE_BYTES);
        end = clock();
        wall_time = (double)(end - start)/CLOCKS_PER_SEC;
        printf("\n\nLSEEK System Call:");
        printf("\nFile Size\t:\t%ld byte(s) \nBlock Size\t:\t%ld byte(s)\nWall Time\t:\t%f seconds\nSpeed\t\t:\t%f MiB/s | %f B/s\n\n",CUR*ITERATION_SIZE_BYTES,BLOCK_SIZE,wall_time,total_bytes_read/(wall_time*1024*1024),total_bytes_read/wall_time);

        // record = (char*)malloc(100 * sizeof(char));
        // sprintf(record, "LSEEK,%lu,%f,%f,%f\n", CUR*ITERATION_SIZE_BYTES, wall_time,(CUR*ITERATION_SIZE_BYTES)/(wall_time),(CUR*ITERATION_SIZE_BYTES)/(wall_time*1024*1024));
        // add_record_to_csv(record);

    }
 
}