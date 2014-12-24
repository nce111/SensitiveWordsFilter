#include "Trie.h"
using namespace std;
/*
说明：
1.TrieNode* Trie::insert(TrieNode* parent, std::string& keyword)即在建立TrieNode树时，以parent为根节点建立，一开始parent为__emptyRoot,然后把keyword按照规则添加到树中，假设一开始__emptyRoot为空，keyword为hello，则会以hello为一条分支建立成为一颗树枝h->e->l->l->o,此后，若想再添加hero，由于hero与hello的前两个字符相同，则会在h->e->l->l->o的基础上，从字母e开始新生长出一颗分支，即h->e->r->o,这两颗分支共用h->e
2.__pace即与编码方式有关，utf16编码，则__pace为2，utf8是变长编码，不再详述.
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