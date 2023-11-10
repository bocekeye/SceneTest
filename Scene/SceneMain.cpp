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
#include "../ultrasound.h"
#include "../Effekseer.h"
#include "../Font.h"
#include "../Pad.h"
#include "../game.h"
#include <DxLib.h>

SceneMain::SceneMain(SceneManager& manager):
    SceneBase(manager),
    m_underwaterH(-1)
{
    m_pPlayer = std::make_shared<Player>();
    m_pEManager = std::make_shared<EnemyManager>(*m_pPlayer);
    m_pLog = std::make_shared<Log>(*m_pPlayer);
    m_pRing = std::make_shared<Ring>(*m_pPlayer);
    

    for (int i = 0; i < 5; i++)
    {
        m_pUltrasound.push_back(std::make_shared<ultrasound>(*m_pPlayer));
        m_pUltrasound.back()->init();
    }

    m_pEffekseer = new EffekseerManager();

    Font::getInstance().load();

    //ゲーム画面用バッファ作成
    m_gameScreen = MakeScreen(Game::kScreenWidth,Game::kScreenHeight,true);
  
    m_pPlayer->setSceneMain(this);
    m_pPlayer->setEffekseer(m_pEffekseer);
    m_underwaterH = LoadGraph("data/skyBlue.png");
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
   // m_pLog->init();
   // m_pRing->init();

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

    for (auto& usound : m_pUltrasound)
    {
        if (usound->isExist())
        {
            update();
        }
    }
 
   // m_pLog->update();
   // m_pRing->update();

    //プレイヤーと敵の当たり判定
    for (auto& enemy : m_pEManager->getEnemyData())
    {
        //存在しない場合
        if (!enemy->isExist()) continue;

        if (enemy->isCol(*m_pPlayer))
        {
            enemy->onDamege();
        }
    }

    //プレイヤーと丸太の当たり判定
    for (auto& log : m_pEManager->getLogData())
    {
        //存在しない場合
        if (!log->isExist()) continue;

        if (log->isCol(*m_pPlayer))
        {
            log->onDamege();
            m_pPlayer->onDamage(1);
        }
    }

    //プレイヤーとわっかの当たり判定
    for (auto& ring : m_pEManager->getRingData())
    {
        //存在しない場合
        if (!ring->isExist()) continue;

        if (ring->isCol(*m_pPlayer))
        {

        }
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

    //海面
    if (!m_pPlayer->isSurface())
    {
        float seaSize = 50000.0f;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
        DrawTriangle3D(VGet(-seaSize / 10, 0, -seaSize), VGet(seaSize / 10, 0, -seaSize),
        VGet(seaSize / 10, 0, seaSize), 0x00fffff, true);

        DrawTriangle3D(VGet(seaSize / 10, 0, seaSize), VGet(-seaSize / 10, 0, seaSize),
         VGet(-seaSize / 10, 0, -seaSize), 0x00fffff, true);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
        //SetUseLighting(FALSE);

        int box = DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x00ffff, true);      
      //int test =  DrawBillboard3D(m_pPlayer->getPos(), 0.5f, 0.5f, 100.0f, 0.0f, m_underwaterH, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
  

    DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), 0x00ff00);

    m_pPlayer->draw();
    m_pEManager->draw();
    for (auto& usound : m_pUltrasound)
    {
        usound->draw();
    }
    
   // m_pLog->draw();
   // m_pRing->draw();

#endif

//    printfDx("%d",m_pEManager->getSize());

//    Font::getInstance().draw("SceneMain");
}

void SceneMain::ultrasoundStart(VECTOR start, VECTOR vec)
{
    for (auto& usound : m_pUltrasound)
    {
        if (usound->isExist()) continue;
        usound->start(start, vec);
        break;
    }
}
