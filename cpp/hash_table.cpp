#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

namespace DSA {
    template<class T>
    class Node {
        std::string m_key;
        T m_value;
        std::shared_ptr<Node> m_next;

    public:

        explicit Node(std::string key, T value) : m_key(std::move(key)), m_value(value), m_next(nullptr) {}

        std::shared_ptr<Node> &next() {
            return m_next;
        }

        [[nodiscard]] std::string key() const {
            return m_key;
        }

        [[nodiscard]] T value() const {
            return m_value;
        }
    };

    template<class T>
    class LinkedList {
        std::shared_ptr<Node<T>> m_first;
        std::shared_ptr<Node<T>> m_last;
    public:
        explicit LinkedList(std::string key, T value) {
            m_first = std::make_shared<Node<T>>(key, value);
            m_last = m_first;
        }

        LinkedList() {
            m_first = nullptr;
            m_last = nullptr;
        }

        [[nodiscard]] bool isEmpty() const {
            return m_first == nullptr;
        };

        void push_back(std::string key, T value) {
            if (isEmpty()) {
                m_first = std::make_shared<Node<T>>(std::move(key), value);
                m_last = m_first;
            } else {
                m_last->next() = std::make_shared<Node<T>>(std::move(key), value);
                m_last = m_last->next();
            }
        };

        std::shared_ptr<Node<T>> pop_back() {
            if (isEmpty()) {
                return nullptr;
            }

            auto curr = m_first;
            while (curr->next() != m_last) {
                curr = curr->next();
            }

            std::shared_ptr<Node<T>> temp = m_last;
            curr->next() = nullptr;
            m_last = curr;

            return temp;
        }

        void remove(const std::string &key) {
            if (isEmpty()) {
                return;
            }

            if (m_first->key() == key) {
                m_first = m_first->next();
                if (m_first == nullptr) {
                    m_last = nullptr;
                }
                return;
            }

            std::shared_ptr<Node<T>> curr = m_first;
            std::shared_ptr<Node<T>> prev = nullptr;

            while (curr != nullptr) {
                if (curr->key() == key) {
                    if (curr->next() == nullptr) {
                        prev->next() = nullptr;
                        m_last = prev;
                    } else {
                        prev->next() = curr->next();
                    }
                    break;
                }

                prev = curr;
                curr = curr->next();
            }

        };

        void display() {
            if (isEmpty()) {
                std::cout << "LinkedList is Empty!";
                return;
            }
            std::shared_ptr<Node<T>> temp = m_first;
            while (temp != nullptr) {
                if (temp->next() == nullptr) {
                    std::cout << "(" << temp->key() << "," << temp->value() << ")";
                } else {
                    std::cout << "(" << temp->key() << "," << temp->value() << ")" << ", ";
                }
                temp = temp->next();
            }
            std::cout << '\n';
        };

        std::shared_ptr<Node<T>> search(const std::string &key) {
            if (isEmpty()) {
                return nullptr;
            }

            auto curr = m_first;

            while (curr != nullptr) {
                if (curr->key() == key) {
                    return curr;
                }

                curr = curr->next();
            }

            return nullptr;
        };

    };

    template<class T>
    class HashTable {
        std::vector<std::unique_ptr<DSA::LinkedList<T>>> m_table;
        std::size_t m_size;

        [[nodiscard]] std::size_t hash(const std::string &key) const {
            std::size_t hash = 0;
            for (char c: key) {
                hash = c + (hash << 6) + (hash << 16) - hash;
            }
            return hash % m_size;
        }

    public:
        explicit HashTable(size_t size) : m_size(size) {
            m_table.resize(m_size);
        }

        void set(std::string key, T value) {
            std::size_t index = hash(key);

            if (!m_table[index]) {
                m_table[index] = std::make_unique<LinkedList<T>>(std::move(key), std::move(value));
            } else {
                m_table[index]->push_back(std::move(key), std::move(value));
            }

        }

        T get(const std::string &key) {
            std::size_t index = hash(key);

            if (!m_table[index]) {
                throw std::out_of_range("Key not found");
            } else {
                return m_table[index]->search(key)->value();
            }
        }
    };

}

int main() {
    auto ht = DSA::HashTable<int>(5);
    ht.set("Dasun", 21);
    ht.set("Kasun", 22);
    ht.set("Damian", 19);

    auto a = ht.get("Damian");

    std::cout << a << std::endl;
};