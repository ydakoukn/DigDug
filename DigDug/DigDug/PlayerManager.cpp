#include "PlayerManager.h"
#include "Cube.h"
// ステージの動ける範囲
namespace{
	const int kX = 5;
	const int kWidth = 300;
	const int kY = 335;
	const int kHeight = 25;
	const int kTipSize = 20;
}
PlayerManager::PlayerManager(){
	
	m_render = nullptr;
	m_updater = nullptr;
}

PlayerManager::PlayerManager(PlayerManager&){}

PlayerManager::~PlayerManager(){
	Shutdown();
}


bool PlayerManager::Initialize(const std::shared_ptr<DxCamera::ViewCamera> camera){
	bool result;

	m_cameraAddress = camera;

	m_playerModel = std::make_shared<DxModel::Rectangle>();
	m_playerModel->Initialize(camera.get(), "res/player.png");
	
	m_updater = std::make_shared<PlayerUpdater>();
	result = m_updater->Initialize(m_playerModel);
	if (!result)
	{
		return false;
	}
	
	m_render = std::make_unique<PlayerRender>();
	result = m_render->Initialize();
	if (!result)
	{
		return false;
	}

	return true;
}


void PlayerManager::Render(const std::shared_ptr<DxShader::ShaderBase> shader){
	m_render->Frame(m_playerModel,shader);

	for (auto index : m_life)
	{
		index->Render(shader,DxModel::eRenderWay::eTexture);
	}
}


void PlayerManager::Update(){
	m_updater->Frame();
	if (GetPosition()._x < kX)
	{
		m_updater->GetVector()._x = kX;
	}
	else
	if (GetPosition()._x > kWidth)
	{
		m_updater->GetVector()._x = kWidth;
	}
	else 
	if (GetPosition()._y > kY)
	{
		m_updater->GetVector()._y = kY;
	}
	else
	if (GetPosition()._y < kHeight)
	{
		m_updater->GetVector()._y = kHeight;
	}

	for (auto index : m_life)
	{
		index->Rotation()._y -= 1;
	}
}

void PlayerManager::EventUpdater(KeyCommand* command){
	m_updater->EventFrame(command);
}

DxMath::Vector3& PlayerManager::GetPosition(){

	return m_updater->GetVector();
	
}

void PlayerManager::SetLife(int x, int y){

	float tipX = x * kTipSize;
	float tipY = y * kTipSize;
	std::shared_ptr<DxModel::ModelBase> pushObject = std::make_shared<DxModel::Cube>();
	pushObject->Initialize(m_cameraAddress.get(), "res/player.png");
	pushObject->Translation(DxMath::Vector3(tipX, tipY, -1));
	pushObject->Scaling(DxMath::Vector3(kTipSize / 2, kTipSize / 2, kTipSize / 2));
	m_life.push_back(pushObject);
}

void PlayerManager::Shutdown(){
	if (m_updater)
	{
		m_updater.reset();
		m_updater = nullptr;
	}

	if (m_render)
	{
		m_render.release();
		m_render = nullptr;
	}
}