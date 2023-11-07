#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneDebug.h"

#include "../Player.h"
#include "../EnemyManager.h"
#include "../Enemy.h"
#include "../PlayerManager.h"
#include "../Log.h"
#include "../Ring.h"
#include "../Effekseer.h"
#include "../Font.h"
#include "../Pad.h"
#include "../game.h"
#include <DxLib.h>

SceneMain::SceneMain(SceneManager& manager):
    SceneBase(manager)
{
    m_pPlayer = std::make_shared<Player>();
    m_pEManager = std::make_shared<EnemyManager>(*m_pPlayer);
    m_pLog = std::make_shared<Log>(*m_pPlayer);
    m_pRing = std::make_shared<Ring>(*m_pPlayer);

    m_pEffekseer = new EffekseerManager();

    Font::getInstance().load();

    //ゲーム画面用バッファ作成
    m_gameScreen = MakeScreen(Game::kScreenWidth,Game::kScreenHeight,true);

    m_pPlayer->setEffekseer(m_pEffekseer);
}

SceneMain::~SceneMain()
{
    //ゲーム画面用バッファの削除
    DeleteGraph(m_gameScreen);
}

void SceneMain::init()
{
    m_pPlayer->init();
    m_pEManager->init();
    m_pLog->init();
    m_pRing->init();
}

void SceneMain::update()
{
   
#ifdef _DEBUG
   /* if (Pad::isTrigger(PAD_INPUT_1))
    {
        m_manager.changeScene(new SceneDebug(m_manager));
        return;
    }*/
    
  
#endif
    m_pPlayer->update();
    m_pEManager->update();
    m_pLog->update();
    m_pRing->update();

    //プレイヤーと敵の当たり判定
    for (auto& enemy : m_pEManager->getData())
    {
        //存在しない場合
        if (!enemy->isExist()) continue;

        if (enemy->isCol(*m_pPlayer))
        {
            enemy->onDamege();
        }
    }

    //プレイヤーと丸太の当たり判定
    if (m_pLog->isCol(*m_pPlayer))
    {
        m_pLog->onDamege();
    }
}

void SceneMain::draw()
{
#if false
    //ゲーム画面の生成
   SetDrawScreen(m_gameScreen);
   ClearDrawScreen();

   m_pPlayer->draw();
   m_pEManager->draw();

    //ゲーム画面の描画
   SetDrawScreen(DX_SCREEN_BACK);

#else

    // デバッグ描画
    // XYZ軸
    float lineSize = 1000.0f;
    for (int i = -10; i < 11; i++)
    {
        DrawLine3D(VGet(-lineSize, 0, i * 100), VGet(lineSize, 0, i * 100), 0xff0000);
        DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), 0x00ff00);
        DrawLine3D(VGet(i * 100, 0, -lineSize), VGet(i * 100, 0, lineSize), 0x0000ff);
    }


    m_pPlayer->draw();
    m_pEManager->draw();
    m_pLog->draw();
    m_pRing->draw();

#endif

//    printfDx("%d",m_pEManager->getSize());

//    Font::getInstance().draw("SceneMain");
}
