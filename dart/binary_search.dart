int binarySort(List<int> arr, int key) {
  var low = 0;
  var high = arr.length;

  while (low < high) {
    var mid = ((low + high) / 2).floor();

    if (arr[mid] == key) {
      return mid;
    } else if (arr[mid] > key) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

void main() {
  var arr = [1, 2, 3, 6, 7, 12, 36, 57, 76];
  print(binarySort(arr, 6));
}
