#pragma once

//Parts�𐶐�����N���X

class IWorld;
#include"Actor\Base\Actor3D.h"
#include"Base/GameUsing.h"
#include"Math/Point2/Point2.h"
class PartsCreater: public Actor3D
{
public:
	explicit PartsCreater(IWorld& world);
	~PartsCreater();

	void OnUpdate(float deltaTime) override;

private:
	//Parts�𐶐�����֐�
	void Create();

	//�H��̎���ƍH���point2�ŕԂ�
	std::vector<Point2> GetFactoryPoints(const FactoryPtr& factory) const;
	std::vector<Point2> GetFactoryPoints(const FactoryPtrs& factorys) const;
private:
	//�����܂ł̊Ԋu
	float m_createInterval;
	//�O�񐶐����ꂽ�ʒu
	MyVector3 m_prevCreatePosition;
};