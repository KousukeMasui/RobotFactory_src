#ifndef	  _EVENT_MESSAGE_H_
#define	  _EVENT_MESSAGE_H_

//メッセージ
enum class EventMessage
{
	None,		//ダミー
	EnemyDead,	//敵死ね
	EnemyMove,	//敵動け
	GameClear,   //ゲームクリア
	TrapDead,
};

#endif