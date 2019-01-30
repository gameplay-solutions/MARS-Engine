#pragma once

#include "Core/EngineCore.h"
#include "Rendering/RenderTypes.h"
#include "Core/ThreadManager.h"
#include "Rendering/API/API_Resources.h"

namespace MARS
{
	class BaseRenderContext
	{
	public:

		virtual HRESULT CreateBuffer(const GPUBufferDesc* Desc, const SubresourceData* InitialData, GPUBuffer* Buffer) = 0;
		virtual HRESULT CreateTexture1D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture1D** InTexture1D) = 0;
		virtual HRESULT CreateTexture2D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture2D** InTexture2D) = 0;
		virtual HRESULT CreateTexture3D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture3D** InTexture3D) = 0;

		virtual HRESULT CreateInputLayout(const VertexLayoutDesc* InputElementDesc, uint32 NumElements, const ShaderByteCode* Shader, VertexLayout* InputLayout) = 0;
		virtual HRESULT CreateVertexShader(const void* ShaderBytecode, size_t BytecodeLen, VertexShader* InVertexShader) = 0;
		virtual HRESULT CreatePixelShader(const void* ShaderBytecode, size_t BytecodeLen, PixelShader* InPixelShader) = 0;
		virtual HRESULT CreateGeometryShader(const void* ShaderBytecode, size_t BytecodeLen, GeometryShader* InGeometryShader) = 0;
		virtual HRESULT CreateHullShader(const void* ShaderBytecode, size_t BytecodeLen, HullShader* InHullShader) = 0;
		virtual HRESULT CreateDomainShader(const void* ShaderBytecode, size_t BytecodeLen, DomainShader* InDomainShader) = 0;
		virtual HRESULT CreateComputeShader(const void* ShaderBytecode, size_t BytecodeLen, ComputeShader* InComputeShader) = 0;

		virtual HRESULT CreateBlendState(const BlendStateDesc* InBlendStateDesc, BlendState* InBlendState) = 0;
		virtual HRESULT CreateRasterizerState(const RasterizerStateDesc* InRasterizerStateDesc, RasterizerState* InRasterizerState) = 0;
		virtual HRESULT CreateSamplerState(const SamplerDesc* InSamplerDesc, Sampler* InSampler) = 0;
		virtual HRESULT CreateQuery(const GPUQueryDesc* QueryDesc, GPUQuery* InQuery) = 0;

		virtual HRESULT CreateGrahpicsPSO(const GraphicsPSODesc* Desc, GraphicsPSO* InPSO) = 0;
		virtual HRESULT CreateComputePSO(const ComputePSODesc* Desc, ComputePSO* InPSO) = 0;
	};
}