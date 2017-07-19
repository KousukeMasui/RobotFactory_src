#ifndef	_COLOR_H_
#define	_COLOR_H_

struct Color
{
	float r;
	float g;
	float b;
	float a;

	//コンストラクタ
	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	//一致する各成分ペアの最も低い値を含むカラーを返します。
	static Color Min(const Color& value1, const Color& value2);
	//一致する各成分ペアの最も高い値を含むカラーを返します。
	static Color Max(const Color& value1, const Color& value2);
	//範囲内に制限
	static Color Clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color());

	//定数
	static const Color Black;
	static const Color White;
};

//代入演算子オーバーロード
Color& operator += (Color& c1, const Color& c2);
Color& operator -= (Color& c1, const Color& c2);
Color& operator *= (Color& c1, const Color& c2);
Color& operator *= (Color& c, float s);
Color& operator /= (Color& c, float s);

//2項演算子オーバーロード
Color operator +(Color c1, const Color& c2);
Color operator -(Color c1, const Color& c2);
Color operator *(Color c1, const Color& c2);
Color operator *(Color c, float s);
Color operator *(float s, Color c);
Color operator /(Color c, float s);

#endif