#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#include <memory>
#include <unordered_map>
class SceneBase;

class SceneManager
{
	public:
		SceneManager();
		SceneManager(SceneManager&);
		~SceneManager();

		bool Initialize();
		
		bool SceneUpdatar();
		bool SceneRender();
		void SceneChanger(std::string);
		void SceneShutdown();

		void Shutdown();

	private:
		enum class eGameState{
			eNone,
			eInitialize,
			eUpData,
			eRender,
			eShutdown,
			eChangeScene,
		};
	private:
		void Register(const std::shared_ptr<SceneBase>);
		std::shared_ptr<SceneBase> FindScene(std::string);
		void SceneInitialize();
	private:
		static std::unordered_map<std::string, std::shared_ptr<SceneBase>> m_scenesMap;
		static std::shared_ptr<SceneBase> m_currentScene;
		static eGameState m_gameState;
};

#endif