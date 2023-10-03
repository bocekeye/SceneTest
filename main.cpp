#include <DxLib.h>
#include "Scene/SceneManager.h"
#include "Scene/SceneTitle.h"
#include "Scene/SceneDebug.h"
#include "game.h"
#include "Font.h"
#include "Sound.h"
#include "Pad.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�w�i�F
	SetBackgroundColor(128, 128, 128,1);

	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	//�E�B���h�E���[�h���ݒ�
	SetMainWindowText(Game::kTitleText);
	//��ʂ̃T�C�Y
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			    // �G���[���N�����璼���ɏI��
	}
	
	//�_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

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

		//��ʂ̃N���A
		ClearDrawScreen();

		sceneManager.update();
		sceneManager.draw();

		Pad::update();

		//Frame Per Second
		auto fps = GetFPS();

		//�`�施�ߐ�
		auto drawcall = GetDrawCallCount();

		DrawFormatString(10, 30, 0xffffff, "FPS = %2.2f", fps);
		DrawFormatString(10, 60, 0xffffff, "DC = %d", drawcall);

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//esc�L�[����������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}

	}



	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				    // �\�t�g�̏I�� 
}
