#pragma once

#include <list>
#include <memory>

class Enemy;
class Player;
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

	std::list<std::shared_ptr<Enemy>> getData(){return m_pEnemy;}


private:
	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	Player& m_player;

	/// <summary>
	/// 敵の数を増やす
	/// </summary>
	void addEnemy();

	int m_addCount;

};

