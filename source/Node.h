#include "map"
using namespace std;
class Trie;

typedef map<string, Node> _TrieMap;
typedef map<string, Node>::const_iterator _TrieMapIterator;

/*
1.ÿ��TrieNode��һ��map��Ա����ӳ���ϵΪһ��string��Ӧһ��TrieNode
2.Encoding������뷽ʽ����UTF16=2��ʾutf16��2���ֽڴ洢һ����
*/

enum Encoding 
{
	UTF8 = 1,
	UTF16 = 2
};

class Node
{
	friend class Trie;
private:
	string __character;
	_TrieMap __map;
	Node* __parent;
	int __dataSize;
public:
	Node(int dataSize);
	Node(string character);
	Node(string character, int dataSize);
	~Node();
	string getCharacter() const;
	Node* findChild(string& nextCharacter) const;
	Node* insertChild(string& nextCharacter);
};

inline Node::Node(int dataSize)
{
	__dataSize = dataSize;
}

inline Node::~Node() 
{

}

inline string Node::getCharacter() const
{
	return __character;
}