
#include "ModelProperty.h"

namespace FbxModelProperty
{
	// Fbx�����荞�ޗp
	struct FbxMeshNode{

		~FbxMeshNode(){
			_uvSetID.clear();
			_index.clear();

		}

		std::string _name; // �m�[�h��
		std::string _parentName; // �e�m�[�h���i���Ȃ��ꍇ��null������j

		ModelProperty::MeshElements _elements; // ���b�V�����ێ�����f�[�^�\��
		std::vector <ModelProperty::Material> _material; // �}�e���A��

		std::unordered_map<std::string, int> _uvSetID;
		std::vector<unsigned int> _index;			// �C���f�b�N�X�z��

		float _matrix4x4[16];
	};
}
