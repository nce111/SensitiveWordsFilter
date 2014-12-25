#include <iostream>
#include <fstream>
#include "Filter.h"
using namespace std;
/*
˵����
1.�ؼ�����Ϊ��bool Filter::censor(std::string& source),�ú����������������дʹ��˵ĺ�����source��������ַ��������source�����дʣ����߰������дʣ���᷵��false,���򷵻�true.
2.Filter::load()������Ϊ�������д��ļ�
����ǰ���������֪�����"��ҩ�䷽"�����дʣ���"��"Ҳ�����дʣ�"��ҩ"Ҳ�����дʣ�"��ҩ��"Ҳ�����д�,����"���"�������дʣ�"��ҩ��"Ҳ�������дʣ�����"��ҩ�䷽��"�����дʣ���Ϊ����Trie::find()�����е�if (___firstNode->__map.empty()) {
return ___firstNode; 
}
��֪��ƥ�䵽"��ҩ�䷽"ʱ��___firstNode->__map.empty()Ϊ�棬��᷵��___firstNode�����ԡ���ҩ�䷽��Ϊһ�����������дʵ�Ԫ
*/
bool Filter::__LEGAL = true;
bool Filter::__ILLEGAL = false;
bool Filter::__initialized = false;
Trie Filter::__trie(UTF16);


void Filter::init(Level level,std::string loadFile) 
{
	if (level == NORMAL) 
	{
		load("normal_keywords_utf16", 82); 
	} 
	else if (level == HIGH) 
	{
		load("high_keywords_utf16", 2);//high_keywords_utf16
	} else
	{
		return;
	}
	__initialized = true;
}

void Filter::load(const char* filePath, int startPos) 
{
	ifstream keywordsFile(filePath, ios::in | ios::binary | ios::ate);
	if (keywordsFile.is_open()) 
	{
		ifstream::pos_type ___totalSize = keywordsFile.tellg();
		keywordsFile.seekg(0, std::ios::beg);
		char *header = new char[startPos];// header
		keywordsFile.read(header, startPos); // header
		char buffer[256];
		int ___count = 0;
		int ___offset = 0;
		while (___count < ___totalSize) 
		{
			keywordsFile.read(buffer + ___offset, 2);
			___count += 2;
			___offset += 2;
			if (buffer[___offset - 4] == '\x0D' && buffer[___offset - 3] == '\x00'
			&& buffer[___offset - 2] == '\x0A' && buffer[___offset - 1] == '\x00') 
			{
				___offset -= 4;
				string ___utf16Word;
				___utf16Word.assign(buffer, ___offset);
				__trie.insert(___utf16Word);
				___offset = 0;
			}
		}
		delete []header;
	}
	keywordsFile.close();
}

bool Filter::censor(const char* source, int length) 
{
	string ___source;
	___source.assign(source, length);
	return censor(___source);
}

bool Filter::censor(string& source) 
{
	if (!__initialized) 
	{
		return __ILLEGAL;
	} 
	else 
	{
		int length = source.size();
		for (int i = 0; i < length; i += 2) 
		{
			std::string substring = source.substr(i, length - i);
			if (__trie.find(substring) != NULL) 
			{
				return __ILLEGAL;
			}
		}
		return __LEGAL;
	}
}