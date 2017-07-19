#pragma once

enum class UnitMessageID
{
	ROOT,			//経路を与える　単一の目的地
	ROOT_VECTOR,	//経路を与える　配列
	DAMAGE,			//ダメージ処理
	HEAL,			//回復
	LIFT,			//持ち物設定メッセージ
};