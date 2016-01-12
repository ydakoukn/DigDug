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

		// このシーンに必要な状態
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
		void Openning();    // オープニング用
		void Main();        // ゲームのメイン、プレイヤーが操作できる
		void Pause();       // ポーズ画面
		void DigHole();     // この関数を呼び出すと穴が掘られる
		void IsPause();     // ポーズ画面を呼ぶか呼ばないか
		void ReturnPrevState();  // ポーズに入る前の状態にする

};

#endif