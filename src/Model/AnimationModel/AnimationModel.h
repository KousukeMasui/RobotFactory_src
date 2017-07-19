#pragma once
#include"../ParentModel.h"
#include<vector>

struct AnimationParameter
{
	//����������
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
	int playAnim;//���ݍĐ����̃A�j���[�V������ID

	float animationTime;//�A�j���[�V�����^�C�}�[
	float animationTotalTime;//�A�j���[�V�����ɂ����鎞��

	int animIndex;//���ݍĐ����̃A�j���[�V�����̃A�j���[�V�����ԍ�(ID�Ƃ͕ʕ��Ȃ̂Ŏg�p�ɒ���)
	int beforeAnimIndex;

	int beforeAnim;//�u�����h�p�A�j���[�V����ID
	float beforeAnimationTime;
	//�A�j���[�V�����̓����Ă��郂�f��
	int beforeSourceModelID;
	int sourceModelID;

	float rate;//�u�����h��rate

	std::vector<int> bones;//�{�[���w�肷��ۂɎg�p

	bool isLoop;//�A�j���[�V���������[�v���邩
};

class AnimationModel : public ParentModel
{
public:
	AnimationModel(MODEL_ID id,bool isOnce, int animIndex,bool isLoop,const MyMatrix4& pose);
	AnimationModel(MODEL_ID id,bool isOnce,int animIndex, bool isLoop,MODEL_ID animModel);
	~AnimationModel();
	//���f���̏���
	void Delete();
	//�����A�j���[�V������ǉ�����֐� �����ŃA�j���[�V�����ݒ���s��
	//unsigned int AddAnimationParameter(int anim,std::vector<int> bones);

	//�A�j���[�V�����ύX�֐� isAttach =�@�O�Ɠ����ꍇ�ł��A�^�b�`����
	void ChangeAnimation(int anim,bool isLoop,bool isBlend=true,bool isAttach=false);

	void Update(float deltaTime, const MyMatrix4& pose);
	void Update(float deltaTime,MODEL_ID animModel, const MyMatrix4& pose);
	void Draw() const;

	//�A�j���[�V�������I���������true
	bool IsAnimationEnd() const;
	bool IsAnimationEnd(const MODEL_ID& modelID, int anim) const;
	float GetAnimationTime() const;
	void SetAnimationTime(float time);

	//�A�j���[�V�����̈ʒu���擾

	//�A�j���[�V�����C���f�b�N�X���擾
	int GetAnimationID() const;
private:
	//�A�j���[�V�����̕ύX�@modelID��MODEL_ID�͕ʂ̐��l�Ȃ̂Œ���
	void AnimationChange(int anim,bool isLoop, int modelID = -1);
	//�Ⴄ���f���̃A�j���[�V�����ɕύX����֐�
	void AnimationChange(int animParamNumber,int anim, bool isLoop, MODEL_ID id);
	//���[�V�����Đ��֐�
	void Play(float deltaTime);
	//���̊֐����g���āA�I�������{�[���ɈႤ�A�j���[�V������������悤�ɏC��������
	//MV1SetAttachAnimBlendRateToFrame
private:
	AnimationParameter animParam;//�A�j���[�V�����p�����[�^

	//int baseAnimIndex;
};