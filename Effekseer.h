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
	
	//ロードするハンドル
	int m_effectResourceHandle;

	//実行中のハンドル
	int m_currentPlayingEffect;

	VECTOR m_stragePos;
};

