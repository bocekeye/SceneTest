#include <DxLib.h>
#include "SceneManager.h"
#include "game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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

	SceneManager* pScene = new SceneManager;
	pScene->init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		//��ʂ̃N���A
		ClearDrawScreen();

		if (!pScene->update())	break;

		pScene->draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		//esc�L�[����������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		while (GetNowHiPerformanceCount() - time < 1667)
		{

		}

	}

	pScene->end();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				    // �\�t�g�̏I�� 
}
