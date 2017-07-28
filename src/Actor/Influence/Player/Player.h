#pragma once

#include"Actor\Base\IWorld.h"
#include"Base/GameUsing.h"
#include"../Base/Influence.h"
#include"Cursor/SelectCursor.h"
#include"Base/Manager/State/StateManager.h"
#include"../MouseSelect/MouseSelect.h"
//プレイヤー
class Player : public Influence
{
public:
	explicit Player(IWorld& world);
	~Player();

	void Update(float deltaTime) override;
	void Draw() const override;

	void Select(const UnitPtr& unit);
	MouseSelect& GetMouseSelect();
private:
	//マウスの先にユニットがいる場合、ステータスを表示させる
	void OnMouseUnitStatusDraw();
	//選択中のユニットの足元にサークルを描画
	void SelectUnitDraw() const;
private:
	//プレイヤーカーソルのエフェクト
	void CursorEffect();
private:
	StateManager m_stateManager;//ステート管理
	//マウスと重なっているユニット
	UnitPtr m_onMouseUnit;
	//現在選択中のユニット
	UnitPtr m_selectedUnit;
	//現在コマンドを表示している工場
	FactoryPtr m_factory;
	//表示するモデル
	Model m_model;

	//オート用のユニットを選択中かのbool
	bool m_isAutoSelect;

	MouseSelect m_mouseSelect;
};