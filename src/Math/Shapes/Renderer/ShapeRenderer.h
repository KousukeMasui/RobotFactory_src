#pragma once
//�`��ׂ̈����ɐ}�`�N���X�����C�u������include���āA�ʂ̏ꏊ�Ɉڂ����ۂ̕ύX���ʓ|�Ȃ̂ŁA�`����܂Ƃ߂��N���X
struct Sphere;
struct Capsule;
struct Line3D;
struct Ray;
struct BoundingBox3D;
class ShapeRenderer
{
public:
	static void Draw(const Sphere& sphere);
	static void Draw(const Capsule& capsule);
	static void Draw(const Line3D& line);
	static void Draw(const Ray& ray);
	static void Draw(const BoundingBox3D& box);
};