#pragma once
#include"Math/Vector/MyVector3.h"
#include"Math/Matrix/MyMatrix4.h"
#include"Math/Color/Color.h"
enum class MODEL_ID;
class ParentModel
{
public:
	ParentModel(MODEL_ID id,bool isDuplicate);
	~ParentModel();

	void Delete() const;//é©ï™ÇçÌèú

	MyVector3 GetBonePosition(int boneID) const;
	MyVector3 GetBonePosition(const char* boneName) const;
	MyMatrix4 GetBoneWorld(int boneID) const;
	MyMatrix4 GetBoneWorld(const char* boneName) const;
	unsigned int GetBoneID(const char* boneName) const;


	Color GetMaterialColor(unsigned int materialIndex) const;
	void SetMaterialColor(unsigned int materialIndex, const Color & color) const;

	void SetAmbientColor(unsigned int materialIndex, const Color & color) const;
	int GetModelID() const;
protected:
	int m_modelID;//ÉÇÉfÉãID
};