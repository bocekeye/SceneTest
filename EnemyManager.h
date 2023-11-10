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
	/// �R���e�i�̗v�f�����擾����
	/// </summary>
	/// <returns>�v�f����Ԃ�</returns>
	int getSize();

	//��
	std::list<std::shared_ptr<Enemy>> getEnemyData(){return m_pEnemy;}

	//�ۑ�
	std::list<std::shared_ptr<Log>> getLogData() { return m_pLog; }

	//�ւ���
	std::list<std::shared_ptr<Ring>> getRingData() { return m_pRing; }

private:

	std::list<std::shared_ptr<Enemy>>  m_pEnemy;
	std::list<std::shared_ptr<Log>>  m_pLog;
	std::list<std::shared_ptr<Ring>> m_pRing;

	Player& m_player;

	/// <summary>
	/// �G�̐��𑝂₷
	/// </summary>
	void addEnemy();

	void addLog();

	void addRing();

	int m_addCount;

};

