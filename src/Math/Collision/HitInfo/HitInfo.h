#pragma once

#include"../../Shapes/3D/Shape3D.h"
#include"../../Shapes/Shape2D.h"

//Collide�̏����i�[����\���� ���݂͎g��Ȃ��������O���Ă���̂Ŏg���������̂��������狳���ĉ������B
struct HitInfo
{
	HitInfo();
	bool isHit;//����������true
	MyVector3 hitPosition;//���������ʒu
	MyVector3 normal;

	float t;//�J�v�Z�����ɏꍇ�̔䗦
};