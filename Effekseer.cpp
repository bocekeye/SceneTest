#include "Effekseer.h"
#include <EffekseerForDXLib.h>

#include <cassert>

EffekseerManager::EffekseerManager():
	m_currentPlayingEffect(0),
	m_stragePos(VGet(0.0f, 0.0f, 0.0f))
{
	//�G�t�F�N�V�A�n���h���̃��[�h
	m_effectResourceHandle = LoadEffekseerEffect("data/water.efk", 30.0f);
}

/// <summary>
/// �G�t�F�N�g���\�[�X�̍폜
/// </summary>
EffekseerManager::~EffekseerManager() 
{
	DeleteEffekseerEffect(m_effectResourceHandle);
}

void EffekseerManager::init()
{
}

void EffekseerManager::update()
{
	Effekseer_Sync3DSetting();

	//�Đ�����3D�G�t�F�N�V�A���X�V����
	UpdateEffekseer3D();
}

void EffekseerManager::draw()
{
	//�Đ�����3D�G�t�F�N�V�A��`�悷��
	DrawEffekseer3D();

//	DrawFormatString(110, 130,0xffffff,"%f", m_stragePos.x);
//	DrawFormatString(110, 150, 0xffffff, "%f", m_stragePos.y);
//	DrawFormatString(110, 170, 0xffffff, "%f", m_stragePos.z);
}

void EffekseerManager::testUpdate(VECTOR pos)
{
	m_stragePos = pos;

	//�G�t�F�N�g�̔���
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect))
	{
		StopEffekseer3DEffect(m_currentPlayingEffect);
	}
	m_currentPlayingEffect = PlayEffekseer3DEffect(m_effectResourceHandle);

	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, pos.x, pos.y, pos.z);
	assert(m_effectResourceHandle != -1);

}
