#pragma once

#include "SceneBase.h"
#include <memory>

class SceneManager;
class Player;
class EnemyManager;
class PlayerManager;
class EffekseerManager;
class SceneMain : public SceneBase
{
public:
	SceneMain(SceneManager& manager);

	virtual ~SceneMain();

	 void init();

	 void update();
	 void draw();

private:

	//プレイヤーを使うためのポインタ
	std::shared_ptr<Player> m_pPlayer;
	//エネミーを使うためのポインタ
	std::shared_ptr<EnemyManager> m_pEManager;

	EffekseerManager* m_pEffekseer;

	//ゲーム画面
	int m_gameScreen;
	int m_shader;

};
