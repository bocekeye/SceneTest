#pragma once

#include <deque>

class SceneBase;

//シーン監視クラス
class SceneManager
{
public:

	/// <summary>
	/// シーンの切り替えを行う
	/// </summary>
	/// <param name="scene">切り替えたい次のシーンのアドレス</param>
	void changeScene(SceneBase* scene);

	/// <summary>
	/// シーンを上に積む
	/// Updateで実行されるのは上につまれたシーンのみ
	/// </summary>
	/// <param name="scene"></param>
	void pushScene(SceneBase* scene);

	/// <summary>
	/// 一番上のシーンを削除する
	/// ただし、その結果スタックが空になることのないように
	/// </summary>
	void popScene();

	/// <summary>
	/// 各シーンの初期化を行う
	/// </summary>
	void init();

	/// <summary>
	/// 各シーンの更新を行う
	/// </summary>
	/// <param name="input">入力ステート</param>
	void update();
	/// <summary>
	/// 各シーンの描画を行う
	/// </summary>
	void draw();

private:
	//今実行中のシーンを切り替えていきたいので	
	//参照ではなくポインタとして宣言
	std::deque<SceneBase*> m_scene;
};

