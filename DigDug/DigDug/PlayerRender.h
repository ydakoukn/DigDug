/*
	Playerのレンダークラス
	描画処理を担当

*/
#ifndef _PLAYERRENDER_H
#define _PLAYERRENDER_H

#include <memory>

#include <TextureShader.h>
#include <ShaderBase.h>
#include <Rectangle.h>

#include "PlayerBase.h"


class PlayerRender :
	private PlayerBase
{
	
	public:
		PlayerRender();
		PlayerRender(PlayerRender&);
		~PlayerRender();
		bool Initialize();
		void Frame(const std::shared_ptr<DxModel::ModelBase>&,const std::shared_ptr<DxShader::ShaderBase>);
	private:

		void Run()override;
		void Shutdown();
	private:

};

#endif