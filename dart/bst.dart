class Node {
  int key;
  String value;
  Node? left;
  Node? right;

  Node({required this.key, required this.value});

  @override
  String toString() {
    return 'Node(key=$key, value=$value)';
  }

  @override
  bool operator ==(Object other) {
    return other.runtimeType == Node && (this.value == (other as Node).value) && (this.key == other.key);
  }
}

class BinarySearchTree {
  Node? root;

  BinarySearchTree(this.root);

  factory BinarySearchTree.fromList(List<Node> nodes) {
    final bst = BinarySearchTree(nodes[0]);
    for (final node in nodes.sublist(1)) {
      bst.insert(node);
    }

    return bst;
  }

  void insert(Node newNode) {
    void _insert(Node newNode, Node currentNode) {
      if (newNode.key < currentNode.key && currentNode.left == null) {
        currentNode.left = newNode;
      }

      if (newNode.key > currentNode.key && currentNode.right == null) {
        currentNode.right = newNode;
      }

      if (newNode.key < currentNode.key) {
        _insert(newNode, currentNode.left!);
      }

      if (newNode.key > currentNode.key) {
        _insert(newNode, currentNode.right!);
      }
    }

    if (root == null) {
      root = newNode;
    } else {
      _insert(newNode, root!);
    }
  }

  Node? find(int key) {
    Node? _find(int key, Node currentNode) {
      if (key == currentNode.key) {
        return currentNode;
      }

      if (key < currentNode.key) {
        if (currentNode.left == null) return null;

        return _find(key, currentNode.left!);
      } else {
        if (currentNode.right == null) return null;

        return _find(key, currentNode.right!);
      }
    }

    if (root == null) {
      return null;
    } else {
      return _find(key, root!);
    }
  }

  Node? min() {
    Node _min(Node currentNode) {
      if (currentNode.left == null) {
        return currentNode;
      } else {
        return _min(currentNode.left!);
      }
    }

    if (root == null) {
      return null;
    } else {
      return _min(root!);
    }
  }

  Node? max() {
    Node _max(Node currentNode) {
      if (currentNode.right == null) {
        return currentNode;
      } else {
        return _max(currentNode.right!);
      }
    }

    if (root == null) {
      return null;
    } else {
      return _max(root!);
    }
  }

  List<int> breadthFirstSearch() {
    final queue = <Node>[];
    final results = <int>[];

    if (root != null) {
      var currentNode = this.root;
      queue.add(currentNode!);

      while (queue.isNotEmpty) {
        currentNode = queue.removeAt(0);
        results.add(currentNode.key);
        if (currentNode.left != null) {
          queue.add(currentNode.left!);
        }

        if (currentNode.right != null) {
          queue.add(currentNode.right!);
        }
      }
    }

    return results;
  }

  List<int> depthFirstPreOrderSearch() {
    final List<int> results = [];
    _preOrderTraverse(Node current) {
      results.add(current.key);
      if (current.left != null) {
        _preOrderTraverse(current.left!);
      }

      if (current.right != null) {
        _preOrderTraverse(current.right!);
      }
    }

    if (root != null) {
      _preOrderTraverse(this.root!);
    }

    return results;
  }

  List<int> depthFirstPostOrderSearch() {
    final List<int> results = [];

    _postOrderTraverse(Node current) {
      if (current.left != null) {
        _postOrderTraverse(current.left!);
      }
      if (current.right != null) {
        _postOrderTraverse(current.right!);
      }
      results.add(current.key);
    }

    if (root != null) {
      _postOrderTraverse(this.root!);
    }

    return results;
  }

  List<int> depthFirstInOrderSearch() {
    final List<int> results = [];

    _postOrderTraverse(Node current) {
      if (current.left != null) {
        _postOrderTraverse(current.left!);
      }
      results.add(current.key);
      if (current.right != null) {
        _postOrderTraverse(current.right!);
      }
    }

    if (root != null) {
      _postOrderTraverse(this.root!);
    }

    return results;
  }

  static bool compareBST(BinarySearchTree bst1, BinarySearchTree bst2) {
    bool _compareSubTree(Node? node1, Node? node2) {
      if (node1 == null && node2 == null) {
        return true;
      }

      if (node1 == null || node2 == null) {
        return false;
      }

      if (node1 != node2) {
        return false;
      }

      bool left = _compareSubTree(node1.left, node2.left);
      bool right = _compareSubTree(node1.right, node2.right);

      return left && right;
    }

    return _compareSubTree(bst1.root, bst2.root);
  }

  void deleteKey(int key) {
    Node _minFromNode(Node root) {
      var currentNode = root;
      while (currentNode.left != null) {
        currentNode = currentNode.left!;
      }

      return currentNode;
    }

    Node? _deleteRecursive(Node? root, int key) {
      if (root == null) {
        return null;
      }

      if (key < root.key) {
        root.left = _deleteRecursive(root.left, key);
      } else if (key > root.key) {
        root.right = _deleteRecursive(root.right, key);
      } else {
        if (root.left == null) {
          return _deleteRecursive(root.right, key);
        } else if (root.right == null) {
          return _deleteRecursive(root.left, key);
        }

        var minNode = _minFromNode(root.right!);
        root.key = minNode.key;
        root.value = minNode.value;

        root.right = _deleteRecursive(root.right, root.key);
      }

      return root;
    }

    root = _deleteRecursive(root, key);
  }
}

void main() {
  final bst = BinarySearchTree(Node(key: 4, value: 'a'));
  bst.insert(Node(key: 1, value: 'b'));
  bst.insert(Node(key: 7, value: 'c'));
  bst.insert(Node(key: -5, value: 'd'));
  bst.insert(Node(key: 3, value: 'e'));
  bst.insert(Node(key: 12, value: 'f'));
  bst.insert(Node(key: 18, value: 'g'));
  bst.insert(Node(key: -18, value: 'h'));

  // print(bst.breadthFirstSearch());

  final bst1 = BinarySearchTree(Node(key: 4, value: 'a'));
  bst1.insert(Node(key: -5, value: 'a'));
  bst1.insert(Node(key: 7, value: 'a'));
  bst1.insert(Node(key: 6, value: 'a'));
  bst1.insert(Node(key: 45, value: 'a'));
  bst1.insert(Node(key: -3, value: 'a'));
  bst1.insert(Node(key: 43, value: 'a'));
  bst1.insert(Node(key: 47, value: 'a'));
  bst1.insert(Node(key: 15, value: 'a'));

  print(bst1.breadthFirstSearch());
  bst1.deleteKey(7);
  print(bst1.breadthFirstSearch());

  final bst3 = BinarySearchTree.fromList([
    Node(key: 4, value: 'a'),
    Node(key: 1, value: 'a'),
    Node(key: 7, value: 'a'),
    Node(key: -5, value: 'a'),
    Node(key: 3, value: 'a'),
    Node(key: 12, value: 'a'),
    Node(key: 18, value: 'a'),
    Node(key: -18, value: 'a'),
  ]);

  // print(bst3.breadthFirstSearch());
  // print(bst3.depthFirstPreOrderSearch());
  // print(bst3.depthFirstPostOrderSearch());
  // print(bst3.depthFirstInOrderSearch());
}
