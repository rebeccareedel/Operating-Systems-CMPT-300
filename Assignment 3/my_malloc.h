// Rebecca Reedel 301454910, Asmita Srivastava 301436340

#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_
#include <stdlib.h>

/*
       DESCRIPTION: -- from man pages
       The malloc() function allocates size bytes and returns a pointer to the
       allocated memory.  The memory is not initialized.  If size is  0,  then
       malloc()  returns either NULL, or a unique pointer value that can later
       be successfully passed to free(). 
       
       RETURN VALUE:
       The  malloc()  and calloc() functions return a pointer to the allocated
       memory, which is suitably aligned for any  built-in  type.   On  error,
       these functions return NULL.  NULL may also be returned by a successful
       call to malloc() with a size of zero, or by a successful call  to  cal‐
       loc() with nmemb or size equal to zero.
*/
void *my_malloc(size_t size);

/*     DESCRIPTION: -- from man pages
       The free() function frees the memory space pointed  to  by  ptr,  which
       must  have  been  returned by a previous call to malloc(), calloc(), or
       realloc().  Otherwise, or if free(ptr) has already been called  before,
       undefined behavior occurs.  If ptr is NULL, no operation is performed. 
       
       RETURN VALUE:
       The free() function returns no value.
*/
void my_free(void *ptr);

/*     NOTES:
       By  default,  Linux  follows  an optimistic memory allocation strategy.
       This means that when malloc() returns non-NULL there  is  no  guarantee
       that  the  memory  really  is available.  In case it turns out that the
       system is out of memory, one or more processes will be  killed  by  the
       OOM   killer.    For   more   information,   see   the  description  of
       /proc/sys/vm/overcommit_memory and /proc/sys/vm/oom_adj in proc(5), and
       the   Linux  kernel  source  file  Documentation/vm/overcommit-account‐
       ing.rst.

       Normally, malloc() allocates memory from the heap, and adjusts the size
       of the heap as required, using sbrk(2).  When allocating blocks of mem‐
       ory larger than MMAP_THRESHOLD bytes, the glibc malloc() implementation
       allocates  the  memory  as  a  private anonymous mapping using mmap(2).
       MMAP_THRESHOLD is 128 kB by  default,  but  is  adjustable  using  mal‐
       lopt(3).   Prior  to Linux 4.7 allocations performed using mmap(2) were
       unaffected by the RLIMIT_DATA resource limit;  since  Linux  4.7,  this
       limit is also enforced for allocations performed using mmap(2).
       
       To avoid corruption in multithreaded applications, mutexes are used in‐
       ternally to protect the memory-management data structures  employed  by
       these  functions.   In a multithreaded application in which threads si‐
       multaneously allocate and free memory, there could  be  contention  for
       these  mutexes.   To scalably handle memory allocation in multithreaded
       applications, glibc creates additional memory allocation arenas if  mu‐
       tex  contention  is  detected.   Each arena is a large region of memory
       that is internally allocated by the system (using brk(2)  or  mmap(2)),
       and managed with its own mutexes.

       SUSv2 requires malloc(), calloc(), and realloc() to set errno to ENOMEM
       upon failure.  Glibc assumes that this is done (and the glibc  versions
       of  these routines do this); if you use a private malloc implementation
       that does not set errno, then certain library routines may fail without
       having a reason in errno.

       Crashes  in  malloc(), calloc(), realloc(), or free() are almost always
       related to heap corruption, such as overflowing an allocated  chunk  or
       freeing the same pointer twice.

       The  malloc()  implementation is tunable via environment variables; see
       mallopt(3) for details.

       */

// used for testing purposes
size_t checkNumBytesFree();

void mem_init();

void print_table();


#endif
