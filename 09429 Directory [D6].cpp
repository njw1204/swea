#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

int folderHash[50005];
int subDirCount[50005];
int parent[50005];
int children[50005][30];
int childrenNo[50005];
int treeNextNode;

int calcFolderHash(char name[NAME_MAXLEN + 1]) {
    int base = 1;
    int hash = 0;

    for (int i = 0; name[i]; i++) {
        hash += base * (name[i] - 'a');
        base *= 26;
    }

    return hash;
}

int findPathNode(char path[PATH_MAXLEN + 1], int dirOutput[50005], int subDirCountAdder = 0) {
    int curNode = 1;
    char searchValue[10] = {0};
    int searchValuePtr = 0;
    int dirOutputPtr = 0;

    subDirCount[1] += subDirCountAdder;

    if (dirOutput) {
        dirOutput[dirOutputPtr++] = 1;
    }

    for (int i = 0; path[i]; i++) {
        if (path[i] == '/') {
            searchValue[searchValuePtr] = '\0';

            if (searchValue[0]) {
                int searchHash = calcFolderHash(searchValue);

                for (int j = 0; j < 30; j++) {
                    if (children[curNode][j]
                        && searchHash == folderHash[children[curNode][j]]) {
                        curNode = children[curNode][j];
                        break;
                    }
                }

                subDirCount[curNode] += subDirCountAdder;

                if (dirOutput) {
                    dirOutput[dirOutputPtr++] = curNode;
                }
            }

            searchValuePtr = 0;
            continue;
        }

        searchValue[searchValuePtr++] = path[i];
    }

    return curNode;
}

void init(int n) {
    for (int i = 0; i <= n; i++) {
        folderHash[i] = 0;
        subDirCount[i] = 0;
        parent[i] = 0;
        childrenNo[i] = 0;
        
        for (int j = 0; j < 30; j++) {
            children[i][j] = 0;
        }
    }

    treeNextNode = 2;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    int dirOutput[1005] = {0};
    folderHash[treeNextNode] = calcFolderHash(name);
    parent[treeNextNode] = findPathNode(path, dirOutput, 1);

    for (int i = 0; i < 30; i++) {
        if (!children[parent[treeNextNode]][i]) {
            children[parent[treeNextNode]][i] = treeNextNode;
            childrenNo[treeNextNode] = i;
            break;
        }
    }

    treeNextNode++;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    int dirOutput[1005] = {0};
    int curNode = findPathNode(path, dirOutput);

    if (curNode == 1) {
        return;
    }

    for (int i = 0; i < 1005; i++) {
        if (dirOutput[i] == curNode) {
            break;
        }

        subDirCount[dirOutput[i]] -= subDirCount[curNode] + 1;
    }

    children[parent[curNode]][childrenNo[curNode]] = 0;
    parent[curNode] = 0;
}

void cmd_cp_dfs(int srcNode, int dstNode) {
    int nowNode = treeNextNode;
    folderHash[treeNextNode] = folderHash[srcNode];
    parent[nowNode] = dstNode;
    subDirCount[nowNode] = subDirCount[srcNode];

    for (int i = 0; i < 30; i++) {
        if (!children[parent[nowNode]][i]) {
            children[parent[nowNode]][i] = nowNode;
            childrenNo[nowNode] = i;
            break;
        }
    }

    treeNextNode++;

    for (int i = 0; i < 30; i++) {
        if (children[srcNode][i]) {
            cmd_cp_dfs(children[srcNode][i], nowNode);
        }
    }
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    int srcNode = findPathNode(srcPath, nullptr);
    int dstNode = findPathNode(dstPath, nullptr, subDirCount[srcNode] + 1);
    cmd_cp_dfs(srcNode, dstNode);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    int dirOutput[1005] = {0};
    int srcNode = findPathNode(srcPath, dirOutput);
    int diff = subDirCount[srcNode] + 1;
    int dstNode = findPathNode(dstPath, nullptr, diff);

    for (int i = 0; i < 1005; i++) {
        if (dirOutput[i] == srcNode) {
            break;
        }

        subDirCount[dirOutput[i]] -= diff;
    }

    children[parent[srcNode]][childrenNo[srcNode]] = 0;
    parent[srcNode] = dstNode;

    for (int i = 0; i < 30; i++) {
        if (!children[parent[srcNode]][i]) {
            children[parent[srcNode]][i] = srcNode;
            childrenNo[srcNode] = i;
            break;
        }
    }
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    int curNode = findPathNode(path, nullptr);
    return subDirCount[curNode];
}
