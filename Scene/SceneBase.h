#pragma once
class SceneManager;

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase(SceneManager& manager);

	virtual ~SceneBase() {}

	virtual void init() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	SceneManager& m_manager;		//シーンマネージャーへの参照
		
};
