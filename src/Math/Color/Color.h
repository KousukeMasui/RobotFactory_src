#ifndef	_COLOR_H_
#define	_COLOR_H_

struct Color
{
	float r;
	float g;
	float b;
	float a;

	//�R���X�g���N�^
	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	//��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂��B
	static Color Min(const Color& value1, const Color& value2);
	//��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂��B
	static Color Max(const Color& value1, const Color& value2);
	//�͈͓��ɐ���
	static Color Clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color());

	//�萔
	static const Color Black;
	static const Color White;
};

//������Z�q�I�[�o�[���[�h
Color& operator += (Color& c1, const Color& c2);
Color& operator -= (Color& c1, const Color& c2);
Color& operator *= (Color& c1, const Color& c2);
Color& operator *= (Color& c, float s);
Color& operator /= (Color& c, float s);

//2�����Z�q�I�[�o�[���[�h
Color operator +(Color c1, const Color& c2);
Color operator -(Color c1, const Color& c2);
Color operator *(Color c1, const Color& c2);
Color operator *(Color c, float s);
Color operator *(float s, Color c);
Color operator /(Color c, float s);

#endif