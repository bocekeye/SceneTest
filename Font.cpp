#include "Font.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "DxLib.h"

namespace
{
	//フォントのファイルパス
	const char* const kDataFilePath = "data/font/";

	//フォントの拡張子
	const char* const kDataExtension = ".ttf";

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


Font::Font()
{

}

void Font::load()
{
	//ファイル情報読み込み
	std::ifstream ifs("data/font.csv");

	std::string line;

	//---------------ほかのやり方ないか考える----------------------
	bool test = false;

	while (getline(ifs, line))
	{
		if (!test)
		{
			test = true;
			continue;
		}
//------------------------------------------------------------------

		//printfDx("%s\n",line.c_str());
		//csvデータ1行を','で複数の文字列に分割
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : ファイル名			string
		//strvec[1]	  : フォント名			string
		//strvec[2]	  : 入力文字			string
		//strvec[3]   : フォントサイズ		int 
		Data data;
		data.handle = -1;
		data.fontname = strvec[1];
		data.inputCharacter = strvec[2];
		data.fontSize = stoi(strvec[3]);
	//	data.fontThick = stoi(strvec[4]);
		
		m_data[strvec[0]] = data;

		//フォントの読み込み
		for (auto& data : m_data)
		{
			//data.first = 文字列
			//data.second = Data
			
			std::string fontname = data.second.fontname;						//フォント名
			int size = data.second.fontSize;									//フォントの大きさ
			std::string filename = kDataFilePath + fontname + kDataExtension;	//ファイル名
			LPCSTR font_path = filename.c_str();								//LPCSTR = const char*		
#if false
			readFile(font_path, data.second.handle,fontname.c_str(), size);		//フォントのファイル読み込み
#else
			readFile(font_path);
#endif
			data.second.handle = CreateFontToHandle(fontname.c_str(),size,-1,-1);
		//	printfDx("%s", fontname.c_str());
			assert(data.second.handle >= 0);
		}
	}
}

/// <summary>
//
/// </summary>
void Font::unload()
{
	for (auto& data : m_data)
	{
		std::string filename = kDataFilePath + data.first + kDataExtension;
		openFile(filename.c_str());
	}
}

void Font::draw(std::string filename)
{
	//assert(m_data.find(filename) != m_data.end());
      std::string inputname = m_data[filename].inputCharacter;
	//printfDx("%s", inputname.c_str());
	DrawStringToHandle(100, 100, m_data[filename].inputCharacter.c_str(), 0xffffff, m_data[filename].handle);
	//printfDx("%s", m_data[filename].handle);
}

#if false
void Font::readFile(LPCSTR  fontPath, int handle, LPCSTR fontname, int size)
{
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) 
	{
		handle = CreateFontToHandle(fontname, size, -1, -1);
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
}
#else
void Font::readFile(LPCSTR fontPath)
{
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
}

#endif
void Font::openFile(LPCSTR fontPath)
{
	//リソース開放
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL))
	{
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
}


