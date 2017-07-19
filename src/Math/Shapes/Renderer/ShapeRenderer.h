#pragma once
//描画の為だけに図形クラスがライブラリをincludeして、別の場所に移した際の変更が面倒なので、描画をまとめたクラス
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