#include "AnimationModel.h"
#include"Loader/Loader.h"
#include<DxLib.h>
#include"Math/Converter.h"
AnimationModel::AnimationModel(MODEL_ID id,bool isOnce, int animIndex, bool isLoop, const MyMatrix4& pose):
	ParentModel(id, !isOnce)
{
	AnimationChange(animIndex, isLoop);
	//ブレンドしてしまって結局Tポーズになるのでそれを補正
	animParam.rate = 1.0f;
	Update(0.0f, pose);
}

AnimationModel::AnimationModel(MODEL_ID id, bool isOnce, int animIndex, bool isLoop, MODEL_ID animModel):
	ParentModel(id, !isOnce)
{
}

void AnimationModel::Delete()
{
}

AnimationModel::~AnimationModel()
{
}


void AnimationModel::ChangeAnimation(int anim, bool isLoop, bool isBlend, bool isAttach)
{
	//アニメーション用のモデルが同じ、かつアニメーションインデックスが同じ場合
	if (animParam.animIndex != anim || isAttach)
		AnimationChange(anim, isLoop);
	if (!isBlend || isAttach)
		animParam.rate = 1.0f;
}

void AnimationModel::AnimationChange(int anim, bool isLoop, int animModelID)
{
	//アニメーション用のモデルが同じ、かつアニメーションインデックスが同じ場合
	//if ((animParam.sourceModelID == animModelID) && animParam.animIndex == anim) return;
	//アニメーションを解除 ここで0の後に1が動く際にデタッチしてしまうのが原因
	animParam.beforeAnim = MV1DetachAnim(m_modelID, animParam.beforeAnim);
	animParam.playAnim = MV1DetachAnim(m_modelID, animParam.playAnim);
	//新しいアニメーションをアタッチ
	animParam.playAnim = MV1AttachAnim(m_modelID, anim, animModelID);

	//ブレンド率を0に設定
	MV1SetAttachAnimBlendRate(m_modelID, animParam.playAnim, 0.0f);
	//sourceModelの更新
	animParam.beforeSourceModelID = animParam.sourceModelID;
	animParam.sourceModelID = animModelID;

	//アニメーションインデックスの更新
	animParam.beforeAnimIndex = animParam.animIndex;
	animParam.animIndex = anim;

	//前のアニメーションを再設定
	animParam.beforeAnim = MV1AttachAnim(m_modelID, animParam.beforeAnimIndex, animParam.beforeSourceModelID);
	//変数の中身の移動
	animParam.beforeAnimationTime = animParam.animationTime;
	//アニメーションタイマを設定
	MV1SetAttachAnimTime(m_modelID, animParam.beforeAnim, animParam.beforeAnimationTime);

	//現在再生中のアニメーションの総合時間を取得
	int mID= animParam.sourceModelID;
	if (animParam.sourceModelID == -1) mID = m_modelID;
	animParam.animationTotalTime = MV1GetAnimTotalTime(mID, animParam.animIndex);

	//アニメーションタイマを初期化
	animParam.animationTime = 0.0f;
	//rateの初期化
	animParam.rate = 0.0f;
	//ループするか
	animParam.isLoop = isLoop;
}

void AnimationModel::AnimationChange(int animParamNumber,int anim, bool isLoop, MODEL_ID id)
{
	//int model = Loader::GetInstance().ModelHandle(id);
	//AnimationChange(anim, model,isLoop);
}

//位置設定とアニメーションを行う更新関数
void AnimationModel::Update(float deltaTime, const MyMatrix4 & pose)
{
	//行列設定
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));

	//アニメーション更新

	Play(deltaTime);
}

void AnimationModel::Update(float deltaTime, MODEL_ID animModel, const MyMatrix4 & pose)
{
	//行列設定
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));

	//アニメーション更新
	//Play(anim, deltaTime, animModel, isAnimationLoop, animParameterNum);
}

void AnimationModel::Draw() const
{
	if (MV1DrawModel(m_modelID) == -1)
	{
		printfDx("draw_error\n");
	}
}

bool AnimationModel::IsAnimationEnd() const
{
	return animParam.animationTime >= animParam.animationTotalTime;
}

bool AnimationModel::IsAnimationEnd(const MODEL_ID & animModel, int anim) const
{
	//切り替わる前に動かした場合falseを返す
	if (animParam.sourceModelID == Loader::GetInstance().ModelHandle(animModel) && animParam.animIndex == anim) return false;

	return IsAnimationEnd();
}

float AnimationModel::GetAnimationTime() const
{
	return animParam.animationTime;
}

void AnimationModel::SetAnimationTime(float time)
{
	animParam.animationTime = time;
}
int AnimationModel::GetAnimationID() const
{
	return animParam.animIndex;
}
void AnimationModel::Play(float deltaTime)
{
	deltaTime /= 2.0f;//vmdは30fpsなので速度を合わせる

	//ブレンド処理。
	if (animParam.rate < 1.0f - FLT_EPSILON)
	{
		/*ブレンドのrate処理*/
		animParam.rate = std::fminf(animParam.rate + 0.05f*deltaTime, 1.0f);
		MV1SetAttachAnimBlendRate(m_modelID, animParam.beforeAnim, 1.0f - animParam.rate);
		MV1SetAttachAnimBlendRate(m_modelID, animParam.playAnim, animParam.rate);
	}
	else
	{
		animParam.rate = 1.0f;
		MV1SetAttachAnimBlendRate(m_modelID, animParam.beforeAnim, 0.0f);
		MV1SetAttachAnimBlendRate(m_modelID, animParam.playAnim, 1.0f);
		//animParam.beforeAnim = MV1DetachAnim(m_modelID, animParam.beforeAnim);
	}
	/*アニメーション処理*/
	animParam.animationTime += deltaTime;
	if (animParam.animationTime >= animParam.animationTotalTime)
	{
		if (animParam.isLoop)
		{
			animParam.animationTime -= animParam.animationTotalTime;
		}
		else
		{
			//最大時間で停止させる
			animParam.animationTime = animParam.animationTotalTime;
		}
	}
	if (MV1SetAttachAnimTime(m_modelID, animParam.playAnim, animParam.animationTime) == -1)
	{
		if (MV1SetAttachAnimBlendRate(m_modelID, animParam.playAnim, 1.0f) == -1)
		{
			printfDx("playAnim_Error\n");
		}
		printfDx("Animation_error\n\n");
	}

}