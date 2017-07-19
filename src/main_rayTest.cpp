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

	// ウインドウモードで起動する
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	// ３Ｄモデルの読み込み
	ModelHandle = MV1LoadModel("res/Model/Player/unitychan.mv1");

	MV1SetScale(ModelHandle, VGet(50.0f, 50.0f, 50.0f));

	// ３Ｄモデルを見える位置に移動する
	MV1SetPosition(ModelHandle, VGet(0.0f, 0.0f, 600.0f));

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	// モデル全体のコリジョン情報を構築
	//MV1SetupCollInfo(ModelHandle, -1, 8, 8, 8);

	// ウインドウが閉じられるか何かキーが押されるまでループ
	while (ProcessMessage() == 0)
	{
		Mouse::GetInstance().Update();
		// 画面をクリア
		ClearDrawScreen();

		//マウスの位置
		MyVector2 mousePosition = Mouse::GetInstance().Position();
		//回転していない場合のターゲットからの距離
		MyVector3 defaultVec = MyVector3(0, 0, -50);

		MyVector2 mouseVelocity = (mousePosition - m_prevMousePosition) / 10.0f;

		//移動処理
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
		SetupCamera_Perspective(45.0f);//60.0fの2択
		SetCameraPositionAndTargetAndUpVec(
			Converter::MyVector3ToVECTOR(m_position),//VGet(0,30,-50),
			Converter::MyVector3ToVECTOR(m_position + MyVector3(0,0,1)),//VGet(0, 30, 0),//m_target),
			VGet(0,1,0));//m_rotate.GetForward()));

		// ３Ｄモデルの描画
		//MV1DrawModel(ModelHandle);
		DrawSphere3D(VGet(0.0f, 0.0f, 600.0f), 50.0f,16, GetColor(255, 0, 0), GetColor(255, 0, 0), true);
		// マウスの座標を取得
		GetMousePoint(&Mx, &My);

		// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Near 面の座標を取得
		StartPos = ConvScreenPosToWorldPos(VGet(Mx, My, 0.0f));

		// マウスポインタがある画面上の座標に該当する３Ｄ空間上の Far 面の座標を取得
		EndPos = ConvScreenPosToWorldPos(VGet(Mx, My, 1.0f));

		// モデルと線分との当たり判定
		HitPoly = MV1CollCheck_Line(ModelHandle, -1, StartPos, EndPos);

		// 当たったかどうかで処理を分岐
		//if (HitPoly.HitFlag == 1)
		if(HitCheck_Line_Sphere(StartPos,EndPos,VGet(0,0,600),50.0f) == 1)
		{
			DrawString(0, 0, "HIT!!!!", GetColor(255, 255, 255));
			continue;
			// 当たった場合は衝突の情報を描画する

			// 当たったポリゴンを黄色で描画する
			DrawTriangle3D(HitPoly.Position[0], HitPoly.Position[1], HitPoly.Position[2], GetColor(255, 255, 0), TRUE);

			// 交差した座標を描画
			DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Pos   %f  %f  %f",
				HitPoly.HitPosition.x, HitPoly.HitPosition.y, HitPoly.HitPosition.z);

			// 当たったポリゴンが含まれるフレームの番号を描画
			DrawFormatString(0, 16, GetColor(255, 255, 255), "Frame     %d", HitPoly.FrameIndex);

			// 当たったポリゴンが使用しているマテリアルの番号を描画
			DrawFormatString(0, 32, GetColor(255, 255, 255), "Material  %d", HitPoly.MaterialIndex);

			// 当たったポリゴンを形成する三頂点の座標を描画
			DrawFormatString(0, 48, GetColor(255, 255, 255), "Position  %f  %f  %f",
				HitPoly.Position[0].x, HitPoly.Position[0].y, HitPoly.Position[0].z);
			DrawFormatString(0, 64, GetColor(255, 255, 255), "          %f  %f  %f",
				HitPoly.Position[1].x, HitPoly.Position[1].y, HitPoly.Position[1].z);
			DrawFormatString(0, 80, GetColor(255, 255, 255), "          %f  %f  %f",
				HitPoly.Position[2].x, HitPoly.Position[2].y, HitPoly.Position[2].z);

			// 当たったポリゴンの法線を描画
			DrawFormatString(0, 96, GetColor(255, 255, 255), "Normal    %f  %f  %f",
				HitPoly.Normal.x, HitPoly.Normal.y, HitPoly.Normal.z);
		}
		else
		{
			// 当たらなかった場合は衝突しなかった旨だけ描画する
			DrawString(0, 0, "NO HIT", GetColor(255, 255, 255));
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}