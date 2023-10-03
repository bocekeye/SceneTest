#include "Font.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DxLib.h"

namespace
{

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




Font::Font()
{
}

void Font::load()
{
	//�t�@�C�����ǂݍ���
	std::ifstream ifs("data/font.csv");	

	std::string line;
	while (getline(ifs, line))
	{
		//printfDx("%s\n",line.c_str());
		//csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : �t�@�C����	string
		//strvec[1]   : BGM�t���O	int (bool�ɕϊ�����)
		//strvec[2]   : ����		float
	
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
