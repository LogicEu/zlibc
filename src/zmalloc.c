#define _DEFAULT_SOURCE
#include <sys/mman.h>
#include <sys/syscall.h>
#include <zstring.h>
#include <zassert.h>
#include <zstdlib.h>

extern int zprintf(const char* fmt, ...);

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#define MEMHINT_FILE (void*)0x600020000000UL
#define MEMCHECK_OWND 0x77777777UL
#define MEMCHECK_FREE 0xfedcba01UL

typedef struct memnode_t {
    size_t checksum;
    size_t size;
    struct memnode_t* next;
    struct memnode_t* prev;
} memnode_t;

static memnode_t* head = NULL;
static void* membase = NULL;
static size_t membytes = 0;

#define MEMBLOCK(ptr) ((void*)((size_t)ptr + sizeof(memnode_t)))
#define MEMNODE(ptr) ((void*)((size_t)ptr - sizeof(memnode_t)))

static size_t mempad(size_t n)
{
    size_t i;
    for (i = sizeof(memnode_t); i < n; i <<= 1);
    return i;
}

static void* memalloc(size_t size)
{
    void* mem;
    if (!membase) {
        mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
        if (mem != MAP_FAILED) {
            membase = mem;
        }
    }
    else mem = mmap(membase + membytes, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED, 0, 0);
    
    if (mem && mem != MAP_FAILED) {
        membytes += size;
    }
    
    return mem;
}

static void* memfree(void)
{
    if (munmap(membase, membytes)) {
        zprintf("munmap error freeing %zub of memory.\n", membytes);
        return MAP_FAILED;
    }
    
    head = NULL;
    membase = NULL;
    membytes = 0;
    
    zprintf("successfully cleaned all memmory.\n");
    return NULL;
}

static void memnode_add(memnode_t* node)
{
    node->checksum = MEMCHECK_FREE;
    node->next = NULL;
    node->prev = NULL;

    if (!head) {
        head = node;
    } else if ((size_t)head > (size_t)node) {
        node->next = head;
        head->prev = node;
        head = node;
    } else {
        memnode_t* curr = head;
        while (curr->next && (size_t)curr->next < (size_t)node) {
            curr = curr->next;
        }
        
        if (curr->next) {
            curr->next->prev = node;
        }
        node->next = curr->next;
        node->prev = curr;
        curr->next = node;
    }
}

static void memnode_remove(memnode_t* node)
{
    node->checksum = MEMCHECK_OWND;

    if (node->next) {
        node->next->prev = node->prev;
    }

    if (node->prev) {
        node->prev->next = node->next;
    }
    else if (head->next) {
        head = head->next;
    }
    else head = NULL;

    node->next = NULL;
    node->prev = NULL;
}

static int memnode_checksum(memnode_t* node, size_t flag)
{
    size_t node_pos = (size_t)node;
    size_t base_pos = (size_t)membase;
    return (
        !base_pos || node_pos % sizeof(void*) ||
        node_pos + sizeof(memnode_t) > base_pos + membytes || 
        node_pos < base_pos || node->checksum != flag
    );
}

static memnode_t* memnode_merge(void)
{
    memnode_t *curr = head;
    while (curr->next) {
        if ((size_t)curr + curr->size + sizeof(memnode_t) == (size_t)curr->next) {

            curr->size += curr->next->size + sizeof(memnode_t);
            curr->next = curr->next->next;

            if (curr->next) {
                curr->next->prev = curr;
            }
        }
        else curr = curr->next;
    }
    return curr;
}

static void memnode_trim(memnode_t* curr)
{
    if (curr->size >= PAGESIZE && (size_t)curr + curr->size + sizeof(memnode_t) == (size_t)membase + membytes) {
        size_t free_size;
        if ((size_t)curr - (size_t)membase) {
            free_size = PAGESIZE;
            while (free_size * 2 <= curr->size) {
                free_size *= 2;
            }
        }
        else free_size = membytes;

        if (membytes == free_size) {
            memfree();
            return;
        }

        if (curr->size > free_size) {
            curr->size -= free_size;
        }
        else {
            memnode_remove(curr);
        }

        membytes -= free_size;
        if (munmap(membase + membytes, free_size)) {
            zprintf("munmap error freeing %zub of memory.\n", free_size);
            return;
        }
    }

    if (curr->size + sizeof(memnode_t) == membytes) {
        memfree();
    }
}

static void memnode_split(memnode_t* node, size_t size)
{
    memnode_t* n = (memnode_t*)((size_t)node + size + sizeof(memnode_t));
    n->size = node->size - (size + sizeof(memnode_t));
    node->size = size;
    memnode_add(n);
}

void* zmalloc(size_t size)
{
    void *mem;
    memnode_t *ptr;

    if (!size) {
        return NULL;
    }

    size_t pad = mempad(size + sizeof(memnode_t));
    size = pad - sizeof(memnode_t);

    size_t alloc_size = PAGESIZE;
    while (pad > alloc_size) {
        alloc_size *= 2;
    }

    ptr = head;
    while (ptr) {
        if (ptr->size >= size) {
            if (memnode_checksum(ptr, MEMCHECK_FREE)) {
                zprintf("heap memory corruption detected at %p\n", ptr);
                zabort();
            }

            if (ptr->size > size) {
                memnode_split(ptr, size);
            }

            mem = MEMBLOCK(ptr);
            memnode_remove(ptr);
            return mem;
        }

        ptr = ptr->next;
    }

    ptr = memalloc(alloc_size);
    if (!ptr || ptr == MAP_FAILED) {
        zprintf("malloc failed to allocate %zub memory.\n", alloc_size);
        return NULL;
    }

    ptr->checksum = MEMCHECK_OWND;
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->size = alloc_size - sizeof(memnode_t);
    
    if (ptr->size > size) {
        memnode_split(ptr, size);
    }

    return MEMBLOCK(ptr);
}

void zfree(void *ptr)
{
    if (!ptr) {
        return;
    }

    memnode_t* node = MEMNODE(ptr);
    if (memnode_checksum(node, MEMCHECK_OWND)) {
        zprintf("free error: object being freed was not allocated (%p).\n", ptr);
        zabort();
    }

    memnode_add(node);
    node = memnode_merge();
    memnode_trim(node);
}

void* zrealloc(void* ptr, size_t size)
{
    if (!ptr) {
        return zmalloc(size);
    }

    memnode_t* node = MEMNODE(ptr);
    if (memnode_checksum(node, MEMCHECK_OWND)) {
        zprintf("realloc error: object being reallocated was not allocated (%p).\n", ptr);
        zabort();
    }

    size_t node_size = node->size;
    memnode_add(node);
    node = memnode_merge();

    void* mem = zmalloc(size);
    if (mem && mem != ptr) {
        size_t len = size < node_size ? size : node_size;
        zmemcpy(mem, ptr, len);
    }

    memnode_trim(node);
    return mem;
}

void* zcalloc(size_t count, size_t size)
{
    size_t n = count * size;
    void* mem = zmalloc(n);
    if (mem) {
        zmemset(mem, 0, n);
    }
    return mem;
}

void* zfmalloc(int fd, size_t size)
{
    if (!size) {
        return NULL;
    }

    size_t alloc_size = PAGESIZE;
    while (size > alloc_size) {
        alloc_size *= 2;
    }
    
    void* mem = mmap(MEMHINT_FILE, alloc_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
    if (!mem || mem == MAP_FAILED) {
        zprintf("fmalloc failed to allocate %zub of memory.\n", alloc_size);
        return NULL;
    }

    void* ret = zmalloc(size);
    if (ret) {
        zmemcpy(ret, mem, size);
    }

    if (munmap(mem, alloc_size)) {
        zprintf("munmap error freeing %zub of memory.\n", alloc_size);
        zabort();
    }

    return ret;
}

#ifndef NDEBUG

void zmalloc_inspect(void)
{
    zprintf("Address: %p\nSize: %zuKb\n", membase, membytes >> 10);

    if (!membase) {
        return;
    }

    size_t freelen = 0, alloclen = 0;
    memnode_t* curr = membase;
    const size_t end = (size_t)membase + membytes;
    while ((size_t)curr < end) {
        switch (curr->checksum) {
            case MEMCHECK_FREE:
                freelen += curr->size;
                zprintf("Free: %p - %zu\n", curr, curr->size);
                break;
            case MEMCHECK_OWND:
                alloclen += curr->size;
                zprintf("Ownd: %p - %zu\n", curr, curr->size);
                break;
            default:
                zprintf("Memmory heap corruption detected at %p\n", curr);
                return;
        }
        curr = (memnode_t*)((size_t)curr + curr->size + sizeof(memnode_t));
    }

    zprintf("Freed Space: %zub\nUsed Space: %zub\n", freelen, alloclen);
}

#endif