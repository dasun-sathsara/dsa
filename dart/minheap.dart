class MinHeap {
  final List<int> _data;
  late int _length;

  MinHeap() : _data = [] {
    _length = 0;
  }

  void add(int value) {
    if (_data.isEmpty) {
      _data.add(value);
    } else {
      _data.add(value);
      _heapifyUp(_length);
    }

    _length++;
  }

  int? poll() {
    if (_length == 0) {
      return null;
    }
    _length--;
    var out = _data[0];

    if (_length == 0) {
      _data.clear();
    } else {
      _data[0] = _data[_length];
      _data.removeAt(_length);
      _heapifyDown(0);
    }

    return out;
  }

  void _heapifyUp(int index) {
    if (index == 0) {
      return;
    }

    var parentIndex = _parent(index);

    if (_data[parentIndex] > _data[index]) {
      var temp = _data[index];
      _data[index] = _data[parentIndex];
      _data[parentIndex] = temp;

      _heapifyUp(parentIndex);
    }
  }

  void _heapifyDown(int index) {
    var leftIndex = _leftChild(index);
    var rightIndex = _rightChild(index);

    var smallest = index;

    if (leftIndex < _length && _data[leftIndex] < _data[smallest]) {
      smallest = leftIndex;
    }
    if (rightIndex < _length && _data[rightIndex] < _data[leftIndex]) {
      smallest = rightIndex;
    }

    if (smallest == index) {
      return;
    }

    var temp = _data[index];
    _data[index] = _data[smallest];
    _data[smallest] = temp;

    _heapifyDown(smallest);
  }

  int _parent(int index) {
    return ((index - 1) / 2).floor();
  }

  int _leftChild(int index) {
    return (index * 2 + 1);
  }

  int _rightChild(int index) {
    return (index * 2 + 2);
  }
}

void main() {
  final heap = MinHeap();
  heap.add(10);
  heap.add(2);
  heap.add(5);
  heap.add(1);
  heap.add(13);
  heap.add(4);
  heap.add(-1);
  heap.add(11);
  heap.add(9);

  print(heap._data);
  print(heap.poll());
  print(heap._data);
  print(heap.poll());
  print(heap._data);
  print(heap.poll());
  print(heap._data);
}
