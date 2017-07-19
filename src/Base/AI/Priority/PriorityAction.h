#pragma once

//�D��x�t��AI�s���e�N���X
class PriorityAction
{
public:
	//�R���X�g���N�^
	explicit PriorityAction(float priority);
	//�f�X�g���N�^
	~PriorityAction() {};

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(float deltaTime) = 0;
	//�`��
	virtual void Draw()const {}
	virtual void End() = 0;
	float Priority();
	bool IsEnd() const;
protected:
	//�D��x��+���Ōv�Z����֐�
	virtual float OnPriority() = 0;
protected:
	bool m_isEnd;//�I��������
private:
	//�D��x
	float m_priority;
};