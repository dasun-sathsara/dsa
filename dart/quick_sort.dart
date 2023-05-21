List<int> quickSort({required List<int> array}) {
  void _swap(List<int> array, int p1, int p2) {
    var temp = array[p1];
    array[p1] = array[p2];
    array[p2] = temp;
  }

  int _pivot({required List<int> array, required int pivotIndex, required int end}) {
    var swapIndex = pivotIndex;
    var pointer = swapIndex + 1;
    while (pointer < end) {
      if (array[pointer] < array[pivotIndex]) {
        swapIndex++;
        _swap(array, pointer, swapIndex);
      }
      pointer++;
    }

    _swap(array, pivotIndex, swapIndex);

    return swapIndex;
  }

  void _quickSort({required List<int> array, required int pivotIndex, required int end}) {
    if (pivotIndex < end) {
      var pivotPoint = _pivot(array: array, pivotIndex: pivotIndex, end: end);
      _quickSort(array: array, pivotIndex: 0, end: pivotPoint);
      _quickSort(array: array, pivotIndex: pivotPoint + 1, end: end);
    }
  }

  _quickSort(array: array, pivotIndex: 0, end: array.length);
  return array;
}

void main() {
  print(quickSort(array: [4, 6, 10, 56, 7, 3, 2, 5, -10, 12, -35, 56, 230]));
}
