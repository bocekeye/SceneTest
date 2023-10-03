#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include <assert.h>
#include "Model.h"


namespace
{
	//�t�@�C����
	const char* const kFileName = "data/player.mv1";

	//�J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 0.0f, 720.0f, 720.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 400.0f, -120.0f };

	//�v���C���[�̈ړ���
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -15.0f };

	//�V���b�g�̑��x
	constexpr float kShotSpeed = 100.0f;

	//���񑬓x
	constexpr float kRotSpeed = 0.03f;

	//�W�����v��
	constexpr float kJumpPower = 16.0f;
	//�d��
	constexpr float kGravity = -1.0f;

	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimNo = 3;	//�ҋ@���[�V����
	constexpr int kIdleShootAnimNo = 5;	//��~���Ă����ԂŃV���b�g�����A�j���[�V����
	constexpr int kWalkAnimNo = 14;	//�ړ����[�V����

	//�A�j���[�V�����؂�ւ��ɂ�����t���[����
	constexpr int kAnimChangeFrame = 4;

	//�����蔻��̃T�C�Y
	constexpr float kColRudius = 60.0f;

	//�ő�HP
	constexpr int kMaxHP = 100;
}

Player::Player() :
	m_updateFunc(&Player::updateIdle),
	m_animNo(kIdleAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_hp(kMaxHP),
	m_damageFrame(0)

{
	//3D���f���̐���
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->setAnimation(m_animNo, true, true);

}

Player::~Player()
{
}

void Player::init()
{
}

void Player::update()
{
	(this->*m_updateFunc)();
}

void Player::draw()
{
	if (m_damageFrame > 0)
	{
		if (m_damageFrame % 2) return;
	}

	m_pModel->draw();
}

float Player::getColRadius()
{
	return kColRudius;
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
}

void Player::updateCamera()
{
	//m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_angle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	//�W�����v���͒P���Ƀv���C���[�ɒǏ]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = m_pos;
	//cameraTrans.y = 0.0f;
	cameraTrans.y = m_pos.y * 0.3f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	//�v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	//�v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	//�J�����̐ݒ�
	//�ǂ��܂ŕ\�����邩
	//SetCameraNearFar(5.0f, 2800.0f);
	SetCameraNearFar(5.0f, 3500.0f);
	//�J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//�J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::updateIdle()
{
	//�A�j���[�V������i�߂�
	m_pModel->update();
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	//�W�����v����
	bool isJumping = true;	//�W�����v���Ă���t���O
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;

		isJumping = false;
	}

	//�v���C���[�̐i�s����
	MATRIX playerRotMtx = MGetRotY(m_angle);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	if (!isJumping)
	{
		//SPACE�{�^���ŃW�����v
		if (Pad::isTrigger(PAD_INPUT_10))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	//���E�L�[�Ő��񂷂�
	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
		isMoving = true;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
		isMoving = true;
	}


	//�㉺�L�[�őO��ړ�
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, move);
		isMoving = true;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos = VSub(m_pos, move);
		isMoving = true;
	}

	if (isMoving)
	{
		if (m_animNo == kIdleAnimNo)
		{
			//���s�A�j���ɕύX
			m_animNo = kWalkAnimNo;
			m_pModel->changeAnimation(14, true, false, 4);
		}
	}
	else
	{
		if (m_animNo == kWalkAnimNo)
		{
			//�ҋ@�A�j���ɕύX
			m_animNo = kIdleAnimNo;
			m_pModel->changeAnimation(kIdleAnimNo, true, false, 4);
		}
	}

	m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));
	updateCamera();
}


