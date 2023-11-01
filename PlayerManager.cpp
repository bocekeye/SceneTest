#include "PlayerManager.h"
#include "Model.h"
#include "Player.h"
#include <DxLib.h>
#include <memory>

PlayerManager::PlayerManager()
{
	//m_model[MotionType::Stand] = "data/spinP.mv1";
	//m_model[MotionType::Swim] = "data/Swimming.mv1";
}

std::list<std::shared_ptr<Player>>& PlayerManager::getPlayers()
{
	// TODO: return ステートメントをここに挿入します
	return m_pPlayer;
}

std::shared_ptr<Player> PlayerManager::make(MotionType type)
{
	if (type == MotionType::Stand)
	{
		//return std::make_shared<Player>(m_model[MotionType::Stand]);
	}



	return nullptr;
}


