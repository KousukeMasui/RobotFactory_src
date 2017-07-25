#pragma once
#include"Distance\MetaDistance.h"
#include"Overlap/OverlapData.h"
#include"RootFind/RootFind.h"
#include"Math/Point2/Point2.h"
class GameManager;
class MetaAI
{
public:
	//�R���X�g���N�^
	MetaAI();
	//�f�X�g���N�^
	~MetaAI();
	//�Q�[���J�n
	void Start(GameManager* manager);
	//�X�V
	void Update();
	//�����ȊO�̃��j�b�g�̈ʒu
	std::vector<Point2> GetUnitPoints(const Unit& unit);
	//�����N���X
	MetaDistance& Distance();
	//�d���`�F�b�N�N���X
	OverlapData& Overlap();
	RootFind& GetFind();
private:
	GameManager* m_manager;
	MetaDistance m_distance;
	OverlapData m_overlap;
	RootFind m_rootFind;
};