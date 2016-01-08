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

//
void PlayerRender::Frame(const std::shared_ptr<DxModel::ModelBase>& player,const std::shared_ptr<DxShader::ShaderBase> shader){
	player->Render(shader, DxModel::eRenderWay::eTexture);
	player->Translation(DxMath::Vector3(GetStatus()._position._x, GetStatus()._position._y, GetStatus()._position._z));
	player->Rotation(DxMath::Vector3(GetStatus()._rotation._x, GetStatus()._rotation._y, GetStatus()._rotation._z));
}

void PlayerRender::Shutdown(){
	return;
}