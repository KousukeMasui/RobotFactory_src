#pragma once

//Parts‚ğ¶¬‚·‚éƒNƒ‰ƒX

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
	//Parts‚ğ¶¬‚·‚éŠÖ”
	void Create();

	//Hê‚Ìü‚è‚ÆHê‚ğpoint2‚Å•Ô‚·
	std::vector<Point2> GetFactoryPoints(const FactoryPtr& factory) const;
	std::vector<Point2> GetFactoryPoints(const FactoryPtrs& factorys) const;
private:
	//¶¬‚Ü‚Å‚ÌŠÔŠu
	float m_createInterval;
	//‘O‰ñ¶¬‚³‚ê‚½ˆÊ’u
	MyVector3 m_prevCreatePosition;
};