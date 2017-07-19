#include "AnimationModel.h"
#include"Loader/Loader.h"
#include<DxLib.h>
#include"Math/Converter.h"
AnimationModel::AnimationModel(MODEL_ID id,bool isOnce, int animIndex, bool isLoop, const MyMatrix4& pose):
	ParentModel(id, !isOnce)
{
	AnimationChange(animIndex, isLoop);
	//�u�����h���Ă��܂��Č���T�|�[�Y�ɂȂ�̂ł����␳
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
	//�A�j���[�V�����p�̃��f���������A���A�j���[�V�����C���f�b�N�X�������ꍇ
	if (animParam.animIndex != anim || isAttach)
		AnimationChange(anim, isLoop);
	if (!isBlend || isAttach)
		animParam.rate = 1.0f;
}

void AnimationModel::AnimationChange(int anim, bool isLoop, int animModelID)
{
	//�A�j���[�V�����p�̃��f���������A���A�j���[�V�����C���f�b�N�X�������ꍇ
	//if ((animParam.sourceModelID == animModelID) && animParam.animIndex == anim) return;
	//�A�j���[�V���������� ������0�̌��1�������ۂɃf�^�b�`���Ă��܂��̂�����
	animParam.beforeAnim = MV1DetachAnim(m_modelID, animParam.beforeAnim);
	animParam.playAnim = MV1DetachAnim(m_modelID, animParam.playAnim);
	//�V�����A�j���[�V�������A�^�b�`
	animParam.playAnim = MV1AttachAnim(m_modelID, anim, animModelID);

	//�u�����h����0�ɐݒ�
	MV1SetAttachAnimBlendRate(m_modelID, animParam.playAnim, 0.0f);
	//sourceModel�̍X�V
	animParam.beforeSourceModelID = animParam.sourceModelID;
	animParam.sourceModelID = animModelID;

	//�A�j���[�V�����C���f�b�N�X�̍X�V
	animParam.beforeAnimIndex = animParam.animIndex;
	animParam.animIndex = anim;

	//�O�̃A�j���[�V�������Đݒ�
	animParam.beforeAnim = MV1AttachAnim(m_modelID, animParam.beforeAnimIndex, animParam.beforeSourceModelID);
	//�ϐ��̒��g�̈ړ�
	animParam.beforeAnimationTime = animParam.animationTime;
	//�A�j���[�V�����^�C�}��ݒ�
	MV1SetAttachAnimTime(m_modelID, animParam.beforeAnim, animParam.beforeAnimationTime);

	//���ݍĐ����̃A�j���[�V�����̑������Ԃ��擾
	int mID= animParam.sourceModelID;
	if (animParam.sourceModelID == -1) mID = m_modelID;
	animParam.animationTotalTime = MV1GetAnimTotalTime(mID, animParam.animIndex);

	//�A�j���[�V�����^�C�}��������
	animParam.animationTime = 0.0f;
	//rate�̏�����
	animParam.rate = 0.0f;
	//���[�v���邩
	animParam.isLoop = isLoop;
}

void AnimationModel::AnimationChange(int animParamNumber,int anim, bool isLoop, MODEL_ID id)
{
	//int model = Loader::GetInstance().ModelHandle(id);
	//AnimationChange(anim, model,isLoop);
}

//�ʒu�ݒ�ƃA�j���[�V�������s���X�V�֐�
void AnimationModel::Update(float deltaTime, const MyMatrix4 & pose)
{
	//�s��ݒ�
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));

	//�A�j���[�V�����X�V

	Play(deltaTime);
}

void AnimationModel::Update(float deltaTime, MODEL_ID animModel, const MyMatrix4 & pose)
{
	//�s��ݒ�
	MV1SetMatrix(m_modelID, Converter::MyMatirx4ToMATRIX(pose));

	//�A�j���[�V�����X�V
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
	//�؂�ւ��O�ɓ��������ꍇfalse��Ԃ�
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
	deltaTime /= 2.0f;//vmd��30fps�Ȃ̂ő��x�����킹��

	//�u�����h�����B
	if (animParam.rate < 1.0f - FLT_EPSILON)
	{
		/*�u�����h��rate����*/
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
	/*�A�j���[�V��������*/
	animParam.animationTime += deltaTime;
	if (animParam.animationTime >= animParam.animationTotalTime)
	{
		if (animParam.isLoop)
		{
			animParam.animationTime -= animParam.animationTotalTime;
		}
		else
		{
			//�ő厞�ԂŒ�~������
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