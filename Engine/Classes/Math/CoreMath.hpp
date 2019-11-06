#pragma once

#include "CoreMinimal.h"

/* Some of these defines are taken from math.h found inside of the Windows 10 SDK.
 * They were copied here to avoid dependencies on Windows platform includes.
 * And to allow easier porting to other systems.
 * */

#ifndef M_PI
#define M_PI				3.14159265358979323846264338327950288	/* pi */
#endif
#ifndef M_PIF
#define M_PIF				3.14159265358979323846264338327950288f  /* float pi */
#endif
#ifndef M_2_PI
#define M_2_PI				6.283185307179586476925286766559		/* 2 * pi */
#endif
#ifndef M_2_PIF
#define M_2_PIF				6.283185307179586476925286766559F		/* 2 * pi */
#endif
#ifndef M_4_PI
#define M_4_PI				12.566370614359172953850573533118		/* 4 * pi */
#endif
#ifndef M_4_PIF
#define M_4_PIF				12.566370614359172953850573533118f		/* 4 * pi */
#endif
#ifndef M_PI_2
#define M_PI_2				1.5707963267948966192313216916398		/* pi / 2 */
#endif
#ifndef M_PI_2F
#define M_PI_2F				1.5707963267948966192313216916398f		/* pi / 2 */
#endif
#ifndef M_PI_4
#define M_PI_4				0.78539816339744830961566084581988		/* pi / 4 */
#endif
#ifndef M_PI_4F
#define M_PI_4F				0.78539816339744830961566084581988f		/* pi / 4 */
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI			1.12837916709551257390					/* 2/sqrt(pi) */
#endif
#ifndef M_E
#define M_E					2.71828182845904523536					/* e */
#endif
#ifndef M_LOG2E
#define M_LOG2E				1.44269504088896340736					/* log2(e) */
#endif
#ifndef M_LOG10E
#define M_LOG10E			0.434294481903251827651					/* log10(e) */
#endif
#ifndef SMALLER_NUMBER
#define SMALLER_NUMBER		1.e-8f									/* 0.00000001 */
#endif
#ifndef SMALL_NUMBER
#define SMALL_NUMBER		1.e-4f									/* 0.0001 */
#endif
#ifndef LARGE_NUMBER
#define LARGE_NUMBER		3.4e+38f								/* 340000000000000000000000000000000000000 */
#endif
#ifndef MAX_FLOAT
#define MAX_FLOAT			3.402823466e+38F						/* Largest float; source float.h */
#endif
#ifndef M_SQRT2
#define M_SQRT2				1.41421356237309504880					/* sqrt(2) */
#endif
#ifndef DELTA
#define DELTA				0.00001f								/* Magic number for delta, used for numerical precision */
#endif

/* @todo(chrisr): implement a math helper struct so we don't have to use glm */

inline namespace MARS{
inline namespace MATH
{
	struct OrthoGraphicMatrix
	{
		float Left, Right, Top, Bottom, Near, Far;
	
		OrthoGraphicMatrix()
			: Left(0), Right(0), Top(0), Bottom(0), Near(0), Far(0)
		{}
	
		OrthoGraphicMatrix(float InLeft, float InRight, float InTop, float InBottom, float InNear, float InFar)
			: Left(InLeft), Right(InRight), Top(InTop), Bottom(InBottom), Near(InNear), Far(InFar)
		{}
	};
	
	struct Math
	{
		static FORCEINLINE float Sin(float  Val)			{	return sinf(Val);	}
		static FORCEINLINE float ASin(float Val)			{	return asinf(Val);	}
		static FORCEINLINE float Sinh(float Val)			{	return sinh(Val);	}
		static FORCEINLINE float Cos(float  Val)			{	return cos(Val);	}
		static FORCEINLINE float ACos(float Val)			{	return acos(Val);	}
		static FORCEINLINE float Tan(float  Val)			{	return tan(Val);	}
		static FORCEINLINE float ATan(float Val)			{	return atan(Val);	}
		static FORCEINLINE float Sqrt(float Val)			{	return sqrtf(Val);	}
		static FORCEINLINE float Pow(float  A, float B)		{	return powf(A, B);	}

		static constexpr FORCEINLINE int32 TruncToInt(float In) { return (int32)In; }
		static constexpr FORCEINLINE float TruncToFloat(float In) { return (float)TruncToInt(In); }
		static FORCEINLINE float FloorToInt(float In) { return floorf(In); }

		template<typename Type> 
		static constexpr FORCEINLINE Type Min(const Type A, const Type B) { return (A <= B) ? A : B; }

		template<typename Type> 
		static constexpr FORCEINLINE Type Max(const Type A, const Type B) { return (A >= B) ? A : B; }

		template<typename Type> 
		static constexpr FORCEINLINE Type Abs(const Type A) { return (A >= (Type)0) ? A : -A; }

		template<typename Type> 
		static constexpr FORCEINLINE Type Sign(const Type A) { return (A > (Type)0) ? (Type)1 : ((A < (Type)0)) ? (Type)-1 : (Type)0; }

		template<typename Type> 
		static constexpr FORCEINLINE Type Clamp(const Type InX, const Type InMin, const Type InMax) { return InX <= InMax ? (InX >= InMin ? InX : InX = InMin) : InX = InMax; }
	};
}}