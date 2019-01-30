#pragma once

#include "Core/EngineCore.h"
#include "Rendering/RenderTypes.h"

#include <vector>

namespace MARS
{
	inline namespace GRAPHICS
	{
		using CPU_Handle = uint64;
		static const CPU_Handle NULL_HANDLE = 0;

		class GraphicsDevice;

		struct GraphicsDeviceChild
		{
			GraphicsDevice* Device = nullptr;
			void Register(GraphicsDevice* InDevice) { Device = InDevice; }
		};

		struct ShaderByteCode
		{
			uint8* Payload;
			size_t Size;
			ShaderByteCode() : Payload(nullptr), Size(0) {}
			~ShaderByteCode() { SAFE_DELETE_ARRAY(Payload); }
		};

		struct VertexShader : public GraphicsDeviceChild
		{
			VertexShader();
			~VertexShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct PixelShader : public GraphicsDeviceChild
		{
			PixelShader();
			~PixelShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct GeometryShader : public GraphicsDeviceChild
		{
			GeometryShader();
			~GeometryShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct HullShader : public GraphicsDeviceChild
		{
			HullShader();
			~HullShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct DomainShader : public GraphicsDeviceChild
		{
			DomainShader();
			~DomainShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct ComputeShader : public GraphicsDeviceChild
		{
			ComputeShader();
			~ComputeShader();

			ShaderByteCode bCode;
			CPU_Handle Resource = NULL_HANDLE;
		};

		struct Sampler : public GraphicsDeviceChild
		{
			CPU_Handle Resource = NULL_HANDLE;
			SamplerDesc Desc;

			Sampler();
			~Sampler();

			bool IsValid() { return Resource != NULL_HANDLE; }
			SamplerDesc GetDesc() { return Desc; }
		};

		struct GPUResource : public GraphicsDeviceChild
		{
			CPU_Handle SRV = NULL_HANDLE;			// main Resource SRV
			std::vector<CPU_Handle> AdditionalSRVs;	// can be used for sub-resources if requested

			CPU_Handle UAV = NULL_HANDLE;			// main Resource UAV
			std::vector<CPU_Handle> AdditionalUAVs;	// can be used for sub-resources if requested

			CPU_Handle Resource;
			CPU_Handle ResourceMemory;

			GPUResource();
			virtual ~GPUResource();
		};

		struct GPUBuffer : public GPUResource
		{
			CPU_Handle CBV = NULL_HANDLE;
			GPUBufferDesc Desc;

			GPUBuffer();
			virtual ~GPUBuffer();

			bool IsValid() { return Resource != NULL_HANDLE; }
			GPUBufferDesc GetDesc() { return Desc; }
		};

		struct GPURingBuffer : public GPUBuffer
		{
			size_t ByteOffset = 0;
			uint64 ResidentFrame = 0;

			size_t GetByteOffset() { return ByteOffset; }
		};

		struct VertexLayout : public GraphicsDeviceChild
		{
			CPU_Handle	Resource = NULL_HANDLE;

			std::vector<VertexLayoutDesc> Desc;

			VertexLayout();
			~VertexLayout();
		};

		struct BlendState : public GraphicsDeviceChild
		{
			CPU_Handle Resource = NULL_HANDLE;
			BlendStateDesc Desc;

			BlendState();
			~BlendState();

			BlendStateDesc GetDesc() { return Desc; }
		};

		struct DepthStencilState : public GraphicsDeviceChild
		{
			CPU_Handle Resource = NULL_HANDLE;
			DepthStencilStateDesc Desc;

			DepthStencilState();
			~DepthStencilState();

			DepthStencilStateDesc GetDesc() { return Desc; }
		};

		struct RasterizerState : public GraphicsDeviceChild
		{
			CPU_Handle Resource = NULL_HANDLE;
			RasterizerStateDesc Desc;

			RasterizerState();
			~RasterizerState();

			RasterizerStateDesc GetDesc() { return Desc; }
		};

		struct Texture : public GPUResource
		{
			TextureDesc	Desc;
			CPU_Handle	RTV = NULL_HANDLE;
			std::vector<CPU_Handle> additionalRTVs;
			bool IndependentRTVArraySlices = false;
			bool IndependentRTVCubemapFaces = false;
			bool IndependentSRVArraySlices = false;
			bool IndependentSRVMIPs = false;
			bool IndependentUAVMIPs = false;

			const TextureDesc& GetDesc() const { return Desc; }

			Texture();
			virtual ~Texture();

			void RequestIndependentRenderTargetArraySlices(bool Val);
			void RequestIndependentRenderTargetCubemapFaces(bool Val);
			void RequestIndependentShaderResourceArraySlices(bool Val);
			void RequestIndependentShaderResourcesForMIPs(bool Val);
			void RequestIndependentUnorderedAccessResourcesForMIPs(bool Val);
		};

		struct Texture1D : public Texture
		{
			Texture1D();
			virtual ~Texture1D();
		};

		struct Texture2D : public Texture
		{
			CPU_Handle	DSV = NULL_HANDLE;
			std::vector<CPU_Handle> additionalDSVs;

			Texture2D();
			virtual ~Texture2D();
		};

		struct Texture3D : public Texture
		{
			Texture3D();
			virtual ~Texture3D();
		};




		struct GPUQuery : public GraphicsDeviceChild
		{
			std::vector<CPU_Handle>	Resource;
			std::vector<int32>			Active;
			GPUQueryDesc				Desc;
			int32							AsyncFrameshift;

			GPUQuery();
			virtual ~GPUQuery();

			bool IsValid() { return !Resource.empty() && Resource[0] != NULL_HANDLE; }
			GPUQueryDesc GetDesc() const { return Desc; }

			bool	ResultPassed;
			uint64	ResultPassedSampleCount;
			uint64	ResultTimestamp;
			uint64	ResultTimestampFrequency;
			bool	ResultDisjoint;
		};


		struct GraphicsPSO : public GraphicsDeviceChild
		{
			CPU_Handle	Pipeline;
			GraphicsPSODesc Desc;

			const GraphicsPSODesc& GetDesc() const { return Desc; }

			GraphicsPSO();
			~GraphicsPSO();
		};
		struct ComputePSO : public GraphicsDeviceChild
		{
			CPU_Handle	Pipeline;
			ComputePSODesc Desc;

			const ComputePSODesc& GetDesc() const { return Desc; }

			ComputePSO();
			~ComputePSO();
		};
	}
}