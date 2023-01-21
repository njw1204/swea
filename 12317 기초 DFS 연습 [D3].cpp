int children[105][10];

void dfs_init(int N, int path[100][2]) {
    for (int i = 0; i < 105; i++) {
        for (int j = 0; j < 10; j++) {
            children[i][j] = 0;
        }
    }

    for (int i = 0; i < N - 1; i++) {
        int parent = path[i][0];
        int child = path[i][1];

        for (int j = 0; j < 10; j++) {
            if (!children[parent][j]) {
                children[parent][j] = child;
                break;
            }
        }
    }
}

int dfs(int n) {
    int result[100] = {0};
    int resultPtr = 0;
    int stack[100] = {0};
    int top = 0;

    stack[top++] = n;

    while (top > 0) {
        int cur = stack[--top];

        if (cur != n) {
            result[resultPtr++] = cur;
        }

        for (int i = 9; i >= 0; i--) {
            if (children[cur][i]) {
                stack[top++] = children[cur][i];
            }
        }
    }

    for (int i = 0; i < resultPtr; i++) {
        if (result[i] > n) {
            return result[i];
        }
    }

    return -1;
}
