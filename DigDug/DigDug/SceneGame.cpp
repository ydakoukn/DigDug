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

// �V�[���̖��O��ݒ�
const std::string SceneGame::m_thisName = "Game";
SceneGame::eState SceneGame::m_nowState = SceneGame::eState::eOpenning; // ���݂̏��
SceneGame::eState SceneGame::m_prevState = SceneGame::eState::eNull;	//�@�O��̏��

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

// �������
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
		assert(!"�J�����쐬���s");
		return;
	}
	
	// �J�����̈ʒu��ݒ�
	m_camera->Translation(DxMath::Vector3(kCameraDefaultX, kCameraDefaultY, kCameraDefaultZ));
	

	m_textureShader = std::make_shared<DxShader::TextureShader>();
	if (!m_textureShader)
	{
		assert(!"�V�F�[�_�[�쐬���s");

		return;
	}

	result = m_textureShader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");
	if (!result)
	{
		assert(!"�V�F�[�_�[���������s");
		return;
	}

	m_stage1 = std::make_unique<Stage1>();
	if (!m_stage1)
	{
		assert(!"�V�F�[�_�[�쐬���s");
		return;
	}
	m_stage1->Initialize(m_camera);

	m_player = std::make_unique<PlayerManager>();
	if (!m_player)
	{
		assert(!"�v���C���[�쐬���s");
		return;
	}
	result = m_player->Initialize(m_camera);
	if (!result)
	{
		assert(!"���������s");
		return;
	}

	m_pauseUI = std::make_shared<DxModel::Rectangle>();
	result = m_pauseUI->Initialize(m_camera.get(), "res/Title.png");
	if (!result)
	{
		assert(!"UI���������s");
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

			// �ŏ��̎w��ʒu���擾
			if (m_stage1->GetStageData(x, y) == kStartPoint)
			{
				m_startPoint.x = x*kTipSize;
				m_startPoint.y = y*kTipSize;
			}

			// ���C�t�̕\���ꏊ���擾
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

// �����@��
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

// �ŏ��̃I�[�v�j���O�p
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

	// x������i�ݏI���Ă���y�����Ɉړ�
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

	// �ŏ��̖ړI�n�ɒ�������A�Q�[���X�^�[�g
	if (xflg&&yflg)
	{
		command = std::make_shared<KeyCommandA>();
		m_player->EventUpdater(command.get());
		m_nowState = eState::eMain;
	}
}

// �Q�[���̃��C��
void SceneGame::Main(){
	
	if (m_nowState != eState::eMain)
	{
		return;
	}
	m_player->Update();

	
	return;
}

// �|�[�Y��ʂɍs�����s���Ȃ���
void SceneGame::IsPause(){
	if (GameController::Get().IsKeyDown('Q'))
	{
		if (m_nowState != eState::ePause)
		{
			m_prevState = m_nowState;
			m_nowState = eState::ePause;
			std::cout << "�|�[�Y��ʂɈڍs" << std::endl;
		}
	}
}

// �|�[�Y��ʗp
void SceneGame::Pause(){
	if (m_nowState != eState::ePause)
	{
		return;
	}
	m_pauseUI->Render(m_textureShader,DxModel::eRenderWay::eTexture);
	ReturnPrevState();
}

// �O��̏�Ԃɖ߂�
void SceneGame::ReturnPrevState(){
	if (GameController::Get().IsKeyDown('E'))
	{
		m_nowState = m_prevState;
	}
}



