Project Group #16 Members Christopher Johnson (joh18725) Carlos Chasi-Mejia (chasi009)

Lab machine: csel-kh250-10.cselabs.umn.edu

Changes made in utils.c

Contributions: work done by both carlos and chris
carlos did most of the forking, merkle.c and good amount of utils.c and child_process
chris did most of the file creation and reading and hashing and good amount in child_process.c also did error handling

No changes made to Makefile

No extra assumptions made 

//design to make merkle tree
In merkle read in arguments for N and filename 
then partition the input file to create blocks folder 
then create first child process that will start the program 
child_process with child_id parameter as 0 

Once in child_process 
read in command arguments for n and child_id 
then checks if child_id is leaf or non leaf
if leaf then creates hashes.out file with associated .out file and then hash associated block file and write it into the hashes.out file and close it and exit program 

if non leaf process, create new left child process using fork, and make it run program (execv) child_process with correct child_id. Then create right_child and do the same as left child. 

Then parent process of these childrens will wait for both the child processes. After this, open left and right hash files and read in data and compute_dual_hash to open and wrtite into parent's hashfile 

//only thing that really changed from intermediate submission was running child program right after creating child instead of creating both children first and then running program

No AI helper tools were used 




