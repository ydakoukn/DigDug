#include "PlayerRender.h"
#include <iostream>
PlayerRender::PlayerRender(){

}
PlayerRender::PlayerRender(PlayerRender& other){}

PlayerRender::~PlayerRender(){

	Shutdown();

}

bool PlayerRender::Initialize(){
	
	return true;
}

void PlayerRender::Run(){
	
	return;
}

void PlayerRender::Frame(const std::shared_ptr<DxModel::ModelBase>& player,const std::shared_ptr<DxShader::ShaderBase> shader){

	player->Render(shader, DxModel::eRenderWay::eTexture);
	player->Translation(DxMath::Vector3(GetStatus()._vector._x, GetStatus()._vector._y, GetStatus()._vector._z));
	player->Rotation(DxMath::Vector3(GetStatus()._rotation._x, GetStatus()._rotation._y, GetStatus()._rotation._z));

}

void PlayerRender::Shutdown(){
	return;
}