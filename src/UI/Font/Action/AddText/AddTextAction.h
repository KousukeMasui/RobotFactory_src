#pragma once
#include"UI/UIAction/Base/UIActions.h"
#include"../../FontSprite.h"
#include<string>
//fontSpriteの文字列を一文字ずつ描画するクラス
class AddTextAction : public FontAction {
public:
	//コンストラクタ
	AddTextAction(const char* startText,const char* addText,float addTime,bool isLoop);
	//デストラクタ
	~AddTextAction();
	//更新
	bool OnUpdate(FontSprite* font, float deltaTime) override;

private:
	//初期テキスト
	const char* m_startText;
	//描画していく文字列
	const char* m_addText;
	//描画更新するまでの時間
	const float m_addTime;
	//描画更新タイマ
	float m_addTimer;

	//現在何文字目まで描画したら
	int m_drawIndex;
	//ループするか
	bool m_isLoop;
};