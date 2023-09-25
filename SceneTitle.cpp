#include "DxLib.h"
#include "game.h"

#include "SceneTitle.h"	


void SceneTitle::init()
{


}

SceneBase* SceneTitle::update()
{

	return this;
}

void SceneTitle::draw()
{

	DrawString(0, 0, "AAAA", GetColor(255, 255, 255));

}