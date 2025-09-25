#include <string>
#include "trie.h"

using namespace std;

// Helper function to count the number of children for a node
int countChildren(TrieNode* node) {
    int children = 0;
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i]) {
            children++;
        }
    }
    return children;
}

void Trie::insert(string key, int val) {
    TrieNode* node = root;

    for(char c : key) {
        int index = c - 'a';
        if(!node->children[index]) {
            node->children[index] = new TrieNode();
            tree_size++;
        }
        node = node->children[index];
    }

    if(node->val == 0) {
        map_size++;
    }
    node->val = val;
}

int Trie::search(string key) {
    TrieNode* node = root;
    
    for(char c : key) {
        int index = c - 'a';
        if(!node->children[index]) {
            return 0;
        }
        node = node->children[index];
    }
    
    return node->val;
}

void Trie::remove(string key)
{
    TrieNode* current_node = root;
    TrieNode* parent_node = nullptr;
    bool is_leaf_node = true;
    int child_index = 0;

    for (char c : key)
    {
        child_index = c - 'a';
        if (!current_node->children[child_index])
        {
            return;
        }
        parent_node = current_node;
        current_node = current_node->children[child_index];
    }
    if (current_node->val != 0)
    {
        current_node->val = 0;
        map_size--;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (current_node->children[i] != NULL)
            {
                is_leaf_node = false;
                break;
            }
        }
        if (is_leaf_node)
        {
            tree_size--;
            if (parent_node != nullptr)
            {
                parent_node->children[child_index] = NULL;
            }
        }
    }
}
