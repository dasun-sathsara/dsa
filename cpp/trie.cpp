#include <iostream>
#include <memory>
#include <string>


class Trie {
private:
    static constexpr size_t ALPHABET = 26;

    struct TrieNode {
        std::shared_ptr<TrieNode> children[ALPHABET]{nullptr};
        bool isEndOfWord{false};
    };

    static bool hasChildren(const std::shared_ptr<TrieNode> &node) {
        for (auto & i : node->children) {
            if (i) {
                return true;
            }
        }
        return false;
    }

    static std::shared_ptr<TrieNode>
    _removeWord(std::shared_ptr<TrieNode> &curr, const std::string &word, size_t index) {
        if (word.size() == index) {
            if (curr->isEndOfWord) {
                curr->isEndOfWord = false;
            }
            if (hasChildren(curr)) {
                return curr;
            } else {
                return nullptr;
            }
        }

        size_t idx = word[index] - 'a';

        if (!curr->children[idx]) {
            throw std::runtime_error(std::string("Word not found."));
        }

        curr->children[idx] = _removeWord(curr->children[idx], word, ++index);

        if (hasChildren(curr)) {
            return curr;
        } else {
            return nullptr;
        }

    }

public:
    Trie() : m_root(std::make_shared<TrieNode>()) {}

    void insert(const std::string &word) {
        auto curr = m_root;
        for (char ch: word) {
            size_t idx = ch - 'a';

            if (!curr->children[idx]) {
                curr->children[idx] = std::make_shared<TrieNode>();
            }
            curr = curr->children[idx];
        }
        curr->isEndOfWord = true;
    }

    bool search(const std::string &word) {
        auto curr = m_root;
        for (char ch: word) {
            size_t idx = ch - 'a';

            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx];
        }
        return curr->isEndOfWord;
    }

    void removeWord(const std::string &word) {
        m_root = _removeWord(m_root, word, 0);
    }

private:
    std::shared_ptr<TrieNode> m_root;
};

int main() {
    Trie trie;
    trie.insert("hel");
    trie.insert("hello");
    trie.removeWord("hel");
    trie.insert("dasun");
    trie.insert("dass");
    trie.removeWord("dass");
    std::cout << trie.search("dass") << '\n';

    return 0;
}