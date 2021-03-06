typedef struct CacheLine {
    int valid;
    int tag;
} CacheLine;

typedef struct CacheSet {
    CacheLine *lines;
    // all lines can be contained
    int capacity;
    // number of current contained line
    int size;
} CacheSet;

typedef struct Cache {
    CacheSet *cacheSets;
    int hits;
    int misses;
    int evictions;
    int verboseFlag;
    int setSize;
    int tagBits;
    int offsetBits;
    int setBits;
} Cache;

void initCacheSet(CacheSet *set, int linePerSet);

void destroyCacheSet(CacheSet *cacheSet);

Cache *createCache(int setBits, int linePerSet, int offsetBits, int verboseFlag);

void destroyCache(Cache *cache);

void splitAddr(Cache *cache, long addr, int *setIndex, int *tagIndex);

int accessMem(Cache *cache, long addr);

/**
 *
 * @param line str from trace file
 * @param op operator of this trace line
 * @param addr hex format of addr of this trace line
 */
void splitOneInst(char *line, char *op, long* addr);

void hitsPlusOne(Cache *cache);

void missesPlusOne(Cache *cache);

void evictionsPlusOne(Cache *cache);

/**
 * 1. split instruction to [space]operation address,size
 * 2. I ignored, L S are same and M is L + S.
 *  2.1 case L:
 *  2.2 case S:
 *  2.3 case M:
 * 3. prints debug info
 * @param line one line from trace file
 */
void analyseOneLine(Cache *cache, char *line, int *hit, int *miss, int *eviction);