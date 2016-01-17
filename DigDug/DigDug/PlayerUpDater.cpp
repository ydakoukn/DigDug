#include <Windows.h>
#include <iostream>
#include <memory>
#include "PlayerUpdater.h"
#include "GameController.h"
#include "KeyCommandW.h"
PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}

namespace{
	const int kTipSize = 20;
	const int kLeft = -180;
	const int kDown = -90;
}

PlayerUpdater::~PlayerUpdater(){
	Shutdown();
}

//
bool PlayerUpdater::Initialize(const std::shared_ptr<DxModel::ModelBase>& object){
	
	// •`‰æ•¨‚Ì‰ŠúˆÊ’u‚ÍPlayer‚Æˆê
	object->Translation()._x = GetStatus()._position._x;
	object->Translation()._y = GetStatus()._position._y;
	object->Translation()._z = GetStatus()._position._z;

	// Set size
	DxMath::Vector3 scale(kTipSize/2, kTipSize/2, kTipSize/2);
	GetStatus()._scale = scale;

	object->Scaling(DxMath::Vector3(GetStatus()._scale._x, GetStatus()._scale._y, GetStatus()._scale._z));

	// Å‰‚Í¶‚ğŒü‚¢‚Ä‚¢‚é
	GetStatus()._rotation._y = kLeft;
	return true;
}

void PlayerUpdater::Frame(){

	this->RunCommand();

	return;
}

void PlayerUpdater::RunCommand(){

	// ƒL[“ü—Íˆ—
	std::unique_ptr<KeyCommand> command = GameController::Get().GetKeyCommnad();
	command->Run(*this);

	return;
}

void PlayerUpdater::EventFrame(KeyCommand* command){
	command->Run(*this);
}

void PlayerUpdater::Shutdown(){
	return;
}

DxMath::Vector3& PlayerUpdater::GetVector(){
	return GetStatus()._position;
}