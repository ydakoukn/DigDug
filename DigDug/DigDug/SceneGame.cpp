#include "SceneGame.h"
#include "GameController.h"
#include "KeyCommand.h"
#include "KeyCommandA.h"
#include "KeyCommandS.h"
#include "SpawnerFor.h"
#include "Enemy.h"
#include "EnemyBase.h"
#include <CollideBoxOBB.h>
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

	// �J�����쐬
	m_camera = std::make_shared<DxCamera::ViewCamera>();
	if (!m_camera)
	{
		assert(!"�J�����쐬���s");
		return;
	}
	
	// �J�����̏����ʒu��ݒ�
	m_camera->Translation(DxMath::Vector3(kCameraDefaultX, kCameraDefaultY, kCameraDefaultZ));
	
	// �V�F�[�_�[�̍쐬
	m_textureShader = std::make_shared<DxShader::TextureShader>();
	if (!m_textureShader)
	{
		assert(!"�V�F�[�_�[�쐬���s");

		return;
	}

	// �g���V�F�[�_�[�t�@�C���̐ݒ�
	result = m_textureShader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");
	if (!result)
	{
		assert(!"�V�F�[�_�[���������s");
		return;
	}

	// �X�e�[�W�̍쐬
	m_stage1 = std::make_unique<Stage1>();
	if (!m_stage1)
	{
		assert(!"�V�F�[�_�[�쐬���s");
		return;
	}
	result = m_stage1->Initialize(m_camera);
	if (!result)
	{
		assert(!"���������s");
		return;
	}

	// �v���C���[�̍쐬
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

	// �X�|�i�[�̍쐬
	m_spawner = std::make_unique<SpawnerFor<Enemy>>();

	// �G�Ǘ��I�u�W�F�N�g�̍쐬
	m_enemyManager = std::make_unique<EnemyManager>();

	// UI�̉摜�̓ǂݍ���
	m_pauseUI = std::make_shared<DxModel::Rectangle>();
	result = m_pauseUI->Initialize(m_camera.get(), "res/Title.png");
	if (!result)
	{
		assert(!"UI���������s");
		return;
	}
	// �傫���̐ݒ�
	m_pauseUI->Scaling() = 100;
	// �����ʒu�̐ݒ�
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

			// �I�[�v�j���O���ɐi�ގw��ʒu���擾
			if (m_stage1->GetStageData(x, y) == kStartPoint)
			{
				m_openningPoint.x = x*kTipSize;
				m_openningPoint.y = y*kTipSize;
			}

			// ���C�t�̕\���ꏊ���擾
			if (m_stage1->GetStageData(x, y) == kPlayerLife)
			{
				m_player->SetLife(x, y);
			}

			static int i = 0;
			// �G�̏����ʒu
			if (m_stage1->GetStageData(x, y) == kEnemy)
			{
				std::shared_ptr<EnemyBase> enemy = m_spawner->Create();
				enemy->Initialize(m_camera, "res/teki2.png");
				enemy->SetPosition(DxMath::Vector3(x*kTipSize, y*kTipSize, kFrontLayer));

				// �����̊Ď��Ώۂɂ���
				m_enemyManager->AddChild(enemy);

			}

		}
	}

	return;
}

//
void SceneGame::Render(){

	m_camera->Render();

	m_stage1->StageRender(m_textureShader);

	m_player->Render(m_textureShader);

	m_enemyManager->Render(m_textureShader);
	return;
}

//
void SceneGame::Updata(){
	
	IsPause();

	Openning();

	Main();

	Pause();

	DigHole();

	return;
}

// �ŏ��̃I�[�v�j���O
// �i�ŏ��̃v���C���[����Ɋ֌W�Ȃ������Ői�ޏ����j
void SceneGame::Openning(){
	if (m_nowState != eState::eOpenning)
	{
		return;
	}

	static bool xflg = false;
	static bool yflg = false;
	std::shared_ptr<KeyCommand> command;

	// xflg��false�̏�ԂȂ�x�����ɐi��
	if (!xflg)
	{
		if (m_player->GetPosition()._x > m_openningPoint.x)
		{
			command = std::make_shared<KeyCommandA>();
			m_player->EventUpdater(command.get());
			if (m_player->GetPosition()._x == m_openningPoint.x)
			{
				xflg = true;
			}
		}
	}

	// x������i�ݏI���Ă���y�����Ɉړ�
	if (xflg)
	{
		if (m_player->GetPosition()._y > m_openningPoint.y)
		{
			command = std::make_shared<KeyCommandS>();
			m_player->EventUpdater(command.get());
			if (m_player->GetPosition()._y == m_openningPoint.y)
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


// �����@��
void SceneGame::DigHole(){

	const int number = m_stage1->GetStageData(m_player->GetPosition());

	// �y�u���b�N�݂̂��폜
	if (number == kSoilLevel1 || number == kSoilLevel2 ||
		number == kSoilLevel3 || number == kSoilLevel4)
	{
		m_stage1->ChangeStageNumber(m_player->GetPosition(), kBlackSpace);
		
	}

	for (auto enemy : m_enemyManager->GetEnemyList())
	{
		DxMath::Vector3 position = enemy->GetProperty()._transform._translation;
		const int enemyNumber = m_stage1->GetStageData(position);
		if (enemyNumber == kSoilLevel1 || enemyNumber == kSoilLevel2 ||
			enemyNumber == kSoilLevel3 || enemyNumber == kSoilLevel4)
		{
			enemy->Collide();
		}
	}
	

	return;
}


// �Q�[���̃��C��
void SceneGame::Main(){
	
	if (m_nowState != eState::eMain)
	{
		return;
	}
	m_player->Update();

	m_enemyManager->Updater();
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



