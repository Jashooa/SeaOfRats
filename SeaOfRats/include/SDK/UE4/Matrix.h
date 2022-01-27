#pragma once

#include <emmintrin.h>

#include "Vector.h"

typedef __m128	VectorRegister;
typedef __m128i VectorRegisterInt;

#define SHUFFLEMASK(A0,A1,B2,B3) ( (A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6) )

#define VectorReplicate( Vec, ElementIndex ) _mm_shuffle_ps( Vec, Vec, SHUFFLEMASK(ElementIndex,ElementIndex,ElementIndex,ElementIndex) )
#define VectorMultiply( Vec1, Vec2 ) _mm_mul_ps( Vec1, Vec2 )
#define VectorMultiplyAdd( Vec1, Vec2, Vec3 ) _mm_add_ps( _mm_mul_ps(Vec1, Vec2), Vec3 )

namespace SDK
{
    // ScriptStruct CoreUObject.Matrix
    struct FMatrix
    {
        union
        {
            __declspec(align(16)) float M[4][4];
        };

        inline void VectorMatrixMultiply(void* Result, const void* Matrix1, const void* Matrix2)
        {
            const VectorRegister* A = (const VectorRegister*) Matrix1;
            const VectorRegister* B = (const VectorRegister*) Matrix2;
            VectorRegister* R = (VectorRegister*) Result;
            VectorRegister Temp, R0, R1, R2, R3;

            // First row of result (Matrix1[0] * Matrix2).
            Temp = VectorMultiply(VectorReplicate(A[0], 0), B[0]);
            Temp = VectorMultiplyAdd(VectorReplicate(A[0], 1), B[1], Temp);
            Temp = VectorMultiplyAdd(VectorReplicate(A[0], 2), B[2], Temp);
            R0 = VectorMultiplyAdd(VectorReplicate(A[0], 3), B[3], Temp);

            // Second row of result (Matrix1[1] * Matrix2).
            Temp = VectorMultiply(VectorReplicate(A[1], 0), B[0]);
            Temp = VectorMultiplyAdd(VectorReplicate(A[1], 1), B[1], Temp);
            Temp = VectorMultiplyAdd(VectorReplicate(A[1], 2), B[2], Temp);
            R1 = VectorMultiplyAdd(VectorReplicate(A[1], 3), B[3], Temp);

            // Third row of result (Matrix1[2] * Matrix2).
            Temp = VectorMultiply(VectorReplicate(A[2], 0), B[0]);
            Temp = VectorMultiplyAdd(VectorReplicate(A[2], 1), B[1], Temp);
            Temp = VectorMultiplyAdd(VectorReplicate(A[2], 2), B[2], Temp);
            R2 = VectorMultiplyAdd(VectorReplicate(A[2], 3), B[3], Temp);

            // Fourth row of result (Matrix1[3] * Matrix2).
            Temp = VectorMultiply(VectorReplicate(A[3], 0), B[0]);
            Temp = VectorMultiplyAdd(VectorReplicate(A[3], 1), B[1], Temp);
            Temp = VectorMultiplyAdd(VectorReplicate(A[3], 2), B[2], Temp);
            R3 = VectorMultiplyAdd(VectorReplicate(A[3], 3), B[3], Temp);

            // Store result
            R[0] = R0;
            R[1] = R1;
            R[2] = R2;
            R[3] = R3;
        }

        inline FMatrix operator*(const FMatrix& Other)
        {
            FMatrix Result;
            VectorMatrixMultiply(&Result, this, &Other);
            return Result;
        }

        inline FVector GetOrigin() const
        {
            return FVector(M[3][0], M[3][1], M[3][2]);
        }
    };
}
