#include "Model.h"
#include "Math/Converter.h"

#include"Loader\Loader.h"

Model::Model(MODEL_ID id):
	ParentModel(id,false)
{
}
Model::~Model() 
{	
}


void Model::Draw(const MyVector3 & position) const
{
	MV1SetPosition(m_modelID, Converter::MyVector3ToVECTOR(position));

	MV1DrawModel(m_modelID);
}

void Model::Draw(const MyVector3 & position, const MyVector3 & scale, const MyMatrix4 & rotate) const
{
	MV1SetPosition(m_modelID, Converter::MyVector3ToVECTOR(position));
	MV1SetScale(m_modelID, Converter::MyVector3ToVECTOR(scale));
	MV1SetRotationMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(rotate));

	MV1DrawModel(m_modelID);

}

void Model::Draw(const MyVector3 & position, const MyVector3 & scale, const MyVector3 & rad) const
{
	MV1SetPosition(m_modelID, Converter::MyVector3ToVECTOR(position));
	MV1SetScale(m_modelID, Converter::MyVector3ToVECTOR(scale));
	MV1SetRotationXYZ(m_modelID, Converter::MyVector3ToVECTOR(rad));

	MV1DrawModel(m_modelID);
}

void Model::Draw(const MyMatrix4 & pose) const
{
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));

	if (MV1DrawModel(m_modelID) == -1)
	{
		printfDx("MODEL_DRAW_ERROR");
	}
}
