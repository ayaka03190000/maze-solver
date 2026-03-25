#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
int W, H;
vector<vector<char>>maze;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
mt19937 gen(time(0));

void dfs(int y, int x) {

    vector<int>dir = { 0,1,2,3 };
    shuffle(dir.begin(), dir.end(), gen);
    for (int i = 0;i < 4;i++) {
        int d = dir[i];
        int ny = y + dy[d] * 2;
		int nx = x + dx[d] * 2;
		if (ny <= 0 || ny >= H - 1 || nx <= 0 || nx >= W - 1)continue;
        if (maze[ny][nx] == '.')continue;
		maze[y + dy[d]][x + dx[d]] = '.';
		maze[ny][nx] = '.';
        dfs(ny, nx);
    }
}

int main()
{
    cout << "迷路の横の長さ=";
    cin >> W;
    cout << "迷路の縦の長さ=";
    cin >> H;

    int sy, sx;
    cout << "スタート位置x座標（1-" << W - 2 << "）=";
    cin >> sx;
    cout << "スタート位置y座標（1-" << H - 2 << "）=";
    cin >> sy;

    maze=vector<vector<char>>(H, vector<char>(W, '#'));
    maze[sy][sx] = '.';
    dfs(sy, sx);

    queue<pair<int, int>>q;
    vector<vector<int>>dist(H, vector<int>(W, -1));
    vector<vector<pair<int, int>>>prev(H, vector<pair<int, int>>(W, { -1,-1 }));
    q.push({ sy,sx });
    dist[sy][sx] = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int y = p.first;
        int x = p.second;
        for (int i = 0;i < 4;i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || ny >= H || nx < 0 || nx >= W)continue;
            if (maze[ny][nx] == '#')continue;
            if (dist[ny][nx] != -1)continue;
            dist[ny][nx] = dist[y][x] + 1;
            prev[ny][nx] = { y,x };
            q.push({ ny,nx });
        }
    }

    int maxdist = -1;
    int gy = sy, gx = sx;
    for (int y = 0;y < H;y++) {
        for (int x = 0;x < W;x++) {
            if (dist[y][x] > maxdist) {
                maxdist = dist[y][x];
                gy = y;
                gx = x;
            }
        }
    }
    maze[sy][sx] = 'S';
    maze[gy][gx] = 'G';

    auto original = maze;
    for (int i = 0;i < H;i++) {
        for (int j = 0;j < W;j++) {
            cout << original[i][j];
        }
        cout << endl;
    }

    int y = gy;
    int x = gx;
    while (!(y == sy && x == sx)) {
        auto p = prev[y][x];
        if (maze[y][x] != 'G') {
            maze[y][x] = 'o';
        }
        y = p.first;
        x = p.second;
    }

    cout << "Enterを押して解答を見る";
    cin.ignore();
    cin.get();
    cout << "===解答===" << endl;

    for (int i = 0;i < H;i++) {
        for (int j = 0;j < W;j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}