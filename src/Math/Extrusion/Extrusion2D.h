#ifndef	  _EXTRUSION_2D_H_
#define	  _EXTRUSION_2D_H_

#include"Math\Vector/MyVector2.h"
#include<vector>
//2D�p�����o���N���X
class Extrusion2D
{
public:
	//�l�p�Ɗۂ̔���̊ۂ̉����o��
	static MyVector2 Box_ExtrusionSphere(MyVector2 SpherePos,float radius,MyVector2 boxPos,std::vector<MyVector2> vertices,MyVector2 contactPos);
};

#endif