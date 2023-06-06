#include <iostream>
#include <memory>
#include <queue>


class RedBlackTree {
private:
    struct Node {
        int data{};
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        bool color{}; // true -> red, false -> black

        Node() = default;

        Node(int key, const std::shared_ptr<Node> &pNode, const std::shared_ptr<Node> &nullNode)
                : data(key), parent(pNode), left(nullNode), right(nullNode), color(true) {
        }

    };

public:
    RedBlackTree() {
        root = nullptr;
        nullNode = std::make_shared<Node>();
        nullNode->left = nullptr;
        nullNode->right = nullptr;
        nullNode->color = 0;
    }

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

            if (currentNode->left != nullNode) {
                queue.push(currentNode->left);
            }

            if (currentNode->right != nullNode) {
                queue.push(currentNode->right);
            }
        }
        std::cout << std::endl;
    }

    void printInOrder() {
        printInOrder(root);
        std::cout << std::endl;
    }

    void insert(int key) {
        std::shared_ptr<Node> node = std::make_shared<Node>(key, nullptr, nullNode);

        if (!root) {
            node->color = 0;
            root = node;
            return;
        }

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
        if (key > parent->data) {
            parent->right = node;
        } else {
            parent->left = node;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixUpInsert(node);
    }


private:
    std::shared_ptr<Node> root;
    std::shared_ptr<Node> nullNode;

    void fixUpInsert(const std::shared_ptr<Node> &node) {
        std::shared_ptr<Node> uncle;
        std::shared_ptr<Node> currentNode = node;

        while (currentNode->parent != nullptr && currentNode->parent->color != 0) {
            if (currentNode->parent == currentNode->parent->parent->right) {
                uncle = currentNode->parent->parent->left;

                if (uncle->color == 1) {
                    uncle->color = 0;
                    currentNode->parent->color = 0;
                    currentNode->parent->parent->color = 1;
                    currentNode = currentNode->parent->parent;
                } else {
                    if (currentNode == currentNode->parent->left) {
                        currentNode = currentNode->parent;
                        rightRotate(currentNode);
                    }

                    currentNode->parent->color = 0;
                    currentNode->parent->parent->color = 1;
                    leftRotate(currentNode->parent->parent);

                    if (currentNode->parent == nullptr) {
                        root = currentNode;
                    }
                }

            } else {
                uncle = currentNode->parent->parent->right;

                if (uncle->color == 1) {
                    uncle->color = 0;
                    currentNode->parent->color = 0;
                    currentNode->parent->parent->color = 1;
                    currentNode = currentNode->parent->parent;
                } else {
                    if (currentNode == currentNode->parent->right) {
                        currentNode = currentNode->parent;
                        leftRotate(currentNode);
                    }

                    currentNode->parent->color = 0;
                    currentNode->parent->parent->color = 1;
                    rightRotate(currentNode->parent->parent);

                    if (currentNode->parent == nullptr) {
                        root = currentNode;
                    }
                }
            }
        }

        root->color = 0;
    }


    void leftRotate(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> right = node->right;
        node->right = right->left;

        if (right->left != nullNode) {
            right->left->parent = node;
        }

        right->parent = node->parent;

        if (node->parent == nullptr) {
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

        if (node->parent == nullptr) {
            this->root = left;
        } else if (node == node->parent->right) {
            node->parent->right = left;
        } else {
            node->parent->left = left;
        }

        left->right = node;
        node->parent = left;
    }

    void printInOrder(const std::shared_ptr<Node> &node) {
        if (node == nullNode) {
            return;
        }

        printInOrder(node->left);
        std::cout << node->data << ", ";
        printInOrder(node->right);
    }

    std::shared_ptr<Node> findMin(const std::shared_ptr<Node> &node) {
        return node->left != nullNode ? findMin(node->left) : node;
    }

    std::shared_ptr<Node> findMax(const std::shared_ptr<Node> &node) {
        return node->right != nullNode ? findMax(node->right) : node;
    }

    std::shared_ptr<Node> findSuccessor(const std::shared_ptr<Node> &node) {
        if (node->right != nullNode) {
            return findMin(node->right);
        } else {
            std::shared_ptr<Node> parent = node->parent;
            std::shared_ptr<Node> currentNode = node;
            while (node != nullptr && currentNode == parent->right) {
                currentNode = parent;
                parent = parent->parent;
            }

            return parent;
        }
    }

    std::shared_ptr<Node> findPredecessor(const std::shared_ptr<Node> &node) {
        if (node->left != nullNode) {
            return findMax(node->left);
        } else {
            std::shared_ptr<Node> parent = node->parent;
            std::shared_ptr<Node> currentNode = node;
            while (node != nullptr && currentNode == parent->left) {
                currentNode = parent;
                parent = parent->parent;
            }

            return parent;
        }
    }
};

int main() {
    RedBlackTree rb;
    rb.insert(1);
    rb.insert(4);
    rb.insert(3);
    rb.insert(5);
    rb.insert(2);
    rb.printBreathFirst();
}