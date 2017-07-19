#ifndef	  _EXTRUSION_2D_H_
#define	  _EXTRUSION_2D_H_

#include"Math\Vector/MyVector2.h"
#include<vector>
//2D用押し出しクラス
class Extrusion2D
{
public:
	//四角と丸の判定の丸の押し出し
	static MyVector2 Box_ExtrusionSphere(MyVector2 SpherePos,float radius,MyVector2 boxPos,std::vector<MyVector2> vertices,MyVector2 contactPos);
};

#endif