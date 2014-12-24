#include "Trie.h"
using namespace std;
/*
˵����
1.TrieNode* Trie::insert(TrieNode* parent, std::string& keyword)���ڽ���TrieNode��ʱ����parentΪ���ڵ㽨����һ��ʼparentΪ__emptyRoot,Ȼ���keyword���չ�����ӵ����У�����һ��ʼ__emptyRootΪ�գ�keywordΪhello�������helloΪһ����֧������Ϊһ����֦h->e->l->l->o,�˺����������hero������hero��hello��ǰ�����ַ���ͬ�������h->e->l->l->o�Ļ����ϣ�����ĸe��ʼ��������һ�ŷ�֧����h->e->r->o,�����ŷ�֧����h->e
2.__pace������뷽ʽ�йأ�utf16���룬��__paceΪ2��utf8�Ǳ䳤���룬��������.
*/

Trie::Trie(Encoding encoding) : __emptyRoot(Node(encoding)), __size(0) 
{
	switch (encoding) 
	{
		case UTF8:
			__pace = 1;
			break;
		case UTF16:
			__pace = 2;
			break;
		default:
			break;
	}
}

Node* Trie::insert(string& keyword) {
	return insert(&__emptyRoot, keyword);
}

Node* Trie::insert(const char* keyword)
{
	std::string ___keyword(keyword);
	return insert(___keyword);
}

Node* Trie::insert(Node* parent, string& keyword) {
	if (keyword.size() == 0) 
	{
		return NULL;
	}
	string ___firstCharacter = keyword.substr(0, __pace);
	Node* ___firstNode = parent->findChild(___firstCharacter);
	if (___firstNode == NULL) 
	{
		return insertBranch(parent, keyword);
	}
	string ___restString = keyword.substr(__pace, keyword.size());
	return insert(___firstNode, ___restString);
}

Node* Trie::insertBranch(Node* parent, string& keyword) 
{
	string ___firstCharacter = keyword.substr(0, __pace);
	Node* ___firstNode = parent->insertChild(___firstCharacter);
	if (___firstNode != NULL) 
	{
		string ___restString = keyword.substr(__pace, keyword.size());
		if (!___restString.empty())
			return insertBranch(___firstNode, ___restString);
	}
	return NULL;
}

Node* Trie::find(std::string& keyword) 
{
	return find(&__emptyRoot, keyword);
}

Node* Trie::find(Node* parent, string& keyword) 
{
	std::string ___firstChild = keyword.substr(0, __pace);
	Node* ___firstNode = parent->findChild(___firstChild);
	if (___firstNode == NULL)
	{
		return NULL;
	}
	if (keyword.size() == (unsigned int)__pace) 
	{
		return ___firstNode;
	}
	std::string ___restString = keyword.substr(__pace, keyword.size());
	if (___firstNode->__map.empty())
	{
		return ___firstNode; 
	}
	return find(___firstNode, ___restString);
}

string Trie::toString() 
{
	string ___result("[");
	bool ___isFirstChild = true;
	for (_TrieMapIterator ___it = __emptyRoot.__map.begin();
		___it != __emptyRoot.__map.end(); ++___it) 
	{
		if (___isFirstChild) 
		{
			___result.append(toString(const_cast<Node*>(&(___it->second))));
			___isFirstChild = false;
		} 
		else 
		{
			___result.append(",");
			___result.append(toString(const_cast<Node*>(&(___it->second))));
		}
	}
	___result.append("]");
	return ___result;
}

string Trie::toString(Node* parent) 
{
	std::string ___result("[");
	___result += parent->getCharacter() + ":";
	bool ___isFirstChild = true;
	for (_TrieMapIterator ___it = parent->__map.begin();
		___it != parent->__map.end(); ++___it) 
	{
		if (___isFirstChild) 
		{
			___result.append(toString(const_cast<Node*>(&(___it->second))));
			___isFirstChild = false;
		} 
		else 
		{
			___result.append(",");
			___result.append(toString(const_cast<Node*>(&(___it->second))));
		}
	}
	___result.append("]");
	return ___result;
}

string Trie::getKeywords() 
{
	string ___result;
	for (_TrieMapIterator ___it = __emptyRoot.__map.begin();
		 ___it != __emptyRoot.__map.end(); ++___it) 
	{
		___result.append(getKeywords(___it->first, &(___it->second)));
	}
	return ___result;
}

string Trie::getKeywords(const std::string& character, const Node* parent) 
{
	string ___result;
	for (_TrieMapIterator ___it = parent->__map.begin();
			___it != parent->__map.end(); ++___it) 
	{
		___result.append(character);
		___result.append(getKeywords(___it->first, &(___it->second)));
	}
// Last character
	if (parent->__map.size() == 0) 
	{
		__size++;
		___result.append(character);
		___result.append("\n");
	}
	return ___result;
}