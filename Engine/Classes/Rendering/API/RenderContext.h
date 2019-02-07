 #pragma once
 
 #include "Core/EngineCore.h"
 #include "Rendering/RenderTypes.h"
 #include "Core/ThreadManager.h"
 #include "Rendering/API/API_Resources.h"
 
 namespace MARS
 {
 	class RenderContext
 	{
 	public:
 
 		enum GRAPHICSDEVICE_CAPABILITY
 		{
 			GRAPHICSDEVICE_CAPABILITY_TESSELLATION,
 			GRAPHICSDEVICE_CAPABILITY_MULTITHREADED_RENDERING,
 			GRAPHICSDEVICE_CAPABILITY_CONSERVATIVE_RASTERIZATION,
 			GRAPHICSDEVICE_CAPABILITY_RASTERIZER_ORDERED_VIEWS,
 			GRAPHICSDEVICE_CAPABILITY_UNORDEREDACCESSTEXTURE_LOAD_FORMAT_EXT,
 			GRAPHICSDEVICE_CAPABILITY_COUNT,
 		};
 
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
 
 		virtual void DestroyResource(GPUResource* Resource) = 0;
 		virtual void DestroyBuffer(GPUBuffer* Buffer) = 0;
 		virtual void DestroyTexture1D(Texture1D* InTexture1D) = 0;
 		virtual void DestroyTexture2D(Texture2D* InTexture2D) = 0;
 		virtual void DestroyTexture3D(Texture3D* InTexture3D) = 0;
 		virtual void DestoryInputLayer(VertexLayout* InputLayout) = 0;
 		virtual void DestroyVertextShader(VertexShader* InShader) = 0;
 		virtual void DestroyPixelShader(PixelShader* InShader) = 0;
 		virtual void DestroyGeometryShader(GeometryShader* InShader) = 0;
 		virtual void DestroyHullShader(HullShader* InShader) = 0;
 		virtual void DestroyDomainShader(DomainShader* InShader) = 0;
 		virtual void DestroyComputeShader(ComputeShader* InShader) = 0;
 		virtual void DestroyBlendState(BlendState* InState) = 0;
 		virtual void DestroyDepthStencilState(DepthStencilState* InState) = 0;
 		virtual void DestroyRasterizerState(RasterizerState* InState) = 0;
 		virtual void DestroySamplerState(Sampler* InState) = 0;
 		virtual void DestroyQuery(GPUQuery* InQuery) = 0;
 		virtual void DestroyGraphicsPSO(GraphicsPSO* InPSO) = 0;
 		virtual void DestroyComputePSO(ComputePSO* InPSO) = 0;
 
 		virtual void SetName(GPUResource* Resource, const String& NewName) = 0;
 
 		virtual void PresentBegin() = 0;
 		virtual void PresentEnd() = 0;
 
 		virtual void CreateCommandLists() = 0;
 		virtual void ExecuteCommandLists() = 0;
 		virtual void FinishCommandList(GRAPHICSTHREAD Thread) = 0;
 
 		virtual void WaitForGPU() = 0;
 
 		virtual void SetResolution(int32 W, int32 H) = 0;
 		virtual Texture2D GetBackBuffer() = 0;
 
 		/*||===================================================================
 		 *|| The following functions are non-API exclusive getters                                                             
 		 *||===================================================================*/
 		inline FORMAT GetBackBufferFormat() const { return BACKBUFFER_FORMAT; }
 		inline static uint32 GetBackBufferCount() { return BACKBUFFER_COUNT; }
 		inline bool GetVSyncEnabled() const { return VSYNC; }
 		inline void SetVSyncEnabled(bool Val) { VSYNC = Val; }
 		inline uint64 GetFrameCount() const { return FRAMECOUNT; }
 		inline int32 GetScreenWidth() const { return SCREENWIDTH; }
 		inline int32 GetScreenHeight() const { return SCREENHEIGHT; }
 		/** inline MARS::Resolution GetScreenResolution() const { return RESOLUTION; } */
 		inline bool ResolutionChanged() const { return RESOLUTIONCHANGED; }
 
 		/*||===================================================================
 		 *|| The following functions are API inclusive meaning that they do not 
 		 *|| need a custom implementation for each API
 		 *||===================================================================*/
 		bool CheckCapability(GRAPHICSDEVICE_CAPABILITY Capability) const;		
 		uint32 GetStride(FORMAT Val) const;
 		bool IsUnorm(FORMAT Val) const;
 
 		/** @todo(Chrisr): move this to the DX Context? Seems like bad practice to have DX specific code in a API generic class
 		 * Leaving for now as I am curious if this will cause problems on other platforms */
 		inline XMMATRIX GetScreenProjection() const
 		{
 			return XMMatrixOrthographicOffCenterLH(0, (float)GetScreenWidth(), (float)GetScreenHeight(), 0, -1, 1); /** int32 to float conversion, this should be changed out */
 		}
 
 	protected:
 
 		uint64 FRAMECOUNT = 0;
 		int32 SCREENWIDTH = 0;
 		int32 SCREENHEIGHT = 0;
 		/** MARS::Resolution RESOLUTION; */
 		FORMAT BACKBUFFER_FORMAT = FORMAT_R10G10B10A2_UNORM;
 		static const uint32 BACKBUFFER_COUNT = 2;
 		bool VSYNC = true;
 		bool FULLSCREEN = false;
 		bool RESOLUTIONCHANGED = false;
 		bool TESSELLATION = false;
 		bool MULTITHREADED_RENDERING = false;
 		bool CONSERVATIVE_RASTERIZATION = false;
 		bool RASTERIZER_ORDERED_VIEWS = false;
 		bool UNORDEREDACCESSTEXTURE_LOAD_EXT = false;
 
 	public:
 
 		/*||===================================================================
 		 *|| Everything below here is #ThreadSensitive                                                  
 		 *||===================================================================*/
 
 		virtual void BindScissorRects(uint32 NumRects, const Rect* Rects, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindViewports(uint32 NumViewports, const Viewport* Viewports, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindRenderTargets(uint32 NumViews, const Texture2D** RenderTargets, Texture2D* DepthStencilTexture, GRAPHICSTHREAD ThreadID, int32 Index = -1) = 0;
 		virtual void ClearRenderTarget(Texture* Texture, const float ColorRGBA[4], GRAPHICSTHREAD ThreadID, int32 Index = -1) = 0;
 		virtual void ClearDepthStencil(Texture2D* Texture, uint32 ClearFlags, float Depth, uint8 Stencil, GRAPHICSTHREAD ThreadID, int32 Index = -1) = 0;
 		virtual void BindResource(SHADERSTAGE Stage, GPUResource* Resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index = -1) = 0;
 		virtual void BindResources(SHADERSTAGE Stage, const GPUResource** Resources, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindUAV(SHADERSTAGE Stage, GPUResource* resource, int32 Slot, GRAPHICSTHREAD ThreadID, int32 Index = -1) = 0;
 		virtual void BindUAVs(SHADERSTAGE Stage, const GPUResource** Resource, int32 Slot, int32 Count, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void UnbindResources(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void UnbindUAVs(int32 Slot, int32 Num, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindSampler(SHADERSTAGE Stage, Sampler* Sampler, int32 Slot, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindConstantBuffer(SHADERSTAGE Stage, GPUBuffer* Buffer, int32 Slot, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindVertexBuffers(const GPUBuffer** VertexBuffers, int32 Slot, int32 Count, const uint32* Strides, const uint32* Offsets, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindIndexBuffer(GPUBuffer* IndexBuffer, const INDEXBUFFER_FORMAT format, uint32 offset, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindStencilRef(uint32 Val, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindBlendFactor(XMFLOAT4 Val, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindGraphicsPSO(GraphicsPSO* PSO, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void BindComputePSO(ComputePSO* PSO, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void Draw(int32 VertexCount, uint32 VertexStartingLocation, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DrawIndexed(int32 indexCount, uint32 IndexStartingLocation, uint32 BaseVertexLocation, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DrawInstanced(int32 VertexCount, int32 InstanceID, uint32 VertexStartingLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DrawIndexedInstanced(int32 indexCount, int32 InstanceID, uint32 IndexStartingLocation, uint32 BaseVertexLocation, uint32 InstanceStartingLocation, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DrawInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DrawIndexedInstancedIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void Dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 ThreadGroupCount, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void DispatchIndirect(GPUBuffer* Args, uint32 ArgsOffset, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void CopyTexture2D(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void CopyTexture2D_Region(Texture2D* Dst, uint32 DstMip, uint32 DstX, uint32 DstY, Texture2D* Src, uint32 SrcMip, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void MSAAResolve(Texture2D* Dst, Texture2D* Src, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void UpdateBuffer(GPUBuffer* Buffer, const void* Data, GRAPHICSTHREAD ThreadID, int32 DataSize = -1) = 0;
 		virtual void* AllocateFromRingBuffer(GPURingBuffer* Buffer, size_t DataSize, uint32& offsetIntoBuffer, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void InvalidateBufferAccess(GPUBuffer* Buffer, GRAPHICSTHREAD ThreadID) = 0;
 		virtual bool DownloadResource(GPUResource* ResourceToDownload, GPUResource* ResourceDest, void* DataDest, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void QueryBegin(GPUQuery* Query, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void QueryEnd(GPUQuery* Query, GRAPHICSTHREAD ThreadID) = 0;
 		virtual bool QueryRead(GPUQuery* Query, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void UAVBarrier(const GPUResource** UAVS, uint32 NumBarriers, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void TransitionBarrier(const GPUResource** Resource, uint32 NumBarriers, RESOURCE_STATES BeforeState, RESOURCE_STATES AfterState, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void EventBegin(const String& Name, GRAPHICSTHREAD ThreadID) = 0;
 		virtual void EventEnd(GRAPHICSTHREAD ThreadID) = 0;
 		virtual void SetMarker(const String& Name, GRAPHICSTHREAD ThreadID) = 0;
 	};
 }