#pragma once

#include <memory>
#include <map>

#include <DxLib.h>
#include <EffekseerForDXLib.h>

//#include "PlayerManager.h"

class PlayerManager;
class Model;
class EffekseerManager;
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
	void onDamage(int damage);

	void setEffekseer(EffekseerManager* effekseer){m_pEffekseer = effekseer;}

	int getHandle() const;
	int getColFrameIndex()const;

private:

	//カメラの更新
	void updateCamera();

	//泳ぐ
	void updateSwim();

	//アニメーション
	//void playAnim();

	enum class MotionType
	{
		swim,
		stand,
	};

	void drawGraphWithShader(int x, int y, int texH, int norm, int psH, int vsH, bool transFlag);

private:
	//メンバ関数ポインタ
	void(Player::* m_updateFunc)();

	//プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;
	EffekseerManager* m_pEffekseer;

	//std::map<MotionType, std::shared_ptr<Model>> m_pModel;
	//再生しているアニメーション番号
	int m_animNo;

	//フレームカウント
	int m_frameCount;

	//プレイヤーの位置
	VECTOR m_pos;

	//ジャンプ処理用加速度
	float m_jumpAcc;

	//重力
	float m_gravity;

	//プレイヤーの向いている方向
	float m_angle;

	//プレイヤーの回転方向
	float m_rotateAngle;
	
	//カメラの向いている方向
	float m_cameraAngle;
	
	//HP
	int m_hp;
	//無敵時間
	int m_damageFrame;

	bool m_isRotation;

	bool m_isReturnSurface;

	int m_offscreen;
	int m_psH;
	int m_cbH;
	int m_distH = 0;

	int m_triangle = 0;
	float* m_cbufferAdress;
	float m_time = 0;

	VECTOR m_cameraPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_targetPos = VGet(0.0f, 0.0f, 0.0f);

	bool m_isLandingWaterAfterJump;
	bool m_isTest = false;

	int m_testModel;

	VECTOR m_displayMove;

	//プレイヤー構造体
	//PlayerData m_playerData;

	bool m_isTestPushKey = false;

};

