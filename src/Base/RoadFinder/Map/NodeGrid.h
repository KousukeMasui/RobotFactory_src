#pragma once
#include <array>
#include <cassert>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "../Node/Node/NodePtr.h"
#include "FieldMap.h"

// �p�X�����p�i�q�m�[�h
class NodeGrid
{
public:
	// �R���X�g���N�^
	explicit NodeGrid(FieldMap& map);
	
	// �m�[�h�̎擾
	NodePtr operator [] (const Point2& position) const;

	// �ߗׂ̖������m�[�h������
	void neighbors(const NodePtr& node, std::function<void(const NodePtr&)> fn) const;

	// �����p�X�m�[�h�̍쐬
	std::vector<NodePtr> createPath(const NodePtr& goal) const;

private:
	// �m�[�h�̍쐬
	void createNode(FieldMap& map);

	// �������̃m�[�h���H
	bool opend(const Point2& position) const;

	// �i�q�̓������H
	bool isInside(const Point2& position) const;

public:
	// �\���i�f�o�b�O�p�j
	void draw() const;

private:
	// ��
	int width_;
	// ����
	int height_;
	// �i�q�m�[�h
	std::vector<std::vector<NodePtr>> grid_;
};

