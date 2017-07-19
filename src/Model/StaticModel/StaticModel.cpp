#include "StaticModel.h"
#include"Loader/Loader.h"
#include<DxLib.h>
#include"Math/Converter.h"
StaticModel::StaticModel(MODEL_ID id, bool isOnce, const MyVector3 & position, const MyVector3 & scale, const MyVector3 & rad):
	ParentModel(id,!isOnce)
{
	MV1SetPosition(m_modelID, Converter::MyVector3ToVECTOR(position));
	MV1SetScale(m_modelID, Converter::MyVector3ToVECTOR(scale));
	MV1SetRotationXYZ(m_modelID, Converter::MyVector3ToVECTOR(rad));
}
StaticModel::StaticModel(MODEL_ID id, bool isOnce, const MyVector3 & position, const MyVector3 & scale, const MyMatrix4 & rotate) :
	ParentModel(id, !isOnce)
{

	MV1SetPosition(m_modelID, Converter::MyVector3ToVECTOR(position));
	MV1SetScale(m_modelID, Converter::MyVector3ToVECTOR(scale));
	MV1SetRotationMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(rotate));
}
StaticModel::StaticModel(MODEL_ID id, bool isOnce, const MyMatrix4 & pose) :
	ParentModel(id, !isOnce)
{
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));
}
StaticModel::~StaticModel()
{
}


void StaticModel::CollideSet(int divisionX, int divisionY, int divisionZ)
{
	MV1SetupCollInfo(m_modelID, -1, divisionX, divisionY, divisionZ);
}

void StaticModel::CollideUpdate()
{
	MV1RefreshCollInfo(m_modelID);
}

void StaticModel::CollideDelete()
{
	MV1TerminateCollInfo(m_modelID);
}

void StaticModel::Draw() const
{
	if (MV1DrawModel(m_modelID) == -1)
	{
		printfDx("•`‰æŽ¸”s : m_modelID=%d\n", m_modelID);
	}
}