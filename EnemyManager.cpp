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
