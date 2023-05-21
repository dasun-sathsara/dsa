import 'dart:math';

int findBreaks(List<int> floors) {
  final jumpAmount = sqrt(floors.length).floor();

  var i = jumpAmount;
  for (; i < floors.length; i += jumpAmount) {
    if (floors[i] == 1) {
      break;
    }
  }

  var j = i - jumpAmount;

  for (; j <= i && j < floors.length; j++) {
    if (floors[j] == 1) {
      return j;
    }
  }
  return -1;
}

void main() {
  var breaks = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1];

  print(findBreaks(breaks));
}
