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

	//モデルの大きさの取得用
	float getRight() { return m_pos.x + kWidth; }
	float getLeft() { return m_pos.x - kWidth; }
	float getTop() { return m_pos.y + kHeight; }
	float getBottom() { return m_pos.y - kHeight; }
	float getFar() { return m_pos.z + kRadius /2; }
	float getNear() { return m_pos.z - kRadius / 2; }

private:

	//モデルの大きさ(仮)
	const float kWidth = 300.0f;
	const float kHeight = 50.0f;
	const float kRadius = 50.0f;

private:

	//座標
	VECTOR m_pos;
	//参照渡し
	Player& m_pPlayer;
	//存在するか
	bool m_isExist;
};

