// <Doubly Circular linked list>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // (typedef를 사용하여) Node 구조체 생성
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

// 함수 리스트
int initialize(listNode** h); // note: initialize는 이중포인터를 매개변수로 받음
int freeList(listNode* h); // note: freeList는 싱글포인터를 매개변수로 받음
int insertLast(listNode* h, int key); // list에 key에 대한 노드 추가
int deleteLast(listNode* h); // list의 마지막 노드 삭제
int insertFirst(listNode* h, int key); // list 처음에 key에 대한 노드 추가
int deleteFirst(listNode* h); // list의 첫번째 노드 삭제
int invertList(listNode* h); // list의 link를 역순으로 재배치

int insertNode(listNode* h, int key); // list 검색 후, 노드 삽입
int deleteNode(listNode* h, int key); // list에 key에 대한 노드 삭제

void printList(listNode* h); // list 출력

int main()
{
	char command; // 변수 command
	int key; // 변수 key
	listNode* headnode=NULL;

    printf("[----- [Kim Yun Seo]  [2020021016] -----]\n"); // [이름] [학번] 출력

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z':  // command 값이 z 또는  일 경우
			initialize(&headnode);
			break;
		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			printList(headnode);
			break;
		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // command 값이 n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // command 값이 e 또는 E 일 경우
			deleteLast(headnode);
			break;
		case 'f': case 'F': // command 값이 f 또는 F 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // command 값이 t 또는 T 일 경우
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // command 값이 r 또는 R 일 경우
			invertList(headnode);
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행

	return 1;
}

int initialize(listNode** h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL) // headNode가 NULL이 아님
		freeList(*h); // 메모리 해제

	// headNode에 대한 메모리를 할당하여 리턴 
	*h = (listNode*)malloc(sizeof(listNode));  // *h에 'headNode' 타입으로 주소 받기
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)
	{
		free(h); // headNode 메모리 해제
		return 1;
	}

	// h와 연결된 listNode 메모리 해제
	// headNode도 해제되어야 함
	listNode* p = h->rlink;
	listNode* prev = NULL;

	while(p != NULL && p != h) { // p가 NULL이 아닐 경우
		prev = p;
		p = p->rlink;
		free(prev); // listNode 메모리 해제
	}
	free(h); // headNode 메모리 해제
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // headNode가 NULL일 경우
		printf("Nothing to print....\n"); // (NULL임을 알림)
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) { // listNode가 NULL이 아닐 경우
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	// print addresses
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { // listNode가 NULL이 아닐 경우
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

// list에 key에 대한 노드하나를 추가
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // listNode가 NULL일 경우

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' 타입으로 주소 받기
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) // 첫 노드로 삽입 
	{
		h->rlink = node; // 노드 추가
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node; // 노드 추가
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}


// list의 마지막 노드 삭제
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // listNode가 NULL일 경우
	{
		printf("nothing to delete.\n"); // (NULL임을 알림)
		return 1;
	}

	listNode* nodetoremove = h->llink;

	// link 정리 
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove); // 노드 삭제

	return 1;
}

// list 처음에 key에 대한 노드하나를 추가
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' 타입으로 주소받기
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	node->rlink = h->rlink;
	h->rlink->llink = node; // 노드 추가
	node->llink = h;
	h->rlink = node; // 노드 추가

	return 1;
}

// list의 첫번째 노드 삭제
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // listNode가 NULL일 경우
	{
		printf("nothing to delete.\n"); // (NULL임을 알림)
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	// link 정리 
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove); // 노드 삭제
	return 1;

}

// 리스트의 링크를 역순으로 재 배치
int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) { // listNode가 NULL일 경우
		printf("nothing to invert...\n"); // (역순으로 재배치할 내용이 없다고 알림)
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	// 최종 바뀔 링크 유지
	h->llink = h->rlink;

	while(n != NULL && n != h){ //listNode가 NULL이 아닐 경우
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle; // 역순으로 재배치
	return 0;
}

// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' 타입으로 주소받기
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	// key를 기준으로 삽입할 위치를 찾는다 
	while(n != NULL && n != h) {
		if(n->key >= key) {
			// 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { // 중간이거나 마지막인 경우 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node; // 노드 추가
			}
			return 0;
		}
		n = n->rlink;
	}

	// 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 
	insertLast(h, key); // 마지막에 노드 추가
	return 0;
}

// list에서 key에 대한 노드 삭제
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) // listNode가 NULL일 경우
	{
		printf("nothing to delete.\n"); // (NULL임을 알림)
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) { // n이 NULL이 아닐 경우
		if(n->key == key) {
			if(n == h->rlink) { // 첫 노드째 노드 인경우 
				deleteFirst(h); // 첫번째 노드 삭제
			} else if (n->rlink == h){ // 마지막 노드인 경우 
				deleteLast(h); // 마지막 노드 삭제
			} else { // 중간인 경우
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); // 노드 삭제
			}
			return 0;
		}
		n = n->rlink;
	}

	// 찾지 못 한경우
	printf("cannot find the node for key = %d\n", key);
	return 0;
}
