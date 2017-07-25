#pragma once

#include<memory>
#include<vector>
#include<functional>

class TreeNode
{
public:
	//�R���X�g���N�^
	explicit TreeNode(int nodeID);
	//�f�t�H���g�R���X�g���N�^
	~TreeNode();

	virtual void Start() = 0;//������

	virtual void Update(float deltaTime) = 0;
	virtual void End() = 0;//�I��
	bool IsEnd();//�I���Ƃ���true
	void AddChild(std::shared_ptr<TreeNode> child);

	//�e�m�[�h���玩���Ɍq���邩��bool
	virtual bool Branch() = 0;

	//���̉��̃m�[�h��Ԃ��B
	std::shared_ptr<TreeNode> NextNode();

	int ID() const;
protected:
	//����ɕ����̃m�[�h�����Ă����B�@���݂̓m�[�h�̍폜�����邱�Ƃ͑z�肵�Ă��Ȃ��B
	//�����̎q�m�[�h
	std::vector<std::shared_ptr<TreeNode>> m_childNodes;
	const int m_nodeID;
	bool m_isEnd;
};