#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include "SceneBase.h"

class SceneGame :
	public SceneBase
{
	public:
		SceneGame(SceneManager*);
		~SceneGame();

		void InitializeScene()override;
		void UpDataScene()override;
		void RenderScene()override;
		void ShutdownScene()override;

	public:
		static const std::string m_thisName;
};

#endif