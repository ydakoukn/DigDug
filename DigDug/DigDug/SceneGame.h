#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include <ShaderBase.h>
#include <TextureShader.h>
#include <ModelBase.h>
#include "SceneBase.h"
#include "Stage1.h"
#include "PlayerManager.h"
class SceneGame :
	public SceneBase
{
	public:
		static const std::string m_thisName;

	public:
		SceneGame(SceneManager*);
		~SceneGame();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	private:

		// ���̃V�[���ɕK�v�ȏ��
		enum class eState{
			eNull = 0,
			ePause,
			eOpenning,
			eMain,
			eEnd,
		};

	private:
		std::unique_ptr<Stage1> m_stage1;
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		std::shared_ptr<DxShader::TextureShader> m_textureShader;
		std::unique_ptr<PlayerManager> m_player;
		std::shared_ptr <DxModel::ModelBase> m_pauseUI;

		POINT m_openningPoint;
		static eState m_nowState;
		static eState m_prevState;

	private:
		void Openning();    // �I�[�v�j���O�p
		void Main();        // �Q�[���̃��C���A�v���C���[������ł���
		void Pause();       // �|�[�Y���
		void DigHole();     // ���̊֐����Ăяo���ƌ����@����
		void IsPause();     // �|�[�Y��ʂ��ĂԂ��Ă΂Ȃ���
		void ReturnPrevState();  // �|�[�Y�ɓ���O�̏�Ԃɂ���

};

#endif