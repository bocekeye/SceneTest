#pragma once
#include <DxLib.h>
#include <memory>

class Player;

class Ring
{
public:
	Ring(Player& player);
	virtual ~Ring(){}

	void init();
	void update();
	void draw();

	//輪っかの位置を取得する
	VECTOR getPos() const { return m_pos; }

	//ダメージを受けた
	void onDamege();

	//当たり判定
	bool isCol(Player& player);

	//モデルの大きさの取得用
	float getRight() { return m_pos.x + 23.0f; }
	float getLeft() { return m_pos.x - 23.0f; }
	float getTop() { return m_pos.y + 66.0f; }
	float getBottom() { return m_pos.y - 39.0f; }
	float getFar() { return m_pos.z + 200.0f; }
	float getNear() { return m_pos.z - 120.0f; }

private:

	//座標
	VECTOR m_pos;
	//参照渡し
	Player& m_pPlayer;
	//存在するか
	bool m_isExist;
};

