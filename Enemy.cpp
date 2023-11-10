#include "Enemy.h"
#include <DxLib.h>
#include <random>
#include <cmath>
#include "Player.h"
#include "Model.h"

namespace
{
	//ファイル名
	const char* const kFileName = "data/sake.mv1";

	//アニメーション番号
	constexpr int kSwimAnimNo = 0;		//泳ぐモーション
}

Enemy::Enemy(Player& player):
	m_pPlayer(player),
	m_pos(VGet(0,100,-1000)),
	m_isExist(false),
	m_randomNum(0.0f),
	m_radius(500.0f),
	m_createRandomInterval(0)
{
	//3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);
	
	//アニメーションの設置
	m_pModel->setAnimation(kSwimAnimNo, true, true);
}

void Enemy::init()
{
	//初期化時は存在する
	m_isExist = true;
	//ランダム計算
	std::random_device rd;
	std::mt19937 mt(rd());
	//-50.0f～50.0f
	std::uniform_real_distribution <float> rdt(-100.0f, 100.0f);

	m_randomNum = rdt(mt);
}

void Enemy::update()
{
	if (!m_isExist) return;
	
	//アニメーションを進める
	m_pModel->update();

#ifdef _DEBUG

	m_lastPos.x = m_pos.x + 200.0f;
	m_testAngle += 15.0f;
	m_testTime += 5.1f;
	float rad = DX_PI_F * m_testAngle / 180.0f;

	//m_pos.z -= 10.0f;

	m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(0,0,0));
	
#endif
}

void Enemy::draw()
{
	if (!m_isExist) return;

	m_pModel->draw();


#if _DEBUG

	DrawString(500, 20, "魚", 0xffffff);
	DrawFormatString(450,50,0xfffffff,"%f",getFar());

#endif
	//DrawSphere3D(m_pos,50,10,0xffffff,0xffffff,true);

}

void Enemy::onDamege()
{
	m_isExist = false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
bool Enemy::isCol(Player& player)
{
	if (!m_isExist) return false;

	if (player.getLeft() > getRight()) return false;
	if (player.getRight() < getLeft()) return false;
	if (player.getTop() < getBottom()) return false;
	if (player.getBottom() > getTop()) return false;
	if (player.getNear() < getFar()) return false;
	if (player.getFar() > getNear()) return false;

	return true;
}