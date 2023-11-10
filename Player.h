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

	//プレイヤーの位置を取得する
	VECTOR getPos() const { return m_pos; }

	//当たり判定の半径
	float getColRadius();

	//ダメージを受けた
	void onDamage(int damage);

	void setEffekseer(EffekseerManager* effekseer){m_pEffekseer = effekseer;}

	void setSceneMain(SceneMain* sceneMain){ m_pSceneMain = sceneMain; }

	int getHandle() const;
	int getColFrameIndex()const;

	void getMaxReachedPoint(float jumpAcc);

	/// <summary>
	/// プレイヤーが向いている方向
	/// </summary>
	/// <returns>角度</returns>
	float getAngle() { return m_angle; } 

	//水面にいるかどうか
	bool isSurface() const {return m_isSurfaceTest;}

	//bool isCol(Enemy& enemy);

	//モデルの大きさの取得
	float getRight() { return m_pos.x + 157.0f; }
	float getLeft() { return m_pos.x - 157.0f; }
	float getTop() { return m_pos.y + 214.0f; }
	float getBottom() { return m_pos.y - 86.0f; }
	float getNear() { return m_pos.z + 459.0f; }
	float getFar() { return m_pos.z - 460.0f; }

private:

	//カメラの更新
	void updateCamera();

	//泳ぐ
	void updateSwim();

	//潜る
	void updateDive();

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

	//超音波クラスを使うポインタ
	//std::shared_ptr<ultrasound> m_pUltrasound;

	SceneMain* m_pSceneMain;

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

	//潜水力
	float m_diveAcc;

	//重力
	float m_gravity;

	//浮力
	float m_buoyancy;

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

	//水面に到着したかどうか
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


	//プレイヤー構造体
	//PlayerData m_playerData;

	bool m_isTestPushKey = false;

	VECTOR m_displayMove = VGet(0.0f, 0.0f, 0.0f);

	VECTOR m_direction;

	//キーをどのくらいの長さ押したか
	int m_pressKeyTime;
	bool m_isPushPressKey = false;
	float m_maxReachedPoint = 0.0f;
	float m_jumpPowerStrage = 0.0f;

	//ダメージを食らったかどうか
	bool m_isDameged;

	bool m_isDisplayEffekseer;

	bool m_isSurfaceTest = false;

};

