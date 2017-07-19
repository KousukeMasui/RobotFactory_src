#pragma once
#include"Math/Vector/MyVector3.h"
#include<functional>
//Effekseerのエフェクトをラッピングするクラス
class Effect3D//Effectだと名前が同じでVCの動きが安定しないので名前を変更
{
public:
	explicit Effect3D(int playHandle);
	~Effect3D();
	
	void Update(float deltaTime);//更新処理
	void Stop(bool isStop);

	void Draw() const;
	void Delete();//削除関数
	bool IsDelete() const;//削除するか

	//再生中か取得
	bool IsPlay() const;

	void SetPosition(const MyVector3& position);
	void SetScale(const MyVector3& scale);
	void SetPositionFunc(const std::function<MyVector3()>& func);
private:

	int m_playHandle;//再生する際のハンドル

	bool m_isDelete;//削除する時true

	bool m_isStop;

	//位置追従用変数
	std::function<MyVector3()> m_positionFunc;
};