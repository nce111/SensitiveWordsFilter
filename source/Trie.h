#include <map>
#include <string>
#include "Node.h"
using namespace std;

/*
˵����
1.__emptyRoot�����潨����TrieNode���ĸ��ڵ�
2.TrieNode* Trie::find(std::string& keyword)�����������Ƿ�������keywordΪ��Ԫ����������һ����֧��������helloworldΪ��Ԫ���������ķ�֧Ϊh->e->l->l->o->w->o->r->l->d,�����hello��ʱ��Ϳ���ȷ��hello�����д�
*/

class Trie 
{
private:
	Node __emptyRoot;
	int __pace;
	Node* insert(Node* parent, string& keyword);
	Node* insertBranch(Node* parent, string& keyword);
	Node* find(Node* parent, string& keyword);
	string toString(Node* parent);
	string getKeywords(const string& character, Node* parent);
public:
	int __size;
	Trie(Encoding encoding);
	~Trie();
	Node* insert(std::string& keyword);
	Node* insert(const char* keyword);
	Node* find(std::string& keyword);
	string toString();
	std::string getKeywords();
};

inline Trie::~Trie() 
{

}