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

	bool isExist() const { return m_isExist; }

	VECTOR getPos() const { return m_pos; }

	void onDamege();

	bool isCol(Player& player);

	//���f���̑傫���̎擾�p
	float getRight() { return m_pos.x + kWidth; }
	float getLeft() { return m_pos.x - kWidth; }
	float getTop() { return m_pos.y + kHeight; }
	float getBottom() { return m_pos.y - kHeight; }
	float getFar() { return m_pos.z + kRadius /2; }
	float getNear() { return m_pos.z - kRadius / 2; }

private:

	//���f���̑傫��(��)
	const float kWidth = 300.0f;
	const float kHeight = 50.0f;
	const float kRadius = 50.0f;

private:

	//���W
	VECTOR m_pos;
	//�Q�Ɠn��
	Player& m_pPlayer;
	//���݂��邩
	bool m_isExist;
};

