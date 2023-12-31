#include "Player.h"

#include "Pad.h"
#include <cassert>
#include <array>
#include "Model.h"
#include "ultrasound.h"
#include "Effekseer.h"
#include "PlayerManager.h"
#include "Scene/SceneMain.h"
#include "game.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>


namespace
{
	//ファイル名
	const char* const kFileName = "data/dolphin.mv1";
	//const char* const kFileName = "data/Shark.mv1";
	//const char* const kFileName = "data/manta.mv1";

	//カメラの初期位置
	constexpr VECTOR kCameraPos{ 0.0f, 620.0f, 800.0f };
	//constexpr VECTOR kCameraPos{ 0.0f, 200.0f, 1000.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 500.0f, -10.0f };

	//プレイヤーの移動量
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };

	//旋回速度
	constexpr float kRotSpeed = 0.03f;

	//ジャンプ力
	constexpr float kJumpPower = 50.0f;

	//重力
	constexpr float kGravity = -1.0f;

	//潜水力
	constexpr float kDivePower = -45.0f;

	//浮力
	constexpr float kBuoyancy = 1.0f;

	//アニメーション番号
	constexpr int kSwimAnimNo = 1;		//泳ぐモーション

	//アニメーション切り替わりにかかるフレーム数
	constexpr int kAnimChangeFrame = 4;

	//当たり判定のサイズ
	constexpr float kColRudius = 60.0f;

	//最大HP
	constexpr int kMaxHP = 10;
}

void Player::drawGraphWithShader(int x, int y, int texH, int norm, int psH, int vsH, bool transFlag)
{
	int w, h;
	GetGraphSize(texH, &w, &h);
	std::array<VERTEX2DSHADER, 4> verts;
	//頂点をZの字になるように並べていく
	//左上
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;

	//右上
	verts[1].pos.x = x + w;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;

	//左下
	verts[2].pos.x = x;
	verts[2].pos.y = y + h;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;

	//右下
	verts[3].pos.x = x + w;
	verts[3].pos.y = y + h;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;

	for (auto& v : verts)
	{
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(255, 255, 255, 255);
		v.pos.z = 0.5f;
		v.rhw = 1.0f;
		v.su = 0.0f;
		v.sv = 0.0f;
	}

	SetUsePixelShader(psH);// シェーダーを使用した描画に使用するピクセルシェーダーを設定する
	SetUseVertexShader(vsH);
	//どのテクスチャを何番に割り当てるのか
	SetUseTextureToShader(0, texH);
	SetUseTextureToShader(1, norm);
	if (transFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// シェーダーを使って２Ｄプリミティブを描画する
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

Player::Player() :
	m_updateFunc(&Player::updateSwim),
	m_animNo(kSwimAnimNo),
	m_frameCount(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_jumpAcc(0.0f),
	m_diveAcc(0.0f),
	m_gravity(0.0f),
	m_buoyancy(0.0f),
	m_angle(0.0f),
	m_rotateAngle(0.0f),
	m_cameraAngle(m_angle),
	m_hp(kMaxHP),
	m_damageFrame(0),
	m_isReturnSurface(false),
	m_circleGauge(0),
	m_isLandingWaterAfterJump(false),
	m_pressKeyTime(0),
	m_direction(VGet(0.0f, 0.0f, -30.0f)),
	m_isDameged(false),
	m_isDisplayEffekseer(false)

{
	//3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);

	m_pEffekseer = new EffekseerManager;

	m_pModel->setAnimation(static_cast<int>(MotionType::swim), true, true);

	m_circleGauge = LoadGraph("data/circle.png");

	//構造体の中身の初期化
	//m_playerData.hp = 0;
	//m_offscreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);
	m_psH = LoadPixelShader("PixelShader.pso");
	m_distH = LoadGraph("data/norm.png");

	//定数バッファの作成
	m_cbH = CreateShaderConstantBuffer(sizeof(float) * 4);
	m_cbufferAdress = static_cast<float*>(GetBufferShaderConstantBuffer(m_cbH));


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
	if (m_damageFrame % 2 == 1)
	{
		return;
	}

	float lineSize = 50000.0f;
	

#if false

	DrawTriangle3D(VGet(-lineSize, 0, -lineSize), VGet(lineSize, 0, -lineSize), VGet(lineSize, 0, lineSize), 0x00fffff, true);
	DrawTriangle3D(VGet(lineSize, 0, lineSize), VGet(-lineSize, 0, lineSize), VGet(-lineSize, 0, -lineSize), 0x00fffff, true);

//	SetDrawScreen(m_offscreen);
//	ClearDrawScreen();

	SetUsePixelShader(m_psH);	

	//どこまで表示するか
	SetCameraNearFar(5.0f, 5000.0f);
	//カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);

	m_pModel->draw();
	//SetRenderTargetToShader(0, -1);
	//SetRenderTargetToShader(0, testH);	// シェーダーを使用した描画での描画先を設定する
	//m_triangle = DrawTriangle3D(VGet(-lineSize, 0, -lineSize), VGet(lineSize, 0, -lineSize), VGet(lineSize, 0, lineSize), 0x00fffff, true);

	drawGraphWithShader(0, 0, testH, m_distH, m_psH, -1, true);

	//SetDrawScreen(DX_SCREEN_BACK);
	m_cbufferAdress[0] = m_time;
	UpdateShaderConstantBuffer(m_cbH);
	SetShaderConstantBuffer(m_cbH, DX_SHADERTYPE_PIXEL, 8);
	
	//drawGraphWithShader(m_pos.x, m_pos.y, m_offscreen, m_distH, m_psH, -1, true);

#else
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), 0x00ff00);

#if true
	int handle = m_pModel->getModelHandle();

	//どの場所に表示するか
	int frameNo = MV1SearchFrame(handle, "Head_end");
	//HPバーを表示する座標データのワールド座標を取得する
	VECTOR hpPos = MV1GetFramePosition(handle, frameNo);
	//HPバー表示位置のワールド座標をスクリーン座標に変換する
	VECTOR screenPos = ConvWorldPosToScreenPos(hpPos);
	if (screenPos.z <= 0.0f || screenPos.z >= 1.0f)
	{
		//表示範囲外の場合何も表示しない
		return;
	}

	//最大HPに対する現在のHPの割合を計算する
	float hpRate = static_cast<float>(m_hp) / static_cast<float> (kMaxHP);

	//HPバーの長さを計算する
	float barWidth = 64 * hpRate;

	//現在のHP
	DrawBoxAA(screenPos.x - 64 / 2, screenPos.y,
		screenPos.x - 64 / 2 + barWidth, screenPos.y + 10,
		0x00ff00, true);


	//枠線
	DrawBoxAA(screenPos.x - 64 / 2, screenPos.y,
		screenPos.x + 64 / 2, screenPos.y + 10,
		0xffffff, false);
#endif

	m_pEffekseer->draw();
	m_pModel->draw();

#endif

#ifdef _DEBUG

	DrawString(150,20,"イルカ",0xffffff);
	DrawFormatString(110, 50, 0xffffff, "m_pos.y = %f", m_pos.y);
	DrawFormatString(110, 70, 0xffffff, "m_displayMove.x = %f", m_displayMove.x);
	DrawFormatString(110, 90, 0xffffff, "m_gravity = %f", m_gravity);
	DrawFormatString(110, 110, 0xffffff, "m_displayMove.z = %f", m_displayMove.z);

	DrawFormatString(110, 130, 0xffffff, "m_hp = %d", m_hp);
	//DrawFormatString(110, 150, 0xffffff, "m_displayMove.y = %f", m_displayMove.y);
	//DrawFormatString(110, 170, 0xffffff, "m_displayMove.z = %f", m_displayMove.z);


#endif

}

float Player::getColRadius()
{
	return kColRudius;
}

void Player::onDamage(int damage)
{
	if (m_damageFrame > 0) return;
	m_hp -= damage;
	m_damageFrame = 60 * 2;
	m_isDameged = true;
}

int Player::getColFrameIndex() const
{
	return m_pModel->getColFrameIndex();
}

void Player::getMaxReachedPoint(float jumpAcc)
{
	m_maxReachedPoint = jumpAcc -2.0f;	
}


int Player::getHandle()const
{
	return m_pModel->getModelHandle();
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
	cameraTrans.y = m_pos.y * 0.9f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	//プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	//プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	m_cameraPos = VTransform(kCameraPos, cameraMtx);
	m_targetPos = VTransform(kCameraTarget, cameraMtx);

	//カメラの設定

	//どこまで表示するか
	SetCameraNearFar(5.0f, 5000.0f);
	//カメラの視野角(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	//カメラの位置、どこからどこを見ているかを設定
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos);
}

/// <summary>
/// 小ジャンプにする予定
/// </summary>
void Player::updateSwim()
{
	//ダメージを食らったとき
	if (m_isDameged)
	{
		if (m_damageFrame-- <= 0)
		{
			m_damageFrame = 0;
			m_isDameged = false;
		}
	}

	//アニメーションを進める
	m_pModel->update();

	//プレイヤーの進行方向
	//もともと向いている方向
	VECTOR beforeFace = (VGet(0.0f, 0.0f, -1.0f));
		
	//引数で指定された回転値分だけY軸回転する回転行列を取得する
	MATRIX playerRotMtx = MGetRotY(m_angle);

	//回転行列を使ったベクトルの変換(現在どこを向いて進んでいるのか？)
	//move→モデルがどの方向を向いているかの情報
	VECTOR move = VTransform(m_direction, playerRotMtx);

	m_pos = VAdd(m_pos, move);

	//水面にいる間はまっすぐの状態にする(仮)
	if (m_pos.y <= 0.0f)
	{
		m_rotateAngle = 0.0f;
	}

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, move);
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos = VSub(m_pos, move);
	}

	//左右キーで旋回する
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
	}

	//潜るキー
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		m_diveAcc = kDivePower;
		m_buoyancy = kBuoyancy;
		m_updateFunc = &Player::updateDive;
	}

	//(仮)超音波を出す
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		VECTOR shotStart =	m_pos;
		//shotStart.z = getFar();

		//超音波ベクトルの生成
		VECTOR ultrasoundVec = move;
		ultrasoundVec = VNorm(ultrasoundVec);
		ultrasoundVec = VScale(ultrasoundVec,100.0f);
		m_pSceneMain->ultrasoundStart(shotStart, ultrasoundVec);
	}

	//ジャンプ処理
	bool isJumping = true;	//ジャンプしているフラグ
	//m_isTestPushKey = false;

	m_jumpAcc += m_gravity;
	m_pos.y += m_jumpAcc;

	//多分水面に戻った時
	if (m_pos.y <= 0.0f)
	{
		isJumping = false;
		m_isReturnSurface = true;
		m_isSurfaceTest = false;
		//m_isTest = false;
	}

	//ジャンプ中ではないとき
	if (!isJumping)
	{
		//SPACEキーでジャンプする
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_jumpAcc = kJumpPower;
			m_jumpPowerStrage = kJumpPower;
			m_isTestPushKey = true;
			m_isReturnSurface = false;
			m_pressKeyTime = 0;
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_jumpAcc = kJumpPower / 2;
			m_jumpPowerStrage = kJumpPower / 2;
			m_isTestPushKey = true;
			m_isReturnSurface = false;
			m_pressKeyTime = 0;
		}
	}
	else
	{	
		//m_isReturnSurface = false;
		//ジャンプ中の時はエフェクシアは表示させない
		m_isDisplayEffekseer = false;
		m_isTest = true;
	}

	//最高到達点の取得
	getMaxReachedPoint(m_jumpPowerStrage);

	//ジャンプキーを押した場合
	if (m_isTestPushKey)
	{
		//潜って水面に到着した時
		if (m_isReturnSurface)
		{
			m_isDisplayEffekseer = true;
			m_isSurfaceTest = true;
			m_gravity = kBuoyancy;
//*****値は表示して見たため計算で求められるなら計算で求める！*****
			if (m_jumpAcc >= m_maxReachedPoint)
			{
				m_jumpAcc = 0.0f;
				m_gravity = 0.0f;
				m_pos.y = 0.0f;
				m_isTestPushKey = false;
			}
		}
		else
		{
			m_gravity = kGravity;
			m_isSurfaceTest = false;
		}
	}


	if (m_isDisplayEffekseer && m_isTest)
	{
		//エフェクトの発生
		m_pEffekseer->testUpdate(m_pos);
		m_isTest = false;	
	}


	//printfDx("%f\n", m_jumpAcc);

	move = VGet(move.x, m_jumpAcc, move.z);				//jump方向
	
	//もともと向いている方向から現在向いている方向の回転行列を求める
	MATRIX targetPos = MGetRotVec2(beforeFace, move);

	m_displayMove = move;

	//モデルの向きからジャンプする向きへ変換する回転行列を取得する
//	MATRIX rotMtx = MGetRotVec2(move, jumpPos);

	//プレイヤーの回転情報をかける
//	rotMtx = MMult(rotMtx, playerRotMtx);

#if false
	//逆行列を求める
	MATRIX invMtx = MInverse(rotMtx);
	rotMtx = MMult(rotMtx, playerRotMtx);
#endif

	//平行移動行列の取得
	VECTOR moveTrans = m_pos;
	MATRIX moveMtx = MGetTranslate(moveTrans);

	//回転行列と平行移動行列をかけて座標に反映する
	MATRIX moveMult = MMult(targetPos, moveMtx);
	MV1SetMatrix(m_pModel->getModelHandle(), moveMult);

	m_pEffekseer->update();
	//m_pModel->setPos(m_pos);
	//m_pModel->setRot(VGet(0.0f, m_angle, 0.0f));
	
	updateCamera();
}

//潜る
void Player::updateDive()
{
	m_pModel->update();

	//プレイヤーの進行方向
	//もともと向いている方向
	VECTOR beforeFace = (VGet(0.0f, 0.0f, -1.0f));

	//引数で指定された回転値分だけY軸回転する回転行列を取得する
	MATRIX playerRotMtx = MGetRotY(m_angle);

	//回転行列を使ったベクトルの変換(現在どこを向いて進んでいるのか？)
	//move→モデルがどの方向を向いているかの情報
	VECTOR move = VTransform(m_direction, playerRotMtx);

	//m_pos = VAdd(m_pos, move);

	//水面にいる間はまっすぐの状態にする(仮)
	if (m_pos.y <= 0.0f)
	{
		m_rotateAngle = 0.0f;
	}

	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, move);
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos = VSub(m_pos, move);
	}

	//左右キーで旋回する
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
	}

	m_diveAcc += m_buoyancy;
	m_pos.y += m_diveAcc;
	
	if (m_pos.y >= 0.0f)
	{
		m_pos.y = 0.0f;
		m_diveAcc = 0.0f;
		m_buoyancy = 0.0f;
		m_updateFunc = &Player::updateSwim;
	}

	move = VGet(move.x, m_diveAcc, move.z);				//dive方向

	//もともと向いている方向から現在向いている方向の回転行列を求める
	MATRIX targetPos = MGetRotVec2(beforeFace, move);

	//平行移動行列の取得
	VECTOR moveTrans = m_pos;
	MATRIX moveMtx = MGetTranslate(moveTrans);

	//回転行列と平行移動行列をかけて座標に反映する
	MATRIX moveMult = MMult(targetPos, moveMtx);
	MV1SetMatrix(m_pModel->getModelHandle(), moveMult);


	updateCamera();

}
