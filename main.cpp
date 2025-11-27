#include <iostream>
#include <string>
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

void insert(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            curr->children[index] = createNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool search(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            return false;
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

void removeWord(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            return; // word not found
        curr = curr->children[index];
    }
    curr->isEndOfWord = false; // unmark as a word
}

TrieNode* findPrefixNode(TrieNode* root, string prefix) {
    TrieNode* curr = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            return nullptr; // prefix not found
        curr = curr->children[index];
    }
    return curr;
}

void dfs(TrieNode* node, string current, vector<string>& results) {
    if (node->isEndOfWord)
        results.push_back(current);

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            char nextChar = 'a' + i;
            dfs(node->children[i], current + nextChar, results);
        }
    }
}
int main(){
    TrieNode* root = createNode();

    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");

    cout << boolalpha; // print true/false instead of 1/0
    cout << "Search 'apple': " << search(root, "apple") << endl; // true
    cout << "Search 'app': "   << search(root, "app")   << endl; // true
    cout << "Search 'bat': "   << search(root, "bat")   << endl; // true
    cout << "Search 'bad': "   << search(root, "bad")   << endl; // false

    removeWord(root, "app");
    cout << "After deleting 'app': " << search(root, "app") << endl; // false
    cout << "But 'apple' still exists: " << search(root, "apple") << endl; // true

return 0;
}
