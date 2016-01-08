#ifndef _SCENETITLE_H
#define _SCENETITLE_H
#include "SceneBase.h"
// フレームワーク
#include <Rectangle.h>
class SceneTitle :
	public SceneBase
{
	public:
		SceneTitle(SceneManager* manager);
		~SceneTitle();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;

	private:
		std::unique_ptr<DxModel::ModelBase> m_titleBackground;
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		std::shared_ptr<DxShader::TextureShader> m_textureShader;
};

#endif