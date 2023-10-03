#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "../Pad.h"
#include <cassert>

void SceneManager::changeScene(SceneBase* scene)
{
	//シーンスタックが空ではなかったら
	if (!m_scene.empty())
	{
		delete m_scene.front();			//topはてっぺんの要素を返してる
		m_scene.pop_front();			//1個減る -> ふつうは0になる
	}
	m_scene.push_front(scene);			//1個増える
}

void SceneManager::pushScene(SceneBase* scene)
{
	m_scene.push_front(scene);			//1個増える
}

void SceneManager::popScene()
{
	//ポップの結果、シーンが0にならないようにする
	if (m_scene.size() > 1)
	{
		delete m_scene.front();
		m_scene.pop_front();
	}
}

void SceneManager::init()
{
	m_scene.front()->init();
}

void SceneManager::update()
{
	m_scene.front()->update();
}

void SceneManager::draw()
{
	for (int i = m_scene.size() - 1; i >= 0; i--)
	{
		m_scene[i]->draw();
	}
}