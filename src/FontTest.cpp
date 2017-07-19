#include "DxLib.h"
#include"Base/VectorUtility/VectorUtility.h"
// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int FontHandle;

	// ＤＸライブラリの初期化
	if (DxLib_Init() == -1) return 0;
	ChangeWindowMode(true);

	// ＤＸフォントデータファイルを読み込み、フォントハンドルを変数 FontHandle に保存する
	FontHandle = LoadFontDataToHandle("res/Texture/Font/TestFont.dft", 1);

	// 作成したフォントで画面左上に『Ｈｅｌｌｏｗ！！』と白色の文字列を描画する
	//DrawStringToHandle(0, 0, "HP", GetColor(255, 255, 255), FontHandle);

	// 次に標準フォントデータで画面に『ＯＫ？』という文字列を描画する
	//DrawString(0, 50, "ＯＫ？", GetColor(255, 128, 100));

	// キー入力を待つ
	WaitKey();

	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle);

	// ＤＸライブラリの終了
	DxLib_End();

	// ソフトの終了
	return 0;
}