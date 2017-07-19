#include "NumberDraw.h"
#include"Loader\Loader.h"
#include"Math/Vector/MyVector2.h"
#include<DxLib.h>
void NumberDraw::Draw(const MyVector2 & position, int digit, int num, float size)
{
	int handle = Loader::GetInstance().TextureHandle(TEXTURE_ID::NUMBER);
	const int width = 50;
	const int height = 100;


	//���ׂ̈Ɋ��鐔�������߂� 
	int d = (int)std::pow(10, (digit - 1));
	float x = position.x;
	//��������
	for (int i = 0; i < digit; i++)
	{
		//�`��ʒu��ݒ�
		//���̌��̐��������߂�
		int n = (int)std::fmax((num / d) % 10 , 0.0f);
		d /= 10;
		//�`��
		//DrawRectGraph(x, position.y, (width * n), 0.0f, width, height, handle, true, false);
		DrawRectExtendGraphF(x, position.y, x+ width*size,position.y + height*size,//�e�N�X�`���̕`��T�C�Y
			(width * n), 0.0f, width, height,//�؂���͈�
			handle, true);
		x += width*size;

	}
}
