#include "SceneResult.h"
#include "SceneDebug.h"
#include "SceneManager.h"

#include "DxLib.h"
#include "../Font.h"
#include "../Pad.h"

SceneResult::SceneResult(SceneManager& manager):
	SceneBase(manager)
{
}

void SceneResult::init()
{
}

void SceneResult::update()
{
#ifdef _DEBUG
    if (Pad::isTrigger(PAD_INPUT_1))
    {
        m_manager.changeScene(new SceneDebug(m_manager));
        return;
    }
#else

#endif
}

void SceneResult::draw()
{

	//DrawString(300, 300,"Scene Result",0xffffff);

	Font::getInstance().draw("SceneResult");

}
