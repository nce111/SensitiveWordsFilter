#include "map"
#include <string>
using namespace std;
class Trie;
class Node;


/*
1.每个TrieNode有一个map成员，其映射关系为一个string对应一个TrieNode
2.Encoding代表编码方式，如UTF16=2表示utf16用2个字节存储一个字
*/

enum Encoding 
{
	UTF8 = 1,
	UTF16 = 2
};

typedef map<string, Node> _TrieMap;
typedef map<string, Node>::iterator _TrieMapIterator;

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