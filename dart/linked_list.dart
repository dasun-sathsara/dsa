import 'dart:io';

class Node {
  int value;
  Node? next;

  Node(int this.value) {}
}

class LinkedList {
  Node? head;
  Node? tail;
  int length = 0;

  void addLast(int value) {
    var newNode = Node(value);

    if (head == null) {
      head = newNode;
      tail = newNode;
      length++;
    } else {
      tail!.next = newNode;
      tail = newNode;
      length++;
    }
  }

  int? popLast() {
    if (head != null) {
      if (head == tail) {
        var value = head!.value;
        head = null;
        tail = null;
        length--;

        return value;
      } else {
        var current = head;
        while (current?.next?.next != null) {
          current = current!.next;
        }
        var last = tail;
        tail = current;
        tail!.next = null;
        return last!.value;
      }
    } else {
      return null;
    }
  }

  void addFirst(int value) {
    var newNode = Node(value);

    if (head == null) {
      head = newNode;
      tail = newNode;
      length++;
    } else {
      newNode.next = head;
      head = newNode;
      length++;
    }
  }

  int? popFirst() {
    if (head == null) {
      return null;
    } else if (head == tail) {
      var value = head!.value;
      head = null;
      tail = null;
      length--;
      return value;
    } else {
      var first = head!.value;
      head = head!.next;
      length--;
      return first;
    }
  }

  bool searchValue(int value) {
    if (head == null) return false;

    var current = head;
    while (current != null) {
      if (current.value == value) {
        return true;
      }
      current = current.next;
    }
    return false;
  }

  int? at(int index) {
    if (head == null) return null;

    var current = head;
    var i = 0;

    while (current != null) {
      if (i == index) {
        return current.value;
      }
      current = current.next;
      i++;
    }
    return null;
  }

  void insert(int index, int value) {
    if (head == null) {
      if (index == 0) {
        var newNode = Node(value);
        head = newNode;
        tail = newNode;
        length++;
        return;
      } else {
        return;
      }
    } else if (index == 0) {
      var newNode = Node(value);
      newNode.next = head;
      head = newNode;
    } else {
      var current = head;
      var ci = 0;

      while (current != null) {
        if (ci == index - 1) {
          var newNode = Node(value);
          newNode.next = current.next;
          current.next = newNode;
          length++;
          return;
        }

        current = current.next;
        ci++;
      }
    }
  }

void printList() {
    Node? current = head;
    while (current != null) {
      stdout.write('${current.value}, ');
      current = current.next;
    }
    stdout.write('\n');
  }
}

void main() {
  final l = LinkedList();
  l.addLast(38);
  l.addLast(20);
  l.addLast(200);

  l.addFirst(3);
  l.addFirst(-19);
  l.printList();

  l.insert(5, 17);

  l.printList();
}
