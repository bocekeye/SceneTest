#include "Font.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DxLib.h"

namespace
{

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
	while (getline(ifs, line))
	{
		//printfDx("%s\n",line.c_str());
		//csvデータ1行を','で複数の文字列に分割
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : ファイル名	string
		//strvec[1]   : BGMフラグ	int (boolに変換する)
		//strvec[2]   : 音量		float
	
		Data data;
		data.filename = strvec[0];
		if (stoi(strvec[1]) == 0)
		{
			data.isBgm = false;
		}
		else
		{
			data.isBgm = true;
		}
		data.volume = stof(strvec[2]);

		m_data.push_back(data);


		/*for (auto& str : strvec)
		{
			printfDx("%s - ",str.c_str());
		}
		printfDx("\n");*/
	}
}
