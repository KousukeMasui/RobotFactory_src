#pragma once
#include<memory>
#include<vector>
#include<map>
#include"Actor\Influence\InfluenceID.h"
//���̃Q�[���ŗǂ��g�p���钷���^����using����N���X
//���j�b�g
class Unit;
using UnitPtr = std::shared_ptr<Unit>;
using UnitPtrs = std::vector<UnitPtr>;
//�H��
class UnitFactory;
using FactoryPtr = std::shared_ptr<UnitFactory>;
using FactoryPtrs = std::vector<FactoryPtr>;
//����
class Parts;
using PartsPtr = std::shared_ptr<Parts>;
using PartsPtrs = std::vector<PartsPtr>;

//�H�ꕪ���ϐ�
using FactoryMap = std::map<InfluenceID, FactoryPtrs>;

class LiftObject;
enum class LIFT_ID;
using LiftObjectPtr = std::shared_ptr<LiftObject>;
using LiftObjects = std::vector<LiftObjectPtr>;
using LiftObjectsMap = std::map<LIFT_ID, LiftObjects>;
