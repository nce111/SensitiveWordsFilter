#include <map>
#include <string>
#include "Node.h"
using namespace std;

/*
说明：
1.__emptyRoot即上面建立的TrieNode树的根节点
2.TrieNode* Trie::find(std::string& keyword)函数即查找是否依次以keyword为单元构建起来的一条分支，比如以helloworld为单元构建起来的分支为h->e->l->l->o->w->o->r->l->d,则查找hello的时候就可以确定hello是敏感词
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