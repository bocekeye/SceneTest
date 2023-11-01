#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>

class Player;
class EffekseerManager
{
public:
	EffekseerManager();
	virtual ~EffekseerManager();

	void init();
	void update();
	void draw();

	void testUpdate(VECTOR pos);

private:
	
	//���[�h����n���h��
	int m_effectResourceHandle;

	//���s���̃n���h��
	int m_currentPlayingEffect;

	VECTOR m_stragePos;
};

