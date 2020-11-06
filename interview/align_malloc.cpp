#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <string.h>
#include <bitset> 

// alignment is 2^n
void* align_malloc(size_t size, size_t alignment) {
    size_t require_size = size + alignment + sizeof(void*);
    size_t offset = alignment + sizeof(void*);
    void* p = malloc(require_size);
    void** p1 = (void**)(((size_t)p + offset) & (~(alignment - 1)));
    p1[-1] = p;
    std::bitset<64> s_bits((size_t)p);
    std::cout << s_bits.to_string()  << std::endl;
    std::bitset<64> d_bits((size_t)p1);
    std::cout << d_bits.to_string()  << std::endl;
    return (void*)p1;
}

void align_free(void* p) {
    void** p1 = (void**)p;
    free(p1[-1]);
}

int main() {
    size_t size = 100;
    void *p = align_malloc(size, 16);
    memset(p, 0, size);
    align_free(p);
    return 0;
}

