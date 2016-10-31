#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <sys/stat.h>

#include "mapreduce.h"
#include "common.h"

using namespace MIMIR_NS;

int rank, size;

#if 0
void map(MapReduce *mr, char *word, void *ptr);
void countword(MapReduce *, char *, int,  void*);
void combiner(MapReduce *, char *, int, \
    char *, int, char *, int, void*);
#endif

int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc <= 3){
        if(rank == 0) printf("Syntax: wordcount filepath prefix outdir\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


#if 0

    char *filedir=argv[1];
    const char *prefix = argv[2];
    const char *outdir = argv[3];

    MapReduce *mr = new MapReduce(MPI_COMM_WORLD);


    mr->map_text_file(filedir, 1, 1, " \n", map);
    mr->reduce(countword, NULL);

#ifdef OUTPUT_KV
  char tmpfile[100];
  sprintf(tmpfile, "results%d.txt", me);
  FILE *outfile=fopen(tmpfile, "w");
  mr->output(1, outfile);
  fclose(outfile);
#endif

    output();

    delete mr;

#endif

    MPI_Finalize();
}

#if 0

void map(MapReduce *mr, char *word, void *ptr){
    int len=(int)strlen(word)+1;
    int64_t one=1;
    if(len <= 1024)
        mr->add_key_value(word,len,(char*)&one,sizeof(one));
}

void countword(MapReduce *mr, char *key, int keysize, void* ptr){
    int64_t count=0;

#if 0
    for(iter->Begin(); !iter->Done(); iter->Next()){
        count+=*(int64_t*)iter->getValue();
    }
#endif

    mr->add_key_value(key, keysize, (char*)&count, sizeof(count));
}

void combiner(MapReduce *mr, char *key, int keysize, \
    char *val1, int val1size, \
    char *val2, int val2size, void* ptr){

    int64_t count=*(int64_t*)(val1)+*(int64_t*)(val2);

    mr->add_key_value(key, keysize, (char*)&count, sizeof(count));
}

#endif
