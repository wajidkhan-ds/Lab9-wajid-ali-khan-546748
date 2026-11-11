#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct WordNode {
    string word;
    int count;
    WordNode* left;
    WordNode* right;

    WordNode(string w) {
        word = w;
        count = 1;
        left = NULL;
        right = NULL;
    }
};

class WordBST {
public:
    WordNode* root;
    int totalWords;
    int uniqueWords;

    WordBST() {
        root = NULL;
        totalWords = 0;
        uniqueWords = 0;
    }

    // lowercase + strip non-letters
    string cleanWord(string w) {
        string result = "";
        for (int i = 0; i < (int)w.size(); i++) {
            char c = w[i];
            if (isalpha(c))
                result += tolower(c);
        }
        return result;
    }

    WordNode* insert(WordNode* node, string w) {
        if (node == NULL) {
            uniqueWords++;
            return new WordNode(w);
        }

        if (w < node->word)
            node->left = insert(node->left, w);
        else if (w > node->word)
            node->right = insert(node->right, w);
        else
            node->count++;

        return node;
    }

    void insert(string w) {
        totalWords++;
        root = insert(root, w);
    }

    void displayAlphabetical(WordNode* node) {
        if (node == NULL) return;
        displayAlphabetical(node->left);
        cout << node->word << " : " << node->count << endl;
        displayAlphabetical(node->right);
    }

    void collectNodes(WordNode* node, vector<WordNode*>& list) {
        if (node == NULL) return;
        collectNodes(node->left, list);
        list.push_back(node);
        collectNodes(node->right, list);
    }

    void displayByFrequency() {
        vector<WordNode*> list;
        collectNodes(root, list);

        sort(list.begin(), list.end(), [](WordNode* a, WordNode* b) {
            return a->count > b->count;
        });

        for (int i = 0; i < (int)list.size(); i++)
            cout << list[i]->word << " : " << list[i]->count << endl;
    }

    void findMostFrequentWord() {
        vector<WordNode*> list;
        collectNodes(root, list);

        if (list.empty()) return;

        int maxCount = 0;
        for (int i = 0; i < (int)list.size(); i++)
            if (list[i]->count > maxCount)
                maxCount = list[i]->count;

        cout << "Most frequent word(s) [count = " << maxCount << "]: ";
        for (int i = 0; i < (int)list.size(); i++)
            if (list[i]->count == maxCount)
                cout << list[i]->word << " ";
        cout << endl;
    }
};

int main() {
    string paragraph = "the quick brown fox jumps over the lazy dog. The fox is quick and smart.";

    WordBST tree;

    string current = "";
    for (int i = 0; i <= (int)paragraph.size(); i++) {
        if (i == (int)paragraph.size() || paragraph[i] == ' ') {
            if (!current.empty()) {
                string cleaned = tree.cleanWord(current);
                if (!cleaned.empty())
                    tree.insert(cleaned);
                current = "";
            }
        } else {
            current += paragraph[i];
        }
    }

    cout << "Alphabetical order:\n";
    tree.displayAlphabetical(tree.root);

    cout << "\nSorted by frequency (high to low):\n";
    tree.displayByFrequency();

    cout << "\n";
    tree.findMostFrequentWord();

    cout << "\nTotal unique words: " << tree.uniqueWords << endl;
    cout << "Total word count:   " << tree.totalWords << endl;

    return 0;
}