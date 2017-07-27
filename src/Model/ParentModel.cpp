#include "ParentModel.h"
#include"Loader\Loader.h"
#include"Math/Converter.h"
#include<DxLib.h>
ParentModel::ParentModel(MODEL_ID id, bool isDuplicate)
{
	if (isDuplicate)
		m_modelID = Loader::GetInstance().ModelCopy(id);
	else
		m_modelID = Loader::GetInstance().ModelHandle(id);
}

ParentModel::~ParentModel()
{
}

void ParentModel::Delete() const
{
	MV1DeleteModel(m_modelID);
}

MyVector3 ParentModel::GetBonePosition(int boneID) const
{
	return Converter::VECTORToMyVector3(MV1GetFramePosition(m_modelID, boneID));
}

MyVector3 ParentModel::GetBonePosition(const char * boneName) const
{
	return GetBonePosition(GetBoneID(boneName));
}

MyMatrix4 ParentModel::GetBoneWorld(int boneID) const
{
	return Converter::MATRIXToMyMatrix4(MV1GetFrameLocalWorldMatrix(m_modelID, boneID));
}

MyMatrix4 ParentModel::GetBoneWorld(const char * boneName) const
{
	return GetBoneWorld(GetBoneID(boneName));
}

unsigned int ParentModel::GetBoneID(const char * boneName) const
{
	return MV1SearchFrame(m_modelID, boneName);
}

Color ParentModel::GetMaterialColor(unsigned int materialIndex) const
{
	auto color = MV1GetMaterialAmbColor(m_modelID, materialIndex);
	return Color(color.r, color.g, color.b, color.a);
}

void ParentModel::SetMaterialColor(unsigned int materialIndex, const Color & color) const
{
	COLOR_F c = { color.r,color.g,color.b,color.a };

	MV1SetMaterialDifColor(m_modelID, materialIndex, c);
	MV1SetMaterialSpcColor(m_modelID, materialIndex, c);
	MV1SetMaterialAmbColor(m_modelID, materialIndex, c);
}

void ParentModel::SetAmbientColor(unsigned int materialIndex, const Color & color) const
{
	COLOR_F c = { color.r,color.g,color.b,color.a };
	MV1SetMaterialAmbColor(m_modelID, materialIndex, c);
}

int ParentModel::GetModelID() const
{
	return m_modelID;
}
