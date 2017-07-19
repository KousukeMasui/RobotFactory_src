#pragma once

//UIに使うスプライトのID
enum class GamePlaySpriteID
{
	NON_DELETE=0,	//必ず削除しないID
	GAUGES,			//ゲージ画像
	GAUGE_FRAME,	//ゲーム枠
	COMMAND_FIRST,	//コマンド選択
	COMMAND_UNIT,	//ユニットコマンド
	COMMAND_FACTORY,//工場コマンド
	PLAY_GAUGE,		//ゲームプレイ中のゲージ画像
};