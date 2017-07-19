#pragma once
#include"../ParentModel.h"
#include<vector>

struct AnimationParameter
{
	//初期化処理
	AnimationParameter():
		playAnim(-1),
		animationTime(0.0f),
		animationTotalTime(0.0f),
		animIndex(-1),
		beforeAnimIndex(-1),
		beforeAnim(-1),
		beforeAnimationTime(0.0f),
		beforeSourceModelID(-1),
		sourceModelID(-1),
		rate(0.0f),
		isLoop(false)
	{

	}
	int playAnim;//現在再生中のアニメーションのID

	float animationTime;//アニメーションタイマー
	float animationTotalTime;//アニメーションにかかる時間

	int animIndex;//現在再生中のアニメーションのアニメーション番号(IDとは別物なので使用に注意)
	int beforeAnimIndex;

	int beforeAnim;//ブレンド用アニメーションID
	float beforeAnimationTime;
	//アニメーションの入っているモデル
	int beforeSourceModelID;
	int sourceModelID;

	float rate;//ブレンドのrate

	std::vector<int> bones;//ボーン指定する際に使用

	bool isLoop;//アニメーションをループするか
};

class AnimationModel : public ParentModel
{
public:
	AnimationModel(MODEL_ID id,bool isOnce, int animIndex,bool isLoop,const MyMatrix4& pose);
	AnimationModel(MODEL_ID id,bool isOnce,int animIndex, bool isLoop,MODEL_ID animModel);
	~AnimationModel();
	//モデルの消去
	void Delete();
	//分割アニメーションを追加する関数 引数でアニメーション設定を行う
	//unsigned int AddAnimationParameter(int anim,std::vector<int> bones);

	//アニメーション変更関数 isAttach =　前と同じ場合でもアタッチする
	void ChangeAnimation(int anim,bool isLoop,bool isBlend=true,bool isAttach=false);

	void Update(float deltaTime, const MyMatrix4& pose);
	void Update(float deltaTime,MODEL_ID animModel, const MyMatrix4& pose);
	void Draw() const;

	//アニメーションが終わった時にtrue
	bool IsAnimationEnd() const;
	bool IsAnimationEnd(const MODEL_ID& modelID, int anim) const;
	float GetAnimationTime() const;
	void SetAnimationTime(float time);

	//アニメーションの位置を取得

	//アニメーションインデックスを取得
	int GetAnimationID() const;
private:
	//アニメーションの変更　modelIDとMODEL_IDは別の数値なので注意
	void AnimationChange(int anim,bool isLoop, int modelID = -1);
	//違うモデルのアニメーションに変更する関数
	void AnimationChange(int animParamNumber,int anim, bool isLoop, MODEL_ID id);
	//モーション再生関数
	void Play(float deltaTime);
	//下の関数を使って、選択したボーンに違うアニメーションをさせるように修正させる
	//MV1SetAttachAnimBlendRateToFrame
private:
	AnimationParameter animParam;//アニメーションパラメータ

	//int baseAnimIndex;
};