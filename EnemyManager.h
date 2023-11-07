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
	/// ƒRƒ“ƒeƒi‚Ì—v‘f”‚ğæ“¾‚·‚é
	/// </summary>
	/// <returns>—v‘f”‚ğ•Ô‚·</returns>
	int getSize();

	std::list<std::shared_ptr<Enemy>> getData(){return m_pEnemy;}

private:
	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	Player& m_player;

	/// <summary>
	/// “G‚Ì”‚ğ‘‚â‚·
	/// </summary>
	void addEnemy();

	int m_addCount;

};

