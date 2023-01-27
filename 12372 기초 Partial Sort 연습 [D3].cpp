template<typename T>
struct MaxHeap {
    int n = 0;
    T arr[100005];

    void push(const T& t) {
        n++;
        arr[n] = t;

        for (int i = n; i > 1; i /= 2) {
            if (arr[i / 2] < arr[i]) {
                T temp = arr[i / 2];
                arr[i / 2] = arr[i];
                arr[i] = temp;
            }
            else {
                break;
            }
        }
    }

    T top() {
        return arr[1];
    }

    void pop() {
        if (size() == 0) {
            return;
        }

        arr[1] = arr[n];
        n--;

        for (int i = 1; ;) {
            bool checkLeft = false, checkRight = false;

            if (i * 2 <= n && arr[i] < arr[i * 2]) {
                checkLeft = true;
            }

            if (i * 2 + 1 <= n && arr[i] < arr[i * 2 + 1]) {
                checkRight = true;
            }

            if (checkLeft && checkRight) {
                if (arr[i * 2] < arr[i * 2 + 1]) {
                    checkLeft = false;
                }
                else {
                    checkRight = false;
                }
            }

            if (!checkLeft && !checkRight) {
                break;
            }
            else if (checkLeft) {
                T temp = arr[i];
                arr[i] = arr[i * 2];
                arr[i * 2] = temp;
                i = i * 2;
            }
            else {
                T temp = arr[i];
                arr[i] = arr[i * 2 + 1];
                arr[i * 2 + 1] = temp;
                i = i * 2 + 1;
            }
        }
    }

    int size() {
        return n;
    }

    void clear() {
        n = 0;
    }
};

struct User {
    int uID;
    int height;

    bool operator<(const User& other) {
        if (height != other.height) {
            return height < other.height;
        }

        return uID > other.uID;
    }
};

MaxHeap<User> pq;

void init() {
    pq.clear();
}

void addUser(int uID, int height) {
    pq.push({uID, height});
}

int getTop10(int result[10]) {
    User users[10];
    int count = (pq.size() > 10 ? 10 : pq.size());

    for (int i = 0; i < count; i++) {
        users[i] = pq.top();
        result[i] = users[i].uID;
        pq.pop();
    }

    for (int i = 0; i < count; i++) {
        pq.push(users[i]);
    }

    return count;
}
