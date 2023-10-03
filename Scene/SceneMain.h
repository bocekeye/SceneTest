#pragma once

#include "SceneBase.h"


#include <memory>

class Player;
class SceneManager;

class SceneMain : public SceneBase
{
public:
	SceneMain(SceneManager& manager);

	virtual ~SceneMain() {}

	 void init();

	 void update();
	 void draw();

private:

	std::shared_ptr<Player> m_pPlayer;
		


};
