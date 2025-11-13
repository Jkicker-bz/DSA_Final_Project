#include <iostream>
using namespace std;

// Each Trie Node can store up to 26 letters (a-x)
Struct TrieNode {
     TrieNode* children[26];
     bool isEndOfWord;
};

TrieNode* getNode(){
     TrieNode* node = new TrieNode;
     node->isEndOfWord = false;
     for (int i = 0; i < 26; i++)
	node->children[i] = nullptr;
     return node;
}

int main(){

return 0;
}
