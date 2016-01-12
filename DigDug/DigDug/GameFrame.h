#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H

// �W�����C�u����
#include <memory>

// ���색�C�u����
#include <Direct3DManager.h>
#include <Rectangle.h>
#include <ViewCamera.h>

// ����N���X
#include "SceneManager.h"

// constants
namespace{
	const bool kFullScreen= false;
	const bool kVsyncEnabled = true;
	const float kScreenDepth = 1000.0f;
	const float kScreenNear = 0.1f;
}


class GameFrame
{

	private:
		std::shared_ptr <Dx11::Direct3DManager> m_d3d11Manager;
		std::unique_ptr <SceneManager> m_sceneManager;

	public:
		GameFrame();
		GameFrame(GameFrame&);
		~GameFrame();
		
		bool Initialize(POINT,HWND);

		bool Updatar();

		void Shutdown();
};

#endif