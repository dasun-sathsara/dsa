List<int> quickSort(List<int> list) {
  void _swap(List<int> list, int left, int right) {
    final temp = list[left];
    list[left] = list[right];
    list[right] = temp;
  }

  int partition(List<int> list, int left, int right) {
    final pivot = (left + (right - left) / 2).floor();
    print(list[left]);
    print(list[pivot]);
    while (left <= right) {
      while (list[left] < list[pivot]) {
        left++;
      }

      while (list[right] > list[pivot]) {
        right--;
      }

      if (left <= right) {
        _swap(list, left, right);
      }
      left++;
      right--;
    }

    return left;
  }

  void _quickSort(List<int> list, int left, int right) {
    if (left < right) {
      final partitionPoint = partition(list, left, right);
      _quickSort(list, left, partitionPoint - 1);
      _quickSort(list, partitionPoint + 1, right);
    }
  }

  _quickSort(list, 0, list.length - 1);
  return list;
}

void main() {
  print(quickSort([4, 6, 10,  7, 3, 2, 5, -10, 12, -35, 56, 230]));
}
