#pragma once
#include <string>
#include <vector>
#include <map>
#include "DxLib.h"

//シングルトンを使用したサウンドクラス
class Sound
{
public:

	/// <summary>
	/// サウンドのロード
	/// </summary>
	void load();		
	/// <summary>
	/// サウンドのアンロード
	/// </summary>
	void unload();

	/// <summary>
	/// 指定のサウンドを鳴らす　*ループ再生しない*
	/// </summary>
	void play(std::string filename);
	
	/// <summary>
	/// BGM再生　				*ループ再生*
	/// </summary>
	/// <param name="filename"></param>
	void playBgm(std::string filename);

	void setVolume(std::string filename,int vol);

	/// <summary>
	/// サウンドを全部一時停止にする
	/// </summary>
	//void stopBgmAndSe(std::string filename);

	/// <summary>
	/// Sound使用者はgetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static Sound& getInstance()
	{
		static Sound instance;		//ここが唯一の実体
		return instance;			//参照を返す
	}
	
private:
	Sound();
	virtual ~Sound(){}

	//コピーも代入も禁止する
	Sound(const Sound&) = delete;
	void operator = (const Sound&) = delete;

private:

	struct Data
	{
		std::string filename;	//ファイル名（パス、拡張子は含まない）
		bool isBgm;				//BGMかどうか
		float volume;			//音量

		int handle;				//サウンドデータ
	};

private:
	std::map<std::string, Data> m_data;

};

