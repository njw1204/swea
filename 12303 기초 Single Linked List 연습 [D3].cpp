#define MAX_NODE 10000

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init() {
    head = getNode(0);
    head->next = head;
}

void addNode2Head(int data) {
    Node* node = getNode(data);
    node->next = head->next;
    head->next = node;
}

void addNode2Tail(int data) {
    Node* ptr = head;

    while (ptr->next != head) {
        ptr = ptr->next;
    }

    Node* node = getNode(data);
    node->next = ptr->next;
    ptr->next = node;
}

void addNode2Num(int data, int num) {
    Node* ptr = head;

    for (int i = 0; i < num - 1; i++) {
        ptr = ptr->next;
    }

    Node* node = getNode(data);
    node->next = ptr->next;
    ptr->next = node;
}

void removeNode(int data) {
    Node* ptr = head;

    while (true) {
        if (ptr->next == head) {
            break;
        }

        if (ptr->next->data == data) {
            ptr->next = ptr->next->next;
        }

        ptr = ptr->next;
    }
}

int getList(int output[MAX_NODE]) {
    Node* ptr = head->next;
    int cnt = 0;

    for (int i = 0; ptr != head; i++) {
        output[i] = ptr->data;
        ptr = ptr->next;
        cnt++;
    }

    return cnt;
}
