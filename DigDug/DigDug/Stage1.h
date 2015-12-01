#ifndef _STAGE1_H
#define _STAGE1_H
// 標準ライブラリ

// 自作ライブラリ

#include <Rectangle.h>
#include <ShaderBase.h>
// 自作クラス

namespace{
	const unsigned int kStageWidth = 16;
	const unsigned int kStageHeight = 20;
	const unsigned int kStageTipSize = 20;
}
class Stage1
{
	public:
		Stage1();
		Stage1(Stage1&);
		~Stage1();
		void Initialize(std::shared_ptr<DxCamera::ViewCamera>);
		void StageRender(std::shared_ptr<DxShader::ShaderBase>);
		void Shutdown();
	private:
		struct StageResorces{
			std::string m_fileName;
		};
	private:
		void ShutdownStage();
	private:
		static int m_stageData[kStageHeight][kStageWidth];
		std::unique_ptr<DxModel::ModelBase> m_stage[kStageHeight][kStageWidth];

		static StageResorces m_resource[];
};

#endif