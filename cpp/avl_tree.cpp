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

    void printDepthFirst() {
        printDepthFirst(root);
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    bool search(int data) {
        if (search(root, data)) {
            return true;
        } else {
            return false;
        }
    }

private:
    std::shared_ptr<Node> root;

    int height(const std::shared_ptr<Node> &node) const {
        return node ? node->height : 0;
    }

    void printDepthFirst(const std::shared_ptr<Node> &node) {
        if (!node) {
            return;
        }

        printDepthFirst(node->left);
        printDepthFirst(node->right);
        std::cout << node->data << ", ";
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

    std::shared_ptr<Node> findMin(const std::shared_ptr<Node> &node) {
        return node->left ? findMin(node->left) : node;
    }

    std::shared_ptr<Node> remove(const std::shared_ptr<Node> &node, int &key) {
        if (!node) {
            return nullptr;
        }

        if (node->data == key) {
            if (!node->right) {
                return node->left;
            }

            if (!node->left) {
                return node->right;
            }

            std::shared_ptr<Node> nodeMin = findMin(node);
            std::shared_ptr<Node> right = remove(node->right, nodeMin->data);
            node->right = right;
            node->data = nodeMin->data;

            updateHeight(node);
            return balance(node);
        }

        if (key > node->data) {
            node->right = remove(node->right, key);
            return node;
        } else {
            node->left = remove(node->left, key);
            return node;
        }
    }

    std::shared_ptr<Node> search(const std::shared_ptr<Node> &node, const int &key) {

        if (!node) {
            return nullptr;
        }

        if (node->data == key) {
            return node;
        }

        if (key > node->data) {
            return search(node->right, key);
        } else {
            return search(node->left, key);
        }
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
    tree.insert(12);
    tree.printDepthFirst();
};