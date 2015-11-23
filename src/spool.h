#ifndef SPOOL_H
#define SPOOL_H

#include "config.h"

namespace MAPREDUCE_NS {

class Spool{
public:
  Spool(int,int _maxblocks=1024);
  ~Spool();

  char *addblock();

  int getblocksize(){
    return blocksize;
  }

private:
  char **blocks;
  int nblock;
  int blocksize;
  int maxblocks;
};

}

#endif
