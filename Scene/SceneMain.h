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

	//プレイヤーを使うためのポインタ
	std::shared_ptr<Player> m_pPlayer;
	//エネミーを使うためのポインタ
	std::shared_ptr<EnemyManager> m_pEManager;
	//丸太を使うためのポインタ
	std::shared_ptr<Log> m_pLog;
	//輪っかを使うためのポインタ
	std::shared_ptr<Ring> m_pRing;
	//超音波を使うためのポインタ
	std::vector<std::shared_ptr<ultrasound>> m_pUltrasound;


	EffekseerManager* m_pEffekseer;

	//ゲーム画面
	int m_gameScreen;
	int m_shader;

	int m_underwaterH;
};
