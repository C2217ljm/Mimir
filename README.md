# README #

This repository contains the source code (src), benchmarks (benchmarks), documentations (doc), and relevant publications (publications) of the multithreaded MapReduce project.

The goal of the project is to enable more efficient big data processing on traditional HPC platforms.

## How do I Compile and Run ##
### Supported Platform ###
GNU/Linux

### Required Software ###
* A C++ compiler must be installed
* MPI library must be installed, MPICH, MVAPICH, etc
* OpenMP support
 
### How to Compile ###
```
$ cd /path/to/src
$ make
```

### How to Run ###
To run the wordcount benchmark:
```
$ cd /path/to/benchmarks/bench_wc
$ make
$ mpiexec -n 2 -ppn 1 ./wordcount input_path log_path spill_path out_path
```

To run the octree_lg benchmark:
```
$ cd /path/to/benchmarks/bench_lg
$ make
$ mpiexec 
```

### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact