#include "Font.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "DxLib.h"

namespace
{
	//�t�H���g�̃t�@�C���p�X
	const char* const kDataFilePath = "data/font/";

	//�t�H���g�̊g���q
	const char* const kDataExtension = ".ttf";

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

	//---------------�ق��̂����Ȃ����l����----------------------
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
		//csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string> strvec = split(line, ',');

		//strvec[0]   : �t�@�C����			string
		//strvec[1]	  : �t�H���g��			string
		//strvec[2]	  : ���͕���			string
		//strvec[3]   : �t�H���g�T�C�Y		int 
		Data data;
		data.handle = -1;
		data.fontname = strvec[1];
		data.inputCharacter = strvec[2];
		data.fontSize = stoi(strvec[3]);
	//	data.fontThick = stoi(strvec[4]);
		
		m_data[strvec[0]] = data;

		//�t�H���g�̓ǂݍ���
		for (auto& data : m_data)
		{
			//data.first = ������
			//data.second = Data
			
			std::string fontname = data.second.fontname;						//�t�H���g��
			int size = data.second.fontSize;									//�t�H���g�̑傫��
			std::string filename = kDataFilePath + fontname + kDataExtension;	//�t�@�C����
			LPCSTR font_path = filename.c_str();								//LPCSTR = const char*		
#if false
			readFile(font_path, data.second.handle,fontname.c_str(), size);		//�t�H���g�̃t�@�C���ǂݍ���
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
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
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
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
}

#endif
void Font::openFile(LPCSTR fontPath)
{
	//���\�[�X�J��
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL))
	{
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
}


