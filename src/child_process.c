#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "hash.h"

#define PATH_MAX 1024
char *blocks_folder = "output/blocks";
char *hashes_folder = "output/hashes";
char *visualization_file = "output/visualization.txt";

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./child_process <blocks_folder> <hashes_folder> <N> <child_id>\n");
        return 1;
    }

    //read command args
    int n = atoi(argv[3]);
    int child_id = atoi(argv[4]);
    printf("child process %d\n", child_id);

    // TODO: If the current process is a leaf process, read in the associated block file 
    // and compute the hash of the block.


    if(child_id >= n-1){ //leaf process
        printf("in leaf process\n");

        //create file
        char bufferFile[132] = "";
        sprintf(bufferFile,"output/hashes/%d.out", child_id);

        FILE *fp1 = fopen(bufferFile, "w+");
        if (fp1 == NULL){
            char buffer1[128];
            sprintf(buffer1,"Leaf Process: failed to open hash file: %d", child_id);
            perror(buffer1);
            exit(-1);
        }

        //make hash and write
        int numout = child_id-(n-1); //used to identify which .txt file to hash 
        char block_hash[SHA256_BLOCK_SIZE * 2 + 1];
        char buffer[64];

        sprintf(buffer,"output/blocks/%d.txt", numout);
        hash_data_block(block_hash, buffer);

        fwrite(block_hash, sizeof(char), strlen(block_hash), fp1);
        fclose(fp1);
        exit(0);
    }





    // TODO: If the current process is not a leaf process, spawn two child processes using  
    // exec() and ./child_process. 
    else{ //non leaf process
        printf("in non-leaf process\n");

        //rileftht process
        pid_t leftchild = fork();
        if (leftchild == 0){ //left process is child 
            int id = (2*child_id)+1;

            //buffers for N and ID args
            char bufferID[2];
            sprintf(bufferID, "%d",id);
            char bufferN[16]; 
            sprintf(bufferN, "%d",n);

            char *args[] = {"./child_process", blocks_folder, hashes_folder, bufferN, bufferID, NULL};
            execv(args[0], args);
        }
        
        //right process
        pid_t rightchild = fork();
        if (rightchild == 0){ //right process is a child
            int id = (2*child_id)+2;
            
            char bufferID[2];
            sprintf(bufferID, "%d",id);
            char bufferN[16]; 
            sprintf(bufferN, "%d",n);

            char *args[] = {"./child_process", blocks_folder, hashes_folder, bufferN, bufferID, NULL};
            execv(args[0], args);
        }

            //wait
            waitpid(leftchild, NULL, 0);
            waitpid(rightchild, NULL, 0);

            char left_hash[SHA256_BLOCK_SIZE * 2 + 1];
            char right_hash[SHA256_BLOCK_SIZE * 2 + 1];
            char result_hash[SHA256_BLOCK_SIZE * 2 + 1];
            char left_fname[PATH_MAX];
            char right_fname[PATH_MAX];

            //name files
            sprintf(left_fname,"output/hashes/%d.out", (2*child_id)+1);
            sprintf(right_fname,"output/hashes/%d.out", (2*child_id)+2);
            
            //open both files
            printf("leftname: %s\n",left_fname);
            printf("rightname: %s\n",right_fname);

            //opening left file, reading hash
            FILE *fp2 = fopen(left_fname, "r+");
            if (fp2 == NULL){
                char buffer1[128];
                sprintf(buffer1,"failed to open left hash file: %d", (2*child_id)+1);
                perror(buffer1);
                exit(-1);
            }

            fscanf(fp2,"%s",left_hash);
            fclose(fp2);

            //opening right file, and reading hash
            FILE *fp3 = fopen(right_fname,"r+");
            if (fp3 == NULL){
                char buffer1[128];
                sprintf(buffer1,"failed to open right hash file: %d", (2*child_id)+2);
                perror(buffer1);
                exit(-1);
            }

            fscanf(fp3,"%s",right_hash);
            fclose(fp3);

            compute_dual_hash(result_hash, left_hash, right_hash);

            //create output file
            char bufferFile[132];
            sprintf(bufferFile,"output/hashes/%d.out", child_id);

            FILE *fp1 = fopen(bufferFile, "w+");
            if (fp1 == NULL){
                char buffer1[128];
                sprintf(buffer1,"failed to open hash file: %d", child_id);
                perror(buffer1);
                exit(-1);
            }
            fprintf(fp1,"%s", result_hash);
            fclose(fp1);
    }
    
}

