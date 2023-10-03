#include "Sound.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "DxLib.h"

namespace
{
	//�T�E���h�̃t�@�C���p�X
	const char* const kDataFilePath = "data/sound";

	//�T�E���h�̊g���q
	const char* const kDataExtension = ".mp3";

	//input�����������delimter�ŕ�������
	//������̕������Ԃ�
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);			//string��getline�Ŏg����f�[�^�ɕϊ�����
		std::string field;							//��������������1�����i�[����
		std::vector<std::string> result;			//������̕�����̔z��

		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}
}

Sound::Sound()
{

}

void Sound::load()
{
	//�t�@�C�����̓ǂݍ���
	std::ifstream ifs("data/sound.csv");				
	std::string line;						

	bool test = false;

	while (getline(ifs, line))
	{
		if (!test)
		{
			test = true;
			continue;
		}

		//csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : �t�@�C����			string
		//strvec[1]	  : BGM���ǂ���			int
		//strvec[2]	  : ����				float

		Data data;
	
		if (stoi(strvec[1]) == 0)
		{
			data.isBgm = false;				//BGM�ł͂Ȃ�
		}
		else
		{
			data.isBgm = true;				//BGM
		}

		data.volume = stof(strvec[2]);		//����
		data.handle = -1;					//�Đ��n���h��

		m_data[strvec[0]] = data;
		//�T�E���h�̓ǂݍ���
		for (auto& data : m_data)
		{

			//printfDx("%s", data.first.c_str());
			std::string filename = kDataFilePath + data.first + kDataExtension;
			data.second.handle = LoadSoundMem(filename.c_str());						//���t�@�C�����������ɓǂݍ���
		}
	}
}

void Sound::unload()
{
	for (auto& data : m_data)
	{
		DeleteSoundMem(data.second.handle);
	}
}
void Sound::play(std::string filename)
{
	assert(m_data.find(filename) != m_data.end());
	PlaySoundMem(m_data[filename].handle,DX_PLAYTYPE_BACK);
}

void Sound::playBgm(std::string filename)
{
	PlaySoundMem(m_data[filename].handle, DX_PLAYTYPE_LOOP);
}

void Sound::setVolume(std::string filename, int vol)
{




}

void Sound::stopBgmAndSe(std::string filename)
{
	StopSoundMem(m_data[filename].handle);
}


