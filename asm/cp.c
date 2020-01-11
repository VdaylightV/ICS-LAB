#include "stdio.h"
#include "string.h"

void *asm_memcpy(void *dest, const void *src, size_t n) {
    return memcpy(dest,src,n);
}

int main() {

	return 0;

}


