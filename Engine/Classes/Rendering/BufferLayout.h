#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	enum class ShaderDataType : uint8
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4
	};
	
#define DataTypes		\
DefineCase(Float,  4)	\
DefineCase(Float2, 8)	\
DefineCase(Float3, 12)	\
DefineCase(Float4, 16)	\
DefineCase(Mat3,   36)	\
DefineCase(Mat4,   64)	\
DefineCase(Int,	   4)	\
DefineCase(Int2,   8)	\
DefineCase(Int3,   12)	\
DefineCase(Int4,   16)	

#define DefineCase(InType, Size) case ShaderDataType::##InType: return Size;

	static uint32 GetDataTypeSize(ShaderDataType Type)
	{
		switch (Type)
		{
			DataTypes

			default:
			{
				NoEntry();
				return -1;
			}
		}

		return -1;
	}

#undef DataTypes
#undef DefineCase

#define DataTypes		\
DefineCase(Float,  1)	\
DefineCase(Float2, 2)	\
DefineCase(Float3, 3)	\
DefineCase(Float4, 4)	\
DefineCase(Mat3,   3*3)	\
DefineCase(Mat4,   4*4)	\
DefineCase(Int,	   1)	\
DefineCase(Int2,   2)	\
DefineCase(Int3,   3)	\
DefineCase(Int4,   4)	

#define DefineCase(InType, Size) case ShaderDataType::##InType: return Size;

	struct BufferElements
	{
		String Name;
		uint32 Offset;
		uint32 Size;
		ShaderDataType Type;
		bool bNormalized;

		uint32 GetComponentCount() const
		{
			switch (Type)
			{
				DataTypes
			}

			return -1;
		}

		BufferElements(ShaderDataType Type, const String& Name, bool bNormalized = false)
		{
			this->Type = Type;
			this->Name = Name;
			Size = GetDataTypeSize(Type);
			Offset = 0;
			bNormalized = false;
		}
	};

#undef DataTypes
#undef DefineCase

	class BufferLayout
	{
	public:
		
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElements>& Element)
			: Elements(Element)
		{
			CalcOffsetsAndStride();
		}

		inline const std::vector<BufferElements>& GetElements() const { return Elements; }
		inline const uint32 GetStride() const { return Stride; }

		std::vector<BufferElements>::iterator begin() { return Elements.begin(); }
		std::vector<BufferElements>::iterator end() { return Elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return Elements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return Elements.end(); }

	private:

		void CalcOffsetsAndStride();
		
		std::vector<BufferElements> Elements;
		uint32 Stride = 0;
	};
}
