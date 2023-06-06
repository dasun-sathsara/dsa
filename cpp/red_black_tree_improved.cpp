#include <iostream>
#include <memory>
#include <queue>

class RedBlackTreeImproved {
private:
    enum class Color {
        Red,
        Black
    };

    struct Node {
        int data{};
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Color color;

        Node() = default;

        Node(int key, const std::shared_ptr<Node> &pNode, const std::shared_ptr<Node> &nullNode)
                : data(key), parent(pNode), left(nullNode), right(nullNode), color(Color::Red) {
        }
    };

public:
    RedBlackTreeImproved() {
        nullNode = std::make_shared<Node>();
        nullNode->left = nullptr;
        nullNode->right = nullptr;
        nullNode->color = Color::Black;
        root = nullNode;
    }

    void insert(int key) {
        std::shared_ptr<Node> node = std::make_shared<Node>(key, nullptr, nullNode);

        std::shared_ptr<Node> parent = nullptr;
        std::shared_ptr<Node> curr = root;

        while (curr != nullNode) {
            parent = curr;
            if (key > curr->data) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        node->parent = parent;
        if (!parent) {
            root = node;
        } else if (key > parent->data) {
            parent->right = node;
        } else {
            parent->left = node;
        }

        node->color = Color::Red;
        fixUpInsert(node);
    }

private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> nullNode;

    void fixUpInsert(const std::shared_ptr<Node> &node) {
        std::shared_ptr<Node> currentNode = node;

        while (currentNode->parent && currentNode->parent->color == Color::Red) {
            if (currentNode->parent == currentNode->parent->parent->left) {
                std::shared_ptr<Node> uncle = currentNode->parent->parent->right;

                if (uncle->color == Color::Red) {
                    uncle->color = Color::Black;
                    currentNode->parent->color = Color::Black;
                    currentNode->parent->parent->color = Color::Red;
                    currentNode = currentNode->parent->parent;
                } else {
                    if (currentNode == currentNode->parent->right) {
                        currentNode = currentNode->parent;
                        leftRotate(currentNode);
                    }

                    currentNode->parent->color = Color::Black;
                    currentNode->parent->parent->color = Color::Red;
                    rightRotate(currentNode->parent->parent);
                }
            } else {
                std::shared_ptr<Node> uncle = currentNode->parent->parent->left;

                if (uncle->color == Color::Red) {
                    uncle->color = Color::Black;
                    currentNode->parent->color = Color::Black;
                    currentNode->parent->parent->color = Color::Red;
                    currentNode = currentNode->parent->parent;
                } else {
                    if (currentNode == currentNode->parent->left) {
                        currentNode = currentNode->parent;
                        rightRotate(currentNode);
                    }

                    currentNode->parent->color = Color::Black;
                    currentNode->parent->parent->color = Color::Red;
                    leftRotate(currentNode->parent->parent);
                }
            }
        }

        root->color = Color::Black;
    }

    void leftRotate(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> right = node->right;
        node->right = right->left;

        if (right->left != nullNode) {
            right->left->parent = node;
        }

        right->parent = node->parent;

        if (!node->parent) {
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }

        right->left = node;
        node->parent = right;
    }

    void rightRotate(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> left = node->left;
        node->left = left->right;

        if (left->right != nullNode) {
            left->right->parent = node;
        }

        left->parent = node->parent;

        if (!node->parent) {
            root = left;
        } else if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }

        left->right = node;
        node->parent = left;
    }
};

