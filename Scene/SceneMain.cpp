#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneTitle.h"

#include "../Player.h"
#include "../Font.h"
#include "SceneDebug.h"
#include "../Pad.h"

SceneMain::SceneMain(SceneManager& manager):
    SceneBase(manager)
{
    m_pPlayer = std::make_shared<Player>();
   // Font::getInstance().load();
}

void SceneMain::init()
{
    m_pPlayer->init();
}

void SceneMain::update()
{
    m_pPlayer->update();
#ifdef _DEBUG
    if (Pad::isTrigger(PAD_INPUT_1))
    {
        m_manager.changeScene(new SceneDebug(m_manager));
        return;
    }

    // デバッグ描画
    // XYZ軸
    float lineSize = 1000.0f;
    for (int i = -10; i < 11; i++)
    {
        DrawLine3D(VGet(-lineSize, 0, i * 100), VGet(lineSize, 0, i * 100),0xff0000);
        DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0),0x00ff00);
        DrawLine3D(VGet(i * 100, 0, -lineSize), VGet(i * 100, 0, lineSize),0x0000ff);
    }

#else

#endif

}

void SceneMain::draw()
{
 //   m_pPlayer->draw();

    Font::getInstance().draw("SceneMain");
}
