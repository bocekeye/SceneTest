#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"

EnemyManager::EnemyManager(Player& player):
	m_player(player),
	m_addCount(0)
{
	m_pEnemy.push_back(std::make_shared<Enemy>(m_player));
}

void EnemyManager::init()
{
	m_pEnemy.back()->init();
}

void EnemyManager::update()
{
#ifdef _DEBUG
	
	for (auto& enemy : m_pEnemy)
	{
		if(!enemy->isExist())
		{		
			addEnemy();		
		}
	}
	
#endif

	//���݂��Ȃ��ꍇ�͏���
	auto rmIt = std::remove_if(m_pEnemy.begin(), m_pEnemy.end(),
	//true�͏�����Afalse�͏����Ȃ�(�����Ă��炤������\�������_��)
		[](const std::shared_ptr<Enemy>& enemy)
		{
			return !enemy->isExist();
		});
	//�����܂ł͎��ۂɂ͏����ĂȂ��A
	//�s�v�Ȃ��̂����ɔ����Ă��邾��
	//�Ȃ̂ŁAerase�Ō�������
	m_pEnemy.erase(rmIt, m_pEnemy.end());

	for (auto& enemy : m_pEnemy)
	{
		if (enemy->isExist())
		{
			enemy->update();
		}
	}
}

void EnemyManager::draw()
{
	for (auto& enemy : m_pEnemy)
	{
		if (enemy->isExist())
		{
			enemy->draw();
		}
	}
}

int EnemyManager::getSize()
{
	return static_cast<int>(m_pEnemy.size());
}

void EnemyManager::addEnemy()
{
	m_pEnemy.push_back(std::make_shared<Enemy>(m_player));
	m_pEnemy.back()->init();
}
