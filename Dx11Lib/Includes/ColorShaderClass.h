#ifndef _COLORSHADERCLASS_H
#define _COLORSHADERCLASS_H
#include <D3D11.h>
#include <d3dx10math.h>
#include <D3DX11async.h>
#include <fstream>

namespace Shader{
	class ColorShaderClass
	{

	private:
		struct MatrixBufferType{
			MatrixBufferType() = default;
			~MatrixBufferType() = default;
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};
	public:
		ColorShaderClass();
		ColorShaderClass(const ColorShaderClass&);
		~ColorShaderClass();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

	private:
		bool InitializeShader(ID3D11Device*, HWND, WCHAR* vsFillName, WCHAR* psFillName);
		void ShutdownShader();
		void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

		bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

		void RenderShader(ID3D11DeviceContext*, int);

	private:
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;

	};


}

#endif