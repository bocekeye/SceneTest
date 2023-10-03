#pragma once
#include "SceneBase.h"
#include <vector>
#include <memory>

class SceneDebug : public SceneBase
{
public:
	SceneDebug(SceneManager& manager);
	virtual ~SceneDebug() {}

	void init() ;

	void update();
	void draw();

private:

	/// <summary>
	/// 値を変更できないように enum class を使用する(??)
	/// シーン遷移番号
	/// </summary>
	enum class SceneNo
	{
		SceneTitle,		// 0
		SceneMain,		// 1
		SceneResult,	// 2
	};


	int m_currentSceneSelect;	//現在のシーン選択
	char m_display;				

};
