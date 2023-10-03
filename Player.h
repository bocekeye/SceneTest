#pragma once
#include <DxLib.h>
#include <memory>

class Model;
class Player
{
public:
	Player();
	virtual ~Player();

	void init();
	void update();
	void draw();

	//�v���C���[�̈ʒu���擾����
	VECTOR getPos() const { return m_pos; }

	//�����蔻��̔��a
	float getColRadius();

	//�_���[�W���󂯂�
	void OnDamage(int damage);

private:

	//�J�����̍X�V
	void updateCamera();

	//�ҋ@
	void updateIdle();

private:
	//�����o�֐��|�C���^
	void (Player::* m_updateFunc)();

	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;
	//�Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;


	//�t���[���J�E���g
	int m_frameCount;

	//�v���C���[�̈ʒu
	VECTOR m_pos;
	//�W�����v�����p�����x
	float m_jumpAcc;

	//�v���C���[�̌����Ă������
	float m_angle;

	//�J�����̌����Ă������
	float m_cameraAngle;

	//HP
	int m_hp;
	//���G����
	int m_damageFrame;
};

