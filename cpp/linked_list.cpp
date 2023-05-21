#include <iostream>
#include <memory>
#include <string>

namespace DSA {
    template<class T>
    class Node {
        T m_value;
        std::shared_ptr<Node> m_next;

    public:

        explicit Node() : m_value(T()), m_next(nullptr) {}

        explicit Node(T value) : m_value(value), m_next(nullptr) {}

        std::shared_ptr<Node> &next() {
            return m_next;
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
        explicit LinkedList(T value) {
            m_first = std::make_shared<Node<T>>(value);
            m_last = m_first;
        }

        LinkedList() {
            m_first = nullptr;
            m_last = nullptr;
        }

        [[nodiscard]] bool isEmpty() const {
            return m_first == nullptr;
        };

        void push_back(T value) {
            if (isEmpty()) {
                m_first = std::make_shared<Node<T>>(value);
                m_last = m_first;
            } else {
                m_last->next() = std::make_shared<Node<T>>(value);
                m_last = m_last->next();
            }
        };

        void push_front(T value) {
            if (isEmpty()) {
                push_back(value);
            } else {
                auto newNode = std::make_shared<Node<T>>(value);
                newNode->next() = m_first;
                m_first = newNode;
            }
        };

        std::shared_ptr<Node<T>> &pop_back() {}
        std::shared_ptr<Node<T>> &pop_first() {}

        void remove(T value) {
            if (isEmpty()) {
                return;
            }

            if (m_first->value() == value) {
                m_first = m_first->next();
                if (m_first == nullptr) {
                    m_last = nullptr;
                }
                return;
            }

            std::shared_ptr<Node<T>> curr = m_first;
            std::shared_ptr<Node<T>> prev = nullptr;

            while (curr != nullptr) {
                if (curr->value() == value) {
                    if (curr->next() == nullptr) {
                        prev->next() = nullptr;
                        m_last = prev;
                    } else {
                        prev->next() = curr->next();
                    }
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
                    std::cout << temp->value();
                } else {
                    std::cout << temp->value() << ", ";
                }
                temp = temp->next();
            }
            std::cout << '\n';
        };

        std::shared_ptr<Node<T>> search(T key) {
            if (isEmpty()) {
                return nullptr;
            }

            auto curr = m_first;

            while (curr != nullptr) {
                if (curr->value() == key) {
                    return curr;
                }

                curr = curr->next();
            }
        };

        void reverse() {
            if (isEmpty()) {
                return;
            }

            std::shared_ptr<Node<T>> prev = nullptr;
            std::shared_ptr<Node<T>> curr = m_first;
            std::shared_ptr<Node<T>> next;

            while (curr != nullptr) {
                next = curr->next();
                curr->next() = prev;
                prev = curr;
                curr = next;
            }

            std::swap(m_first, m_last);

        };
    };

}

int main() {
    auto linkedList = DSA::LinkedList<int>(20);
    linkedList.push_back(55);
    linkedList.push_back(23);
    linkedList.push_back(11);
    linkedList.reverse();
    linkedList.display();
};
