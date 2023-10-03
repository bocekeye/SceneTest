#pragma once

#include "SceneBase.h"
#include "SceneManager.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& manager);

	virtual ~SceneTitle() {}

	 void init();

	 void update();
	 void draw();

private:

	//update用メンバ関数ポインタ
	void (SceneTitle::* m_updateFunc)();

	//フェードインの時のUpdate関数
	void fadeInUpdate();
	//通常状態のUpdate関数
	void normalUpdate();
	//フェードアウトの時のUpdate関数
	void fadeOutUpdate();

	
	int m_fadeTimer;	//フェードタイマー
	int m_fadeValue;				//黒矩形とのブレンド具合


	//テスト
	int m_fadeX;
	int m_fadeY;
	int m_period;			//振れ幅
	int m_swingWidth;		//周期
	float m_testTimer = 0.0f;
	float m_radius = 1000.0f;			//半径


};
