#include "NumberDraw.h"
#include"Loader\Loader.h"
#include"Math/Vector/MyVector2.h"
#include<DxLib.h>
void NumberDraw::Draw(const MyVector2 & position, int digit, int num, float size)
{
	int handle = Loader::GetInstance().TextureHandle(TEXTURE_ID::NUMBER);
	const int width = 50;
	const int height = 100;


	//桁の為に割る数字を求める 
	int d = (int)std::pow(10, (digit - 1));
	float x = position.x;
	//桁数分回す
	for (int i = 0; i < digit; i++)
	{
		//描画位置を設定
		//その桁の数字を求める
		int n = (int)std::fmax((num / d) % 10 , 0.0f);
		d /= 10;
		//描画
		//DrawRectGraph(x, position.y, (width * n), 0.0f, width, height, handle, true, false);
		DrawRectExtendGraphF(x, position.y, x+ width*size,position.y + height*size,//テクスチャの描画サイズ
			(width * n), 0.0f, width, height,//切り取り範囲
			handle, true);
		x += width*size;

	}
}
