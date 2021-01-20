//
// Created by reol on 1/20/21.
//

#include <malloc.h>
#include "Live2DAllocator.hpp"


void *Live2DAllocator::Allocate(const Live2D::Cubism::Framework::csmSizeType size) {
    return malloc(size);
}

void Live2DAllocator::Deallocate(void *memory) {
    free(memory);
}

void *Live2DAllocator::AllocateAligned(const Live2D::Cubism::Framework::csmSizeType size,
                                       const Live2D::Cubism::Framework::csmUint32 alignment) {
    size_t offset, shift, alignedAddress;
    void *allocation;
    void **preamble;

    offset = alignment - 1 + sizeof(void *);

    allocation = Allocate(size + static_cast<Live2D::Cubism::Framework::csmUint32>(offset));

    alignedAddress = reinterpret_cast<size_t>(allocation) + sizeof(void *);

    shift = alignedAddress % alignment;

    if (shift) {
        alignedAddress += (alignment - shift);
    }

    preamble = reinterpret_cast<void **>(alignedAddress);
    preamble[-1] = allocation;

    return reinterpret_cast<void *>(alignedAddress);
}

void Live2DAllocator::DeallocateAligned(void *alignedMemory) {
    void **preamble;

    preamble = static_cast<void **>(alignedMemory);

    Deallocate(preamble[-1]);
}
