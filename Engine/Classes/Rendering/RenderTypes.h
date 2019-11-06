#pragma once

#include "CoreMinimal.h"
#include "Math\CoreMath.hpp"

inline namespace MARS
{
	enum class GraphicsAPI : uint8
	{
		None = 0,
		OpenGL,
		DirectX11,
		DirectX12,
		Vulkan,
	
		MAX = 255,
	};
	
	struct Color;

	struct LinearColor
	{
		float R, G, B, A;

		static double ColorToLinearColor_Pow22[256];
		static double ColorToLinearColor_sRGB[256];

		FORCEINLINE LinearColor() : R(0), G(0), B(0), A(0) { }
		FORCEINLINE explicit LinearColor(DEFAULT_CONSTRUCT) : R(0.f), G(0.f), B(0.f), A(0.f) { }
		constexpr FORCEINLINE LinearColor(float InR, float InG, float InB, float InA = 1.f) : R(InR), G(InG), B(InB), A(InA) { }
		LinearColor(const Color& InColor);
		static LinearColor FromsRGB(const Color& InColor);
		static LinearColor FromPow22Color(const Color& InColor);
		Color ToColor() const;

		FORCEINLINE const float& operator[](const int32& Index)
		{
			return (&R)[Index];
		}

		FORCEINLINE LinearColor operator+(const LinearColor& Other) const
		{
			return LinearColor(	
			this->R	+ Other.R,
			this->G	+ Other.G,
			this->B	+ Other.B,
			this->A	+ Other.A);
		}

		FORCEINLINE LinearColor operator+=(const LinearColor& Other)
		{
			R += Other.R;
			G += Other.G;
			B += Other.B;
			A += Other.A;
			return *this;
		}

		FORCEINLINE LinearColor operator-(const LinearColor& Other) const
		{
			return LinearColor(	
			this->R - Other.R,
			this->G - Other.G,
			this->B - Other.B,
			this->A - Other.A);
		}

		FORCEINLINE LinearColor operator-=(const LinearColor& Other)
		{
			R -= Other.R;
			G -= Other.G;
			B -= Other.B;
			A -= Other.A;
			return *this;
		}

		FORCEINLINE LinearColor operator*(const LinearColor& Other) const
		{
			return LinearColor(	
			this->R * Other.R,
			this->G * Other.G,
			this->B * Other.B,
			this->A * Other.A);
		}

		FORCEINLINE LinearColor operator*=(const LinearColor& Other)
		{
			R *= Other.R;
			G *= Other.G;
			B *= Other.B;
			A *= Other.A;
			return *this;
		}

		FORCEINLINE LinearColor operator/(const LinearColor& Other) const
		{
			return LinearColor(	
			this->R / Other.R,
			this->G / Other.G,
			this->B / Other.B,
			this->A / Other.A);
		}

		FORCEINLINE LinearColor operator/=(const LinearColor& Other)
		{
			R /= Other.R;
			G /= Other.G;
			B /= Other.B;
			A /= Other.A;
			return *this;
		}

		FORCEINLINE LinearColor operator*(float Scalar) const
		{
			return LinearColor(	
			this->R * Scalar,
			this->G * Scalar,
			this->B * Scalar,
			this->A * Scalar);
		}

		FORCEINLINE LinearColor operator*=(float Scalar)
		{
			R *= Scalar;
			G *= Scalar;
			B *= Scalar;
			A *= Scalar;
			return *this;
		}

		FORCEINLINE LinearColor operator/(float Scalar) const
		{
			return LinearColor(
			this->R / Scalar,
			this->G / Scalar,
			this->B / Scalar,
			this->A / Scalar);
		}

		FORCEINLINE LinearColor operator/=(float Scalar)
		{
			R /= Scalar;
			G /= Scalar;
			B /= Scalar;
			A /= Scalar;
			return *this;
		}

		/*
		 *	Returns a new Linear Color clamped between 0 and 1
		 **/
		FORCEINLINE LinearColor Clamp(float Min = 0.f, float Max = 1.f) const
		{
			return LinearColor(
			glm::clamp(R, Min, Max),
			glm::clamp(G, Min, Max),
			glm::clamp(B, Min, Max),
			glm::clamp(A, Min, Max)
			);
		}

		FORCEINLINE bool operator==(const LinearColor& Other) const
		{
			return this->R == Other.R && this->G == Other.G && this->B == Other.B && this->A == Other.A;
		}

		FORCEINLINE bool operator!=(const LinearColor& Other) const
		{
			return this->R != Other.R || this->G != Other.G || this->B != Other.B || this->A != Other.A;
		}

		FORCEINLINE bool NearlyEqual(const LinearColor& Other, float Tolerance = SMALL_NUMBER)
		{
			return	glm::abs(this->R - Other.R) < Tolerance && 
					glm::abs(this->G - Other.G) < Tolerance && 
					glm::abs(this->B - Other.B) < Tolerance && 
					glm::abs(this->A - Other.A) < Tolerance;
		}

		FORCEINLINE LinearColor NewOpacity(float NewOp) const
		{
			LinearColor NewLinearColor = *this;
			NewLinearColor.A = NewOp;
			return NewLinearColor;
		}

		FORCEINLINE void PrintColor() const
		{
			Log::Get(LogTemp).Info("(R:{0}), (G:{1}), (B:{2}), (A:{3})", R, G, B, A);
		}

		FORCEINLINE String ToString() const
		{
			Unimplemented()
		}

		static const LinearColor White;
		static const LinearColor Black;
		static const LinearColor Red;
		static const LinearColor Green;
		static const LinearColor Blue;
		static const LinearColor Yellow;
		static const LinearColor Gray;
		static const LinearColor Transparent;
	};

	struct Color
	{
		union
		{
			struct
			{
				uint8 R, G, B, A;
			};
	
			uint32 Stride;
		};
	
		FORCEINLINE Color(Color&& Other) = default;
		FORCEINLINE Color(const Color& Other) = default;
		FORCEINLINE explicit Color(DEFAULT_CONSTRUCT) { R = G = B = A = 0; }
		constexpr FORCEINLINE Color(uint8 InR, uint8 InG, uint8 InB, uint8 InA = 255) : B(InB), G(InG), R(InR), A(InA) { } // Intel byte code order. Will require a non-intel version
		FORCEINLINE explicit Color(uint32 InColor)
		{
			R = G = B = InColor; A = 255;
			//ColorByteCode() = InColor;
		}
	
		uint32& ColorByteCode(void)
		{
			return *((uint32*)this);
		}
	
		const uint32& ColorByteCode(void) const
		{
			return *((uint32*)this);
		}
	
		FORCEINLINE bool operator==(const Color& Other)
		{
			return ColorByteCode() == Other.ColorByteCode();
		}
	
		FORCEINLINE bool operator!=(const Color& Other)
		{
			return ColorByteCode() != Other.ColorByteCode();
		}
	
		Color NewColorWithAlpha(uint8 Alpha) const
		{
			return Color(R, G, B, Alpha);
		}
	
		FORCEINLINE void PrintColor() const
		{
			Log::Get(LogTemp).Info("(R:{0}), (G:{1}), (B:{2}), (A:{3})", R, G, B, A);
		}

		FORCEINLINE String ToString() const
		{
			Unimplemented()
		}

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Transparent;
	
	};
}