#include "config.h"


/// Number of hash bucket (2^x)
int BUCKET_COUNT=1024*1024;

/// Communication buffer size
int64_t COMM_BUF_SIZE=64*1024*1024;

/// Page size
int64_t DATA_PAGE_SIZE=64*1024*1024;

/// Input buffer size
int64_t INPUT_BUF_SIZE=64*1024*1024;

/// KV exchange communication mode 
/// (0: collective; 1: point to point)
int KV_EXCH_COMM=0;

/// Maximum number of pages
int MAX_PAGE_COUNT=1024;

/// Number of set when converting KVs to KMVs (2^x)
int SET_COUNT=1024*1024;

/// Maximum string size pass to map_text_file
int MAX_STR_SIZE=8192;

/// Unit size for comm buffer
int COMM_UNIT_SIZE=4096;

/// Debug Level
int DBG_LEVEL=0;


