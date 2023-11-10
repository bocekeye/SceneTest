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
	/// ƒRƒ“ƒeƒi‚Ì—v‘f”‚ğæ“¾‚·‚é
	/// </summary>
	/// <returns>—v‘f”‚ğ•Ô‚·</returns>
	int getSize();

	//‹›
	std::list<std::shared_ptr<Enemy>> getEnemyData(){return m_pEnemy;}

	//ŠÛ‘¾
	std::list<std::shared_ptr<Log>> getLogData() { return m_pLog; }

	//—Ö‚Á‚©
	std::list<std::shared_ptr<Ring>> getRingData() { return m_pRing; }

private:

	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	std::list<std::shared_ptr<Log>>  m_pLog;
	std::list<std::shared_ptr<Ring>> m_pRing;

	Player& m_player;

	/// <summary>
	/// “G‚Ì”‚ğ‘‚â‚·
	/// </summary>
	void addEnemy();

	void addLog();

	void addRing();

	int m_addCount;

};

