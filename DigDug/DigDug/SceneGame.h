#ifndef _SCENEGAME_H
#define _SCENEGAME_H


#include <ShaderBase.h>
#include <TextureShader.h>

#include "SceneBase.h"
#include "Stage1.h"
class SceneGame :
	public SceneBase
{
	public:
		SceneGame(SceneManager*);
		~SceneGame();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render(Dx11::Direct3DManager*)override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;

	private:
		std::unique_ptr<Stage1> m_stage1;
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		std::shared_ptr<DxShader::TextureShader> m_textureShader;
};

#endif