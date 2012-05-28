#ifndef ARGOS_TAINT_H_
#define ARGOS_TAINT_H_ 1


extern ram_addr_t ram_size;
extern argos_memmap_t *argos_memmap;
#define IS_VALID(ptag)  \
    (                   \
      ( (unsigned long)argos_memmap ) <= ( (unsigned long)(ptag) )  &&          \
      ( (unsigned long)(ptag) )  < ( (unsigned long)argos_memmap ) + ram_size   \
    )


#endif
