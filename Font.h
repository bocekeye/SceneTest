#pragma once

#include <string>
#include <vector>
#include <map>
#include "DxLib.h"

//シングルトンを使用したフォントクラス
class Font
{
public:

	/// <summary>
	/// フォントの読み込み
	/// </summary>
	void load();

	void unload();

	/// <summary>
	/// フォントの描画
	/// </summary>
	/// <param name="filename">どこで描画させるのか</param>
	void draw(std::string filename);

	/// <summary>
	/// Font使用者はgetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static Font& getInstance()
	{
		static Font instance;		//ここが唯一の実体
		return instance;			//参照を返す
	}

private:

	Font();
	virtual ~Font() {}

	//コピーも代入も禁止する
	Font(const Font&) = delete;
	void operator = (const Font&) = delete;


private:

	struct Data
	{
		//固定データ??
		std::string filename;		//ファイル名（パス、拡張子は含まない）
		std::string fontname;		//フォント名
		std::string inputCharacter;	//文字入力
		int fontSize;				//フォントの大きさ
		int fontThick;

		//フォントデータ
		int handle;
	};


private:
	//ファイル情報
	//std::vector<Data> m_data;

	std::map<std::string,Data>	m_data;

#if false
	void readFile(LPCSTR fontPath,int handle, LPCSTR fontname, int size);

#else
	void readFile(LPCSTR fontPath);
#endif

	/// <summary>
	/// フォント開放
	/// </summary>
	/// <param name="fontPath"></param>
	void openFile(LPCSTR fontPath);

};

