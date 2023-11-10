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

	//存在するかどうか
	bool isExist() const { return m_isExist; }

	VECTOR getPos() const { return m_pos; }

	void onDamege();

	void create();

	bool isCol(Player& player);

	//モデルの大きさの取得用
	float getRight() { return m_pos.x + kWidth + m_randomNum; }
	float getLeft() { return m_pos.x - kWidth + m_randomNum; }
	float getTop() { return m_pos.y + kHeight; }
	float getBottom() { return m_pos.y - kHeight; }
	float getNear() { return m_pos.z; }
	float getFar() { return m_pos.z ; }


private:

	//モデルの大きさ(仮)
	const float kWidth = 400.0f;
	const float kHeight = 50.0f;
	const float kRadius = 100.0f;

private:

	//座標
	VECTOR m_pos;
	//参照渡し
	Player& m_pPlayer;
	//存在するか
	bool m_isExist;

	//乱数保存
	int m_randomNum;
};

