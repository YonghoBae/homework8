/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- [Yongho Bae] [2020039008] -----]\n");

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
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	/* 현재 노드, 이전 노드 포인터 선언 및 초기화*/
	listNode *p=h,*prev=NULL;
	/* prev 메모리해제하고 p로 이동 반복*/
	do{
		prev=p;
		p=p->rlink;
		free(prev);
	}while(p!=h);
	/*헤드노드 메모리해제*/
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	/*노드 메모리할당 및 초기화*/
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	/*node 연결*/
	node->llink = h->llink;
	node->rlink = h->llink->rlink;
	h->llink->rlink = node;
	h->llink = node;
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	/*마지막 노드를 가리키는 포인터 last 선언 및 초기화*/
	listNode *last=h->llink;
	/*리스트가 비어있을 경우 종료*/
	if(h == h->rlink){
		printf("list is empty!\n");
		return 1;
	}
	/*마지막 노드 이전 노드를 헤드노드와 연결*/
	h->llink = h->llink->llink;
	h->llink->rlink = h;
	/*마지막 노드 메모리할당 해제*/
	free(last);
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	/*노드 메모리할당 및 초기화*/
	listNode *node=(listNode*)malloc(sizeof(listNode));
	node->key=key;
	/*node 연결*/
	node->llink=h;
	node->rlink=h->rlink;
	h->rlink=node;
	node->rlink->llink = node;
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	/*첫번째 노드를 가리키는 포인터 first 선언 및 초기화*/
	listNode *first=h->rlink;
	/*리스트가 비어있을 경우 종료*/
	if(h == h->rlink){
		printf("list is empty!\n");
		return 1;
	}
	/*첫번째 노드 다음 노드를 헤드노드와 연결*/
	h->rlink=h->rlink->rlink;
	h->rlink->llink=h;
	/*첫번째 노드 메모리할당 해제*/
	free(first);
	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	/*이전 노드, 현재 노드를 가리키는 포인터 선언 및 초기화*/
	listNode *prev=NULL, *curr=h;
	/*링크를 역으로 연결*/
	do{
		prev = curr;
		curr = curr->rlink;
		prev->rlink = prev->llink;
		prev->llink = curr;
	}while(curr!=h);
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	/*비어있는 리스트일 경우*/
	if(h->rlink==h){
		insertFirst(h,key);
		return 0;
	}

	/*노드 메모리할당 및 초기화, 노드 탐색을 위한 포인터 search 선언 및 초기화*/
	listNode *node=(listNode*)malloc(sizeof(listNode));
	listNode *search=h->rlink;
	node->key=key;
	node->llink=node->rlink=NULL;
	/*입력받은 key보다 큰값이 나오기 전까지 반복, 끝까지 탐색했을 때 큰값이 없으면 탈출*/
	while(search->key<key){
		if(search == h){
			break;
		}
		search=search->rlink;
	}

	/*찾은 위치에 노드 링크 연결*/
	node->rlink=search;
	node->llink=search->llink;
	search->llink->rlink=node;
	search->llink=node;
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	/*삭제할 노드를 탐색할 포인터 search 선언 및 초기화*/
	listNode *search=h->rlink;
	/*비어있는 리스트일 경우*/
	if(h->rlink==h){
		printf("list is empty!\n");
		return 0;
	}
	/*입력받은 key가 나오기 전까지 반복, 끝까지 탐색했을 때 key값이 없으면 함수종료*/
	while(search->key!=key){
		search = search->rlink;
		if(search==h){
			printf("key:%d does not exist in list\n");
			return 0;
		}
	}
	/*찾은 노드의 연결 끊고 메모리할당 해제*/
	search->llink->rlink = search->rlink;
	search->rlink->llink = search->llink;
	free(search);
	return 0;
}
