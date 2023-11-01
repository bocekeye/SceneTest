#pragma once

#include <memory>
#include <list>
#include <map>
#include <DxLib.h>
#include <string>



class Model;
class Player;

/// <summary>
/// �v���C���[�̓���̎��
/// </summary>
class PlayerManager
{
public:

	PlayerManager();
	virtual ~PlayerManager(){}

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	std::list<std::shared_ptr<Player>>& getPlayers();


	enum class MotionType : int 
	{
		Swim,
		Stand,
		
	};

	std::shared_ptr<Player> make(MotionType type);

private:

	std::list<std::shared_ptr<Player>> m_pPlayer;
	std::shared_ptr<Model> m_pModel;

	std::map<MotionType,std::string > m_model;	//�v���C���[�̎�ʂƃ��f���̃y�A

//protected:
public:


	struct PlayerData
	{
		VECTOR m_pos;
		int hp;
	};

};
