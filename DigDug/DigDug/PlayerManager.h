#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
/*
Player管理クラス
updaterとrenderのオブジェクトを保持し、
playerの状態の管理などを請け負うとこ？

*/
#include <memory>
#include <ShaderBase.h>

#include "PlayerBase.h"
#include "PlayerUpdater.h"
#include "PlayerRender.h"

class PlayerManager
{

	public:
		PlayerManager();
		PlayerManager(PlayerManager&);
		~PlayerManager();

		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		void Render(const std::shared_ptr<DxShader::ShaderBase>);
		void Update();
		Vector3 GetPosition();
	private:
		void Shutdown();
	private:
		std::unique_ptr<PlayerUpdater> m_updater;
		std::unique_ptr<PlayerRender> m_render;
		std::shared_ptr<DxModel::ModelBase> m_playerModel;
};

#endif