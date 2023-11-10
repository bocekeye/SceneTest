#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Log.h"
#include "Ring.h"

EnemyManager::EnemyManager(Player& player):
	m_player(player),
	m_addCount(0)
{
	m_pEnemy.push_back(std::make_shared<Enemy>(player));
	m_pLog.push_back(std::make_shared<Log>(player));
	m_pRing.push_back(std::make_shared<Ring>(player));
}

void EnemyManager::init()
{
	//printfDx("EMANAGER INIT");

	for (auto& enemy : m_pEnemy)
	{
		enemy->init();
	}
	for (auto& log : m_pLog)
	{
		log->init();
	}

	for (auto& ring : m_pRing)
	{
		ring->init();
	}

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
	
	for (auto& log : m_pLog)
	{
		if (!log->isExist())
		{
			addLog();
		}
	}


	for (auto& ring : m_pRing)
	{	
		if (!ring->isExist())
		{
			addRing();
		}
	}

#endif

	//存在しない場合は消す
	auto rmIt = std::remove_if(m_pEnemy.begin(), m_pEnemy.end(),
	//trueは消える、falseは消えない(消えてもらう条件を表すラムダ式)
		[](const std::shared_ptr<Enemy>& enemy)
		{
			return !enemy->isExist();
		});
	//ここまでは実際には消してなく、
	//不要なものを後ろに避けているだけ
	//なので、eraseで後ろを消す
	m_pEnemy.erase(rmIt, m_pEnemy.end());

	auto logRmIt = std::remove_if(m_pLog.begin(), m_pLog.end(),
		[](const std::shared_ptr<Log>& log)
		{
			return !log->isExist();
		});
	m_pLog.erase(logRmIt, m_pLog.end());

	auto ringRmIt = std::remove_if(m_pRing.begin(), m_pRing.end(),
		[](const std::shared_ptr<Ring>& ring)
		{
			return !ring->isExist();
		});
	m_pRing.erase(ringRmIt, m_pRing.end());

	for (auto& enemy : m_pEnemy)
	{
		if (enemy->isExist())
		{
			enemy->update();
		}
	}

	for (auto& log : m_pLog)
	{
		if (log->isExist())
		{
			log->update();
		}
	}

	for (auto& ring : m_pRing)
	{
		if (ring->isExist())
		{
			ring->update();
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
	for (auto& log : m_pLog)
	{
		if (log->isExist())
		{
			log->draw();
		}
	}
	for (auto& ring : m_pRing)
	{
		if (ring->isExist())
		{
			ring->draw();
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

void EnemyManager::addLog()
{
	m_pLog.push_back(std::make_shared<Log>(m_player));
	m_pLog.back()->create();
}

void EnemyManager::addRing()
{
	m_pRing.push_back(std::make_shared<Ring>(m_player));
	m_pRing.back()->create();
}

