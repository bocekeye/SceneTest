#include "Sound.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "DxLib.h"

namespace
{
	//サウンドのファイルパス
	const char* const kDataFilePath = "data/sound";

	//サウンドの拡張子
	const char* const kDataExtension = ".mp3";

	//inputした文字列をdelimterで分割して
	//分割後の文字列を返す
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);			//stringをgetlineで使えるデータに変換する
		std::string field;							//分割した文字列1つ分を格納する
		std::vector<std::string> result;			//分割後の文字列の配列

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
	//ファイル情報の読み込み
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

		//csvデータ1行を','で複数の文字列に分割
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : ファイル名			string
		//strvec[1]	  : BGMかどうか			int
		//strvec[2]	  : 音量				float

		Data data;
	
		if (stoi(strvec[1]) == 0)
		{
			data.isBgm = false;				//BGMではない
		}
		else
		{
			data.isBgm = true;				//BGM
		}

		data.volume = stof(strvec[2]);		//音量
		data.handle = -1;					//再生ハンドル

		m_data[strvec[0]] = data;
		//サウンドの読み込み
		for (auto& data : m_data)
		{

			//printfDx("%s", data.first.c_str());
			std::string filename = kDataFilePath + data.first + kDataExtension;
			data.second.handle = LoadSoundMem(filename.c_str());						//音ファイルをメモリに読み込む
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


