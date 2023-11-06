#pragma once
#include <DxLib.h>
#include <memory>

class Player;
class Model;

class Enemy
{
public:

	Enemy(Player& player);
	virtual ~Enemy(){}

	void init();
	void update();
	void draw();

	bool isExist() const {return m_isExist;}

	//int getHandle() const;
	//int getColFrameIndex()const;

	VECTOR getPos() const { return m_pos; }
	VECTOR getLastPos() const { return m_lastPos; }

	void onDamege();

	//���f���̑傫���̎擾�p
	float getRight() { return m_pos.x + 23.0f; }
	float getLeft() { return m_pos.x - 23.0f; }
	float getTop() { return m_pos.y + 66.0f; }
	float getBottom() { return m_pos.y - 39.0f; }
	float getFar() { return m_pos.z + 200.0f; }
	float getNear() { return m_pos.z - 120.0f; }

private:

	std::shared_ptr<Model> m_pModel;

	//���W
	VECTOR m_pos;
	VECTOR m_lastPos;
	//�Q�Ɠn��
	Player& m_pPlayer;
	//���݂��邩
	bool m_isExist;
	//�����_���Ȑ��p�̃����o�ϐ�
	float m_randomNum;

	float m_testTime = 0.0f;
	float m_testAngle = 0.0f;
	int m_testInterval = 0;

//	int m_handle = -1;

	float m_radius;	//���a

};

