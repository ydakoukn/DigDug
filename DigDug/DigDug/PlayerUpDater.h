#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	Player��Updater�N���X
	�X�V������S��

*/
#include <ModelBase.h>

#include "PlayerBase.h"
#include "KeyCommand.h"
class PlayerUpdater :
	PlayerBase
{
	
	public:
		PlayerUpdater();
		PlayerUpdater(PlayerUpdater&);
		~PlayerUpdater();
		bool Initialize(const std::shared_ptr<DxModel::ModelBase>&);
		void Frame();
		void EventFrame(KeyCommand* command);
		DxMath::Vector3& GetVector();

	private:
	
		void Shutdown();
		void RunCommand();

};

#endif