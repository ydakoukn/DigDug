#ifndef _SCENETITLE_H
#define _SCENETITLE_H
#include "SceneBase.h"
class SceneTitle :
	public SceneBase
{
	public:
		SceneTitle(SceneManager* manager);
		~SceneTitle();

		void InitializeScene()override;
		void UpDataScene()override;
		void RenderScene()override;
		void ShutdownScene()override;

	public:
		static const std::string m_thisName;
};

#endif