
/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node // headnode 제외한 나머지 node 구조체
{
	int key;			// node별로 갖는 key 값
	struct Node *llink; // 왼쪽 node의 위치
	struct Node *rlink; // 오른쪽 node의 위치
} listNode;

typedef struct Head // headnode 구조체
{
	struct Node *first; // headnode가 가리키는 node가 실질적으로 key값을 가지는 첫번째 node가 됨
} headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode **h); // headnode 초기화하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode *h); // 연결리스트의 메모리를 모두 해제하는 함수

int insertNode(headNode *h, int key);  // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertLast(headNode *h, int key);  // list 마지막에 key에 대한 노드하나를 추가
int insertFirst(headNode *h, int key); // list 처음에 key에 대한 노드하나를 추가
int deleteNode(headNode *h, int key);  // list에서 key에 대한 노드 삭제
int deleteLast(headNode *h);		   // list의 마지막 노드 삭제
int deleteFirst(headNode *h);		   // list의 첫번째 노드 삭제
int invertList(headNode *h);		   // 리스트의 링크를 역순으로 재 배치

void printList(headNode *h); // 연결리스트 출력하는 함수

int main()
{
	char command;
	int key;
	headNode *headnode = NULL;

	do
	{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':
			initialize(&headnode);
			break;
		case 'p':
		case 'P':
			printList(headnode);
			break;
		case 'i':
		case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e':
		case 'E':
			deleteLast(headnode);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't':
		case 'T':
			deleteFirst(headnode);
			break;
		case 'r':
		case 'R':
			invertList(headnode);
			break;
		case 'q':
		case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode **h)
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)	  // headnode가 NULL이 아니라면
		freeList(*h); // freeList 함수를 이용해 기존 연결리스트 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode *)malloc(sizeof(headNode)); // headnode에 메모리 동적 할당
	(*h)->first = NULL;						   // headnode가 가리키고 있는 node는 null로 초기화
	return 1;								   // headnode 반환
}

int freeList(headNode *h)
{
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode *p = h->first; // headnode가 가리키는 node부터 시작

	listNode *prev = NULL; // 이전 node를 나타내는 구조체 선언 및 NULL로 초기화
	while (p != NULL)
	{				  // headnode가 가리키는 first node가 NULL일 때 까지
		prev = p;	  // 현재 일반 node 중 가장 앞에 있는 node를 prev에 대입하고
		p = p->rlink; // p가 앞에서 두번째에 있는 node로 변경됨
		free(prev);	  // 가장 앞에 있는 node 메모리 해제
	}
	free(h); // 마지막으로 headnode 메모리 해제 후 반환
}

void printList(headNode *h)
{				 // 연결리스트 출력하는 함수
	int i = 0;	 // node 개수 저장하는 변수
	listNode *p; // node 구조체

	printf("\n---PRINT\n"); // 안내문 출력

	if (h == NULL) // headnode가 NULL이면
	{
		printf("Nothing to print....\n"); // 안내문 출력 후 반환
		return;
	}

	p = h->first; // headnode가 NULL이 아니면 node구조체에 headnode가 가리키는 첫번째 node를 대입

	while (p != NULL) // p가 NULL일 때 까지
	{
		printf("[ [%d]=%d ] ", i, p->key); // i번째 node의 key를 출력
		p = p->rlink;					   // 출력한 node의 다음 node로 link 변경
		i++;							   // node 개수 증가
	}

	printf("  items = %d\n", i); // 출력한 node의 개수 출력
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
	node->key = key;									   // key값 저장
	node->rlink = NULL;									   // 오른쪽 node의 link는 null
	node->llink = NULL;									   // 왼쪽 node의 link는 null

	if (h->first == NULL) // headnode가 가리키는 node가 null이라면
	{
		h->first = node; // 새로운 node를 headnode가 가리키게 하고 반환 후 함수 종료
		return 0;
	}

	listNode *n = h->first;	 // headnode가 가리키는 node가 null이 아니면 node n을 선언하고 headnode가 가리키는 node를 대입
	while (n->rlink != NULL) // headnode가 가리키는 node의 오른쪽 node가 존재하는 동안 반복
	{
		n = n->rlink; // n node의 위치를 오른쪽 node로 변경, 마지막 node까지 반복하게 됨
	}
	n->rlink = node; // n node의 오른쪽 node link를 입력받은 node로 변경
	node->llink = n; // 입력받은 node의 왼쪽 node link를 n으로 변경
	return 0;		 // 반환 후 함수 종료
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{

	if (h->first == NULL) // headnode가 가리키는 node가 없을 경우
	{
		printf("nothing to delete.\n"); // 안내문 출력하고 반환 후 함수 종료
		return 0;
	}

	listNode *n = h->first; // node n 선언 및 headnode가 가리키는 node로 초기화
	listNode *trail = NULL; // node trail 선언 및 null로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->rlink == NULL) // headnode의 오른쪽 노드의 오른쪽 노드가 null이면
	{
		h->first = NULL; // headnode가 가리키는 node가 없도록 하고
		free(n);		 // 기존 가리키던 node는 메모리 해제 후 반환 후 함수 종료
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->rlink != NULL) // 마지막 노드까지 한칸씩 이동하면서
	{
		trail = n; // trail과 n의 위치를 한칸씩 오른쪽으로 이동
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; // n이 마지막 node, trail이 마지막 직전 node라는 것을 확인했으므로 trail의 오른쪽 node를 null로 하고
	free(n);			 // 원래 마지막 node였던 n을 메모리 해제

	return 0; // 반환 후 함수 종료
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적 할당
	node->key = key;									   // 새로운 node에 key값 저장
	node->rlink = node->llink = NULL;					   // 양쪽 node 주소는 null로 초기화

	if (h->first == NULL) // headnode가 가리키는 node가 없을 경우
	{
		h->first = node; // 만든 node가 headnode가 가리키는 node이도록 대입
		return 1;		 // 반환 후 함수 종료
	}

	node->rlink = h->first; // node의 오른쪽 node는 기존 headnode가 가리키던 node가 되도록 함
	node->llink = NULL;		// node의 왼쪽 node는 null

	listNode *p = h->first; // 새로운 node p를 만들고 headnode가 가리키는 node 대입
	p->llink = node;		// 기존에 headnode가 가리키는 노드가 가리키는 node가 왼쪽 node 주소로 이 함수의 node를 갖게 함
	h->first = node;		// 기존 headnode가 가리키는 노드는 이 함수의 node가 됨

	return 0; // 반환 후 함수 종료
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{

	if (h->first == NULL) // headnode가 가리키고 있는 node가 없으면
	{
		printf("nothing to delete.\n"); // 안내문 출력 후 반환 후 함수 종료
		return 0;
	}
	listNode *n = h->first; // 새로운 node 선언 및 headnode가 가리키고 있는 node로 초기화

	h->first = n->rlink; // headnode가 기존 headnode가 가리키고 있는 node의 오른쪽 node를 가리기도록 함

	free(n); // 기존 headnode가 가리키고 있는 node는 메모리 해제

	return 0; // 반환 후 함수 종료
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{

	if (h->first == NULL) // headnode가 가리키고 있는 node가 없으면
	{
		printf("nothing to invert...\n"); // 안내문 출력 후 반환 후 함수 종료
		return 0;
	}
	listNode *n = h->first;	 // node n 선언 및 headnode가 가리키고 있는 node로 초기화
	listNode *trail = NULL;	 // node trail 선언 및 null로 초기화
	listNode *middle = NULL; // node middle 선언 및 null로 초기화

	while (n != NULL) // 연결리스트가 끝날 때 까지
	{
		trail = middle; // 연속으로 이어진 세 node trail, middle, n 모두 한 칸씩 다음으로 이동 및 올바르게 가리키도록 수정
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle; // headnode가 가리키고 있는 node를 middle로 변경, 이로써 연결리스트가 역순으로 배치됨

	return 0; // 반환 후 함수 종료
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 새로운 node 선언 및 메모리 동적할당
	node->key = key;									   // 새로운 node에 key값 저장
	node->llink = node->rlink = NULL;					   // 새 node의 왼쪽, 오른쪽 node는 아직 null

	if (h->first == NULL) // headnode가 가리키는 node가 없으면
	{
		h->first = node; // 새로운 node가 headnode가 가리키는 node가 되고 반환 후 함수 종료
		return 0;
	}

	listNode *n = h->first; // n에 headnode가 가리키는 node 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL)
	{
		if (n->key >= key)
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first) // 첫 노드 앞에 삽입해야 한다면
			{
				insertFirst(h, key); // insertFirst 함수를 이용해 첫 노드 앞에 삽입
			}
			else
			{					 /* 중간이거나 마지막인 경우 */
				node->rlink = n; // node를 n과 n의 왼쪽 노드 사이에 끼움
				node->llink = n->llink;
				n->llink->rlink = node; // 왼쪽 node의 오른쪽 node가 자기 자신이 되도록 수정
			}
			return 0; // 반환 후 함수종료
		}

		n = n->rlink; // n node는 오른쪽 node가 됨
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // insertLast 함수를 이용해 마지막 노드로 삽입
	return 0;			// 반환 후 함수 종료
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{
	if (h->first == NULL) // headnode가 가리키는 node가 없을 경우
	{
		printf("nothing to delete.\n"); // 안내문 출력하고 함수 종료
		return 0;
	}

	listNode *n = h->first; // node n 선언 후 headnode가 가리키는 node로 초기화

	while (n != NULL) // n이 null일 때 까지 n으ㅐ 위치를 한칸씩 다음으로 이동하면서 반복
	{
		if (n->key == key)
		{
			if (n == h->first)
			{					/* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 함수를 이용해 맨 왼쪽 노드 삭제
			}
			else if (n->rlink == NULL)
			{				   /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 함수를 이용해 맨 오른쪽 노드 삭제
			}
			else
			{								/* 중간인 경우 */
				n->llink->rlink = n->rlink; // 양쪽 노드들이 서로의 주소를 갖도록 함
				n->rlink->llink = n->llink;
				free(n); // 기존 중간 노드 메모리 해제
			}
			return 1; // 반환 후 함수 종료
		}

		n = n->rlink; // key값이 일치하지 않으면 다음 node 탐색 시작
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 안내문 출력 후 반환 후 함수 종료
	return 1;
}
