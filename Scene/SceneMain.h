#pragma once

#include "SceneBase.h"
#include <memory>
#include <vector>
#include <DxLib.h>

class SceneManager;
class Player;
class EnemyManager;
class PlayerManager;
class Log;
class Ring;
class ultrasound;
class EffekseerManager;

class SceneMain : public SceneBase
{
public:
	SceneMain(SceneManager& manager);

	virtual ~SceneMain();

	 void init();

	 void update();
	 void draw();

	 void ultrasoundStart(VECTOR start,VECTOR vec);

private:

	//�v���C���[���g�����߂̃|�C���^
	std::shared_ptr<Player> m_pPlayer;
	//�G�l�~�[���g�����߂̃|�C���^
	std::shared_ptr<EnemyManager> m_pEManager;
	//�ۑ����g�����߂̃|�C���^
	std::shared_ptr<Log> m_pLog;
	//�ւ������g�����߂̃|�C���^
	std::shared_ptr<Ring> m_pRing;
	//�����g���g�����߂̃|�C���^
	std::vector<std::shared_ptr<ultrasound>> m_pUltrasound;


	EffekseerManager* m_pEffekseer;

	//�Q�[�����
	int m_gameScreen;
	int m_shader;

	int m_underwaterH;
};
