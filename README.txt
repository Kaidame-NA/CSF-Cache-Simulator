Sambhav Chordia - schordi1@jhu.edu
Edward Wang - ewang43@jhu.edu

schordi1 implementations:
    Makefile
    getLoadHits
    getLoadMisses
    getTotalLoads
    getTotalCycles
    uintLog2
    load
    store
    getBlockToBeEvicted
    main
    Experiment
    
ewang43 implementations:
    Makefile
    main
    isValidNonnegativeInt
    intLog2
    areParametersValid
    Cache constructor
    getStoreHits
    getStoreMisses
    getTotalStores
    load
    getBlock
    getBlockToBeEvicted
    store


Explanation:
    In this experiement we used a 1024 B cache.
    First we went through numerous differnt cache sizes (sets/blocks/associativity) to find the most effective size.

    example test runs: 

    ./csim 256 1 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 263687
    Load misses: 54510
    Store hits: 153611
    Store misses: 43875
    Total cycles: 30102783

    ./csim 128 1 8 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 260491
    Load misses: 57706
    Store hits: 163197
    Store misses: 34289
    Total cycles: 38663283

    ./csim 64 1 16 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 260084
    Load misses: 58113
    Store hits: 173877
    Store misses: 23609
    Total cycles: 52953083

    ./csim 128 2 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 291761
    Load misses: 26436
    Store hits: 163375
    Store misses: 34111
    Total cycles: 26318983

    ./csim 64 4 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 300101
    Load misses: 18096
    Store hits: 164798
    Store misses: 32688
    Total cycles: 25342683

    ./csim 16 16 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 301985
    Load misses: 16212
    Store hits: 165096
    Store misses: 32390
    Total cycles: 25124483

    ./csim 8 32 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 302403
    Load misses: 15794
    Store hits: 165124
    Store misses: 32362
    Total cycles: 25079883

    Through the above tests you can see that the most effective cache size is the "1 256 4" variation

    ./csim 1 256 4 write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 307414
    Load misses: 10783
    Store hits: 167494
    Store misses: 29992
    Total cycles: 24341783

    ./csim 1 256 4 write-allocate write-back lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 307414
    Load misses: 10783
    Store hits: 167494
    Store misses: 29992
    Total cycles: 7785483

    ./csim 1 256 4 no-write-allocate write-through lru < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 304782
    Load misses: 13415
    Store hits: 157960
    Store misses: 39526
    Total cycles: 21566257

        ./csim 1 256 4 write-allocate write-through fifo < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 301858
    Load misses: 16339
    Store hits: 165349
    Store misses: 32137
    Total cycles: 25111883

    ./csim 1 256 4 write-allocate write-back fifo < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 301858
    Load misses: 16339
    Store hits: 165349
    Store misses: 32137
    Total cycles: 8998183

    ./csim 1 256 4 no-write-allocate write-through fifo < gcc.trace
    Total loads: 318197
    Total stores: 197486
    Load hits: 300841
    Load misses: 17356
    Store hits: 153851
    Store misses: 43635
    Total cycles: 21956248

    Through the above experiemnts where we alter the combination of write-allocate, no-write-allocate, write-through, write-back, LRU and FIFO, we can see that the 
    options with the lowest total cycles and misses is the cache with the setting - 1 256 4 write-allocate write-back lru. This makes sense since a fully associative
    cache is the one that will have the least cache misses because if we want to cache the data in memory locations with the same index, we do not need to evict as 
    long as there is still space in the cache. Write-allocate and write-back also seem to be the best options. Although they incur a larger penalty during a store miss
    since the data needs to be loaded into the cache and may need to write back if a block is evicted, whereas in no-write-allocate and write-through, a store miss
    only costs the 100 cycles to write directly to memory, write-allocate and write-back makes up for it as there is less cost during a store hit (only costs 1 cycle)
    and there are more likely to be store hits and load hits as we loaded the block into cache. So, if we are writing to a certain block of memory a lot, after the
    first miss, write-allocate and write-back will only cost 1 cycle for each subsequent write, while write-through and no-write-allocate will cost 100 cycles every
    write. This was tested with other files as well where it also had the results as the mose efficient cache.

    
