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

	//プレイヤーの位置を取得する
	VECTOR getPos() const { return m_pos; }

	//当たり判定の半径
	float getColRadius();

	//ダメージを受けた
	void OnDamage(int damage);

private:

	//カメラの更新
	void updateCamera();

	//待機
	void updateIdle();

private:
	//メンバ関数ポインタ
	void (Player::* m_updateFunc)();

	//プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;
	//再生しているアニメーション番号
	int m_animNo;


	//フレームカウント
	int m_frameCount;

	//プレイヤーの位置
	VECTOR m_pos;
	//ジャンプ処理用加速度
	float m_jumpAcc;

	//プレイヤーの向いている方向
	float m_angle;

	//カメラの向いている方向
	float m_cameraAngle;

	//HP
	int m_hp;
	//無敵時間
	int m_damageFrame;
};

