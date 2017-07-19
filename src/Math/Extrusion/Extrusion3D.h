#ifndef	  _EXTRUSION_3D_H_
#define	  _EXTRUSION_3D_H_

#include"Math/Vector/MyVector3.h"
#include"Math/Matrix/MyMatrix4.h"
struct Sphere;
struct BoundingBox3D;
//押し出し用クラス
class Extrusion3D
{
public:
	//四角と丸の判定の丸の押し出し
	static MyVector3 Box_ExtrusionSphere(const MyVector3& SpherePos, float radius, const MyVector3& boxPos, const MyVector3& size, const MyVector3& contactPos);
	static MyVector3 Box_ExtrusionSphere(const Sphere& sphere, const BoundingBox3D& box, const MyVector3& contactPos,const MyVector3& velocity);
	static MyVector3 Box_ExtrusionSphere(const MyVector3& spherePos, float radius,
		const MyVector3& boxPos,const MyVector3& size, const MyMatrix4& boxRotate, const MyVector3& contactPos);
};

#endif