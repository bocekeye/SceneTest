#pragma once

#include <memory>
#include <map>

#include <DxLib.h>
#include <EffekseerForDXLib.h>

//#include "PlayerManager.h"

class PlayerManager;
class Model;
class EffekseerManager;
class ultrasound;
class Enemy;
class SceneMain;

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
	void onDamage(int damage);

	void setEffekseer(EffekseerManager* effekseer){m_pEffekseer = effekseer;}

	void setSceneMain(SceneMain* sceneMain){ m_pSceneMain = sceneMain; }

	int getHandle() const;
	int getColFrameIndex()const;

	void getMaxReachedPoint(float jumpAcc);

	/// <summary>
	/// �v���C���[�������Ă������
	/// </summary>
	/// <returns>�p�x</returns>
	float getAngle() { return m_angle; } 

	//���ʂɂ��邩�ǂ���
	bool isSurface() const {return m_isSurfaceTest;}

	//bool isCol(Enemy& enemy);

	//���f���̑傫���̎擾
	float getRight() { return m_pos.x + 157.0f; }
	float getLeft() { return m_pos.x - 157.0f; }
	float getTop() { return m_pos.y + 214.0f; }
	float getBottom() { return m_pos.y - 86.0f; }
	float getNear() { return m_pos.z + 459.0f; }
	float getFar() { return m_pos.z - 460.0f; }

private:

	//�J�����̍X�V
	void updateCamera();

	//�j��
	void updateSwim();

	//����
	void updateDive();

	//�A�j���[�V����
	//void playAnim();

	enum class MotionType
	{
		swim,
		stand,
	};

	void drawGraphWithShader(int x, int y, int texH, int norm, int psH, int vsH, bool transFlag);

private:
	//�����o�֐��|�C���^
	void(Player::* m_updateFunc)();

	//�����g�N���X���g���|�C���^
	//std::shared_ptr<ultrasound> m_pUltrasound;

	SceneMain* m_pSceneMain;

	//�v���C���[�̃��f��
	std::shared_ptr<Model> m_pModel;


	EffekseerManager* m_pEffekseer;

	//std::map<MotionType, std::shared_ptr<Model>> m_pModel;
	//�Đ����Ă���A�j���[�V�����ԍ�
	int m_animNo;

	//�t���[���J�E���g
	int m_frameCount;

	//�v���C���[�̈ʒu
	VECTOR m_pos;

	//�W�����v�����p�����x
	float m_jumpAcc;

	//������
	float m_diveAcc;

	//�d��
	float m_gravity;

	//����
	float m_buoyancy;

	//�v���C���[�̌����Ă������
	float m_angle;

	//�v���C���[�̉�]����
	float m_rotateAngle;
	
	//�J�����̌����Ă������
	float m_cameraAngle;
	
	//HP
	int m_hp;
	//���G����
	int m_damageFrame;

	//���ʂɓ����������ǂ���
	bool m_isReturnSurface;

	int m_offscreen;
	int m_psH;
	int m_cbH;
	int m_distH = 0;

	int m_circleGauge;

	int m_triangle = 0;
	float* m_cbufferAdress;
	float m_time = 0;

	VECTOR m_cameraPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);

	bool m_isLandingWaterAfterJump;
	bool m_isTest = false;

	int m_testModel;


	//�v���C���[�\����
	//PlayerData m_playerData;

	bool m_isTestPushKey = false;

	VECTOR m_displayMove = VGet(0.0f, 0.0f, 0.0f);

	VECTOR m_direction;

	//�L�[���ǂ̂��炢�̒�����������
	int m_pressKeyTime;
	bool m_isPushPressKey = false;
	float m_maxReachedPoint = 0.0f;
	float m_jumpPowerStrage = 0.0f;

	//�_���[�W��H��������ǂ���
	bool m_isDameged;

	bool m_isDisplayEffekseer;

	bool m_isSurfaceTest = false;

};

