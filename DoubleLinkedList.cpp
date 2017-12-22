#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum BOOL {TRUE,FALSE};

typedef struct Node{
	Node *prev;
	int data;
	Node *next;
}node;

typedef struct List {
	Node *head;
	Node *tail;
	int cnt;
}list;

BOOL createList(List *lp);
BOOL addList(List *lp);
BOOL deleteList(List *lp);
int searchList(List *lp, int cnt);
void printList(List *lp);
void destoryList(List *lp);

int main()
{
	int i;
	int num;
	List lp;
	char menuList[4][10] = { "1. ADD","2. DELETE","3. PRINT","4. EXIT" };
	if(createList(&lp)==FALSE)
		return -1;
	while (1)
	{
		for (i = 0; i < 4; i++)
		{
			printf("%s\n", menuList[i]);
		}
		printf("Choose the Menu >> ");
		scanf("%d", &num);
		switch (num)
		{
		case 1 : addList(&lp); break;
		case 2 : deleteList(&lp); break;
		case 3 : printList(&lp); break;
		case 4 : return 0; break;
		}
	}
	return 0;

}

BOOL createList(List *lp)
{
	Node *headNode = NULL;
	Node *tailNode = NULL;
	headNode = (Node*)malloc(sizeof(Node));
	if (headNode == NULL)
	{
		printf("Memory Allocated is failed\n");
		return FALSE;
	}
	tailNode = (Node*)malloc(sizeof(Node));
	if (tailNode == NULL)
	{
		printf("Memory Allocated is failed\n");
		free(headNode);
		return FALSE;
	}

	lp->head = headNode;
	lp->tail = tailNode;
	lp->head->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;
	lp->cnt = 0;
	return TRUE;
}

BOOL addList(List *lp)
{
	Node *tp=NULL, *ap=NULL;
	tp = (Node*)malloc(sizeof(Node));
	if (tp == NULL)
	{
		printf("Can't allocate memory\n");
		return FALSE;
	}

	printf("Enter Your Number >>");
	scanf("%d", &(tp->data));

	if (lp->head->next == lp->tail)
	{
		lp->head->next = tp;
		tp->next = lp->tail;
		tp->prev = lp->head;
		lp->tail->prev = tp;
	}

	else
	{
		ap = lp->tail->prev;
		ap->next = tp;
		tp->prev = ap;
		tp->next = lp->tail;
		lp->tail->prev = tp;
	}
	lp->cnt++;
	return TRUE;
}

BOOL deleteList(List *lp)
{
	Node *tp = NULL;
	Node *sp = NULL;
	int i;
	int num;
	printf("Enter a number that you want delete >> ");
	scanf("%d", &num);
	int findNum = searchList(lp, num);
	if (findNum == -2)
	{
		printf("List is empty\n");
		return FALSE;
	}
	else if (findNum == -1)
	{
		printf("Not Have %d in LIST\n", num);
		return FALSE;
	}
	else
	{
		tp = lp->head->next;
		for (i = 0; i < findNum; i++)
		{
			tp = tp->next;
		}
		sp = tp->prev;
		sp->next = tp->next;
		tp->next->prev = sp;
		free(tp);
		lp->cnt--;
		return TRUE;
	}

}

int searchList(List *lp, int num)
{
	int i;
	Node *tp = lp->head->next;
	if (lp->head->next == lp->tail)
	{
		return -2;
	}

	for (i = 0; i < lp->cnt;i++)
	{
		if (tp->data == num)
		{
			return i;
		}
		tp = tp->next;
	}

	return -1;
}

void printList(List *lp)
{
	Node *tp = lp->head->next;
	if (lp->head->next == lp->tail)
	{
		printf("There are nothing in LIST\n");
		return;
	}

	while (tp != lp->tail)
	{
		printf("%d ", tp->data);
		tp = tp->next;
	}
	printf("\n");
}

void destroyList(List *lp)
{
	int i;
	Node *tp = lp->head->next;
	while (tp != lp->tail)
	{
		tp->prev->next = tp->next;
		tp->next->prev = tp->prev;
		free(tp);
	}
	free(lp->head);
	free(lp->tail);

	return;
}