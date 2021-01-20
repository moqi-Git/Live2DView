//
// Created by reol on 1/20/21.
//

#ifndef LIVE2DVIEWSAMPLE_LIVE2DALLOCATOR_HPP
#define LIVE2DVIEWSAMPLE_LIVE2DALLOCATOR_HPP


#include <ICubismAllocator.hpp>

class Live2DAllocator: public Live2D::Cubism::Framework::ICubismAllocator {

    void *Allocate(const Live2D::Cubism::Framework::csmSizeType size) override;

    void Deallocate(void *memory) override;

    void *AllocateAligned(const Live2D::Cubism::Framework::csmSizeType size,
                          const Live2D::Cubism::Framework::csmUint32 alignment) override;

    void DeallocateAligned(void *alignedMemory) override;
};


#endif //LIVE2DVIEWSAMPLE_LIVE2DALLOCATOR_HPP
