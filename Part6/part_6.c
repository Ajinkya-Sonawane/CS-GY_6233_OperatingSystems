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
#include <fcntl.h>

#define MAX_BLOCK_SIZE 600000
#define PART_6_FILENAME "Part6/PART_6.csv"

typedef struct {
    int FD;
    int BLOCK_SIZE;
    unsigned int *BUFFER;
    unsigned int xor;
    int THREAD_NO;
    int NUM_OF_THREADS;
} struct_read_thread;


void add_record_to_csv(char *record){
    FILE *fptr;
    fptr = fopen(PART_6_FILENAME,"a");
    fprintf(fptr,"%s",record);
    fclose(fptr);
}

void init_csv_file(){
    FILE *fptr;
    fptr = fopen(PART_6_FILENAME,"w");
    fprintf(fptr,"Block Size,Number of Threads,Wall Time, Speed");
    fclose(fptr);
}

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

void *read_thread(void *arg) {
    struct_read_thread *thread_args = (struct_read_thread *)arg;
    int r;
    int size;
    unsigned long offset = thread_args->THREAD_NO * thread_args->BLOCK_SIZE;
    int count = 0;
    while ((r = pread(thread_args->FD, thread_args->BUFFER, thread_args->BLOCK_SIZE, offset)) > 0) {
        size = r/sizeof(unsigned int);
        thread_args->xor ^= xorbuf(thread_args->BUFFER, size);
        count++;
        offset = (((unsigned long)thread_args->NUM_OF_THREADS * count) + thread_args->THREAD_NO) * (unsigned long)thread_args->BLOCK_SIZE;
    }
    
    pthread_exit(NULL);
}

void read_from_disk_with_threads(char *FILENNAME, int BLOCK_SIZE, int NUM_OF_THREADS) {
    int fd = open(FILENNAME, O_RDONLY);
    struct_read_thread thread_args[NUM_OF_THREADS];
    int i;
    int xor = 0;
    pthread_t threads[NUM_OF_THREADS];
    unsigned int buf_size = BLOCK_SIZE / sizeof(unsigned int);

    //Initialize read_thread structure for each thread 
    for (i=0; i < NUM_OF_THREADS; i++) {
        struct_read_thread argument;
        argument.BLOCK_SIZE = buf_size * sizeof(unsigned int);
        argument.FD = fd;
        argument.THREAD_NO = i;
        argument.NUM_OF_THREADS = NUM_OF_THREADS;
        argument.BUFFER = (unsigned int *)malloc(buf_size * sizeof(unsigned int));
        argument.xor = 0;
        thread_args[i] = argument;
    }

    //Create and run the threads in parallel
    for (i=0; i < NUM_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, read_thread, (void *)(&thread_args[i]));
    }

    //Wait and XOR the contents of the file read by each thread
    for (i=0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
        xor ^= thread_args[i].xor;
    }
    printf("\nWith multi-threading \nBlock Size\t\t: %d\nNumber of threads\t: %d\nxor\t\t\t: %08x\n",BLOCK_SIZE,NUM_OF_THREADS, xor);
}

void read_from_disk_without_threads(char *FILENAME,int BLOCK_SIZE){

    int size = ceil(BLOCK_SIZE/(long)sizeof(unsigned int));
    unsigned int buf[size];
    unsigned int xor = 0;
    int bytes_read;

    int fd = open(FILENAME, O_RDONLY);
    unsigned int read_size;
    while ((bytes_read=read(fd, buf, BLOCK_SIZE)) > 0) {
        read_size = ceil(bytes_read/sizeof(unsigned int));
        xor ^= xorbuf(buf, read_size);
    }
    printf("\nWithout multi-threading \nBlock Size\t: %d\nxor\t\t: %08x\n",BLOCK_SIZE, xor);
    close(fd);
}

unsigned int get_file_size_bytes(char *filename){
    unsigned int file_size_bytes = 0;
    int fd = open(filename,O_RDONLY);
    file_size_bytes = lseek(fd,0,SEEK_END);
    close(fd);
    return file_size_bytes;
}

int main(int argc, char *argv[]) {

    char *FILENAME;
    char mode;
    long BLOCK_SIZE;
    int BLOCK_COUNT;
    int NUM_OF_THREADS;
    clock_t start,end;
    double wall_time;
    char *record;
    FILENAME = argv[1];

    //Chose the following by through trials
    BLOCK_SIZE = 524288;
    NUM_OF_THREADS = 3;
    unsigned int FILZESIZE = get_file_size_bytes(FILENAME);
    init_csv_file();
    for(long BLOCK_SIZE=8192;BLOCK_SIZE < MAX_BLOCK_SIZE;BLOCK_SIZE*=2){
        for(int NUM_OF_THREADS = 1; NUM_OF_THREADS <= 10; NUM_OF_THREADS+=1){
            //Calculate read and XOR time using threads
            start = clock();
            read_from_disk_with_threads(FILENAME, BLOCK_SIZE, NUM_OF_THREADS);
            end = clock();
            wall_time = (double)(end - start)/CLOCKS_PER_SEC;
            record = (char*)malloc(100 * sizeof(char));
            sprintf(record, "\n%ld,%d,%f,%f", BLOCK_SIZE, NUM_OF_THREADS,wall_time,FILZESIZE/(wall_time*1024*1024));

            add_record_to_csv(record);            
            printf("Wall Time\t\t: %f\n",wall_time);
        }
    }


}
