#include "Rendering/API/RenderContext_DX11.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"Dxgi.lib")
#pragma comment(lib,"dxguid.lib")

#include <sstream>

using namespace MARS::GRAPHICS;

inline uint32 __ParseBindFlags(uint32 Val)
{
	uint32 _Flag = 0;

	if (Val & BIND_INDEX_BUFFER) _Flag |= D3D11_BIND_INDEX_BUFFER;
	if (Val & BIND_VERTEX_BUFFER) _Flag |= D3D11_BIND_VERTEX_BUFFER;
	if (Val & BIND_STREAM_OUTPUT) _Flag |= D3D11_BIND_STREAM_OUTPUT;
	if (Val & BIND_RENDER_TARGET) _Flag |= D3D11_BIND_RENDER_TARGET;
	if (Val & BIND_DEPTH_STENCIL) _Flag |= D3D11_BIND_DEPTH_STENCIL;
	if (Val & BIND_CONSTANT_BUFFER) _Flag |= D3D11_BIND_SHADER_RESOURCE;
	if (Val & BIND_UNORDERED_ACCESS) _Flag |= D3D11_BIND_UNORDERED_ACCESS;

	return _Flag;
}

inline uint32 __ParseCPUFlags(int32 Val) 
{
	uint32 _Flag = 0;

	if (Val & CPU_ACCESS_WRITE) _Flag |= D3D11_CPU_ACCESS_WRITE;
	if (Val & CPU_ACCESS_READ) _Flag |= D3D11_CPU_ACCESS_READ;

	return _Flag;
}

inline uint32 __ParseResourceFlags(uint32 Val)
{
	uint32 _Flag = 0;

	if (Val & RESOURCE_MISC_SHARED) _Flag |= D3D11_RESOURCE_MISC_SHARED;
	if (Val & RESOURCE_MISC_TEXTURECUBE) _Flag |= D3D11_RESOURCE_MISC_TEXTURECUBE;
	if (Val & RESOURCE_MISC_BUFFER_STRUCTURED) _Flag |= D3D11_RESOURCE_MISC_TILED;
	if (Val & RESOURCE_MISC_DRAWINDIRECT_ARGS) _Flag |= D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
	if (Val & RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) _Flag |= D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	if (Val & RESOURCE_MISC_TILED) _Flag |= D3D11_RESOURCE_MISC_TILED;

	return _Flag;
}

inline D3D11_FILTER __ConvertFilter(FILTER Val)
{
	switch (Val)
	{
		case FILTER_MIN_MAG_MIP_POINT: return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case FILTER_MIN_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_MIN_POINT_MAG_MIP_LINEAR: return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		case FILTER_MIN_LINEAR_MAG_MIP_POINT: return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		case FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case FILTER_MIN_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case FILTER_MIN_MAG_MIP_LINEAR: return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		case FILTER_ANISOTROPIC: return D3D11_FILTER_ANISOTROPIC;
		case FILTER_COMPARISON_MIN_MAG_MIP_POINT: return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		case FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR: return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
		case FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT: return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
		case FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		case FILTER_COMPARISON_MIN_MAG_MIP_LINEAR: return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		case FILTER_COMPARISON_ANISOTROPIC: return D3D11_FILTER_COMPARISON_ANISOTROPIC;
		case FILTER_MINIMUM_MIN_MAG_MIP_POINT: return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;
		case FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR: return D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR;
		case FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT: return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT;
		case FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT;
		case FILTER_MINIMUM_MIN_MAG_MIP_LINEAR: return D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR;
		case FILTER_MINIMUM_ANISOTROPIC: return D3D11_FILTER_MINIMUM_ANISOTROPIC;
		case FILTER_MAXIMUM_MIN_MAG_MIP_POINT: return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
		case FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR: return D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR;
		case FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT: return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT;
		case FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR: return D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT: return D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT;
		case FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR: return D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR;
		case FILTER_MAXIMUM_ANISOTROPIC: return D3D11_FILTER_MAXIMUM_ANISOTROPIC;
			
		default: break;
	}

	return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
}

inline D3D11_TEXTURE_ADDRESS_MODE __ConvertTextureAddress(TEXTURE_ADDRESS_MODE Val)
{
	switch (Val)
	{
		case TEXTURE_ADDRESS_WRAP: return D3D11_TEXTURE_ADDRESS_WRAP;
		case TEXTURE_ADDRESS_MIRROR: return D3D11_TEXTURE_ADDRESS_MIRROR;
		case TEXTURE_ADDRESS_CLAMP: return D3D11_TEXTURE_ADDRESS_CLAMP;
		case TEXTURE_ADDRESS_BORDER: return D3D11_TEXTURE_ADDRESS_BORDER;
		case TEXTURE_ADDRESS_MIRROR_ONCE: return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
		default: break;
	}

	return D3D11_TEXTURE_ADDRESS_WRAP;
}

inline D3D11_COMPARISON_FUNC __ConvertComparison(COMPARISON_FUNC Val)
{
	switch (Val)
	{
		case COMPARISON_NEVER: return D3D11_COMPARISON_NEVER;
		case COMPARISON_LESS: return D3D11_COMPARISON_LESS;
		case COMPARISON_EQUAL: return D3D11_COMPARISON_EQUAL;
		case COMPARISON_LESS_EQUAL: return D3D11_COMPARISON_LESS_EQUAL;
		case COMPARISON_GREATER: return D3D11_COMPARISON_GREATER;
		case COMPARISON_NOT_EQUAL: return D3D11_COMPARISON_NOT_EQUAL;
		case COMPARISON_GREATER_EQUAL: return D3D11_COMPARISON_GREATER_EQUAL;
		case COMPARISON_ALWAYS:	return D3D11_COMPARISON_ALWAYS;
		default: break;
	}

	return D3D11_COMPARISON_NEVER;
}

inline D3D11_FILL_MODE __ConvertFillMode(FILL_MODE Val)
{
	switch (Val)
	{
		case FILL_WIREFRAME: return D3D11_FILL_WIREFRAME;
		case FILL_SOLID: return D3D11_FILL_SOLID;
		default: break;
	}

	return D3D11_FILL_WIREFRAME;
}

inline D3D11_CULL_MODE __ConvertCullMode(CULL_MODE Val)
{
	switch (Val)
	{
		case CULL_NONE: return D3D11_CULL_NONE;
		case CULL_FRONT: return D3D11_CULL_FRONT;
		case CULL_BACK: return D3D11_CULL_BACK;
		default: break;
	}

	return D3D11_CULL_NONE;
}

inline D3D11_DEPTH_WRITE_MASK __ConvertDepthWriteMask(DEPTH_WRITE_MASK Val)
{
	switch (Val)
	{
		case DEPTH_WRITE_MASK_ZERO:	return D3D11_DEPTH_WRITE_MASK_ZERO;
		case DEPTH_WRITE_MASK_ALL: return D3D11_DEPTH_WRITE_MASK_ALL;
		default: break;
	}

	return D3D11_DEPTH_WRITE_MASK_ZERO;
}

inline D3D11_STENCIL_OP __ConvertStencilOp(STENCIL_OP Val)
{
	switch (Val)
	{
		case STENCIL_OP_KEEP: return D3D11_STENCIL_OP_KEEP;
		case STENCIL_OP_ZERO: return D3D11_STENCIL_OP_ZERO;
		case STENCIL_OP_REPLACE: return D3D11_STENCIL_OP_REPLACE;
		case STENCIL_OP_INCR_SAT: return D3D11_STENCIL_OP_INCR_SAT;
		case STENCIL_OP_DECR_SAT: return D3D11_STENCIL_OP_DECR_SAT;
		case STENCIL_OP_INVERT: return D3D11_STENCIL_OP_INVERT;
		case STENCIL_OP_INCR: return D3D11_STENCIL_OP_INCR;
		case STENCIL_OP_DECR: return D3D11_STENCIL_OP_DECR;
		default: break;
	}

	return D3D11_STENCIL_OP_KEEP;
}

inline D3D11_BLEND __ConvertBlend(BLEND Val)
{
	switch (Val)
	{
		case BLEND_ZERO: return D3D11_BLEND_ZERO;
		case BLEND_ONE: return D3D11_BLEND_ONE;
		case BLEND_SRC_COLOR: return D3D11_BLEND_SRC_COLOR;
		case BLEND_INV_SRC_COLOR: return D3D11_BLEND_INV_SRC_COLOR;
		case BLEND_SRC_ALPHA: return D3D11_BLEND_SRC_ALPHA;
		case BLEND_INV_SRC_ALPHA: return D3D11_BLEND_INV_SRC_ALPHA;
		case BLEND_DEST_ALPHA: return D3D11_BLEND_DEST_ALPHA;
		case BLEND_INV_DEST_ALPHA: return D3D11_BLEND_INV_DEST_ALPHA;
		case BLEND_DEST_COLOR: return D3D11_BLEND_DEST_COLOR;
		case BLEND_INV_DEST_COLOR: return D3D11_BLEND_INV_DEST_COLOR;
		case BLEND_SRC_ALPHA_SAT: return D3D11_BLEND_SRC_ALPHA_SAT;
		case BLEND_BLEND_FACTOR: return D3D11_BLEND_BLEND_FACTOR;
		case BLEND_INV_BLEND_FACTOR: return D3D11_BLEND_INV_BLEND_FACTOR;
		case BLEND_SRC1_COLOR: return D3D11_BLEND_SRC1_COLOR;
		case BLEND_INV_SRC1_COLOR: return D3D11_BLEND_INV_SRC1_COLOR;
		case BLEND_SRC1_ALPHA: return D3D11_BLEND_SRC1_ALPHA;
		case BLEND_INV_SRC1_ALPHA: return D3D11_BLEND_INV_SRC1_ALPHA;
		default: break;
	}

	return D3D11_BLEND_ZERO;
}

inline D3D11_BLEND_OP __ConvertBlendOp(BLEND_OP Val)
{
	switch (Val)
	{
		case BLEND_OP_ADD: return D3D11_BLEND_OP_ADD;
		case BLEND_OP_SUBTRACT:	return D3D11_BLEND_OP_SUBTRACT;
		case BLEND_OP_REV_SUBTRACT:	return D3D11_BLEND_OP_REV_SUBTRACT;
		case BLEND_OP_MIN: return D3D11_BLEND_OP_MIN;
		case BLEND_OP_MAX: return D3D11_BLEND_OP_MAX;
		default: break;
	}

	return D3D11_BLEND_OP_ADD;
}
inline D3D11_USAGE __ConvertUsage(USAGE Val)
{
	switch (Val)
	{
		case USAGE_DEFAULT:	return D3D11_USAGE_DEFAULT;
		case USAGE_IMMUTABLE: return D3D11_USAGE_IMMUTABLE;
		case USAGE_DYNAMIC: return D3D11_USAGE_DYNAMIC;
		case USAGE_STAGING: return D3D11_USAGE_STAGING;
		default: break;
	}

	return D3D11_USAGE_DEFAULT;
}

inline D3D11_INPUT_CLASSIFICATION __ConvertInputClassification(INPUT_CLASSIFICATION Val)
{
	switch (Val)
	{
		case INPUT_PER_VERTEX_DATA: return D3D11_INPUT_PER_VERTEX_DATA;
		case INPUT_PER_INSTANCE_DATA: return D3D11_INPUT_PER_INSTANCE_DATA;
		default: break;
	}

	return D3D11_INPUT_PER_VERTEX_DATA;
}

inline DXGI_FORMAT __ConvertFormat(FORMAT Val)
{
	switch (Val)
	{
		case FORMAT_R32G32B32A32_TYPELESS: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
		case FORMAT_R32G32B32A32_FLOAT:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case FORMAT_R32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
		case FORMAT_R32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
		case FORMAT_R32G32B32_TYPELESS: return DXGI_FORMAT_R32G32B32_TYPELESS;
		case FORMAT_R32G32B32_FLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
		case FORMAT_R32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
		case FORMAT_R32G32B32_SINT:	return DXGI_FORMAT_R32G32B32_SINT;
		case FORMAT_R16G16B16A16_TYPELESS: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
		case FORMAT_R16G16B16A16_FLOAT:	return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case FORMAT_R16G16B16A16_UNORM:	return DXGI_FORMAT_R16G16B16A16_UNORM;
		case FORMAT_R16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
		case FORMAT_R16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
		case FORMAT_R16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
		case FORMAT_R32G32_TYPELESS: return DXGI_FORMAT_R32G32_TYPELESS;
		case FORMAT_R32G32_FLOAT: return DXGI_FORMAT_R32G32_FLOAT;
		case FORMAT_R32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
		case FORMAT_R32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
		case FORMAT_R32G8X24_TYPELESS: return DXGI_FORMAT_R32G8X24_TYPELESS;
		case FORMAT_D32_FLOAT_S8X24_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case FORMAT_R32_FLOAT_X8X24_TYPELESS: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case FORMAT_X32_TYPELESS_G8X24_UINT: return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
		case FORMAT_R10G10B10A2_TYPELESS: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case FORMAT_R10G10B10A2_UNORM: return DXGI_FORMAT_R10G10B10A2_UNORM;
		case FORMAT_R10G10B10A2_UINT: return DXGI_FORMAT_R10G10B10A2_UINT;
		case FORMAT_R11G11B10_FLOAT: return DXGI_FORMAT_R11G11B10_FLOAT;
		case FORMAT_R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
		case FORMAT_R8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case FORMAT_R8G8B8A8_UNORM_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case FORMAT_R8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
		case FORMAT_R8G8B8A8_SNORM:	return DXGI_FORMAT_R8G8B8A8_SNORM;
		case FORMAT_R8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
		case FORMAT_R16G16_TYPELESS: return DXGI_FORMAT_R16G16_TYPELESS;
		case FORMAT_R16G16_FLOAT: return DXGI_FORMAT_R16G16_FLOAT;
		case FORMAT_R16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
		case FORMAT_R16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
		case FORMAT_R16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
		case FORMAT_R16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
		case FORMAT_R32_TYPELESS: return DXGI_FORMAT_R32_TYPELESS;
		case FORMAT_D32_FLOAT: return DXGI_FORMAT_D32_FLOAT;
		case FORMAT_R32_FLOAT: return DXGI_FORMAT_R32_FLOAT;
		case FORMAT_R32_UINT: return DXGI_FORMAT_R32_UINT;
		case FORMAT_R32_SINT: return DXGI_FORMAT_R32_SINT;
		case FORMAT_R24G8_TYPELESS: return DXGI_FORMAT_R24G8_TYPELESS;
		case FORMAT_D24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case FORMAT_R24_UNORM_X8_TYPELESS: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case FORMAT_X24_TYPELESS_G8_UINT: return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
		case FORMAT_R8G8_TYPELESS: return DXGI_FORMAT_R8G8_TYPELESS;
		case FORMAT_R8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
		case FORMAT_R8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
		case FORMAT_R8G8_SNORM:	return DXGI_FORMAT_R8G8_SNORM;
		case FORMAT_R8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
		case FORMAT_R16_TYPELESS: return DXGI_FORMAT_R16_TYPELESS;
		case FORMAT_R16_FLOAT: return DXGI_FORMAT_R16_FLOAT;
		case FORMAT_D16_UNORM: return DXGI_FORMAT_D16_UNORM;
		case FORMAT_R16_UNORM: return DXGI_FORMAT_R16_UNORM;
		case FORMAT_R16_UINT: return DXGI_FORMAT_R16_UINT;
		case FORMAT_R16_SNORM: return DXGI_FORMAT_R16_SNORM;
		case FORMAT_R16_SINT: return DXGI_FORMAT_R16_SINT;
		case FORMAT_R8_TYPELESS: return DXGI_FORMAT_R8_TYPELESS;
		case FORMAT_R8_UNORM: return DXGI_FORMAT_R8_UNORM;
		case FORMAT_R8_UINT: return DXGI_FORMAT_R8_UINT;
		case FORMAT_R8_SNORM: return DXGI_FORMAT_R8_SNORM;
		case FORMAT_R8_SINT: return DXGI_FORMAT_R8_SINT;
		case FORMAT_A8_UNORM: return DXGI_FORMAT_A8_UNORM;
		case FORMAT_R1_UNORM: return DXGI_FORMAT_R1_UNORM;
		case FORMAT_R9G9B9E5_SHAREDEXP: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
		case FORMAT_R8G8_B8G8_UNORM: return DXGI_FORMAT_R8G8_B8G8_UNORM;
		case FORMAT_G8R8_G8B8_UNORM: return DXGI_FORMAT_G8R8_G8B8_UNORM;
		case FORMAT_BC1_TYPELESS: return DXGI_FORMAT_BC1_TYPELESS;
		case FORMAT_BC1_UNORM: return DXGI_FORMAT_BC1_UNORM;
		case FORMAT_BC1_UNORM_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
		case FORMAT_BC2_TYPELESS: return DXGI_FORMAT_BC2_TYPELESS;
		case FORMAT_BC2_UNORM: return DXGI_FORMAT_BC2_UNORM;
		case FORMAT_BC2_UNORM_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;
		case FORMAT_BC3_TYPELESS: return DXGI_FORMAT_BC3_TYPELESS;
		case FORMAT_BC3_UNORM: return DXGI_FORMAT_BC3_UNORM;
		case FORMAT_BC3_UNORM_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
		case FORMAT_BC4_TYPELESS: return DXGI_FORMAT_BC4_TYPELESS;
		case FORMAT_BC4_UNORM: return DXGI_FORMAT_BC4_UNORM;
		case FORMAT_BC4_SNORM: return DXGI_FORMAT_BC4_SNORM;
		case FORMAT_BC5_TYPELESS: return DXGI_FORMAT_BC5_TYPELESS;
		case FORMAT_BC5_UNORM: return DXGI_FORMAT_BC5_UNORM;
		case FORMAT_BC5_SNORM: return DXGI_FORMAT_BC5_SNORM;
		case FORMAT_B5G6R5_UNORM: return DXGI_FORMAT_B5G6R5_UNORM;
		case FORMAT_B5G5R5A1_UNORM: return DXGI_FORMAT_B5G5R5A1_UNORM;
		case FORMAT_B8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case FORMAT_B8G8R8X8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
		case FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
		case FORMAT_B8G8R8A8_TYPELESS: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case FORMAT_B8G8R8A8_UNORM_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case FORMAT_B8G8R8X8_TYPELESS: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case FORMAT_B8G8R8X8_UNORM_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case FORMAT_BC6H_TYPELESS: return DXGI_FORMAT_BC6H_TYPELESS;
		case FORMAT_BC6H_UF16: return DXGI_FORMAT_BC6H_UF16;
		case FORMAT_BC6H_SF16: return DXGI_FORMAT_BC6H_SF16;
		case FORMAT_BC7_TYPELESS: return DXGI_FORMAT_BC7_TYPELESS;
		case FORMAT_BC7_UNORM: return DXGI_FORMAT_BC7_UNORM;
		case FORMAT_BC7_UNORM_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;
		case FORMAT_AYUV: return DXGI_FORMAT_AYUV;
		case FORMAT_Y410: return DXGI_FORMAT_Y410;
		case FORMAT_Y416: return DXGI_FORMAT_Y416;
		case FORMAT_NV12: return DXGI_FORMAT_NV12;
		case FORMAT_P010: return DXGI_FORMAT_P010;
		case FORMAT_P016: return DXGI_FORMAT_P016;
		case FORMAT_420_OPAQUE: return DXGI_FORMAT_420_OPAQUE;
		case FORMAT_YUY2: return DXGI_FORMAT_YUY2;
		case FORMAT_Y210: return DXGI_FORMAT_Y210;
		case FORMAT_Y216: return DXGI_FORMAT_Y216;
		case FORMAT_NV11: return DXGI_FORMAT_NV11;
		case FORMAT_AI44: return DXGI_FORMAT_AI44;
		case FORMAT_IA44: return DXGI_FORMAT_IA44;
		case FORMAT_UNKNOWN: return DXGI_FORMAT_UNKNOWN;
		case FORMAT_P8:	return DXGI_FORMAT_P8;
		case FORMAT_A8P8: return DXGI_FORMAT_A8P8;
		case FORMAT_B4G4R4A4_UNORM:	return DXGI_FORMAT_B4G4R4A4_UNORM;
		case FORMAT_FORCE_UINT:	return DXGI_FORMAT_FORCE_UINT;
		default: break;
	}

	return DXGI_FORMAT_UNKNOWN;
}

inline D3D11_TEXTURE1D_DESC __ConvertTextureDesc1D(const TextureDesc* Desc)
{
	D3D11_TEXTURE1D_DESC _Desc;
	_Desc.Width = Desc->Width;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.ArraySize = Desc->ArraySize;
	_Desc.Format = __ConvertFormat(Desc->Format);
	_Desc.Usage = __ConvertUsage(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUFlags(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceFlags(Desc->MiscFlags);

	return _Desc;
}

inline D3D11_TEXTURE2D_DESC __ConvertTextureDesc2D(const TextureDesc* Desc)
{
	D3D11_TEXTURE2D_DESC _Desc;
	_Desc.Width = Desc->Width;
	_Desc.Height = Desc->Height;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.ArraySize = Desc->ArraySize;
	_Desc.Format = __ConvertFormat(Desc->Format);
	_Desc.SampleDesc.Count = Desc->SampleDesc.Count;
	_Desc.SampleDesc.Quality = Desc->SampleDesc.Quality;
	_Desc.Usage = __ConvertUsage(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUFlags(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceFlags(Desc->MiscFlags);

	return _Desc;
}

inline D3D11_TEXTURE3D_DESC __ConvertTextureDesc3D(const TextureDesc* Desc)
{
	D3D11_TEXTURE3D_DESC _Desc;
	_Desc.Width = Desc->Width;
	_Desc.Height = Desc->Height;
	_Desc.Depth = Desc->Depth;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.Format = __ConvertFormat(Desc->Format);
	_Desc.Usage = __ConvertUsage(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUFlags(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceFlags(Desc->MiscFlags);

	return _Desc;
}

inline D3D11_SUBRESOURCE_DATA __ConvertSubresourceData(const SubresourceData& InitialData)
{
	D3D11_SUBRESOURCE_DATA _Data;
	_Data.pSysMem = InitialData.pSysMem;
	_Data.SysMemPitch = InitialData.SysMemPitch;
	_Data.SysMemSlicePitch = InitialData.SysMemSlicePitch;

	return _Data;
}

inline uint32 __ParseBindFlags_Inv(uint32 Val)
{
	uint32 _Flag = 0;

	if (Val & D3D11_BIND_VERTEX_BUFFER) _Flag |= BIND_VERTEX_BUFFER;
	if (Val & D3D11_BIND_INDEX_BUFFER) _Flag |= BIND_INDEX_BUFFER;
	if (Val & D3D11_BIND_CONSTANT_BUFFER) _Flag |= BIND_CONSTANT_BUFFER;
	if (Val & D3D11_BIND_SHADER_RESOURCE) _Flag |= BIND_SHADER_RESOURCE;
	if (Val & D3D11_BIND_STREAM_OUTPUT) _Flag |= BIND_STREAM_OUTPUT;
	if (Val & D3D11_BIND_RENDER_TARGET) _Flag |= BIND_RENDER_TARGET;
	if (Val & D3D11_BIND_DEPTH_STENCIL) _Flag |= BIND_DEPTH_STENCIL;
	if (Val & D3D11_BIND_UNORDERED_ACCESS) _Flag |= BIND_UNORDERED_ACCESS;

	return _Flag;
}

inline uint32 __ParseCPUAccessFlags_Inv(uint32 Val)
{
	uint32 _Flag = 0;

	if (Val & D3D11_CPU_ACCESS_WRITE) _Flag |= CPU_ACCESS_WRITE;
	if (Val & D3D11_CPU_ACCESS_READ) _Flag |= CPU_ACCESS_READ;

	return _Flag;
}
inline uint32 __ParseResourceMiscFlags_Inv(uint32 Val)
{
	uint32 _Flag = 0;

	if (Val & D3D11_RESOURCE_MISC_SHARED) _Flag |= RESOURCE_MISC_SHARED;
	if (Val & D3D11_RESOURCE_MISC_TEXTURECUBE) _Flag |= RESOURCE_MISC_TEXTURECUBE;
	if (Val & D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS) _Flag |= RESOURCE_MISC_DRAWINDIRECT_ARGS;
	if (Val & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) _Flag |= RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	if (Val & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) _Flag |= RESOURCE_MISC_BUFFER_STRUCTURED;
	if (Val & D3D11_RESOURCE_MISC_TILED) _Flag |= RESOURCE_MISC_TILED;

	return _Flag;
}

inline FORMAT __ConvertFormat_Inv(DXGI_FORMAT Val)
{
	switch (Val)
	{
		case DXGI_FORMAT_UNKNOWN: return FORMAT_UNKNOWN;
		case DXGI_FORMAT_R32G32B32A32_TYPELESS: return FORMAT_R32G32B32A32_TYPELESS;
		case DXGI_FORMAT_R32G32B32A32_FLOAT: return FORMAT_R32G32B32A32_FLOAT;
		case DXGI_FORMAT_R32G32B32A32_UINT:	return FORMAT_R32G32B32A32_UINT;
		case DXGI_FORMAT_R32G32B32A32_SINT:	return FORMAT_R32G32B32A32_SINT;
		case DXGI_FORMAT_R32G32B32_TYPELESS: return FORMAT_R32G32B32_TYPELESS;
		case DXGI_FORMAT_R32G32B32_FLOAT: return FORMAT_R32G32B32_FLOAT;
		case DXGI_FORMAT_R32G32B32_UINT: return FORMAT_R32G32B32_UINT;
		case DXGI_FORMAT_R32G32B32_SINT: return FORMAT_R32G32B32_SINT;
		case DXGI_FORMAT_R16G16B16A16_TYPELESS: return FORMAT_R16G16B16A16_TYPELESS;
		case DXGI_FORMAT_R16G16B16A16_FLOAT: return FORMAT_R16G16B16A16_FLOAT;
		case DXGI_FORMAT_R16G16B16A16_UNORM: return FORMAT_R16G16B16A16_UNORM;
		case DXGI_FORMAT_R16G16B16A16_UINT: return FORMAT_R16G16B16A16_UINT;
		case DXGI_FORMAT_R16G16B16A16_SNORM: return FORMAT_R16G16B16A16_SNORM;
		case DXGI_FORMAT_R16G16B16A16_SINT: return FORMAT_R16G16B16A16_SINT;
		case DXGI_FORMAT_R32G32_TYPELESS: return FORMAT_R32G32_TYPELESS;
		case DXGI_FORMAT_R32G32_FLOAT: return FORMAT_R32G32_FLOAT;
		case DXGI_FORMAT_R32G32_UINT: return FORMAT_R32G32_UINT;
		case DXGI_FORMAT_R32G32_SINT: return FORMAT_R32G32_SINT;
		case DXGI_FORMAT_R32G8X24_TYPELESS: return FORMAT_R32G8X24_TYPELESS;
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT: return FORMAT_D32_FLOAT_S8X24_UINT;
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS: return FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT: return FORMAT_X32_TYPELESS_G8X24_UINT;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS: return FORMAT_R10G10B10A2_TYPELESS;
		case DXGI_FORMAT_R10G10B10A2_UNORM:	return FORMAT_R10G10B10A2_UNORM;
		case DXGI_FORMAT_R10G10B10A2_UINT: return FORMAT_R10G10B10A2_UINT;
		case DXGI_FORMAT_R11G11B10_FLOAT: return FORMAT_R11G11B10_FLOAT;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:	return FORMAT_R8G8B8A8_TYPELESS;
		case DXGI_FORMAT_R8G8B8A8_UNORM: return FORMAT_R8G8B8A8_UNORM;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB: return FORMAT_R8G8B8A8_UNORM_SRGB;
		case DXGI_FORMAT_R8G8B8A8_UINT: return FORMAT_R8G8B8A8_UINT;
		case DXGI_FORMAT_R8G8B8A8_SNORM: return FORMAT_R8G8B8A8_SNORM;
		case DXGI_FORMAT_R8G8B8A8_SINT:	return FORMAT_R8G8B8A8_SINT;
		case DXGI_FORMAT_R16G16_TYPELESS: return FORMAT_R16G16_TYPELESS;
		case DXGI_FORMAT_R16G16_FLOAT: return FORMAT_R16G16_FLOAT;
		case DXGI_FORMAT_R16G16_UNORM: return FORMAT_R16G16_UNORM;
		case DXGI_FORMAT_R16G16_UINT: return FORMAT_R16G16_UINT;
		case DXGI_FORMAT_R16G16_SNORM: return FORMAT_R16G16_SNORM;
		case DXGI_FORMAT_R16G16_SINT: return FORMAT_R16G16_SINT;
		case DXGI_FORMAT_R32_TYPELESS: return FORMAT_R32_TYPELESS;
		case DXGI_FORMAT_D32_FLOAT:	return FORMAT_D32_FLOAT;
		case DXGI_FORMAT_R32_FLOAT: return FORMAT_R32_FLOAT;
		case DXGI_FORMAT_R32_UINT: return FORMAT_R32_UINT;
		case DXGI_FORMAT_R32_SINT: return FORMAT_R32_SINT;
		case DXGI_FORMAT_R24G8_TYPELESS: return FORMAT_R24G8_TYPELESS;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:	return FORMAT_D24_UNORM_S8_UINT;
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:	return FORMAT_R24_UNORM_X8_TYPELESS;
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT: return FORMAT_X24_TYPELESS_G8_UINT;
		case DXGI_FORMAT_R8G8_TYPELESS: return FORMAT_R8G8_TYPELESS;
		case DXGI_FORMAT_R8G8_UNORM: return FORMAT_R8G8_UNORM;
		case DXGI_FORMAT_R8G8_UINT:	return FORMAT_R8G8_UINT;
		case DXGI_FORMAT_R8G8_SNORM: return FORMAT_R8G8_SNORM;
		case DXGI_FORMAT_R8G8_SINT:	return FORMAT_R8G8_SINT;
		case DXGI_FORMAT_R16_TYPELESS: return FORMAT_R16_TYPELESS;
		case DXGI_FORMAT_R16_FLOAT:	return FORMAT_R16_FLOAT;
		case DXGI_FORMAT_D16_UNORM:	return FORMAT_D16_UNORM;
		case DXGI_FORMAT_R16_UNORM:	return FORMAT_R16_UNORM;
		case DXGI_FORMAT_R16_UINT: return FORMAT_R16_UINT;
		case DXGI_FORMAT_R16_SNORM:	return FORMAT_R16_SNORM;
		case DXGI_FORMAT_R16_SINT: return FORMAT_R16_SINT;
		case DXGI_FORMAT_R8_TYPELESS: return FORMAT_R8_TYPELESS;
		case DXGI_FORMAT_R8_UNORM: return FORMAT_R8_UNORM;
		case DXGI_FORMAT_R8_UINT: return FORMAT_R8_UINT;
		case DXGI_FORMAT_R8_SNORM: return FORMAT_R8_SNORM;
		case DXGI_FORMAT_R8_SINT: return FORMAT_R8_SINT;
		case DXGI_FORMAT_A8_UNORM: return FORMAT_A8_UNORM;
		case DXGI_FORMAT_R1_UNORM: return FORMAT_R1_UNORM;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP: return FORMAT_R9G9B9E5_SHAREDEXP;
		case DXGI_FORMAT_R8G8_B8G8_UNORM: return FORMAT_R8G8_B8G8_UNORM;
		case DXGI_FORMAT_G8R8_G8B8_UNORM: return FORMAT_G8R8_G8B8_UNORM;
		case DXGI_FORMAT_BC1_TYPELESS: return FORMAT_BC1_TYPELESS;
		case DXGI_FORMAT_BC1_UNORM:	return FORMAT_BC1_UNORM;
		case DXGI_FORMAT_BC1_UNORM_SRGB: return FORMAT_BC1_UNORM_SRGB;
		case DXGI_FORMAT_BC2_TYPELESS: return FORMAT_BC2_TYPELESS;
		case DXGI_FORMAT_BC2_UNORM:	return FORMAT_BC2_UNORM;
		case DXGI_FORMAT_BC2_UNORM_SRGB: return FORMAT_BC2_UNORM_SRGB;
		case DXGI_FORMAT_BC3_TYPELESS: return FORMAT_BC3_TYPELESS;
		case DXGI_FORMAT_BC3_UNORM:	return FORMAT_BC3_UNORM;
		case DXGI_FORMAT_BC3_UNORM_SRGB: return FORMAT_BC3_UNORM_SRGB;
		case DXGI_FORMAT_BC4_TYPELESS: return FORMAT_BC4_TYPELESS;
		case DXGI_FORMAT_BC4_UNORM:	return FORMAT_BC4_UNORM;
		case DXGI_FORMAT_BC4_SNORM:	return FORMAT_BC4_SNORM;
		case DXGI_FORMAT_BC5_TYPELESS: return FORMAT_BC5_TYPELESS;
		case DXGI_FORMAT_BC5_UNORM:	return FORMAT_BC5_UNORM;
		case DXGI_FORMAT_BC5_SNORM:	return FORMAT_BC5_SNORM;
		case DXGI_FORMAT_B5G6R5_UNORM: return FORMAT_B5G6R5_UNORM;
		case DXGI_FORMAT_B5G5R5A1_UNORM: return FORMAT_B5G5R5A1_UNORM;
		case DXGI_FORMAT_B8G8R8A8_UNORM: return FORMAT_B8G8R8A8_UNORM;
		case DXGI_FORMAT_B8G8R8X8_UNORM: return FORMAT_B8G8R8X8_UNORM;
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM: return FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:	return FORMAT_B8G8R8A8_TYPELESS;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: return FORMAT_B8G8R8A8_UNORM_SRGB;
		case DXGI_FORMAT_B8G8R8X8_TYPELESS: return FORMAT_B8G8R8X8_TYPELESS;
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: return FORMAT_B8G8R8X8_UNORM_SRGB;
		case DXGI_FORMAT_BC6H_TYPELESS: return FORMAT_BC6H_TYPELESS;
		case DXGI_FORMAT_BC6H_UF16:	return FORMAT_BC6H_UF16;
		case DXGI_FORMAT_BC6H_SF16:	return FORMAT_BC6H_SF16;
		case DXGI_FORMAT_BC7_TYPELESS: return FORMAT_BC7_TYPELESS;
		case DXGI_FORMAT_BC7_UNORM: return FORMAT_BC7_UNORM;
		case DXGI_FORMAT_BC7_UNORM_SRGB: return FORMAT_BC7_UNORM_SRGB;
		case DXGI_FORMAT_AYUV: return FORMAT_AYUV;
		case DXGI_FORMAT_Y410: return FORMAT_Y410;
		case DXGI_FORMAT_Y416: return FORMAT_Y416;
		case DXGI_FORMAT_NV12: return FORMAT_NV12;
		case DXGI_FORMAT_P010: return FORMAT_P010;
		case DXGI_FORMAT_P016: return FORMAT_P016;
		case DXGI_FORMAT_420_OPAQUE: return FORMAT_420_OPAQUE;
		case DXGI_FORMAT_YUY2: return FORMAT_YUY2;
		case DXGI_FORMAT_Y210: return FORMAT_Y210;
		case DXGI_FORMAT_Y216: return FORMAT_Y216;
		case DXGI_FORMAT_NV11: return FORMAT_NV11;
		case DXGI_FORMAT_AI44: return FORMAT_AI44;
		case DXGI_FORMAT_IA44: return FORMAT_IA44;
		case DXGI_FORMAT_P8: return FORMAT_P8;
		case DXGI_FORMAT_A8P8: return FORMAT_A8P8;
		case DXGI_FORMAT_B4G4R4A4_UNORM: return FORMAT_B4G4R4A4_UNORM;
		case DXGI_FORMAT_FORCE_UINT: return FORMAT_FORCE_UINT;
		default: break;
	}

	return FORMAT_UNKNOWN;
}
inline USAGE __ConvertUsage_Inv(D3D11_USAGE Val)
{
	switch (Val)
	{
		case D3D11_USAGE_DEFAULT: return USAGE_DEFAULT;
		case D3D11_USAGE_IMMUTABLE: return USAGE_IMMUTABLE;
		case D3D11_USAGE_DYNAMIC: return USAGE_DYNAMIC;
		case D3D11_USAGE_STAGING: return USAGE_STAGING;
		default: break;
	}

	return USAGE_DEFAULT;
}

inline TextureDesc __ConvertTextureDesc_Inv(const D3D11_TEXTURE1D_DESC* Desc)
{
	TextureDesc _Desc;
	_Desc.Width = Desc->Width;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.ArraySize = Desc->ArraySize;
	_Desc.Format = __ConvertFormat_Inv(Desc->Format);
	_Desc.Usage = __ConvertUsage_Inv(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags_Inv(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUAccessFlags_Inv(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceMiscFlags_Inv(Desc->MiscFlags);

	return _Desc;
}

inline TextureDesc __ConvertTextureDesc_Inv(const D3D11_TEXTURE2D_DESC* Desc)
{
	TextureDesc _Desc;
	_Desc.Width = Desc->Width;
	_Desc.Height = Desc->Height;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.ArraySize = Desc->ArraySize;
	_Desc.Format = __ConvertFormat_Inv(Desc->Format);
	_Desc.SampleDesc.Count = Desc->SampleDesc.Count;
	_Desc.SampleDesc.Quality = Desc->SampleDesc.Quality;
	_Desc.Usage = __ConvertUsage_Inv(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags_Inv(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUAccessFlags_Inv(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceMiscFlags_Inv(Desc->MiscFlags);

	return _Desc;
}
inline TextureDesc __ConvertTextureDesc_Inv(const D3D11_TEXTURE3D_DESC* Desc)
{
	TextureDesc _Desc;
	_Desc.Width = Desc->Width;
	_Desc.Height = Desc->Height;
	_Desc.Depth = Desc->Depth;
	_Desc.MipLevels = Desc->MipLevels;
	_Desc.Format = __ConvertFormat_Inv(Desc->Format);
	_Desc.Usage = __ConvertUsage_Inv(Desc->Usage);
	_Desc.BindFlags = __ParseBindFlags_Inv(Desc->BindFlags);
	_Desc.CPUAccessFlags = __ParseCPUAccessFlags_Inv(Desc->CPUAccessFlags);
	_Desc.MiscFlags = __ParseResourceMiscFlags_Inv(Desc->MiscFlags);

	return _Desc;
}


HRESULT RenderContext_DX11::CreateBuffer(const GPUBufferDesc* Desc, const SubresourceData* InitialData, GPUBuffer* Buffer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateTexture1D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture1D** InTexture1D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateTexture2D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture2D** InTexture2D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateTexture3D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture3D** InTexture3D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateInputLayout(const VertexLayoutDesc* InputElementDesc, uint32 NumElements, const ShaderByteCode* Shader, VertexLayout* InputLayout)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateVertexShader(const void* ShaderBytecode, size_t BytecodeLen, VertexShader* InVertexShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreatePixelShader(const void* ShaderBytecode, size_t BytecodeLen, PixelShader* InPixelShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateGeometryShader(const void* ShaderBytecode, size_t BytecodeLen, GeometryShader* InGeometryShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateHullShader(const void* ShaderBytecode, size_t BytecodeLen, HullShader* InHullShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateDomainShader(const void* ShaderBytecode, size_t BytecodeLen, DomainShader* InDomainShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateComputeShader(const void* ShaderBytecode, size_t BytecodeLen, ComputeShader* InComputeShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateBlendState(const BlendStateDesc* InBlendStateDesc, BlendState* InBlendState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateRasterizerState(const RasterizerStateDesc* InRasterizerStateDesc, RasterizerState* InRasterizerState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateSamplerState(const SamplerDesc* InSamplerDesc, Sampler* InSampler)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateQuery(const GPUQueryDesc* QueryDesc, GPUQuery* InQuery)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateGrahpicsPSO(const GraphicsPSODesc* Desc, GraphicsPSO* InPSO)
{
	throw std::logic_error("The method or operation is not implemented.");
}

HRESULT RenderContext_DX11::CreateComputePSO(const ComputePSODesc* Desc, ComputePSO* InPSO)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyResource(GPUResource* Resource)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyBuffer(GPUBuffer* Buffer)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyTexture1D(Texture1D* InTexture1D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyTexture2D(Texture2D* InTexture2D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyTexture3D(Texture3D* InTexture3D)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestoryInputLayer(VertexLayout* InputLayout)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyVertextShader(VertexShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyPixelShader(PixelShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyGeometryShader(GeometryShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyHullShader(HullShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyDomainShader(DomainShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyComputeShader(ComputeShader* InShader)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyBlendState(BlendState* InState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyDepthStencilState(DepthStencilState* InState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyRasterizerState(RasterizerState* InState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroySamplerState(Sampler* InState)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyQuery(GPUQuery* InQuery)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyGraphicsPSO(GraphicsPSO* InPSO)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DestroyComputePSO(ComputePSO* InPSO)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::SetName(GPUResource* Resource, const String& NewName)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::PresentBegin()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::PresentEnd()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::CreateCommandLists()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::ExecuteCommandLists()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::FinishCommandList(GRAPHICSTHREAD Thread)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::WaitForGPU()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::SetResolution(int32 W, int32 H)
{
	throw std::logic_error("The method or operation is not implemented.");
}

Texture2D RenderContext_DX11::GetBackBuffer()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindScissorRects(uint32 NumRects, const Rect* Rects, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindViewports(uint32 NumViewports, const Viewport* Viewports, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindRenderTargets(uint32 NumViews, const Texture2D** RenderTargets, Texture2D* DepthStencilTexture, GRAPHICSTHREAD ThreadID, int32 Index /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::ClearRenderTarget(Texture* Texture, const float ColorRGBA[4], GRAPHICSTHREAD ThreadID, int32 Index /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::ClearDepthStencil(Texture2D* Texture, uint32 ClearFlags, float Depth, uint8 Stencil, GRAPHICSTHREAD ThreadID, int32 Index /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindResource(SHADERSTAGE Stage, GPUResource* Resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindResources(SHADERSTAGE Stage, const GPUResource** Resources, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindUAV(SHADERSTAGE Stage, GPUResource* resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindUAVs(SHADERSTAGE Stage, const GPUResource** Resource, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::UnbindResources(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::UnbindUAVs(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindSampler(SHADERSTAGE Stage, Sampler* Sampler, int32 Slot, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindConstantBuffer(SHADERSTAGE Stage, GPUBuffer* Buffer, int32 Slot, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindVertexBuffers(const GPUBuffer** VertexBuffers, int32 Slot, int32 Count, const uint32* Strides, const uint32* Offsets, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindIndexBuffer(GPUBuffer* IndexBuffer, const INDEXBUFFER_FORMAT format, uint32 offset, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindStencilRef(uint32 Val, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindBlendFactor(XMFLOAT4 Val, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindGraphicsPSO(GraphicsPSO* PSO, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::BindComputePSO(ComputePSO* PSO, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::Draw(int32 VertexCount, uint32 VertexStartingLocation, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DrawIndexed(int32 indexCount, uint32 IndexStartingLocation, uint32 BaseVertexLocation, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DrawInstanced(int32 VertexCount, int32 InstanceID, uint32 VertexStartingLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DrawIndexedInstanced(int32 indexCount, int32 InstanceID, uint32 IndexStartingLocation, uint32 BaseVertexLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DrawInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DrawIndexedInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::Dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 ThreadGroupCount, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::DispatchIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::CopyTexture2D(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::CopyTexture2D_Region(Texture2D* Dst, uint32 DstMip, uint32 DstX, uint32 DstY, Texture2D* Src, uint32 SrcMip, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::MSAAResolve(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::UpdateBuffer(GPUBuffer* Buffer, const void* Data, GRAPHICSTHREAD ThreadID, int32 DataSize /*= -1*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void* RenderContext_DX11::AllocateFromRingBuffer(GPURingBuffer* Buffer, size_t DataSize, uint32& offsetIntoBuffer, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::InvalidateBufferAccess(GPUBuffer* Buffer, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool RenderContext_DX11::DownloadResource(GPUResource* ResourceToDownload, GPUResource* ResourceDest, void* DataDest, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::QueryBegin(GPUQuery* Query, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::QueryEnd(GPUQuery* Query, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool RenderContext_DX11::QueryRead(GPUQuery* Query, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::UAVBarrier(const GPUResource** UAVS, uint32 NumBarriers, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::TransitionBarrier(const GPUResource** Resource, uint32 NumBarriers, RESOURCE_STATES BeforeState, RESOURCE_STATES AfterState, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::EventBegin(const String& Name, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::EventEnd(GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RenderContext_DX11::SetMarker(const String& Name, GRAPHICSTHREAD ThreadID)
{
	throw std::logic_error("The method or operation is not implemented.");
}

