#include <iostream>
#include <memory>
#include <queue>

class AVLTree {
public:
    struct Node {
        int data;
        int height{};
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        explicit Node(int key) : data(key), height(1), left(nullptr), right(nullptr) {}
    };

    AVLTree() : root(nullptr) {}

    void printBreathFirst() const {
        if (!root) {
            return;
        }

        std::queue<std::shared_ptr<Node>> queue;
        queue.push(root);

        while (!queue.empty()) {
            std::shared_ptr<Node> currentNode = queue.front();
            std::cout << currentNode->data << ", ";
            queue.pop();

            if (currentNode->left) {
                queue.push(currentNode->left);
            }

            if (currentNode->right) {
                queue.push(currentNode->right);
            }
        }
        std::cout << std::endl;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {}

//    bool search(int data) {}

private:
    std::shared_ptr<Node> root;

    int height(const std::shared_ptr<Node> &node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(const std::shared_ptr<Node> &node) const {
        return height(node->left) - height(node->right);
    }

    void updateHeight(const std::shared_ptr<Node> &node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    std::shared_ptr<Node> rotateRight(const std::shared_ptr<Node> &node) {
        std::shared_ptr<Node> leftNode = node->left;
        node->left = leftNode->right;
        leftNode->right = node;
        updateHeight(node);
        updateHeight(leftNode);
        return leftNode;
    }

    std::shared_ptr<Node> rotateLeft(const std::shared_ptr<Node> &node) {
        std::shared_ptr<Node> rightNode = node->right;
        node->right = rightNode->left;
        rightNode->left = node;
        updateHeight(node);
        updateHeight(rightNode);
        return rightNode;
    }

    std::shared_ptr<Node> balance(const std::shared_ptr<Node> &node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf == 2) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (bf == -2) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    std::shared_ptr<Node> insert(const std::shared_ptr<Node> &node, int key) {
        if (!node) {
            return std::make_shared<Node>(key);
        }

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }

        return balance(node);
    }
};


int main() {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.insert(3);
    tree.insert(7);
    tree.printBreathFirst();
};