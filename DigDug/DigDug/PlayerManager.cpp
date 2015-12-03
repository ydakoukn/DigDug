#include "PlayerManager.h"


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

	

	m_playerModel = std::make_shared<DxModel::Rectangle>();
	m_playerModel->Initialize(camera.get(), "res/player.png");
	
	m_updater = std::make_unique<PlayerUpdater>();
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
}


void PlayerManager::Update(){
	m_updater->Frame();
}

Vector3  PlayerManager::GetPosition(){

	return m_updater->GetVector();
	
}

void PlayerManager::Shutdown(){
	if (m_updater)
	{
		m_updater.release();
		m_updater = nullptr;
	}

	if (m_render)
	{
		m_render.release();
		m_render = nullptr;
	}
}