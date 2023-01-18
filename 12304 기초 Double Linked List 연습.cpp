#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init() {
	head = getNode(0);
	head->prev = head;
	head->next = head;
}

void addNode2Head(int data) {
	Node* node = getNode(data);
	node->prev = head;
	node->next = head->next;
	head->next->prev = node;
	head->next = node;
}

void addNode2Tail(int data) {
	Node* node = getNode(data);
	Node* tail = head->prev;
	node->prev = tail;
	node->next = tail->next;
	tail->next->prev = node;
	tail->next = node;
}

void addNode2Num(int data, int num) {
	Node* ptr = head;

	for (int i = 0; i < num - 1; i++) {
		ptr = ptr->next;
	}

	Node* node = getNode(data);
	node->prev = ptr;
	node->next = ptr->next;
	ptr->next->prev = node;
	ptr->next = node;
}

int findNode(int data) {
	Node* ptr = head->next;

	for (int index = 1; ptr != head; index++) {
		if (ptr->data == data) {
			return index;
		}

		ptr = ptr->next;
	}

	return -1;
}

void removeNode(int data) {
	Node* ptr = head->next;

	while (ptr != head) {
		if (ptr->data == data) {
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
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

int getReversedList(int output[MAX_NODE]) {
	Node* ptr = head->prev;
	int cnt = 0;

	for (int i = 0; ptr != head; i++) {
		output[i] = ptr->data;
		ptr = ptr->prev;
		cnt++;
	}

	return cnt;
}
