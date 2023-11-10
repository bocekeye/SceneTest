#pragma once
#include <DxLib.h>
#include <memory>

class Player;

class Log
{
public:
	Log(Player player);
	virtual ~Log(){}

	void init();
	void update();
	void draw();

	//���݂��邩�ǂ���
	bool isExist() const { return m_isExist; }

	VECTOR getPos() const { return m_pos; }

	void onDamege();

	void create();

	bool isCol(Player& player);

	//���f���̑傫���̎擾�p
	float getRight() { return m_pos.x + kWidth + m_randomNum; }
	float getLeft() { return m_pos.x - kWidth + m_randomNum; }
	float getTop() { return m_pos.y + kHeight; }
	float getBottom() { return m_pos.y - kHeight; }
	float getNear() { return m_pos.z; }
	float getFar() { return m_pos.z ; }


private:

	//���f���̑傫��(��)
	const float kWidth = 400.0f;
	const float kHeight = 50.0f;
	const float kRadius = 100.0f;

private:

	//���W
	VECTOR m_pos;
	//�Q�Ɠn��
	Player& m_pPlayer;
	//���݂��邩
	bool m_isExist;

	//�����ۑ�
	int m_randomNum;
};

