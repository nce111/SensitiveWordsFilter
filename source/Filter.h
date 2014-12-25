#include <string>
#include "Trie.h"
using namespace std;



enum Level
{
NORMAL = 1,
HIGH = 2
};

class Filter 
{
private:
	static bool __initialized;
	static Trie __trie;
	static void load(const char* fileName, int startPos);
	static bool censor(string& source);
public:
	static bool __LEGAL;
	static bool __ILLEGAL;
	static void init(Level level, string loadFile = "");
	static bool isInitialized();
	static bool censor(const char* source, int length);
};

inline bool Filter::isInitialized() {
	return __initialized;
}