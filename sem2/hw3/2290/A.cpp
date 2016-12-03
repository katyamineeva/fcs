#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

using std::cout;
using std::ifstream;
using std::vector;
using std::queue;
using std::map;


class Point {
 public:
     int x;
     int y;

     Point() {
         x = 0;
         y = 0;
     }

     Point(int i, int j) {
         x = i;
         y = j;
     }

     void changePoint(int i, int j) {
         x = i;
         y = j;
     }
};

bool operator == (Point p1, Point p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

bool operator != (Point p1, Point p2) {
    return !(p1 == p2);
}

const Point NOT_VISITED(-1, -1);
const Point START(-2, -2);
const Point PRIZE(-3, -3);


Point readData(vector<vector<char>>& maze) {
    ifstream fin("input.txt");

    int n = 0;
    int m = 0;
    fin >> n;
    fin >> m;

    vector<char> wall(m + 2, '1');
    maze.resize(n + 2, wall);
    Point prize;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            fin >> maze[i][j];
            if (maze[i][j] == '*') {
                prize.x = i;
                prize.y = j;
            }
        }
    }

    int k = 0;
    int x = 0;
    int y = 0;

    fin >> k;

    for (int i = 0; i < k; ++i) {
        fin >> x >> y;
        maze[x][y] = 's';
    }
    fin.close();

    return prize;
}

void recoverAnswer(Point start, vector<vector<Point>>& nextPoint) {
    vector<Point> way;
    Point curPoint = start;
    way.push_back(curPoint);

    while (nextPoint[curPoint.x][curPoint.y] != PRIZE) {
        curPoint = nextPoint[curPoint.x][curPoint.y];
        way.push_back(curPoint);
    }

    cout << way.size() - 1 << '\n';
    for (auto point : way) {
        cout << point.x << ' ' << point.y << '\n';
    }
}

bool dealWithPoint(Point myPoint,
                   Point curPoint,
                   vector<vector<char>>& maze,
                   vector<vector<Point>>& prevPoint,
                   queue<Point>& myQueue) {
    if (maze[myPoint.x][myPoint.y] == 's') {
        prevPoint[myPoint.x][myPoint.y] = curPoint;
        recoverAnswer(myPoint, prevPoint);
        return true;
    }
    if (maze[myPoint.x][myPoint.y] == '0' && prevPoint[myPoint.x][myPoint.y] == NOT_VISITED) {
        myQueue.push(myPoint);
        prevPoint[myPoint.x][myPoint.y] = curPoint;
    }
    return false;
}

bool bfs(vector<vector<char>>& maze, Point prize) {
    vector<Point> pattern(maze[0].size(), NOT_VISITED);
    vector<vector<Point>> prevPoint(maze.size(), pattern);

    queue<Point> myQueue;
    myQueue.push(prize);
    prevPoint[prize.x][prize.y] = PRIZE;
    Point curPoint, p1, p2, p3, p4;

    while (!myQueue.empty()) {
        curPoint = myQueue.front();
        myQueue.pop();
        p1.changePoint(curPoint.x, curPoint.y - 1);
        p2.changePoint(curPoint.x - 1, curPoint.y);
        p3.changePoint(curPoint.x + 1, curPoint.y);
        p4.changePoint(curPoint.x, curPoint.y + 1);

        if (dealWithPoint(p1, curPoint, maze, prevPoint, myQueue) ||
            dealWithPoint(p2, curPoint, maze, prevPoint, myQueue) ||
            dealWithPoint(p3, curPoint, maze, prevPoint, myQueue) ||
            dealWithPoint(p4, curPoint, maze, prevPoint, myQueue)) {
            return true;
        }
    }
    cout << -1;
    return false;
}


int main() {
    vector<vector<char>> maze;
    Point prize = readData(maze);
    bfs(maze, prize);
    return 0;
}
