class Node {
  double value;

  Node(this.value);

  @override
  String toString() => '$value';
}

class BST {
  Node root;
  BST? left;
  BST? right;

  BST(this.root);

  @override
  String toString() => '$root';

  void insert(double value) {
    void _insert(double value, BST bst) {
      if (value < bst.root.value && bst.left == null) {
        bst.left = BST(Node(value));
      }

      if (value > bst.root.value && bst.right == null) {
        bst.right = BST(Node(value));
      }

      if (value < bst.root.value) {
        _insert(value, bst.left!);
      }

      if (value > bst.root.value) {
        _insert(value, bst.right!);
      }
    }

    _insert(value, this);
  }
}

void main() {
  var bst = BST(Node(12));
  bst.left = BST(Node(3));
  bst.left!.left = BST(Node(-5));
  bst.left!.right = BST(Node(-7));
  bst.right = BST(Node(14));
  bst.right!.right = BST(Node(18));
  bst.insert(-10);
  bst.insert(-1);
  bst.insert(-15);

  bst.insert(20);
  // bst.insert(12);
  bst.insert(25);
  bst.insert(15);

  print_bst(bst);
}

print_bst(BST bst) {
  BST? current = bst;
  while (current != null) {
    print(current);
    current = current.left;
  }

  print('');
  print('');
  current = bst;
  while (current != null) {
    print(current);
    current = current.right;
  }
}
