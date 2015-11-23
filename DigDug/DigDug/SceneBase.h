#ifndef _SCENEBASE_H
#define _SCENEBASE_H
#include <string>
#include<iostream>
#include "SceneManager.h"
class SceneBase
{
	
	public:
		SceneBase(const std::string &name,SceneManager& manager):
		m_sceneName(name),
		m_manager(manager){}
		virtual ~SceneBase() = default;
		virtual void InitializeScene() = 0;
		virtual void UpDataScene() = 0;
		virtual void RenderScene() = 0;
		virtual void ShutdownScene() = 0;
		const std::string GetName(){ return m_sceneName; }

	protected:
		SceneManager& m_manager;

	private:
		const std::string m_sceneName;
		
};

#endif