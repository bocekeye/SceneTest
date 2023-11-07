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
	/// �R���e�i�̗v�f�����擾����
	/// </summary>
	/// <returns>�v�f����Ԃ�</returns>
	int getSize();

	std::list<std::shared_ptr<Enemy>> getData(){return m_pEnemy;}

private:
	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	Player& m_player;

	/// <summary>
	/// �G�̐��𑝂₷
	/// </summary>
	void addEnemy();

	int m_addCount;

};

