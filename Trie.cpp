//
//  Trie.cpp
//  
//
//  Created by Alice on 10/7/18.
//

class Trie {
private:
    class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        bool is_word = false;
    };
    
public:
    TrieNode* root;
    
    Trie() { root = new TrieNode();}
    
    void insert(string word) {
        TrieNode* p = this->root;
        int size = word.length();
        
        for (int i = 0; i < size; i++){
            if (p->children.find(word[i]) == p->children.end())
                p->children[word[i]] = new TrieNode();
            
            p = p->children[word[i]];
        }
        p->is_word = true;
    }
    
    bool search(string word) {
        TrieNode* p = this->root;
        int size = word.length();
        
        for (int i = 0; i < size; i++){
            if (p->children.find(word[i]) == p->children.end())
                return false;
            
            p = p->children[word[i]];
        }
        return p->is_word;
    }
    
    bool startsWith(string prefix) {
        TrieNode* p = this->root;
        int size = prefix.length();
        
        for (int i = 0; i < size; i++){
            if (p->children.find(prefix[i]) == p->children.end()) return false;
            
            p = p->children[prefix[i]];
        }
        return true;
    }
    
    
};
