#include "Node.h"

using namespace std;

Node::Node(string character, int dataSize) 
{
	if (character.size() == 2)
		__character.assign(character);
}

Node::Node(string character) 
{
	if (character.size() == 2)
		__character.assign(character);
}

Node* Node::findChild(string& nextCharacter) const 
{
	_TrieMapIterator ___trieMapIt = __map.find(nextCharacter);
	return (___trieMapIt == __map.end()) ? NULL : const_cast<Node*>(&(___trieMapIt->second));
}

Node* Node::insertChild(string& nextCharacter) 
{
	if (!findChild(nextCharacter)) 
	{
		__map.insert(pair<string, Node>(nextCharacter, Node(nextCharacter, __dataSize)));
		return &(__map.find(nextCharacter)->second);
	}
	return NULL;
}