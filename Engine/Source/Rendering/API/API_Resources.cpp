#include "Rendering/API/API_Resources.h"

/** @todo(Chrisr): Implement the Shader functions inside of the API Contextes and uncomment the func call here */

namespace MARS
{
	inline namespace GRAPHICS
	{
		VertexShader::VertexShader()
		{
		}
		VertexShader::~VertexShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyVertexShader(this);
			}
		}

		PixelShader::PixelShader()
		{
		}
		PixelShader::~PixelShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyPixelShader(this);
			}
		}

		GeometryShader::GeometryShader()
		{
		}
		GeometryShader::~GeometryShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyGeometryShader(this);
			}
		}

		DomainShader::DomainShader()
		{
		}
		DomainShader::~DomainShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyDomainShader(this);
			}
		}

		HullShader::HullShader()
		{
		}
		HullShader::~HullShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyHullShader(this);
			}
		}

		ComputeShader::ComputeShader()
		{
		}
		ComputeShader::~ComputeShader()
		{
			if (Device != nullptr)
			{
				//Device->DestroyComputeShader(this);
			}
		}

		Sampler::Sampler()
		{
		}
		Sampler::~Sampler()
		{
			if (Device != nullptr)
			{
				//Device->DestroySamplerState(this);
			}
		}

		GPUResource::GPUResource()
		{
		}
		GPUResource::~GPUResource()
		{
			if (Device != nullptr)
			{
				//Device->DestroyResource(this);
			}
		}

		GPUBuffer::GPUBuffer() : GPUResource()
		{
		}
		GPUBuffer::~GPUBuffer()
		{
			if (Device != nullptr)
			{
				//Device->DestroyBuffer(this);
			}
		}

		VertexLayout::VertexLayout()
		{
		}
		VertexLayout::~VertexLayout()
		{
			if (Device != nullptr)
			{
				//Device->DestroyInputLayout(this);
			}
		}

		BlendState::BlendState()
		{
		}
		BlendState::~BlendState()
		{
			if (Device != nullptr)
			{
				//Device->DestroyBlendState(this);
			}
		}

		DepthStencilState::DepthStencilState()
		{
		}
		DepthStencilState::~DepthStencilState()
		{
			if (Device != nullptr)
			{
				//Device->DestroyDepthStencilState(this);
			}
		}

		RasterizerState::RasterizerState()
		{
		}
		RasterizerState::~RasterizerState()
		{
			if (Device != nullptr)
			{
				//Device->DestroyRasterizerState(this);
			}
		}

		Texture::Texture() : GPUResource()
		{
		}
		Texture::~Texture()
		{
		}
		void Texture::RequestIndependentRenderTargetArraySlices(bool Val)
		{
			IndependentRTVArraySlices = Val;
		}
		void Texture::RequestIndependentRenderTargetCubemapFaces(bool Val)
		{
			IndependentRTVCubemapFaces = Val;
		}
		void Texture::RequestIndependentShaderResourceArraySlices(bool Val)
		{
			IndependentSRVArraySlices = Val;
		}
		void Texture::RequestIndependentShaderResourcesForMIPs(bool Val)
		{
			IndependentSRVMIPs = Val;
		}
		void Texture::RequestIndependentUnorderedAccessResourcesForMIPs(bool Val)
		{
			IndependentUAVMIPs = Val;
		}

		Texture1D::Texture1D() :Texture()
		{
		}
		Texture1D::~Texture1D()
		{
			if (Device != nullptr)
			{
				//Device->DestroyTexture1D(this);
			}
		}

		Texture2D::Texture2D() :Texture()
		{
		}
		Texture2D::~Texture2D()
		{
			if (Device != nullptr)
			{
				//Device->DestroyTexture2D(this);
			}
		}

		Texture3D::Texture3D() :Texture()
		{
		}
		Texture3D::~Texture3D()
		{
			if (Device != nullptr)
			{
				//Device->DestroyTexture3D(this);
			}
		}

		GPUQuery::GPUQuery()
		{
			AsyncFrameshift = 0;
		}
		GPUQuery::~GPUQuery()
		{
			if (Device != nullptr)
			{
				//Device->DestroyQuery(this);
			}
		}


		GraphicsPSO::GraphicsPSO()
		{
		}
		GraphicsPSO::~GraphicsPSO()
		{
			if (Device != nullptr)
			{
				//Device->DestroyGraphicsPSO(this);
			}
		}

		ComputePSO::ComputePSO()
		{
		}
		ComputePSO::~ComputePSO()
		{
			if (Device != nullptr)
			{
				//Device->DestroyComputePSO(this);
			}
		}
	}
}