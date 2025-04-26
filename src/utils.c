#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

// Create N files and distribute the data from the input file evenly among them
// See section 3.1 of the project writeup for important implementation details
void partition_file_data(char *input_file, int n, char *blocks_folder) {
    // Hint: Use fseek() and ftell() to determine the size of the file
    //open file
    FILE *fp = fopen(input_file,"r");
    printf("%s\n", input_file);
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    int data_size;
    fseek(fp,0,SEEK_END); //goes to end of the file
    int len = ftell(fp); // len is the size of the input file  
    fseek(fp, 0, SEEK_SET); //returns pointer to the start of the input file
    
    //files will be made,read, and written within a single for loop, i is equal 
    //also, since read moves the ptr, no extra ptr arithmitic is needed for fp
    for(int i = 0; i < n ; i++){
        //make new [i].txt file
        char buffer[132];
        sprintf(buffer,"output/blocks/%d.txt", i);
        FILE *fp2 = fopen(buffer, "w+");

        if (i == n-1){ //last split
            data_size = floor(len/n) + len%n;
            char buffer[data_size];
            //read from input file
            fread(buffer, 1, data_size, fp);
            // printf("%s\n",buffer); //used for debugging
            //write to final [n].txt
            fwrite(buffer, 1, data_size, fp2);
        }
        else{ //files 0 - n-1
            data_size = floor(len/n);
            char buffer[data_size];
            //read from input file
            fread(buffer, 1, data_size, fp);
            // printf("%s\n",buffer); //used for debugging
            //write to new [i].txt
            fwrite(buffer, 1, data_size, fp2);
        }
        //close [i].file
        fclose(fp2);
    }
    //finished reading from fp, so close it
    fclose(fp);
}


// ##### DO NOT MODIFY THIS FUNCTION #####
void setup_output_directory(char *block_folder, char *hash_folder) {
    // Remove output directory
    pid_t pid = fork();
    if (pid == 0) {
        char *argv[] = {"rm", "-rf", "./output/", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(1);
        }
        exit(0);
    } else {
        wait(NULL);
    }

    sleep(1);

    // Creating output directory
    if (mkdir("output", 0777) < 0) {
        printf("ERROR: mkdir output failed\n");
        exit(1);
    }

    sleep(1);

    // Creating blocks directory
    if (mkdir(block_folder, 0777) < 0) {
        printf("ERROR: mkdir output/blocks failed\n");
        exit(1);
    }

    // Creating hashes directory
    if (mkdir(hash_folder, 0777) < 0) {
        printf("ERROR: mkdir output/hashes failed\n");
        exit(1);
    }
}