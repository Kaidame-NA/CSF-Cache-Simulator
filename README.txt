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
    Using a 1 MB cache as the test case. We would say that the 512 512 4 write-allocate write-back cache is most effective. However when altering the LRU and FIFO instruction, the total number of cycles did not change.