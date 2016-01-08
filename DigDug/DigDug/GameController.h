#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H

#include "KeyCommand.h"
#include <memory>
namespace{
	const int kMaxKeyType = 256;
}

class GameController
{
	public:
		void Initialize();
		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);
		static void Create();

		static void Shutdown();
		static GameController& Get();

		std::unique_ptr<KeyCommand> GetKeyCommnad();
	private:
		bool m_keys[kMaxKeyType];
		static GameController* m_controller;
	
	private:
		GameController();
		GameController(GameController&);
		~GameController();
};

#endif