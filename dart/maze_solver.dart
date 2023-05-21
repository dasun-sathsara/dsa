class Point {
  final int x;
  final int y;

  Point(this.x, this.y);
  @override
  String toString() {
    return '($x,$y)';
  }
}

const directions = [
  [0, -1],
  [1, 0],
  [0, 1],
  [-1, 0]
];

bool walk(List<String> maze, String wall, String end, Point current, List<List<bool>> seen, List<Point> path) {
  //Base Cases

  //Check for out of bounds
  if ((current.x < 0 || current.x >= maze[0].length) || (current.y < 0 || current.y >= maze.length)) {
    return false;
  }

  //Check for walls
  if (maze[current.y][current.x] == wall) {
    return false;
  }

  //Check for end (destination)
  if (maze[current.y][current.x] == end) {
    path.add(current);
    return true;
  }

  //Check for seen tiles
  if (seen[current.y][current.x]) {
    return false;
  }

  seen[current.y][current.x] = true;

  //Pre
  path.add(current);

  //Recurse
  for (final direction in directions) {
    if (walk(maze, wall, end, Point(current.x + direction[0], current.y + direction[1]), seen, path)) {
      return true;
    }
  }

  //Post
  path.remove(current);

  return false;
}

void solve(List<String> maze, String wall, Point start, String end) {
  List<List<bool>> seen = [];
  final path = <Point>[];

  maze.asMap().keys.forEach((row) {
    seen.add(List.filled(maze[row].length, false));
  });

  if (walk(maze, wall, end, start, seen, path)) {
    print(path);
  } else {
    print('No way.');
  }
}

void main() {
  final maze = [
    'XXXXXXXXXXXX X',
    'X      XXXXX X',
    'XEXXX  XXXXX X',
    'XXXXX  XXXXX X',
    'XXXXX        X',
    'XXXXXXXXXXXX X',
  ];

  final wall = 'X';
  final end = 'E';

  solve(maze, wall, Point(12, 0), end);
}
