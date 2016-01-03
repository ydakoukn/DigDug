#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	Player��Updater�N���X
	�X�V������S��

*/
#include <ModelBase.h>

#include "PlayerBase.h"
class PlayerUpdater :
	private PlayerBase
{
	
	public:
		PlayerUpdater();
		PlayerUpdater(PlayerUpdater&);
		~PlayerUpdater();
		bool Initialize(const std::shared_ptr<DxModel::ModelBase>&);
		void Frame();
		DxMath::Vector3& GetVector();

	private:
	
		void Shutdown();
		void Run()override;

};

#endif