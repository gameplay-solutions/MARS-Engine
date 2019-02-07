#pragma once

#include "Core/EngineCore.h"
#include "Rendering/API/RenderContext.h"
#include "Platform/Windows/Windows_PlatformHandler.h"

#include <d3d11_3.h>
#include <DXGI1_3.h>

namespace MARS
{
inline namespace GRAPHICS
{
	class RenderContext_DX11 : public RenderContext
	{
	private:
		
		ID3D11Device*					Device = nullptr;
		D3D_DRIVER_TYPE					DriverType;
		D3D_FEATURE_LEVEL				FeatureLevel;
		IDXGISwapChain1*				SwapChain = nullptr;
		ID3D11RenderTargetView*			RenderTargetView = nullptr;
		ID3D11Texture2D*				BackBuffer = nullptr;
		ID3D11DeviceContext*			DeviceContext[GRAPHICSTHREAD_COUNT] = {};
		ID3DUserDefinedAnnotation*		UserDefinedAnnotation[GRAPHICSTHREAD_COUNT] = {};

		ID3D11VertexShader*				PrevVS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11PixelShader*				PrevPS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11HullShader*				PrevHS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11DomainShader*				PrevDS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11GeometryShader*			PrevGS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11ComputeShader*			PrevCS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11BlendState*				PrevBS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11RasterizerState*			PrevRS[GRAPHICSTHREAD_COUNT] = {};
		ID3D11InputLayout*				PrevIL[GRAPHICSTHREAD_COUNT] = {};
		PRIMITIVETOPOLOGY*				PrevPT[GRAPHICSTHREAD_COUNT] = {};
		ID3D11DepthStencilState*		PrevDSS[GRAPHICSTHREAD_COUNT]= {};

		ID3D11UnorderedAccessView*		RasterUAVs[GRAPHICSTHREAD_COUNT] = {};
		uint8 RasterUAVSlot				[GRAPHICSTHREAD_COUNT] = {};
		uint8 RasterUAVCount			[GRAPHICSTHREAD_COUNT] = {};

		uint32							PrevSampleMask[GRAPHICSTHREAD_COUNT] = {};
		XMFLOAT4						PrevBlendFactor[GRAPHICSTHREAD_COUNT] = {};

		uint32							StencilRef[GRAPHICSTHREAD_COUNT];
		XMFLOAT4						BlendFactor[GRAPHICSTHREAD_COUNT];

		void ValidateRasterUAVs(GRAPHICSTHREAD ThreadID);
		void CreateBackBufferResources();

	public:

		RenderContext_DX11(MARS::WindowType InWindow, bool Fullscreen = false, bool EnableDebugLayer = false);
		virtual ~RenderContext_DX11();

		virtual HRESULT CreateBuffer(const GPUBufferDesc* Desc, const SubresourceData* InitialData, GPUBuffer* Buffer) override;
		virtual HRESULT CreateTexture1D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture1D** InTexture1D) override;
		virtual HRESULT CreateTexture2D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture2D** InTexture2D) override;
		virtual HRESULT CreateTexture3D(const TextureDesc* Desc, const SubresourceData* InitialData, Texture3D** InTexture3D) override;

		virtual HRESULT CreateInputLayout(const VertexLayoutDesc* InputElementDesc, uint32 NumElements, const ShaderByteCode* Shader, VertexLayout* InputLayout) override;
		virtual HRESULT CreateVertexShader(const void* ShaderBytecode, size_t BytecodeLen, VertexShader* InVertexShader) override;
		virtual HRESULT CreatePixelShader(const void* ShaderBytecode, size_t BytecodeLen, PixelShader* InPixelShader) override;
		virtual HRESULT CreateGeometryShader(const void* ShaderBytecode, size_t BytecodeLen, GeometryShader* InGeometryShader) override;
		virtual HRESULT CreateHullShader(const void* ShaderBytecode, size_t BytecodeLen, HullShader* InHullShader) override;
		virtual HRESULT CreateDomainShader(const void* ShaderBytecode, size_t BytecodeLen, DomainShader* InDomainShader) override;
		virtual HRESULT CreateComputeShader(const void* ShaderBytecode, size_t BytecodeLen, ComputeShader* InComputeShader) override;

		virtual HRESULT CreateBlendState(const BlendStateDesc* InBlendStateDesc, BlendState* InBlendState) override;
		virtual HRESULT CreateRasterizerState(const RasterizerStateDesc* InRasterizerStateDesc, RasterizerState* InRasterizerState) override;
		virtual HRESULT CreateSamplerState(const SamplerDesc* InSamplerDesc, Sampler* InSampler) override;
		virtual HRESULT CreateQuery(const GPUQueryDesc* QueryDesc, GPUQuery* InQuery) override;

		virtual HRESULT CreateGrahpicsPSO(const GraphicsPSODesc* Desc, GraphicsPSO* InPSO) override;
		virtual HRESULT CreateComputePSO(const ComputePSODesc* Desc, ComputePSO* InPSO) override;

		virtual void DestroyResource(GPUResource* Resource) override;
		virtual void DestroyBuffer(GPUBuffer* Buffer) override;
		virtual void DestroyTexture1D(Texture1D* InTexture1D) override;
		virtual void DestroyTexture2D(Texture2D* InTexture2D) override;
		virtual void DestroyTexture3D(Texture3D* InTexture3D) override;
		virtual void DestoryInputLayer(VertexLayout* InputLayout) override;
		virtual void DestroyVertextShader(VertexShader* InShader) override;
		virtual void DestroyPixelShader(PixelShader* InShader) override;
		virtual void DestroyGeometryShader(GeometryShader* InShader) override;
		virtual void DestroyHullShader(HullShader* InShader) override;
		virtual void DestroyDomainShader(DomainShader* InShader) override;
		virtual void DestroyComputeShader(ComputeShader* InShader) override;
		virtual void DestroyBlendState(BlendState* InState) override;
		virtual void DestroyDepthStencilState(DepthStencilState* InState) override;
		virtual void DestroyRasterizerState(RasterizerState* InState) override;
		virtual void DestroySamplerState(Sampler* InState) override;
		virtual void DestroyQuery(GPUQuery* InQuery) override;
		virtual void DestroyGraphicsPSO(GraphicsPSO* InPSO) override;
		virtual void DestroyComputePSO(ComputePSO* InPSO) override;

		virtual void SetName(GPUResource* Resource, const String& NewName) override;

		virtual void PresentBegin() override;
		virtual void ExecuteCommandLists() override;
		virtual void PresentEnd() override;

		virtual void CreateCommandLists() override;
		virtual void FinishCommandList(GRAPHICSTHREAD Thread) override;

		virtual void WaitForGPU() override;

		virtual void SetResolution(int32 W, int32 H) override;
		virtual Texture2D GetBackBuffer() override;

		/*||===================================================================*/
 		/*|| Everything below here is #ThreadSensitive                                                  
 		/*||===================================================================*/
		virtual void BindScissorRects(uint32 NumRects, const Rect* Rects, GRAPHICSTHREAD ThreadID) override;
		virtual void BindViewports(uint32 NumViewports, const Viewport* Viewports, GRAPHICSTHREAD ThreadID) override;
		virtual void BindRenderTargets(uint32 NumViews, const Texture2D** RenderTargets, Texture2D* DepthStencilTexture, GRAPHICSTHREAD ThreadID, int32 Index = -1) override;
		virtual void ClearRenderTarget(Texture* Texture, const float ColorRGBA[4], GRAPHICSTHREAD ThreadID, int32 Index = -1) override;
		virtual void ClearDepthStencil(Texture2D* Texture, uint32 ClearFlags, float Depth, uint8 Stencil, GRAPHICSTHREAD ThreadID, int32 Index = -1) override;
		virtual void BindResource(SHADERSTAGE Stage, GPUResource* Resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index = -1) override;
		virtual void BindResources(SHADERSTAGE Stage, const GPUResource** Resources, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID) override;
		virtual void BindUAV(SHADERSTAGE Stage, GPUResource* resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index = -1) override;
		virtual void BindUAVs(SHADERSTAGE Stage, const GPUResource** Resource, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID) override;
		virtual void UnbindResources(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID) override;
		virtual void UnbindUAVs(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID) override;
		virtual void BindSampler(SHADERSTAGE Stage, Sampler* Sampler, int32 Slot, GRAPHICSTHREAD ThreadID) override;
		virtual void BindConstantBuffer(SHADERSTAGE Stage, GPUBuffer* Buffer, int32 Slot, GRAPHICSTHREAD ThreadID) override;
		virtual void BindVertexBuffers(const GPUBuffer** VertexBuffers, int32 Slot, int32 Count, const uint32* Strides, const uint32* Offsets, GRAPHICSTHREAD ThreadID) override;
		virtual void BindIndexBuffer(GPUBuffer* IndexBuffer, const INDEXBUFFER_FORMAT format, uint32 offset, GRAPHICSTHREAD ThreadID) override;
		virtual void BindStencilRef(uint32 Val, GRAPHICSTHREAD ThreadID) override;
		virtual void BindBlendFactor(XMFLOAT4 Val, GRAPHICSTHREAD ThreadID) override;
		virtual void BindGraphicsPSO(GraphicsPSO* PSO, GRAPHICSTHREAD ThreadID) override;
		virtual void BindComputePSO(ComputePSO* PSO, GRAPHICSTHREAD ThreadID) override;
		virtual void Draw(int32 VertexCount, uint32 VertexStartingLocation, GRAPHICSTHREAD ThreadID) override;
		virtual void DrawIndexed(int32 indexCount, uint32 IndexStartingLocation, uint32 BaseVertexLocation, GRAPHICSTHREAD ThreadID) override;
		virtual void DrawInstanced(int32 VertexCount, int32 InstanceID, uint32 VertexStartingLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID) override;
		virtual void DrawIndexedInstanced(int32 indexCount, int32 InstanceID, uint32 IndexStartingLocation, uint32 BaseVertexLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID) override;
		virtual void DrawInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) override;
		virtual void DrawIndexedInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) override;
		virtual void Dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 ThreadGroupCount, GRAPHICSTHREAD ThreadID) override;
		virtual void DispatchIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) override;
		virtual void CopyTexture2D(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID) override;
		virtual void CopyTexture2D_Region(Texture2D* Dst, uint32 DstMip, uint32 DstX, uint32 DstY, Texture2D* Src, uint32 SrcMip, GRAPHICSTHREAD ThreadID) override;
		virtual void MSAAResolve(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID) override;
		virtual void UpdateBuffer(GPUBuffer* Buffer, const void* Data, GRAPHICSTHREAD ThreadID, int32 DataSize = -1) override;
		virtual void* AllocateFromRingBuffer(GPURingBuffer* Buffer, size_t DataSize, uint32& offsetIntoBuffer, GRAPHICSTHREAD ThreadID) override;
		virtual void InvalidateBufferAccess(GPUBuffer* Buffer, GRAPHICSTHREAD ThreadID) override;
		virtual bool DownloadResource(GPUResource* ResourceToDownload, GPUResource* ResourceDest, void* DataDest, GRAPHICSTHREAD ThreadID) override;
		virtual void QueryBegin(GPUQuery* Query, GRAPHICSTHREAD ThreadID) override;
		virtual void QueryEnd(GPUQuery* Query, GRAPHICSTHREAD ThreadID) override;
		virtual bool QueryRead(GPUQuery* Query, GRAPHICSTHREAD ThreadID) override;
		virtual void UAVBarrier(const GPUResource** UAVS, uint32 NumBarriers, GRAPHICSTHREAD ThreadID) override;
		virtual void TransitionBarrier(const GPUResource** Resource, uint32 NumBarriers, RESOURCE_STATES BeforeState, RESOURCE_STATES AfterState, GRAPHICSTHREAD ThreadID) override;
		virtual void EventBegin(const String& Name, GRAPHICSTHREAD ThreadID) override;
		virtual void EventEnd(GRAPHICSTHREAD ThreadID) override;
		virtual void SetMarker(const String& Name, GRAPHICSTHREAD ThreadID) override;	
	};
}
}