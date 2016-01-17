#include "SceneTitle.h"
#include "SceneGame.h"
#include "GameController.h"
#include "Cube.h"

const std::string SceneTitle::m_thisName = "Title";
SceneTitle::SceneTitle(SceneManager* manager) :
SceneBase(m_thisName,*manager)
{
	m_camera = nullptr;
	m_textureShader = nullptr;
	m_titleBackground = nullptr;
}


SceneTitle::~SceneTitle()
{
	m_camera = nullptr;
	m_textureShader = nullptr;
	m_titleBackground = nullptr;
}


void SceneTitle::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start title" << std::endl;
	m_camera = std::make_shared<DxCamera::ViewCamera>();
	if (!m_camera)
	{
		std::cout << "カメラ作成失敗" << std::endl;
		return;
	}
	
	m_camera->Translation(DxMath::Vector3(0,0,-100));


	m_textureShader = std::make_shared<DxShader::TextureShader>();
	if (!m_textureShader)
	{
		std::cout << "シェーダー作成失敗" << std::endl;
		return;
	}
	bool result;
	result = m_textureShader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");
	if (!result)
	{
		std::cout << "シェーダー初期化失敗" << std::endl;
		return;
	}

	m_titleBackground = std::make_unique<DxModel::Rectangle>();
	m_titleBackground->Initialize(m_camera.get(), "res/Title.png");

	m_titleBackground->Scaling(DxMath::Vector3(40, 50, -10));

	return;
}


void SceneTitle::Updata(){

	if (GameController::Get().IsKeyDown(VK_SPACE))
	{
		SetChangeScene(SceneGame::m_thisName);
	}
	return;
}


void SceneTitle::Render(){
	m_camera->Render();
	m_titleBackground->Render(m_textureShader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneTitle::Shutdown(){
	m_camera.reset();

	m_textureShader.reset();
	m_titleBackground.release();
	return;
}