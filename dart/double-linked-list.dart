import 'dart:io';

class Node {
  final int data;
  Node? next;
  Node? prev;

  Node(this.data);
}

class DoublyLinkedList {
  Node? head;
  DoublyLinkedList([int? data]) {
    if (data != null) {
      head = Node(data);
    }
  }

  void addFront(int data) {
    var newNode = Node(data);
    if (head == null) {
      head = newNode;
    } else {
      head!.prev = newNode;
      newNode.next = head;
      head = newNode;
    }
  }

  void addEnd(int data) {
    var newNode = Node(data);
    if (head == null) {
      head = newNode;
    } else {
      var currentNode = head;

      while (currentNode!.next != null) {
        currentNode = currentNode.next;
      }
      newNode.prev = currentNode;
      currentNode.next = newNode;
    }
  }

  void addAfter({required int index, required int data}) {
    var newNode = Node(data);
    if (head == null) {
      return;
    }

    var currentIndex = 0;
    var currentNode = head;

    while (currentNode!.next != null) {
      if (currentIndex == index) {
        newNode.next = currentNode.next;
        currentNode.next!.prev = newNode;
        newNode.prev = currentNode;
        currentNode.next = newNode;
      }
      currentNode = currentNode.next;
      currentIndex++;
    }

    if (currentIndex == index) {
      newNode.prev = currentNode;
      currentNode.next = newNode;
    }
  }

  void addBefore({required int index, required int data}) {
    var newNode = Node(data);
    if (head == null) {
      return;
    }

    var currentIndex = 0;
    var currentNode = head;

    while (currentNode!.next != null) {
      if (currentIndex == index) {
        newNode.prev = currentNode.prev;
        newNode.next = currentNode;
        currentNode.prev!.next = newNode;
        currentNode.prev = newNode;
      }
      currentNode = currentNode.next;
      currentIndex++;
    }

    if (currentIndex == index) {
      newNode.prev = currentNode.prev;
      newNode.next = currentNode;
      currentNode.prev!.next = newNode;
      currentNode.prev = newNode;
    }
  }

  void printList() {
    if (head != null) {
      var currentNode = head;

      stdout.write('${currentNode!.data}, ');
      while (currentNode!.next != null) {
        currentNode = currentNode.next;
        stdout.write('${currentNode!.data}, ');
      }

      stdout.write('\n');
    }
  }
}

void main() {
  var list = DoublyLinkedList(45);
  list.printList();
  list.addFront(14);
  list.addFront(1);
  list.addEnd(15);
  list.addEnd(18);
  list.addAfter(index: 4, data: 5);
  list.addAfter(index: 5, data: 12);
  list.addAfter(index: 40, data: 12);
  list.printList();
  list.addBefore(index: 6, data: 65);
  list.printList();
}
