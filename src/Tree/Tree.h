#pragma once

class TreeNode;
#include<string>
#include<memory>
class Tree
{
public:
	Tree();
	~Tree();
	void SetRoot(std::shared_ptr<TreeNode> root);
	void Update(float deltaTime);

	int ID() const;

private:
	//��ԉ��̊K�w�̃m�[�h(�t)��T��
	std::shared_ptr<TreeNode> SearchLeaf();
	void Change();//�m�[�h�̕ύX
private:
	//���݂̃m�[�h
	std::shared_ptr<TreeNode> m_nowNode;
	//�������ɂȂ��ԏ�̃m�[�h
	std::shared_ptr<TreeNode> m_root;
};