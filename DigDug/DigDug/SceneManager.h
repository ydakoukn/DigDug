#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#include <memory>
#include <unordered_map>
class SceneBase;

class SceneManager
{
	public:
		SceneManager();
		~SceneManager();

		bool UpData();
		bool Initialize();
		bool Render();
		void Shutdown();
		void ChangeScene(std::string);

		bool Frame();

	private:
		enum class GameState{
			eNone,
			eInitialize,
			eUpData,
			eRender,
			eShutdown,
		};
	private:
		void Register(const std::shared_ptr<SceneBase>);
		
		std::shared_ptr<SceneBase> GetScene(std::string);

		GameState m_state;
	private:
		static std::unordered_map<std::string, std::shared_ptr<SceneBase>> m_scenes;
		static std::shared_ptr<SceneBase> m_currentScene;
		static std::shared_ptr<SceneBase> m_nextScene;
};

#endif