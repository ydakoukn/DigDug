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
}

PlayerUpdater::~PlayerUpdater(){
	Shutdown();
}

bool PlayerUpdater::Initialize(const std::shared_ptr<DxModel::ModelBase>& object){
	
	DxMath::Vector3 position(kTipSize / 4, 340, -20);
	
	GetStatus()._vector = position;
	
	object->Translation()._x = GetStatus()._vector._x;
	object->Translation()._y = GetStatus()._vector._y;
	object->Translation()._z = GetStatus()._vector._z;
	DxMath::Vector3 scale(kTipSize / 2, kTipSize / 2, 10);
	GetStatus()._scale = scale;
	object->Scaling(DxMath::Vector3(GetStatus()._scale._x, GetStatus()._scale._y, GetStatus()._scale._z));

	return true;
}

void PlayerUpdater::Run(){

	std::unique_ptr<KeyCommand> command = GameController::Get().GetKeyCommnad();
	command->Run(*this);

	return;
}

void PlayerUpdater::Frame(){

	this->Run();

	return;
}

void PlayerUpdater::Shutdown(){
	return;
}

DxMath::Vector3& PlayerUpdater::GetVector(){
	return GetStatus()._vector;
}