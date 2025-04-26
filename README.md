Overview

This project implements a parallelized Merkle Tree hashing algorithm for secure file integrity verification. Merkle Trees (hash trees) enable efficient and tamper-evident verification of large datasets by representing file contents as a binary tree of cryptographic hashes. This project simulates a real-world system used in blockchain technologies, version control systems, and distributed storage.

Features

- Merkle Tree Construction: Builds a complete binary Merkle Tree from fixed-size data chunks.

- Parallel Processing: Uses parent-child process creation to compute hash values for tree nodes in parallel.

- Cryptographic Security: Ensures file integrity using SHA-based hashing at each level of the tree.

- Process Synchronization: Coordinates multiple processes using fork() and synchronization primitives for efficient computation.

How It Works

- File is split into equal-sized chunks (data blocks).

- Each chunk is hashed to form a leaf node.

- Parent nodes recursively hash pairs of child hashes to form the tree up to a single root.

- The root hash can be used to verify the integrity of any chunk without reprocessing the entire file.


How To Run:

You can create all of the necessary executable files with
```
$ make all
```

Running the program can be accomplished with
```
$ ./merkle input/T1.txt 8
```

The Makefile contains three tests (T1, T2, T3). After running “make all” or “make inter”, you can run these test cases like such:
```
$ make t1
```



