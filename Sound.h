#pragma once
#include <string>
#include <vector>
#include <map>
#include "DxLib.h"

//�V���O���g�����g�p�����T�E���h�N���X
class Sound
{
public:

	/// <summary>
	/// �T�E���h�̃��[�h
	/// </summary>
	void load();		
	/// <summary>
	/// �T�E���h�̃A�����[�h
	/// </summary>
	void unload();

	/// <summary>
	/// �w��̃T�E���h��炷�@*���[�v�Đ����Ȃ�*
	/// </summary>
	void play(std::string filename);
	
	/// <summary>
	/// BGM�Đ��@				*���[�v�Đ�*
	/// </summary>
	/// <param name="filename"></param>
	void playBgm(std::string filename);

	void setVolume(std::string filename,int vol);

	/// <summary>
	/// �T�E���h��S���ꎞ��~�ɂ���
	/// </summary>
	//void stopBgmAndSe(std::string filename);

	/// <summary>
	/// Sound�g�p�҂�getInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static Sound& getInstance()
	{
		static Sound instance;		//�������B��̎���
		return instance;			//�Q�Ƃ�Ԃ�
	}
	
private:
	Sound();
	virtual ~Sound(){}

	//�R�s�[��������֎~����
	Sound(const Sound&) = delete;
	void operator = (const Sound&) = delete;

private:

	struct Data
	{
		std::string filename;	//�t�@�C�����i�p�X�A�g���q�͊܂܂Ȃ��j
		bool isBgm;				//BGM���ǂ���
		float volume;			//����

		int handle;				//�T�E���h�f�[�^
	};

private:
	std::map<std::string, Data> m_data;

};

