import 'dart:math';

List<int> merge(List<int> list1, List<int> list2) {
  var l1 = 0;
  var l2 = 0;
  var result = <int>[];

  while (l1 < list1.length && l2 < list2.length) {
    if (list1[l1] < list2[l2]) {
      result.add(list1[l1]);
      l1++;
    } else {
      result.add(list2[l2]);
      l2++;
    }
  }

  if (l1 < list1.length) {
    result.addAll(list1.getRange(l1, list1.length));
  }
  if (l2 < list2.length) {
    result.addAll(list2.getRange(l2, list2.length));
  }

  return result;
}

List<int> sort(List<int> list) {
  if (list.length < 2) {
    return list;
  }

  var mid = list.length ~/ 2;
  return merge(sort(list.getRange(0, mid).toList()), sort(list.getRange(mid, list.length).toList()));
}

void main() {
  var a = [10, 12, 15, 16, 20, 21];
  var b = [3, 5, 7, 9, 20, 22, 25];
  // print(merge(b, a));
  // print(sort([34, 23, 43, 23, 10, -121, 323, 65, 34]));

  var c = List.generate(100, (index) {
    var random = Random().nextInt(100);

    if (Random().nextBool()) {
      return random;
    } else {
      return random * -1;
    }
  });

  var copy = c.getRange(0, c.length).toList();
  copy.sort((a, b) => a.compareTo(b));
  print(c);
  print(copy);

  print(sort(c));
}
