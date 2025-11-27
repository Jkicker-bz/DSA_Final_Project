#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Each Trie Node can store up to 26 letters (a-x)
struct TrieNode {
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
            curr->children[index] = getNode();
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

vector<string> autocomplete(TrieNode* root, string prefix) {
    vector<string> results;

    TrieNode* prefixNode = findPrefixNode(root, prefix);
    if (prefixNode == nullptr)
        return results; // empty list

    dfs(prefixNode, prefix, results);
    return results;
}

int main(){
    TrieNode* root = getNode();
    // Insert sample dictionary
    insert(root, "apple");
    insert(root, "app");
    insert(root, "apply");
    insert(root, "apt");
    insert(root, "bat");
    insert(root, "batch");
    insert(root, "banana");

    string prefix = "ap";
    vector<string> suggestions = autocomplete(root, prefix);

    cout << "Autocomplete suggestions for \"" << prefix << "\":" << endl;
    for (string s : suggestions)
        cout << " - " << s << endl;
return 0;
}
