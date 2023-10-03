#pragma once

#include <string>
#include <vector>
#include <map>
#include "DxLib.h"

//�V���O���g�����g�p�����t�H���g�N���X
class Font
{
public:

	/// <summary>
	/// �t�H���g�̓ǂݍ���
	/// </summary>
	void load();

	void unload();

	/// <summary>
	/// �t�H���g�̕`��
	/// </summary>
	/// <param name="filename">�ǂ��ŕ`�悳����̂�</param>
	void draw(std::string filename);

	/// <summary>
	/// Font�g�p�҂�getInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static Font& getInstance()
	{
		static Font instance;		//�������B��̎���
		return instance;			//�Q�Ƃ�Ԃ�
	}

private:

	Font();
	virtual ~Font() {}

	//�R�s�[��������֎~����
	Font(const Font&) = delete;
	void operator = (const Font&) = delete;


private:

	struct Data
	{
		//�Œ�f�[�^??
		std::string filename;		//�t�@�C�����i�p�X�A�g���q�͊܂܂Ȃ��j
		std::string fontname;		//�t�H���g��
		std::string inputCharacter;	//��������
		int fontSize;				//�t�H���g�̑傫��
		int fontThick;

		//�t�H���g�f�[�^
		int handle;
	};


private:
	//�t�@�C�����
	//std::vector<Data> m_data;

	std::map<std::string,Data>	m_data;

#if false
	void readFile(LPCSTR fontPath,int handle, LPCSTR fontname, int size);

#else
	void readFile(LPCSTR fontPath);
#endif

	/// <summary>
	/// �t�H���g�J��
	/// </summary>
	/// <param name="fontPath"></param>
	void openFile(LPCSTR fontPath);

};

