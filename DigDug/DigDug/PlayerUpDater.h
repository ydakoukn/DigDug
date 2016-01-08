#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	PlayerのUpdaterクラス
	更新処理を担当

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