import 'dart:io';

class Node {
  int value;
  Node? next;

  Node(this.value);

  @override
  String toString() {
    return value.toString();
  }
}

class Stack {
  Node? top;
  int length = 0;
  int maxLength;

  Stack({required this.maxLength});

  bool get isEmpty => length == 0;

  bool get isFull => length == maxLength;

  int? get peak => top?.value;

  void push(int value) {
    if (length != maxLength) {
      if (top == null) {
        var newNode = Node(value);
        top = newNode;
      } else {
        var newNode = Node(value);
        newNode.next = top;
        top = newNode;
      }
      length++;
    }
  }

  int? pop() {
    if (length == 1) {
      var val = top!.value;
      top = null;
      length--;
      return val;
    } else if (length > 1) {
      var val = top!.value;
      top = top!.next;
      length--;
      return val;
    } else {
      return null;
    }
  }

  void printStack() {
    Node? current = top;
    while (current != null) {
      stdout.write('${current.value}, ');
      current = current.next;
    }
    stdout.write('\n');
  }
}

void main() {
  var stack = Stack(maxLength: 5);
  print(stack.peak);
  stack.push(10);
  stack.push(4);
  print(stack.pop());
  stack.push(45);
  stack.printStack();
  print(stack.peak);
}
