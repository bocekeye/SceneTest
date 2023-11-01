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

	//�v���C���[���g�����߂̃|�C���^
	std::shared_ptr<Player> m_pPlayer;
	//�G�l�~�[���g�����߂̃|�C���^
	std::shared_ptr<EnemyManager> m_pEManager;

	EffekseerManager* m_pEffekseer;

	//�Q�[�����
	int m_gameScreen;
	int m_shader;

};
