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

class Queue {
  Node? front;
  Node? rear;
  int maxLength;
  int length = 0;

  Queue({required this.maxLength});

  void enqueue(int value) {
    if (length == maxLength) return;

    if (length == 0) {
      var newNode = Node(value);
      front = newNode;
      rear = newNode;
    } else if (length == 1) {
      var newNode = Node(value);
      front!.next = newNode;
      rear = newNode;
    } else {
      var newNode = Node(value);
      rear!.next = newNode;
      rear = newNode;
    }
    length++;
  }

  int? dequeue() {
    if (length == 1) {
      var val = front!.value;
      front = null;
      rear = null;
      length--;

      return val;
    } else if (length > 1) {
      var val = front!.value;
      front = front!.next;
      length--;

      return val;
    }
    return null;
  }

  void printQueue() {
    Node? current = front;
    while (current != null) {
      stdout.write('${current.value}, ');
      current = current.next;
    }
    stdout.write('\n');
  }
}

void main() {
  var queue = Queue(maxLength: 10);
  queue.enqueue(10);
  queue.enqueue(11);
  queue.enqueue(15);
  queue.enqueue(152);
  queue.printQueue();
  print(queue.dequeue());
  queue.printQueue();
  print(queue.dequeue());
  queue.printQueue();
  print(queue.dequeue());
  queue.printQueue();
  print(queue.dequeue());
  queue.printQueue();
  print(queue.dequeue());
}
