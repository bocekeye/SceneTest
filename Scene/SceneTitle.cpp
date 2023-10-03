#include "DxLib.h"
#include "../game.h"

#include "SceneTitle.h"	
#include "SceneDebug.h"
#include "SceneMain.h"
#include "SceneManager.h"
#include "../Font.h"
#include "../Pad.h"
#include "../Sound.h"
#include "../fadeManager.h"

#include <cmath>

namespace
{
    //フェード開始までの時間
    constexpr int kFadeInterval = 120;
}


SceneTitle::SceneTitle(SceneManager& manager):
	SceneBase(manager),
	m_updateFunc(&SceneTitle::fadeInUpdate),
    m_fadeTimer(kFadeInterval),
    m_fadeValue(255),
	m_fadeX(100),
	m_fadeY(0),
	m_period(120),
	m_swingWidth(100)
{

}

void SceneTitle::init()
{


}

void SceneTitle::update()
{
#ifdef _DEBUG

	(this->*m_updateFunc)();

#else

#endif

}

void SceneTitle::draw()
{
	Font::getInstance().draw("SceneTitle");
	Sound::getInstance().play("bgmMain");

	
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);	//(255:MAX,0:MIN)
	//特定の場所を真っ黒に塗りつぶす
	//DrawCircle(m_fadeX, m_fadeY, 100, 0x000000);
	DrawBox(static_cast<float>(Game::kScreenWidth) / 2, static_cast<float>(Game::kScreenHeight) / 2, m_fadeX, m_fadeY, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::fadeInUpdate()
{
	//真っ黒から徐々に表示する場合
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(kFadeInterval));
	//グラデーションを使って徐々に表示する場合
	/*fadeTimer_;*/
	if (m_radius <= 0.0f)
	{
		m_updateFunc = &SceneTitle::normalUpdate;
		m_radius = 0.0f;
	}

	m_radius -= 5.0f;
	//printfDx("%f\n", m_radius);

	m_testTimer += 10.0f;
	float rad = m_testTimer * DX_PI_F / 180.0f;

	m_fadeX = static_cast<float>(Game::kScreenWidth) / 2.0f + (m_radius * cos(rad));
	m_fadeY = static_cast<float>(Game::kScreenHeight) / 2.0f + (m_radius * sin(rad));

}

void SceneTitle::normalUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		//m_updateFunc = &SceneTitle::fadeOutUpdate;
		m_manager.changeScene(new SceneDebug(m_manager));
		return;
	}
}

void SceneTitle::fadeOutUpdate()
{

	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(kFadeInterval));
	if (++m_fadeTimer == kFadeInterval)
	{
		m_manager.changeScene(new SceneDebug(m_manager));
		return;
	}
}
