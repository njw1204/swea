int field[15][15];

void bfs_init(int map_size, int map[10][10]) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            field[i][j] = 0;
        }
    }

    for (int i = 1; i <= map_size; i++) {
        for (int j = 1; j <= map_size; j++) {
            field[i][j] = map[i - 1][j - 1] + 1;
        }
    }
}

int bfs(int x1, int y1, int x2, int y2) {
    int temp;
    temp = x1;
    x1 = y1;
    y1 = temp;
    temp = x2;
    x2 = y2;
    y2 = temp;

    int visited[15][15] = {0};
    int q[105][2] = {0};
    int begin = 0, end = 0;

    q[end][0] = x1;
    q[end][1] = y1;
    visited[x1][y1] = 1;
    end++;

    while (end > begin) {
        int curX = q[begin][0];
        int curY = q[begin][1];
        begin++;

        if (curX == x2 && curY == y2) {
            break;
        }

        int dxs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < 4; i++) {
            int nextX = curX + dxs[i][0];
            int nextY = curY + dxs[i][1];

            if (field[nextX][nextY] == 1 && !visited[nextX][nextY]) {
                q[end][0] = nextX;
                q[end][1] = nextY;
                visited[nextX][nextY] = visited[curX][curY] + 1;
                end++;
            }
        }
    }

    if (!visited[x2][y2]) {
        return -1;
    }

    return visited[x2][y2] - 1;
}
