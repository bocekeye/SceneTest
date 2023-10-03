#include "Player.h"
#include <DxLib.h>
#include "Pad.h"
#include <assert.h>
#include "Model.h"


namespace
{
	//ファイル名
	const char* const kFileName = "data/player.mv1";

	//カメラの初期位置
	constexpr VECTOR kCameraPos{ 0.0f, 720.0f, 720.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 400.0f, -120.0f };

	//プレイヤーの移動量
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -15.0f };

	//ショットの速度
	constexpr float kShotSpeed = 100.0f;

	//旋回速度
	constexpr float kRotSpeed = 0.03f;

	//ジャンプ力
	constexpr float kJumpPower = 16.0f;
	//重力
	constexpr float kGravity = -1.0f;

	//アニメーション番号
	constexpr int kIdleAnimNo = 3;	//待機モーション
	constexpr int kIdleShootAnimNo = 5;	//停止している状態でショットを撃つアニメーション
	constexpr int kWalkAnimNo = 14;	//移動モーション

	//アニメーション切り替わりにかかるフレーム数
	constexpr int kAnimChangeFrame = 4;

	//当たり判定のサイズ
	constexpr float kColRudius = 60.0f;

	//最大HP
	constexpr int kMaxHP = 100;
}

Player::Player() :
	m_updateFunc(&Player::updateIdle),
	m_animNo(kIdleAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_angle(0.0f),
	m_cameraAngle(m_angle),
	m_hp(kMaxHP),
	m_damageFrame(0)

{
	//3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->setAnimation(m_animNo, true, true);

}

Player::~Player()
{
}

void Player::init()
{
}

void Player::update()
{
	(this->*m_updateFunc)();
}

void Player::draw()
{
	if (m_damageFrame > 0)
	{
		if (m_damageFrame % 2) return;
	}

	m_pModel->draw();
}

float Player::getColRadius()
{
	return kColRudius;
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
}

void Player::updateCamera()
{
	//m_cameraAngle = m_angle;
	m_cameraAngle = (m_cameraAngle * 0.8f) + (m_angle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_cameraAngle);

	//ジャンプ時は単純にプレイヤーに追従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = m_pos;
	//cameraTrans.y = 0.0f;
	cameraTrans.y = m_pos.y * 0.3f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	//プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	//プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	//カメラの設定
	//どこまで表示するか
	//SetCameraNearFar(5.0f, 2800.0f);
	SetCameraNearFar(5.0f, 3500.0f);
	//カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);
}

void Player::updateIdle()
{
	//アニメーションを進める
	m_pModel->update();
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	//ジャンプ処理
	bool isJumping = true;	//ジャンプしているフラグ
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;

		isJumping = false;
	}

	//プレイヤーの進行方向
	MATRIX playerRotMtx = MGetRotY(m_angle);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	if (!isJumping)
	{
		//SPACEボタンでジャンプ
		if (Pad::isTrigger(PAD_INPUT_10))
		{
			m_jumpAcc = kJumpPower;
		}
	}

	//左右キーで旋回する
	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
		isMoving = true;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
		isMoving = true;
	}


	//上下キーで前後移動
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, move);
		isMoving = true;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos = VSub(m_pos, move);
		isMoving = true;
	}

	if (isMoving)
	{
		if (m_animNo == kIdleAnimNo)
		{
			//歩行アニメに変更
			m_animNo = kWalkAnimNo;
			m_pModel->changeAnimation(14, true, false, 4);
		}
	}
	else
	{
		if (m_animNo == kWalkAnimNo)
		{
			//待機アニメに変更
			m_animNo = kIdleAnimNo;
			m_pModel->changeAnimation(kIdleAnimNo, true, false, 4);
		}
	}

	m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));
	updateCamera();
}


