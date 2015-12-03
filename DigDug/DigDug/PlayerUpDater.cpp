#include <Windows.h>
#include <iostream>
#include "PlayerUpdater.h"
#include "GameController.h"

PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}

namespace{
	const int kTipSize = 20;
}

PlayerUpdater::~PlayerUpdater(){
	Shutdown();
}

bool PlayerUpdater::Initialize(const std::shared_ptr<DxModel::ModelBase>& object){
	
	Vector3 position(kTipSize/4, 340, -20);
	
	GetStatus()._vector = position;
	
	object->Translation().x = GetStatus()._vector._x;
	object->Translation().y = GetStatus()._vector._y;
	object->Translation().z = GetStatus()._vector._z;
	Scale scale(kTipSize / 2, kTipSize / 2, 10);
	GetStatus()._scale = scale;
	object->Scaling(D3DXVECTOR3(GetStatus()._scale._x, GetStatus()._scale._y, GetStatus()._scale._z));

	return true;
}

void PlayerUpdater::Run(){




	if (GameController::GetPtr()->IsKeyDown('D'))
	{
		GetStatus()._vector._x += 1.0f;
	}
	
	
	return;
}

void PlayerUpdater::Frame(){

	this->Run();

	return;
}

void PlayerUpdater::Shutdown(){
	return;
}

Vector3& PlayerUpdater::GetVector(){
	return GetStatus()._vector;
}