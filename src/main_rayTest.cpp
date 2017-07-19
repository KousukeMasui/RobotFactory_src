#include "DxLib.h"
#include"Math/MyVector2.h"
#include"Math/MyVector3.h"
#include"Math/MyMatrix4.h"
#include"Input/Mouse/Mouse.h"
#include"Math/Converter.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ModelHandle;
	VECTOR StartPos, EndPos;
	MV1_COLL_RESULT_POLY HitPoly;
	MyVector2 m_prevMousePosition;
	MyMatrix4 m_rotate = MyMatrix4::Identity();
	MyVector3 m_target = MyVector3(0, 30, 0) , m_position = MyVector3(0, 30, -50);
	float m_distance = 50.0f;
	int Mx, My;

	// �E�C���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return -1;
	}

	// �R�c���f���̓ǂݍ���
	ModelHandle = MV1LoadModel("res/Model/Player/unitychan.mv1");

	MV1SetScale(ModelHandle, VGet(50.0f, 50.0f, 50.0f));

	// �R�c���f����������ʒu�Ɉړ�����
	MV1SetPosition(ModelHandle, VGet(0.0f, 0.0f, 600.0f));

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// ���f���S�̂̃R���W���������\�z
	//MV1SetupCollInfo(ModelHandle, -1, 8, 8, 8);

	// �E�C���h�E�������邩�����L�[���������܂Ń��[�v
	while (ProcessMessage() == 0)
	{
		Mouse::GetInstance().Update();
		// ��ʂ��N���A
		ClearDrawScreen();

		//�}�E�X�̈ʒu
		MyVector2 mousePosition = Mouse::GetInstance().Position();
		//��]���Ă��Ȃ��ꍇ�̃^�[�Q�b�g����̋���
		MyVector3 defaultVec = MyVector3(0, 0, -50);

		MyVector2 mouseVelocity = (mousePosition - m_prevMousePosition) / 10.0f;

		//�ړ�����
		if (Mouse::GetInstance().IsPressState(MouseCommand::MIDDLE))
		{
			MyVector3 velocity =
				m_rotate.GetForward() * -mouseVelocity.y +
				m_rotate.GetLeft() * mouseVelocity.x;

			//m_target += velocity;

			m_target += MyVector3(mouseVelocity.x, mouseVelocity.y, 0.0f);
		}

		m_position = m_target + (defaultVec * m_rotate).Normalize() * m_distance;// *m_distance;

		m_prevMousePosition = mousePosition;

		m_distance = m_distance - Mouse::GetInstance().Wheel();

		SetCameraNearFar(10.0f, 10000.0f);
		SetupCamera_Perspective(45.0f);//60.0f��2��
		SetCameraPositionAndTargetAndUpVec(
			Converter::MyVector3ToVECTOR(m_position),//VGet(0,30,-50),
			Converter::MyVector3ToVECTOR(m_position + MyVector3(0,0,1)),//VGet(0, 30, 0),//m_target),
			VGet(0,1,0));//m_rotate.GetForward()));

		// �R�c���f���̕`��
		//MV1DrawModel(ModelHandle);
		DrawSphere3D(VGet(0.0f, 0.0f, 600.0f), 50.0f,16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
		// �}�E�X�̍��W���擾
		GetMousePoint(&Mx, &My);

		// �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Near �ʂ̍��W���擾
		StartPos = ConvScreenPosToWorldPos(VGet(Mx, My, 0.0f));

		// �}�E�X�|�C���^�������ʏ�̍��W�ɊY������R�c��ԏ�� Far �ʂ̍��W���擾
		EndPos = ConvScreenPosToWorldPos(VGet(Mx, My, 1.0f));

		// ���f���Ɛ����Ƃ̓����蔻��
		HitPoly = MV1CollCheck_Line(ModelHandle, -1, StartPos, EndPos);

		// �����������ǂ����ŏ����𕪊�
		//if (HitPoly.HitFlag == 1)
		if(HitCheck_Line_Sphere(StartPos,EndPos,VGet(0,0,600),50.0f) == 1)
		{
			DrawString(0, 0, "HIT!!!!", GetColor(255, 255, 255));
			continue;
			// ���������ꍇ�͏Փ˂̏���`�悷��

			// ���������|���S�������F�ŕ`�悷��
			DrawTriangle3D(HitPoly.Position[0], HitPoly.Position[1], HitPoly.Position[2], GetColor(255, 255, 0), TRUE);

			// �����������W��`��
			DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Pos   %f  %f  %f",
				HitPoly.HitPosition.x, HitPoly.HitPosition.y, HitPoly.HitPosition.z);

			// ���������|���S�����܂܂��t���[���̔ԍ���`��
			DrawFormatString(0, 16, GetColor(255, 255, 255), "Frame     %d", HitPoly.FrameIndex);

			// ���������|���S�����g�p���Ă���}�e���A���̔ԍ���`��
			DrawFormatString(0, 32, GetColor(255, 255, 255), "Material  %d", HitPoly.MaterialIndex);

			// ���������|���S�����`������O���_�̍��W��`��
			DrawFormatString(0, 48, GetColor(255, 255, 255), "Position  %f  %f  %f",
				HitPoly.Position[0].x, HitPoly.Position[0].y, HitPoly.Position[0].z);
			DrawFormatString(0, 64, GetColor(255, 255, 255), "          %f  %f  %f",
				HitPoly.Position[1].x, HitPoly.Position[1].y, HitPoly.Position[1].z);
			DrawFormatString(0, 80, GetColor(255, 255, 255), "          %f  %f  %f",
				HitPoly.Position[2].x, HitPoly.Position[2].y, HitPoly.Position[2].z);

			// ���������|���S���̖@����`��
			DrawFormatString(0, 96, GetColor(255, 255, 255), "Normal    %f  %f  %f",
				HitPoly.Normal.x, HitPoly.Normal.y, HitPoly.Normal.z);
		}
		else
		{
			// ������Ȃ������ꍇ�͏Փ˂��Ȃ������|�����`�悷��
			DrawString(0, 0, "NO HIT", GetColor(255, 255, 255));
		}

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}