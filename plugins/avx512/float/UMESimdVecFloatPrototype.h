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

#ifndef UME_SIMD_VEC_FLOAT_PROTOTYPE_H_
#define UME_SIMD_VEC_FLOAT_PROTOTYPE_H_

#include <type_traits>
#include "../../../UMESimdInterface.h"
#include "../../UMESimdPluginScalarEmulation.h"
#include <immintrin.h>

#include "../UMESimdMaskAVX512.h"
#include "../UMESimdSwizzleAVX512.h"
#include "../UMESimdVecUintAVX512.h"

namespace UME {
namespace SIMD {

    template<typename SCALAR_FLOAT_TYPE, uint32_t VEC_LEN>
    struct SIMDVec_f_traits {
        // Generic trait class not containing type definition so that only correct explicit
        // type definitions are compiled correctly
    };

    // 32b vectors
    template<>
    struct SIMDVec_f_traits<float, 1> {
        typedef SIMDVec_u<uint32_t, 1> VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 1>  VEC_INT_TYPE;
        typedef int32_t                      SCALAR_INT_TYPE;
        typedef uint32_t                     SCALAR_UINT_TYPE;
        typedef float*                       SCALAR_TYPE_PTR;
        typedef SIMDVecMask<1>                    MASK_TYPE;
        typedef SIMDVecSwizzle<1>                 SWIZZLE_MASK_TYPE;
    };

    // 64b vectors
    template<>
    struct SIMDVec_f_traits<float, 2> {
        typedef SIMDVec_f<float, 1>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 2> VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 2>  VEC_INT_TYPE;
        typedef int32_t                      SCALAR_INT_TYPE;
        typedef uint32_t                     SCALAR_UINT_TYPE;
        typedef float*                       SCALAR_TYPE_PTR;
        typedef SIMDVecMask<2>                    MASK_TYPE;
        typedef SIMDVecSwizzle<2>                 SWIZZLE_MASK_TYPE;
    };

    template<>
    struct SIMDVec_f_traits<double, 1> {
        typedef SIMDVec_u<uint64_t, 1> VEC_UINT_TYPE;
        typedef SIMDVec_i<int64_t, 1>  VEC_INT_TYPE;
        typedef int64_t                      SCALAR_INT_TYPE;
        typedef uint64_t                     SCALAR_UINT_TYPE;
        typedef double*                      SCALAR_TYPE_PTR;
        typedef SIMDVecMask<1>                    MASK_TYPE;
        typedef SIMDVecSwizzle<1>                 SWIZZLE_MASK_TYPE;
    };

    // 128b vectors
    template<>
    struct SIMDVec_f_traits<float, 4> {
        typedef SIMDVec_f<float, 2>     HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 4>  VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 4>   VEC_INT_TYPE;
        typedef int32_t                       SCALAR_INT_TYPE;
        typedef uint32_t                      SCALAR_UINT_TYPE;
        typedef float*                        SCALAR_TYPE_PTR;
        typedef SIMDVecMask<4>                     MASK_TYPE;
        typedef SIMDVecSwizzle<4>                  SWIZZLE_MASK_TYPE;
    };

    template<>
    struct SIMDVec_f_traits<double, 2> {
        typedef SIMDVec_f<double, 1>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 2> VEC_UINT_TYPE;
        typedef SIMDVec_i<int64_t, 2>  VEC_INT_TYPE;
        typedef int64_t                      SCALAR_INT_TYPE;
        typedef uint64_t                     SCALAR_UINT_TYPE;
        typedef double*                      SCALAR_TYPE_PTR;
        typedef SIMDVecMask<2>                    MASK_TYPE;
        typedef SIMDVecSwizzle<2>                 SWIZZLE_MASK_TYPE;
    };

    // 256b vectors
    template<>
    struct SIMDVec_f_traits<float, 8> {
        typedef SIMDVec_f<float, 4>     HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 8>  VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 8>   VEC_INT_TYPE;
        typedef int32_t                       SCALAR_INT_TYPE;
        typedef uint32_t                      SCALAR_UINT_TYPE;
        typedef float*                        SCALAR_TYPE_PTR;
        typedef SIMDVecMask<8>                     MASK_TYPE;
        typedef SIMDVecSwizzle<8>                  SWIZZLE_MASK_TYPE;
    };

    template<>
    struct SIMDVec_f_traits<double, 4> {
        typedef SIMDVec_f<double, 2>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 4>  VEC_UINT_TYPE;
        typedef SIMDVec_i<int64_t, 4>   VEC_INT_TYPE;
        typedef int64_t                       SCALAR_INT_TYPE;
        typedef uint64_t                      SCALAR_UINT_TYPE;
        typedef double*                       SCALAR_TYPE_PTR;
        typedef SIMDVecMask<4>                     MASK_TYPE;
        typedef SIMDVecSwizzle<4>                  SWIZZLE_MASK_TYPE;
    };

    // 512b vectors
    template<>
    struct SIMDVec_f_traits<float, 16> {
        typedef SIMDVec_f<float, 8>     HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 16> VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 16>  VEC_INT_TYPE;
        typedef int32_t                       SCALAR_INT_TYPE;
        typedef uint32_t                      SCALAR_UINT_TYPE;
        typedef float*                        SCALAR_TYPE_PTR;
        typedef SIMDVecMask<16>                    MASK_TYPE;
        typedef SIMDVecSwizzle<16>                 SWIZZLE_MASK_TYPE;
    };

    template<>
    struct SIMDVec_f_traits<double, 8> {
        typedef SIMDVec_f<double, 4>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 8>  VEC_UINT_TYPE;
        typedef SIMDVec_i<int64_t, 8>   VEC_INT_TYPE;
        typedef int64_t                       SCALAR_INT_TYPE;
        typedef uint64_t                      SCALAR_UINT_TYPE;
        typedef double*                       SCALAR_TYPE_PTR;
        typedef SIMDVecMask<8>                     MASK_TYPE;
        typedef SIMDVecSwizzle<8>                  SWIZZLE_MASK_TYPE;
    };

    // 1024b vectors
    template<>
    struct SIMDVec_f_traits<float, 32> {
        typedef SIMDVec_f<float, 16>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 32>  VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 32>  VEC_INT_TYPE;
        typedef int32_t                       SCALAR_INT_TYPE;
        typedef uint32_t                      SCALAR_UINT_TYPE;
        typedef float*                        SCALAR_TYPE_PTR;
        typedef SIMDVecMask<32>                    MASK_TYPE;
        typedef SIMDVecSwizzle<32>                 SWIZZLE_MASK_TYPE;
    };

    template<>
    struct SIMDVec_f_traits<double, 16> {
        typedef SIMDVec_f<double, 8>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 16> VEC_UINT_TYPE;
        typedef SIMDVec_i<int64_t, 16>  VEC_INT_TYPE;
        typedef int64_t                       SCALAR_INT_TYPE;
        typedef uint64_t                      SCALAR_UINT_TYPE;
        typedef double*                       SCALAR_TYPE_PTR;
        typedef SIMDVecMask<16>                    MASK_TYPE;
        typedef SIMDVecSwizzle<16>                 SWIZZLE_MASK_TYPE;
    };

    template<typename SCALAR_FLOAT_TYPE, uint32_t VEC_LEN>
    class SIMDVec_f final :
        public SIMDVecFloatInterface<
        SIMDVec_f<SCALAR_FLOAT_TYPE, VEC_LEN>,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_UINT_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_INT_TYPE,
        SCALAR_FLOAT_TYPE,
        VEC_LEN,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::MASK_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::SWIZZLE_MASK_TYPE>,
        public SIMDVecPackableInterface<
        SIMDVec_f<SCALAR_FLOAT_TYPE, VEC_LEN>,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::HALF_LEN_VEC_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_FLOAT_TYPE, VEC_LEN>                         VEC_EMU_REG;

        typedef SIMDVec_f VEC_TYPE;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_UINT_TYPE    VEC_UINT_TYPE;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_INT_TYPE     VEC_INT_TYPE;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::MASK_TYPE MASK_TYPE;
    private:
        VEC_EMU_REG mVec;

    public:
        inline SIMDVec_f() : mVec() {};

        inline explicit SIMDVec_f(SCALAR_FLOAT_TYPE i) : mVec(i) {}

        // UTOF
        inline explicit SIMDVec_f(VEC_UINT_TYPE const & vecUint) {

        }

        // ITOF
        inline explicit SIMDVec_f(VEC_INT_TYPE const & vecInt) {

        }

        inline explicit SIMDVec_f(SCALAR_FLOAT_TYPE const *p) { this->load(p); }

        inline SIMDVec_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1) {
            mVec.insert(0, i0);  mVec.insert(1, i1);
        }

        inline SIMDVec_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1,
            SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3) {
            mVec.insert(0, i0);  mVec.insert(1, i1);
            mVec.insert(2, i2);  mVec.insert(3, i3);
        }

        inline SIMDVec_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1,
            SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3,
            SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5,
            SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7)
        {
            mVec.insert(0, i0);  mVec.insert(1, i1);
            mVec.insert(2, i2);  mVec.insert(3, i3);
            mVec.insert(4, i4);  mVec.insert(5, i5);
            mVec.insert(6, i6);  mVec.insert(7, i7);
        }

        inline SIMDVec_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1,
            SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3,
            SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5,
            SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7,
            SCALAR_FLOAT_TYPE i8, SCALAR_FLOAT_TYPE i9,
            SCALAR_FLOAT_TYPE i10, SCALAR_FLOAT_TYPE i11,
            SCALAR_FLOAT_TYPE i12, SCALAR_FLOAT_TYPE i13,
            SCALAR_FLOAT_TYPE i14, SCALAR_FLOAT_TYPE i15)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);
            mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);
            mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);
            mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);
            mVec.insert(14, i14);  mVec.insert(15, i15);
        }

        inline SIMDVec_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1,
            SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3,
            SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5,
            SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7,
            SCALAR_FLOAT_TYPE i8, SCALAR_FLOAT_TYPE i9,
            SCALAR_FLOAT_TYPE i10, SCALAR_FLOAT_TYPE i11,
            SCALAR_FLOAT_TYPE i12, SCALAR_FLOAT_TYPE i13,
            SCALAR_FLOAT_TYPE i14, SCALAR_FLOAT_TYPE i15,
            SCALAR_FLOAT_TYPE i16, SCALAR_FLOAT_TYPE i17,
            SCALAR_FLOAT_TYPE i18, SCALAR_FLOAT_TYPE i19,
            SCALAR_FLOAT_TYPE i20, SCALAR_FLOAT_TYPE i21,
            SCALAR_FLOAT_TYPE i22, SCALAR_FLOAT_TYPE i23,
            SCALAR_FLOAT_TYPE i24, SCALAR_FLOAT_TYPE i25,
            SCALAR_FLOAT_TYPE i26, SCALAR_FLOAT_TYPE i27,
            SCALAR_FLOAT_TYPE i28, SCALAR_FLOAT_TYPE i29,
            SCALAR_FLOAT_TYPE i30, SCALAR_FLOAT_TYPE i31)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);
            mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);
            mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);
            mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);
            mVec.insert(14, i14);  mVec.insert(15, i15);
            mVec.insert(16, i16);  mVec.insert(17, i17);
            mVec.insert(18, i18);  mVec.insert(19, i19);
            mVec.insert(20, i20);  mVec.insert(21, i21);
            mVec.insert(22, i22);  mVec.insert(23, i23);
            mVec.insert(24, i24);  mVec.insert(25, i25);
            mVec.insert(26, i26);  mVec.insert(27, i27);
            mVec.insert(28, i28);  mVec.insert(29, i29);
            mVec.insert(30, i30);  mVec.insert(31, i31);
        }

        // Override Access operators
        inline SCALAR_FLOAT_TYPE operator[] (uint32_t index) const {
            return mVec[index];
        }

        // Override Mask Access operators
        inline IntermediateMask<SIMDVec_f, MASK_TYPE> operator[] (MASK_TYPE & mask) {
            return IntermediateMask<SIMDVec_f, MASK_TYPE>(mask, static_cast<SIMDVec_f &>(*this));
        }

        // insert[] (scalar)
        inline SIMDVec_f & insert(uint32_t index, SCALAR_FLOAT_TYPE value) {
            mVec.insert(index, value);
            return *this;
        }
    };

    // ***************************************************************************
    // *
    // *    Partial specialization of floating point SIMD for VEC_LEN == 1.
    // *    This specialization is necessary to eliminate PACK operations from
    // *    being used on SIMD1 types.
    // *
    // ***************************************************************************
    template<typename SCALAR_FLOAT_TYPE>
    class SIMDVec_f<SCALAR_FLOAT_TYPE, 1> :
        public SIMDVecFloatInterface<
        SIMDVec_f<SCALAR_FLOAT_TYPE, 1>,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::VEC_UINT_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::VEC_INT_TYPE,
        SCALAR_FLOAT_TYPE,
        1,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::SCALAR_UINT_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::MASK_TYPE,
        typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::SWIZZLE_MASK_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_FLOAT_TYPE, 1>                         VEC_EMU_REG;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::MASK_TYPE MASK_TYPE;

        typedef SIMDVec_f VEC_TYPE;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::VEC_UINT_TYPE    VEC_UINT_TYPE;
        typedef typename SIMDVec_f_traits<SCALAR_FLOAT_TYPE, 1>::VEC_INT_TYPE     VEC_INT_TYPE;

    private:
        VEC_EMU_REG mVec;

    public:
        inline SIMDVec_f() : mVec() {};

        inline explicit SIMDVec_f(SCALAR_FLOAT_TYPE f) : mVec(f) {};

        // UTOF
        inline explicit SIMDVec_f(VEC_UINT_TYPE const & vecUint) {

        }

        // ITOF
        inline explicit SIMDVec_f(VEC_INT_TYPE const & vecInt) {

        }

        inline explicit SIMDVec_f(SCALAR_FLOAT_TYPE const *p) { this->load(p); }

        // Override Access operators
        inline SCALAR_FLOAT_TYPE operator[] (uint32_t index) const {
            return mVec[index];
        }

        // Override Mask Access operators
        inline IntermediateMask<SIMDVec_f, SIMDVecMask<1>> operator[] (SIMDVecMask<1> & mask) {
            return IntermediateMask<SIMDVec_f, SIMDVecMask<1>>(mask, static_cast<SIMDVec_f &>(*this));
        }

        // insert[] (scalar)
        inline SIMDVec_f & insert(uint32_t index, SCALAR_FLOAT_TYPE value) {
            mVec.insert(index, value);
            return *this;
        }
    };

}
}

#endif