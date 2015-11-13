// The MIT License (MIT)
//
// Copyright (c) 2015 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's 
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#ifndef UME_SIMD_VEC_UINT32_2_H_
#define UME_SIMD_VEC_UINT32_2_H_

#include <type_traits>
#include "../../../UMESimdInterface.h"
#include "../../UMESimdPluginScalarEmulation.h"
#include <immintrin.h>

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_u<uint32_t, 2> final :
        public SIMDVecUnsignedInterface<
        SIMDVec_u<uint32_t, 2>,
        uint32_t,
        2,
        SIMDVecMask<2>,
        SIMDVecSwizzle<2 >> ,
        public SIMDVecPackableInterface<
        SIMDVec_u<uint32_t, 2>,
        SIMDVec_u<uint32_t, 1 >>
    {
    public:
        // Conversion operators require access to private members.
        friend class SIMDVec_i<int32_t, 2>;

    private:
        uint32_t mVec[2];

    public:
        inline SIMDVec_u() {}

        inline explicit SIMDVec_u(uint32_t i) {
            mVec[0] = i;
            mVec[1] = i;
        }

        // LOAD-CONSTR - Construct by loading from memory
        inline explicit SIMDVec_u(uint32_t const *p) {
            mVec[0] = p[0];
            mVec[1] = p[1];
        };

        inline SIMDVec_u(uint32_t i0, uint32_t i1)
        {
            mVec[0] = i0;
            mVec[1] = i1;
        }

        // EXTRACT
        inline uint32_t extract(uint32_t index) const {
            return mVec[index & 1];
        }

        // Override Access operators
        inline uint32_t operator[] (uint32_t index) const {
            return mVec[index & 1];
        }

        // Override Mask Access operators
        inline IntermediateMask<SIMDVec_u, SIMDVecMask<2>> operator[] (SIMDVecMask<2> const & mask) {
            return IntermediateMask<SIMDVec_u, SIMDVecMask<2>>(mask, static_cast<SIMDVec_u &>(*this));
        }

        // insert[] (scalar)
        inline SIMDVec_u & insert(uint32_t index, uint32_t value) {
            mVec[index & 1] = value;
            return *this;
        }

        // PREFINC
        inline SIMDVec_u & prefinc() {
            mVec[0]++;
            mVec[1]++;
            return *this;
        }

        // MPREFINC
        inline SIMDVec_u & prefinc(SIMDVecMask<2> const & mask) {
            if (mask[0] == true) mVec[0]++;
            if (mask[1] == true) mVec[1]++;
            return *this;
        }

        // UNIQUE
        inline bool unique() const {
            return mVec[0] != mVec[1];
        }

        // GATHERS
        inline SIMDVec_u & gather(uint32_t* baseAddr, uint64_t* indices) {
            mVec[0] = baseAddr[indices[0]];
            mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // MGATHERS
        inline SIMDVec_u & gather(SIMDVecMask<2> const & mask, uint32_t* baseAddr, uint64_t* indices) {
            if (mask[0] == true) mVec[0] = baseAddr[indices[0]];
            if (mask[1] == true) mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // GATHERV
        inline SIMDVec_u & gather(uint32_t* baseAddr, SIMDVec_u const & indices) {
            mVec[0] = baseAddr[indices[0]];
            mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // MGATHERV
        inline SIMDVec_u & gather(SIMDVecMask<2> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) {
            if (mask[0] == true) mVec[0] = baseAddr[indices[0]];
            if (mask[1] == true) mVec[1] = baseAddr[indices[1]];
            return *this;
        }
        // SCATTERS
        inline uint32_t* scatter(uint32_t* baseAddr, uint64_t* indices) {
            baseAddr[indices[0]] = mVec[0];
            baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }
        // MSCATTERS
        inline uint32_t* scatter(SIMDVecMask<2> const & mask, uint32_t* baseAddr, uint64_t* indices) {
            if (mask[0] == true) baseAddr[indices[0]] = mVec[0];
            if (mask[1] == true) baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }
        // SCATTERV
        inline uint32_t* scatter(uint32_t* baseAddr, SIMDVec_u const & indices) {
            baseAddr[indices[0]] = mVec[0];
            baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }
        // MSCATTERV
        inline uint32_t* scatter(SIMDVecMask<2> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) {
            if (mask[0] == true) baseAddr[indices[0]] = mVec[0];
            if (mask[1] == true) baseAddr[indices[1]] = mVec[1];
            return baseAddr;
        }

        // PACK
        // PACKLO
        // PACKHI
        // UNPACK
        inline void unpack(SIMDVec_u<uint32_t, 1> & a, SIMDVec_u<uint32_t, 1> & b) const {
            a.insert(0, mVec[0]);
            b.insert(0, mVec[1]);
        }
        // UNPACKLO
        // UNPACKHI

        // UTOI
        inline  operator SIMDVec_i<int32_t, 2> const (); // Definition is deferred until SIMDVec_i<int32_t,2> is defined
    };

}
}

#endif