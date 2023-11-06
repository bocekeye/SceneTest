#include "Player.h"

#include "Pad.h"
#include <cassert>
#include <array>
#include "Model.h"
#include "Effekseer.h"
#include "PlayerManager.h"
#include "game.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>


namespace
{
	//�t�@�C����
	const char* const kFileName = "data/dolphin.mv1";
	//const char* const kFileName = "data/Shark.mv1";
	//const char* const kFileName2 = "data/Swimming.mv1";

	//�J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 0.0f, 920.0f, 800.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 500.0f, -10.0f };

	//�v���C���[�̈ړ���
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };

	//���񑬓x
	constexpr float kRotSpeed = 0.03f;

	//�W�����v��
	constexpr float kJumpPower = 50.0f;
	//�d��
	constexpr float kGravity = -1.0f;

	//�A�j���[�V�����ԍ�
	constexpr int kSwimAnimNo = 1;		//�j�����[�V����

	//�A�j���[�V�����؂�ւ��ɂ�����t���[����
	constexpr int kAnimChangeFrame = 4;

	//�����蔻��̃T�C�Y
	constexpr float kColRudius = 60.0f;

	//�ő�HP
	constexpr int kMaxHP = 100;
}

void Player::drawGraphWithShader(int x, int y, int texH, int norm, int psH, int vsH, bool transFlag)
{
	int w, h;
	GetGraphSize(texH, &w, &h);
	std::array<VERTEX2DSHADER, 4> verts;
	//���_��Z�̎��ɂȂ�悤�ɕ��ׂĂ���
	//����
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;

	//�E��
	verts[1].pos.x = x + w;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;

	//����
	verts[2].pos.x = x;
	verts[2].pos.y = y + h;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;

	//�E��
	verts[3].pos.x = x + w;
	verts[3].pos.y = y + h;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;

	for (auto& v : verts)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(255, 255, 255, 255);
		v.pos.z = 0.5f;
		v.rhw = 1.0f;
		v.su = 0.0f;
		v.sv = 0.0f;
	}

	SetUsePixelShader(psH);// �V�F�[�_�[���g�p�����`��Ɏg�p����s�N�Z���V�F�[�_�[��ݒ肷��
	SetUseVertexShader(vsH);
	//�ǂ̃e�N�X�`�������ԂɊ��蓖�Ă�̂�
	SetUseTextureToShader(0, texH);
	SetUseTextureToShader(1, norm);
	if (transFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// �V�F�[�_�[���g���ĂQ�c�v���~�e�B�u��`�悷��
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

Player::Player() :
	m_updateFunc(&Player::updateSwim),
	m_animNo(kSwimAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_gravity(0.0f),
	m_angle(0.0f),
	m_rotateAngle(0.0f),
	m_cameraAngle(m_angle),
	m_hp(kMaxHP),
	m_damageFrame(0),
	m_isReturnSurface(false),
	m_isLandingWaterAfterJump(false),
	m_pressKeyTime(0)

{
	//3D���f���̐���
	m_pModel = std::make_shared<Model>(kFileName);

	m_pEffekseer = new EffekseerManager;

	m_pModel->setAnimation(static_cast<int>(MotionType::swim), true, true);

	//�\���̂̒��g�̏�����
	//m_playerData.hp = 0;
	//m_offscreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	m_psH = LoadPixelShader("PixelShader.pso");
	m_distH = LoadGraph("data/norm.png");

	//�萔�o�b�t�@�̍쐬
	m_cbH = CreateShaderConstantBuffer(sizeof(float) * 4);
	m_cbufferAdress = static_cast<float*>(GetBufferShaderConstantBuffer(m_cbH));


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

	float lineSize = 10000.0f;
	int testH = m_pModel->getModelHandle();

#if false

	DrawTriangle3D(VGet(-lineSize, 0, -lineSize), VGet(lineSize, 0, -lineSize), VGet(lineSize, 0, lineSize), 0x00fffff, true);
	DrawTriangle3D(VGet(lineSize, 0, lineSize), VGet(-lineSize, 0, lineSize), VGet(-lineSize, 0, -lineSize), 0x00fffff, true);

//	SetDrawScreen(m_offscreen);
//	ClearDrawScreen();

	SetUsePixelShader(m_psH);	

	//�ǂ��܂ŕ\�����邩
	SetCameraNearFar(5.0f, 5000.0f);
	//�J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//�J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);

	m_pModel->draw();
	//SetRenderTargetToShader(0, -1);
	//SetRenderTargetToShader(0, testH);	// �V�F�[�_�[���g�p�����`��ł̕`����ݒ肷��
	//m_triangle = DrawTriangle3D(VGet(-lineSize, 0, -lineSize), VGet(lineSize, 0, -lineSize), VGet(lineSize, 0, lineSize), 0x00fffff, true);

	drawGraphWithShader(0, 0, testH, m_distH, m_psH, -1, true);

	//SetDrawScreen(DX_SCREEN_BACK);
	m_cbufferAdress[0] = m_time;
	UpdateShaderConstantBuffer(m_cbH);
	SetShaderConstantBuffer(m_cbH, DX_SHADERTYPE_PIXEL, 8);
	
	//drawGraphWithShader(m_pos.x, m_pos.y, m_offscreen, m_distH, m_psH, -1, true);

#else


	SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);
	DrawTriangle3D(VGet(-lineSize / 10, 0, -lineSize), VGet(lineSize / 10, 0, -lineSize), VGet(lineSize / 10, 0, lineSize), 0x00fffff, true);
	DrawTriangle3D(VGet(lineSize / 10, 0, lineSize), VGet(-lineSize / 10, 0, lineSize), VGet(-lineSize / 10, 0, -lineSize), 0x00fffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), 0x00ff00);

	m_pEffekseer->draw();
	m_pModel->draw();

#endif

#ifdef _DEBUG
	DrawFormatString(110, 50, 0xffffff, "m_gravity = %f", m_gravity);
	DrawFormatString(110, 70, 0xffffff, "m_displayMove.x = %f", m_displayMove.x);
	DrawFormatString(110, 90, 0xffffff, "m_pos.y = %f", m_pos.y);
	DrawFormatString(110, 110, 0xffffff, "m_displayMove.z = %f", m_displayMove.z);

	DrawFormatString(110, 130, 0xffffff, "m_maxReachedPoint = %f", m_maxReachedPoint);
	//DrawFormatString(110, 150, 0xffffff, "m_displayMove.y = %f", m_displayMove.y);
	//DrawFormatString(110, 170, 0xffffff, "m_displayMove.z = %f", m_displayMove.z);


#endif

}

float Player::getColRadius()
{
	return kColRudius;
}

void Player::onDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
}

int Player::getColFrameIndex() const
{
	return m_pModel->getColFrameIndex();
}

void Player::getMaxReachedPoint(float jumpAcc)
{
	m_maxReachedPoint = jumpAcc -2.0f;	
}

int Player::getHandle()const
{
	return m_pModel->getModelHandle();
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
	cameraTrans.y = m_pos.y * 0.9f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	//�v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	//�v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	m_cameraPos = VTransform(kCameraPos, cameraMtx);
	m_targetPos = VTransform(kCameraTarget, cameraMtx);

	//�J�����̐ݒ�

	//�ǂ��܂ŕ\�����邩
	SetCameraNearFar(5.0f, 5000.0f);
	//�J�����̎���p(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//�J�����̈ʒu�A�ǂ�����ǂ������Ă��邩��ݒ�
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);
}


/// <summary>
/// ���W�����v�ɂ���\��
/// </summary>
void Player::updateSwim()
{
	//�A�j���[�V������i�߂�
	m_pModel->update();

	//�v���C���[�̐i�s����
	//�����Ŏw�肳�ꂽ��]�l������Y����]�����]�s����擾����
	MATRIX playerRotMtx = MGetRotY(m_angle);

	//�s����g�����x�N�g���̕ϊ�(�ǂ��������Ă���̂��H)
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	m_displayMove = move;

	//m_pos = VAdd(m_pos, move);

	//���ʂɂ���Ԃ͂܂������̏�Ԃɂ���(��)
	if (m_pos.y <= 0.0f)
	{
		m_rotateAngle = 0.0f;
	}

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, move);
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos = VSub(m_pos, move);
	}

	//���E�L�[�Ő��񂷂�
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
	}
	
	//�W�����v����
	bool isJumping = true;	//�W�����v���Ă���t���O
	//m_isTestPushKey = false;

	m_jumpAcc += m_gravity;
	m_pos.y += m_jumpAcc;

	//�������ʂɖ߂�����
	if (m_pos.y <= 0.0f)
	{
		isJumping = false;
		m_isReturnSurface = true;
		m_isTest = false;
	}

	//�W�����v���ł͂Ȃ��Ƃ�
	if (!isJumping)
	{
		//SPACE�L�[�ŃW�����v����
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_jumpAcc = kJumpPower;
			m_jumpPowerStrage = kJumpPower;
			m_isTestPushKey = true;
			m_isReturnSurface = false;
			m_pressKeyTime = 0;
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower / 2;
			m_jumpPowerStrage = kJumpPower / 2;
			m_isTestPushKey = true;
			m_isReturnSurface = false;
			m_pressKeyTime = 0;
		}
	}
	else
	{	
		m_isReturnSurface = false;
	}

	//�ō����B�_�̎擾
	getMaxReachedPoint(m_jumpPowerStrage);

	//�W�����v�L�[���������ꍇ
	if (m_isTestPushKey)
	{
		//�����Đ��ʂɓ���������
		if (m_isReturnSurface)
		{
			m_gravity = -kGravity;
//*****�l�͕\�����Č������ߌv�Z�ŋ��߂���Ȃ�v�Z�ŋ��߂�I*****
			if (m_jumpAcc >= m_maxReachedPoint)
			{
				m_jumpAcc = 0.0f;
				m_gravity = 0.0f;
				m_pos.y = 0.0f;
				m_isTestPushKey = false;
			}
		}
		else
		{
			m_gravity = kGravity;
		}
	}


	if (m_isTest)
	{
		if (m_pos.y <= 0)
		{
			//�G�t�F�N�g�̔���
			m_pEffekseer->testUpdate(m_pos);
			m_isTest = false;
		}
	}

	if (m_pos.y >= 1.0f)
	{
		m_isTest = true;
	}

	printfDx("%f\n", m_jumpAcc);

	//move�����f�����ǂ̕����������Ă��邩�̏��
	//jumpPos�̕����Ɍ�����
	VECTOR jumpPos = VGet(move.x, m_jumpAcc, move.z);

	//���f���̌�������W�����v��������֕ϊ������]�s����擾����
	MATRIX rotMtx = MGetRotVec2(move, jumpPos);

	//�v���C���[�̉�]����������
	rotMtx = MMult(rotMtx, playerRotMtx);

#if false
	//�t�s������߂�
	MATRIX invMtx = MInverse(rotMtx);
	rotMtx = MMult(rotMtx, playerRotMtx);
#endif

	//���s�ړ��s��̎擾
	VECTOR moveTrans = m_pos;
	MATRIX moveMtx = MGetTranslate(moveTrans);

	//��]�s��ƕ��s�ړ��s��������č��W�ɔ��f����
	
	MATRIX moveMult = MMult(rotMtx, moveMtx);
	MV1SetMatrix(m_pModel->getModelHandle(), moveMult);

	m_pEffekseer->update();
	//m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(m_rotateAngle, m_angle, 0.0f));
	
	updateCamera();
}
