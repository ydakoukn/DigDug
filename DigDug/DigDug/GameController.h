#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#include <memory>
class GameController
{
	public:
		void Initialize();
		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);
		
		static void Create();

		static void Shutdown();
		static GameController* GetPtr();

	private:
		bool m_keys[256];
		static GameController* m_controller;

	private:
		GameController();
		GameController(GameController&);
		~GameController();
};

#endif