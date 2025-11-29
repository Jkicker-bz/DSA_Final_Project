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

void loadDefaultWords(TrieNode* root) {
    string words[] = {
        "apple","app","apply","apt","ape",
        "banana","band","bank","bat","batch",
        "cat","cart","car","care","case",
        "dog","doll","dove","door","dock",
        "eat","ear","earth","easy","east"
    };

    for (string w : words)
        insert(root, w);
}

int main() {
    TrieNode* root = getNode();
    string choice;

    // Load default words automatically
    loadDefaultWords(root);

    while (true) {
        cout << "\n=========== TRIE WORD SYSTEM ===========\n";
        cout << "1. View Word Bank\n";
        cout << "2. Insert Word\n";
        cout << "3. Search (with Autocomplete)\n";
        cout << "4. Delete Word\n";
        cout << "x. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == "1") {
            cout << "\n--- Word Bank ---\n";
            vector<string> allWords;
            dfs(root, "", allWords);

            if (allWords.empty()) {
                cout << "No words in dictionary.\n";
            } else {
                for (string w : allWords)
                    cout << "- " << w << endl;
            }

        } else if (choice == "2") {
            string word;
            cout << "Enter word to insert: ";
            cin >> word;
            insert(root, word);
            cout << "Inserted successfully!\n";

            // Ask to view after insertion
            char viewChoice;
            cout << "View word bank now? (y/n): ";
            cin >> viewChoice;

            if (viewChoice == 'y' || viewChoice == 'Y') {
                vector<string> allWords;
                dfs(root, "", allWords);
                cout << "\n--- Word Bank ---\n";
                for (string w : allWords)
                    cout << "- " << w << endl;
            }

        } else if (choice == "3") {
            string prefix;
            cout << "Enter word or prefix: ";
            cin >> prefix;

            vector<string> suggestions = autocomplete(root, prefix);

            if (suggestions.empty()) {
                cout << "No matches found.\n";
            } else {
                cout << "\nSuggestions:\n";
                for (string s : suggestions)
                    cout << "- " << s << endl;
            }

        } else if (choice == "4") {
            string word;
            cout << "Enter word to delete: ";
            cin >> word;
            removeWord(root, word);
            cout << "Word unmarked (simple delete performed).\n";

        } else if (choice == "x" || choice == "X") {
            cout << "Exiting... Goodbye!\n";
            break;

        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
