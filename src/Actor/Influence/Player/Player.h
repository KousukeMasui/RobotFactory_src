#pragma once

#include"Actor\Base\IWorld.h"
#include"Base/GameUsing.h"
#include"../Base/Influence.h"
#include"Cursor/SelectCursor.h"
#include"Base/Manager/State/StateManager.h"
#include"../MouseSelect/MouseSelect.h"
//�v���C���[
class Player : public Influence
{
public:
	explicit Player(IWorld& world);
	~Player();

	void Update(float deltaTime) override;
	void Draw() const override;

	void Select(const UnitPtr& unit);
	MouseSelect& GetMouseSelect();
private:
	//�}�E�X�̐�Ƀ��j�b�g������ꍇ�A�X�e�[�^�X��\��������
	void OnMouseUnitStatusDraw();
	//�I�𒆂̃��j�b�g�̑����ɃT�[�N����`��
	void SelectUnitDraw() const;
private:
	//�v���C���[�J�[�\���̃G�t�F�N�g
	void CursorEffect();
private:
	StateManager m_stateManager;//�X�e�[�g�Ǘ�
	//�}�E�X�Əd�Ȃ��Ă��郆�j�b�g
	UnitPtr m_onMouseUnit;
	//���ݑI�𒆂̃��j�b�g
	UnitPtr m_selectedUnit;
	//���݃R�}���h��\�����Ă���H��
	FactoryPtr m_factory;
	//�\�����郂�f��
	Model m_model;

	//�I�[�g�p�̃��j�b�g��I�𒆂���bool
	bool m_isAutoSelect;

	MouseSelect m_mouseSelect;
};