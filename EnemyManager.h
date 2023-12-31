#pragma once

#include <list>
#include <vector>
#include <memory>

class Enemy;
class Player;
class Log;
class Ring;

class EnemyManager
{
public:
	EnemyManager(Player& player);
	virtual ~EnemyManager(){}

	void init();
	void update();
	void draw();

	
	/// <summary>
	/// コンテナの要素数を取得する
	/// </summary>
	/// <returns>要素数を返す</returns>
	int getSize();

	//魚
	std::list<std::shared_ptr<Enemy>> getEnemyData(){return m_pEnemy;}

	//丸太
	std::list<std::shared_ptr<Log>> getLogData() { return m_pLog; }

	//輪っか
	std::list<std::shared_ptr<Ring>> getRingData() { return m_pRing; }

private:

	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	std::list<std::shared_ptr<Log>>  m_pLog;
	std::list<std::shared_ptr<Ring>> m_pRing;

	Player& m_player;

	/// <summary>
	/// 敵の数を増やす
	/// </summary>
	void addEnemy();

	void addLog();

	void addRing();

	int m_addCount;

};

