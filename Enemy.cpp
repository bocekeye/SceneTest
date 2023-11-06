#include "Enemy.h"
#include <DxLib.h>
#include <random>
#include <cmath>
#include "Player.h"
#include "Model.h"

namespace
{
	const char* const kFileName = "data/sake.mv1";
}

Enemy::Enemy(Player& player):
	m_pPlayer(player),
	m_pos(VGet(0,100,0)),
	m_isExist(true),
	m_randomNum(0.0f),
	m_radius(500.0f)
{
	//3Dƒ‚ƒfƒ‹‚Ì¶¬
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->setUseCollision(true,true);
}

void Enemy::init()
{
	//‰Šú‰»‚Í‘¶İ‚·‚é
	m_isExist = true;
	//ƒ‰ƒ“ƒ_ƒ€ŒvZ
	std::random_device rd;
	std::mt19937 mt(rd());
	//-50.0f`50.0f
	std::uniform_real_distribution <float> rdt(-500.0f, 500.0f);

	m_randomNum = rdt(mt);

}

void Enemy::update()
{
	if (!m_isExist) return;
	
#ifdef _DEBUG
	if (m_pos.x >= 2000.0f || m_pos.x <= -2000.0f)
	{
		m_isExist = false;
	}

	//m_lastPos = m_pos;
	m_testAngle += 15.0f;
	m_testTime += 5.1f;

	if (m_testInterval++ >= 300)
	{
		m_isExist = false;
	}

	float rad = DX_PI_F * m_testAngle / 180.0f;

//	m_pos.x = m_radius * cos(rad);
//	m_pos.y = m_radius * sin(rad) + 700.0f;

//	m_pos.y += m_randomNum;
//	m_pos.z = m_pPlayer.getPos().z;

//	m_pos.y += m_randomNum;
//	m_pos.z += m_randomNum;

	m_pModel->setPos(m_pos);
	m_pModel->setRot(VGet(0,0,0));

	

#endif
}

void Enemy::draw()
{
	if (!m_isExist) return;

	m_pModel->draw();

	//DrawSphere3D(m_pos,50,10,0xffffff,0xffffff,true);
//	DrawCapsule3D(m_pos, m_lastPos,50, 30, 0x0ff00f, 0xffffff, true);
	
}

void Enemy::onDamege()
{
	//printfDx("SSS");
}

//int Enemy::getColFrameIndex() const
//{
//	return m_pModel->getColFrameIndex();
//}
//
//int Enemy::getHandle()const
//{
//	return m_pModel->getModelHandle();
//}
