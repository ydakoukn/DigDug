#include "EnemyBase.h"
#include <Rectangle.h>
namespace{
	const int kTipSize = 20;
}

EnemyBase::EnemyBase()
{
}


EnemyBase:: ~EnemyBase()
{
}

//
void EnemyBase::Initialize(std::shared_ptr<DxCamera::ViewCamera> camera, std::string path){

	GetProperty()._enemy = std::make_shared<DxModel::Rectangle>();
	GetProperty()._enemy->Initialize(camera.get(), path);
	GetProperty()._enemy->Scaling(DxMath::Vector3(kTipSize / 2, kTipSize / 2, kTipSize / 2));
	InitializeBuffer();
}

//
void EnemyBase::Render(std::shared_ptr<DxShader::ShaderBase> shader){
	GetProperty()._enemy->Render(shader, DxModel::eRenderWay::eTexture);
	GetProperty()._enemy->Translation(DxMath::Vector3(GetProperty()._transform._translation._x, GetProperty()._transform._translation._y, GetProperty()._transform._translation._z));
	GetProperty()._enemy->Rotation(DxMath::Vector3(GetProperty()._transform._rotation._x, GetProperty()._transform._rotation._y, GetProperty()._transform._rotation._z));
	RenderBuffer();
}

EnemyBase::Property& EnemyBase::GetProperty(){
	return m_property;
}

//
void EnemyBase::Updater(){

	
	UpdateBuffer();
}

//
void EnemyBase::Collide(){
	m_isColldie = true;
	if (m_isColldie)
	{
		CollideBuffer();
	}
	m_isColldie = false;
}

//
void EnemyBase::SetPosition(DxMath::Vector3 position){
	GetProperty()._transform._translation = position;
}