import 'dart:io';

class Node {
  String key;
  dynamic value;
  Node? next;

  Node(this.key, this.value) {}

  @override
  String toString() {
    return '$key:$value';
  }
}

class LinkedList {
  Node? head;
  int length = 0;

  void insert(String key, dynamic value) {
    if (head == null) {
      var newNode = Node(key, value);
      head = newNode;
      length++;
    } else {
      var currentNode = head!;

      while (currentNode.next != null) {
        if (currentNode.key == key) {
          currentNode.value = value;
          return;
        }
        currentNode = currentNode.next!;
      }
      if (currentNode.key == key) {
        currentNode.value = value;
        return;
      } else {
        var newNode = Node(key, value);
        currentNode.next = newNode;
        length++;
        return;
      }
    }
  }

  dynamic find(String key) {
    var currentNode = head;

    while (currentNode != null) {
      if (currentNode.key == key) {
        return currentNode.value;
      }
      currentNode = currentNode.next;
    }
    return null;
  }

  bool deleteFromKey(String key) {
    if (head != null && head!.key == key) {
      var temp = head;

      head = head?.next;
      temp!.next = null;
      length--;

      return true;
    }

    Node? current = head;

    while (current != null) {
      if (current.next != null && current.next!.key == key) {
        if (current.next!.next == null) {
          current.next = null;
        } else {
          current.next = current.next!.next;
        }
        length--;
        return true;
      }
      current = current.next;
    }

    return false;
  }

  void printList() {
    Node? current = head;
    while (current != null) {
      stdout.write('${current}, ');
      current = current.next;
    }
    stdout.write('\n');
  }

  String printListReturn() {
    Node? current = head;
    String outString = '';
    while (current != null) {
      outString += '${current}, ';
      current = current.next;
    }
    outString += '\n';
    return outString;
  }
}

class HashTable {
  late final List<LinkedList?> buckets;
  final int maxSize;

  HashTable(this.maxSize) {
    buckets = List.filled(maxSize, null, growable: false);
  }

  int _hash(String key) {
    return key.hashCode % maxSize;
  }

  void set({required String key, required dynamic value}) {
    final index = _hash(key);

    if (buckets[index] == null) {
      final linkedList = LinkedList();
      linkedList.insert(key, value);
      buckets[index] = linkedList;
    } else {
      final linkedList = buckets[index]!;
      linkedList.insert(key, value);
    }
  }

  dynamic get(String key) {
    final index = _hash(key);
    if (buckets[index] == null) {
      return null;
    } else {
      final ll = buckets[index]!;
      return ll.find(key);
    }
  }

  void printHashTable() {
    buckets.asMap().forEach((index, ll) {
      if (ll == null) {
        print('$index. null');
      } else {
        stdout.write('$index. ${ll.printListReturn()}');
      }
    });
  }
}

void main() {
  final map = HashTable(17);
  map.set(key: 'name', value: 'Dasun');
  map.set(key: 'age', value: 20);
  map.set(key: 'hobbies', value: ['coding', 'movies']);
  map.set(key: 'isGood', value: true);
  map.set(key: 'foo', value: 'bar');
  map.set(key: 'foo', value: 'bark');
  map.printHashTable();
  print('');
  print(map.get('hobbies'));
}
