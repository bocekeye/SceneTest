#include "Player.h"

#include "Pad.h"
#include <cassert>
#include <array>
#include "Model.h"
#include "Effekseer.h"
#include "PlayerManager.h"
#include "game.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>


namespace
{
	//ファイル名
	const char* const kFileName = "data/dolphin.mv1";
	//const char* const kFileName2 = "data/Swimming.mv1";

	//カメラの初期位置
	constexpr VECTOR kCameraPos{ 0.0f, 920.0f, 800.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 500.0f, -10.0f };

	//プレイヤーの移動量
	constexpr VECTOR kPlayerVec{ 0.0f, 0.0f, -30.0f };

	//旋回速度
	constexpr float kRotSpeed = 0.03f;

	//ジャンプ力
	constexpr float kJumpPower = 50.0f;
	//重力
	constexpr float kGravity = -1.0f;

	//アニメーション番号
	constexpr int kSwimAnimNo = 1;		//泳ぐモーション

	//アニメーション切り替わりにかかるフレーム数
	constexpr int kAnimChangeFrame = 4;

	//当たり判定のサイズ
	constexpr float kColRudius = 60.0f;

	//最大HP
	constexpr int kMaxHP = 100;
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
	m_angle(0.0f),
	m_rotateAngle(0.0f),
	m_cameraAngle(m_angle),
	m_hp(kMaxHP),
	m_damageFrame(0),
	m_isRotation(false),
	m_isLandingWaterAfterJump(false)

{
	//3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);

	m_pEffekseer = new EffekseerManager;

	m_pModel->setAnimation(static_cast<int>(MotionType::swim), true, true);

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

	float lineSize = 10000.0f;
	int testH = m_pModel->getModelHandle();

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


	SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);
	DrawTriangle3D(VGet(-lineSize / 10, 0, -lineSize), VGet(lineSize / 10, 0, -lineSize), VGet(lineSize / 10, 0, lineSize), 0x00fffff, true);
	DrawTriangle3D(VGet(lineSize / 10, 0, lineSize), VGet(-lineSize / 10, 0, lineSize), VGet(-lineSize / 10, 0, -lineSize), 0x00fffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	m_pEffekseer->draw();
	m_pModel->draw();

#endif

#ifdef _DEBUG
	DrawFormatString(110, 50, 0xffffff, "%f", m_jumpAcc);
	DrawFormatString(110, 70, 0xffffff, "m_pos.x = %f", m_pos.x);
	DrawFormatString(110, 90, 0xffffff, "m_pos.y = %f", m_pos.y);
	DrawFormatString(110, 110, 0xffffff, "m_pos.z = %f", m_pos.z);

	DrawFormatString(110, 130, 0xffffff, "m_displayMove.x = %f", m_displayMove.x);
	DrawFormatString(110, 150, 0xffffff, "m_displayMove.y = %f", m_displayMove.y);
	DrawFormatString(110, 170, 0xffffff, "m_displayMove.z = %f", m_displayMove.z);

	

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
}

int Player::getColFrameIndex() const
{
	return m_pModel->getColFrameIndex();
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


//TODO: 名前を変えろ！！
/// <summary>
/// 小ジャンプにする予定
/// </summary>
void Player::updateSwim()
{
	//アニメーションを進める
	m_pModel->update();

	//プレイヤーの進行方向
	MATRIX playerRotMtx = MGetRotY(m_angle);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);

	m_displayMove = move;

	m_time += 1.0f / 60.0f;

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
	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_angle -= kRotSpeed;
		//isMoving = true;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_angle += kRotSpeed;
	//	isMoving = true;
	}
	
	//ジャンプ処理
	bool isJumping = true;	//ジャンプしているフラグ
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;

	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;

		isJumping = false;
		m_isTest = false;
	}
	//ジャンプ中ではないとき
	if (!isJumping)
	{
		//SPACEキーでジャンプする
		if (Pad::isTrigger(PAD_INPUT_10))
		{
			m_jumpAcc = kJumpPower;
		}
	}
	else
	{	
		move.y = m_jumpAcc;
		//元のモデルがどちらを向いているかの情報
		VECTOR midelDir = VGet(0, 0, -1);

		//進行方向に向けて変換する？
		MATRIX rotMtx = MGetRotVec2(midelDir, move);
		MV1SetMatrix(m_pModel->getModelHandle(), rotMtx);

		if (m_pos.y >= 1.0f)
		{
			m_isTest = true;
		}
	}
	if (m_isTest)
	{
		if (m_pos.y <= 0)
		{
			//エフェクトの発生
			m_pEffekseer->testUpdate(m_pos);
			m_isTest = false;
		}
	}

	m_pEffekseer->update();
	m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(m_rotateAngle, m_angle, 0.0f));
	updateCamera();
}
