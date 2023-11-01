#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Scene/SceneManager.h"
#include "Scene/SceneTitle.h"
#include "Scene/SceneDebug.h"
#include "game.h"
#include "Font.h"
#include "Sound.h"
#include "Pad.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//背景色
	SetBackgroundColor(128, 128, 128,1);

	//ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	//ウィンドウモード名設定
	SetMainWindowText(Game::kTitleText);
	//画面のサイズ
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			    // エラーが起きたら直ちに終了
	}
	//Effekseerの初期化
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		return -1;
	}
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	
	//DxLibの3D設定をEffekseerにも反映
	Effekseer_Sync3DSetting();

	//描画モードを設定する
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//Zバッファの書き込み
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	//ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseLighting(TRUE);

	SceneManager sceneManager;
#ifdef _DEBUG
	sceneManager.changeScene(new SceneDebug(sceneManager));
#else
	sceneManager.changeScene(new SceneTitle(sceneManager));
#endif

//	Font::getInstance().load();
//	Sound::getInstance().load();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//画面のクリア
		ClearDrawScreen();

		sceneManager.update();
		sceneManager.draw();

		Pad::update();

		//Frame Per Second
		auto fps = GetFPS();

		//描画命令数
		auto drawcall = GetDrawCallCount();

		DrawFormatString(10, 30, 0xffffff, "FPS = %2.2f", fps);
		DrawFormatString(10, 60, 0xffffff, "DC = %d", drawcall);

		//裏画面を表画面を入れ替える
		ScreenFlip();

		//escキーを押したら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}

	}


	Effkseer_End();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				    // ソフトの終了 
}
