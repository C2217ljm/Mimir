/*
 * (c) 2016 by University of Delaware, Argonne National Laboratory, San Diego 
 *     Supercomputer Center, National University of Defense Technology, 
 *     National Supercomputer Center in Guangzhou, and Sun Yat-sen University.
 *
 *     See COPYRIGHT in top-level directory.
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>

#include "mimir.h"

using namespace MIMIR_NS;

int rank, size;

void map (Readable<char*,void> *input,
          Writable<char*,uint64_t> *output, void *ptr);
void countword (Readable<char*,uint64_t> *input,
                Writable<char*,uint64_t> *output, void *ptr);
void combine (Combinable<char*,uint64_t> *combiner,
              char**, uint64_t*, uint64_t*, uint64_t*, void *ptr);

uint64_t nwords = 0, nunique = 0;

int main (int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0)
            fprintf(stdout, "Usage: %s output input ...\n", argv[0]);
        return 0;
    }

    std::string output = argv[1];
    std::vector<std::string> input;
    for (int i = 2; i < argc; i++) {
        input.push_back(argv[i]);
    }
    MimirContext<char*, uint64_t, char*, void>* ctx 
        = new MimirContext<char*, uint64_t, char*, void>(MPI_COMM_WORLD,
                                           map, countword,
                                           input, output,
                                           NULL,
#ifdef COMBINER
                                           combine,
#else
                                           NULL,
#endif
                                           NULL,
                                           true,
                                           IMPLICIT_OUTPUT);
    ctx->set_outfile_format("text");
    ctx->map();
    nunique = ctx->reduce();
    delete ctx;

    if (rank == 0) printf("nunique=%ld\n", nunique);

    MPI_Finalize();
}

void map (Readable<char*,void> *input, Writable<char*,uint64_t> *output, void *ptr)
{
    char *line = NULL;
    while (input->read(&line, NULL) == 0) {
        char *saveptr = NULL;
        char *word = strtok_r(line, " ", &saveptr);
        while (word != NULL) {
            if (strlen(word) < 1024) {
                uint64_t one = 1;
                output->write(&word, &one);
                nwords += 1;
            }
            word = strtok_r(NULL, " ", &saveptr);
        }
    }
}

void countword (Readable<char*,uint64_t> *input,
                Writable<char*,uint64_t> *output, void *ptr) 
{
    char *key = NULL;
    uint64_t val = 0;
    uint64_t count = 0;
    while (input->read(&key, &val) == 0) {
        count += val;
    }
    output->write(&key, &count);
}

void combine (Combinable<char*,uint64_t> *combiner,
              char **key, uint64_t *val1, uint64_t *val2,
              uint64_t *rval, void *ptr)
{
    *rval = *val1 + *val2;
}
