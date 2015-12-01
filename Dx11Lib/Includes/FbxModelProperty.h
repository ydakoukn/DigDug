
#include "ModelProperty.h"

namespace FbxModelProperty
{
	// Fbx�����荞�ޗp
	struct FbxMeshNode{

		~FbxMeshNode(){
			Release();

		}

		void Release()
		{
			_uvSetID.clear();
			_texcoord.clear();
			_material.clear();
			_index.clear();
			_position.clear();
			_normal.clear();
		}

		std::vector<unsigned int>		_index;				// �C���f�b�N�X�z��
		std::vector<FbxVector4>			_position;		// �|�W�V�����z��
		std::vector<FbxVector4>			_normal;			// �@���z��
		std::vector<FbxVector2>			_texcoord;

		std::string _name; // �m�[�h��
		std::string _parentName; // �e�m�[�h���i���Ȃ��ꍇ��null������j

		ModelProperty::MeshElements _elements; // ���b�V�����ێ�����f�[�^�\��
		std::vector <ModelProperty::Material> _material; // �}�e���A��

		std::unordered_map<std::string, int> _uvSetID;

		float _matrix4x4[16];
	};
}
