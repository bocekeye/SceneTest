#include "SceneManager.h"
#include <cassert>
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "Pad.h"



SceneManager::SceneManager() :
	m_pScene()
{
}
SceneManager::~SceneManager()
{

}
void SceneManager::init()
{
#ifdef _DEBUG
	m_pScene.reset(new SceneDebug);
#else
	m_pScene.reset(new SceneTitle);
#endif
	m_pScene->init();
}
void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
}

bool SceneManager::update()
{
	assert(m_pScene);
	if (!m_pScene)	return false;
	
	Pad::update();
	SceneBase* pScene = m_pScene->update();
	if (!pScene)
	{
		m_pScene->end();
		return false;	// nullptrで終了
	}

	if (pScene != m_pScene.get())
	{
		// 前のシーンの終了処理
		m_pScene->end();

		m_pScene.reset(pScene);
		m_pScene->init();
	}
	return true;
}

void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->draw();
}