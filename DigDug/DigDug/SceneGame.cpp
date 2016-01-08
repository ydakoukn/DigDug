#include "SceneGame.h"
#include "GameController.h"
#include "KeyCommand.h"
#include "KeyCommandA.h"
#include "KeyCommandS.h"
#include <assert.h>
namespace{
	const float kCameraDefaultX = 260.0f;
	const float kCameraDefaultY = 190.0f;
	const float kCameraDefaultZ = -500.0f;
	const float kFrontLayer = -20.0f;
	const float kPauseBackgroundX = 420.0f;
	const float kPauseBackgroundY = 220.0f;
}

// シーンの名前を設定
const std::string SceneGame::m_thisName = "Game";
SceneGame::eState SceneGame::m_nowState = SceneGame::eState::eOpenning; // 現在の状態
SceneGame::eState SceneGame::m_prevState = SceneGame::eState::eNull;	//　前回の状態

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName, *manager){

	m_player = nullptr;
	m_stage1 = nullptr;
	m_textureShader = nullptr;
	m_camera = nullptr;
}

SceneGame::~SceneGame(){

	Shutdown();
}

// 解放処理
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

void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	bool result;
	std::cout << "Start game" << std::endl;

	m_camera = std::make_shared<DxCamera::ViewCamera>();
	if (!m_camera)
	{
		assert(!"カメラ作成失敗");
		return;
	}
	
	// カメラの位置を設定
	m_camera->Translation(DxMath::Vector3(kCameraDefaultX, kCameraDefaultY, kCameraDefaultZ));
	

	m_textureShader = std::make_shared<DxShader::TextureShader>();
	if (!m_textureShader)
	{
		assert(!"シェーダー作成失敗");

		return;
	}

	result = m_textureShader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");
	if (!result)
	{
		assert(!"シェーダー初期化失敗");
		return;
	}

	m_stage1 = std::make_unique<Stage1>();
	if (!m_stage1)
	{
		assert(!"シェーダー作成失敗");
		return;
	}
	m_stage1->Initialize(m_camera);

	m_player = std::make_unique<PlayerManager>();
	if (!m_player)
	{
		assert(!"プレイヤー作成失敗");
		return;
	}
	result = m_player->Initialize(m_camera);
	if (!result)
	{
		assert(!"初期化失敗");
		return;
	}

	m_pauseUI = std::make_shared<DxModel::Rectangle>();
	result = m_pauseUI->Initialize(m_camera.get(), "res/Title.png");
	if (!result)
	{
		assert(!"UI初期化失敗");
		return;
	}
	m_pauseUI->Scaling() = 100;
	m_pauseUI->Translation()._x = kPauseBackgroundX;
	m_pauseUI->Translation()._y = kPauseBackgroundY;
	// serch player first position
	for (int y = 0; y < kStageHeight; ++y)
	{
		for (int x = 0; x < kStageWidth; ++x)
		{
			if (m_stage1->GetStageData(x, y) == kPlayer)
			{
				//set player first position
				m_player->GetPosition()._x = x*kTipSize;
				m_player->GetPosition()._y = y*kTipSize;
				m_player->GetPosition()._z = kFrontLayer;
			}

			// 最初の指定位置を取得
			if (m_stage1->GetStageData(x, y) == kStartPoint)
			{
				m_startPoint.x = x*kTipSize;
				m_startPoint.y = y*kTipSize;
			}

			// ライフの表示場所を取得
			if (m_stage1->GetStageData(x, y) == kPlayerLife)
			{
				m_player->SetLife(x, y);
			}

		}
	}

	return;
}


void SceneGame::Render(){

	m_camera->Render();

	m_stage1->StageRender(m_textureShader);

	m_player->Render(m_textureShader);

	return;
}

void SceneGame::Updata(){
	
	IsPause();

	Openning();

	Main();

	Pause();

	DigHole();

	return;
}

// 穴を掘る
void SceneGame::DigHole(){

	const int number = m_stage1->GetStageData(m_player->GetPosition());

	switch (number)
	{
	case kSoilLevel1:
	case kSoilLevel2:
	case kSoilLevel3:
	case kSoilLevel4:

		m_stage1->ChangeStageNumber(m_player->GetPosition(), kBlackSpace);
		break;
	}

}

// 最初のオープニング用
void SceneGame::Openning(){
	if (m_nowState != eState::eOpenning)
	{
		return;
	}

	static bool xflg = false;
	static bool yflg = false;
	std::shared_ptr<KeyCommand> command;

	if (!xflg)
	{
		if (m_player->GetPosition()._x > m_startPoint.x)
		{
			command = std::make_shared<KeyCommandA>();
			m_player->EventUpdater(command.get());
			if (m_player->GetPosition()._x == m_startPoint.x)
			{
				xflg = true;
			}
		}
	}

	// x方向を進み終えてからy方向に移動
	if (xflg)
	{
		if (m_player->GetPosition()._y > m_startPoint.y)
		{
			command = std::make_shared<KeyCommandS>();
			m_player->EventUpdater(command.get());
			if (m_player->GetPosition()._y == m_startPoint.y)
			{
				yflg = true;
			}
		}
	}

	// 最初の目的地に着いたら、ゲームスタート
	if (xflg&&yflg)
	{
		command = std::make_shared<KeyCommandA>();
		m_player->EventUpdater(command.get());
		m_nowState = eState::eMain;
	}
}

// ゲームのメイン
void SceneGame::Main(){
	
	if (m_nowState != eState::eMain)
	{
		return;
	}
	m_player->Update();

	
	return;
}

// ポーズ画面に行くか行かないか
void SceneGame::IsPause(){
	if (GameController::Get().IsKeyDown('Q'))
	{
		if (m_nowState != eState::ePause)
		{
			m_prevState = m_nowState;
			m_nowState = eState::ePause;
			std::cout << "ポーズ画面に移行" << std::endl;
		}
	}
}

// ポーズ画面用
void SceneGame::Pause(){
	if (m_nowState != eState::ePause)
	{
		return;
	}
	m_pauseUI->Render(m_textureShader,DxModel::eRenderWay::eTexture);
	ReturnPrevState();
}

// 前回の状態に戻る
void SceneGame::ReturnPrevState(){
	if (GameController::Get().IsKeyDown('E'))
	{
		m_nowState = m_prevState;
	}
}



