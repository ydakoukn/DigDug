#include "SceneGame.h"
#include "GameController.h"
const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager){	}

SceneGame::~SceneGame(){

	Shutdown();
}


void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	bool result;
	std::cout << "Start game" << std::endl;

	m_camera = std::make_shared<DxCamera::ViewCamera>();
	if (!m_camera)
	{
		std::cout << "カメラ作成失敗" << std::endl;
		return;
	}
	
	m_camera->SetPosition(300, 230, -600);
	

	m_textureShader = std::make_shared<DxShader::TextureShader>();
	if (!m_textureShader)
	{
		std::cout << "シェーダー作成失敗" << std::endl;
		return;
	}

	result = m_textureShader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");
	if (!result)
	{
		std::cout << "シェーダー初期化失敗" << std::endl;
		return;
	}

	m_stage1 = std::make_unique<Stage1>();
	if (!m_stage1)
	{
		std::cout << "ステージ作成失敗" << std::endl;
		return;
	}
	m_stage1->Initialize(m_camera);

	m_player = std::make_unique<PlayerManager>();
	if (!m_player)
	{
		std::cout << "プレイヤー作成失敗" << std::endl;
		return;
	}
	result = m_player->Initialize(m_camera);
	if (!result)
	{
		std::cout << "失敗" << std::endl;
	}

	return;
}
float a = 0;
void SceneGame::Updata(){
	
	m_player->Update();

	m_stage1->GetStageData(m_player->GetPosition());

	return;
}


void SceneGame::Render(){

	
	m_camera->Render();

	m_stage1->StageRender(m_textureShader);

	m_player->Render(m_textureShader);

	
	return;
}

void SceneGame::Shutdown(){
	if (m_player)
	{
		m_player.release();
		m_player = nullptr;
	}
	if (m_stage1)
	{
		m_stage1->Shutdown();
		m_stage1.release();
		m_stage1 = nullptr;
	}
	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		m_textureShader.reset();
		m_textureShader = nullptr;
	}
	if (m_camera)
	{
		m_camera.reset();
		m_camera = nullptr;
	}
	return;
}