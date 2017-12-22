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
BOOL addList(List *lp, Node temp);
BOOL deleteList(List *lp, int num);
int searchList(List *lp, int num);

int main()
{


}

BOOL createList(List *lp)
{
	Node headNode;
	Node tailNode;
	*(lp->head) = headNode;
	*(lp->tail) = tailNode;
	lp->cnt = 0;
	*(lp->head->prev) = headNode;
	*(lp->head->next) = tailNode;
	*(lp->tail->prev) = headNode;
	*(lp->tail->next) = tailNode;
	return TRUE;
}

BOOL addList(List *lp, Node temp)
{
	Node *tp=NULL, *ap=NULL;
	
	if (lp->head->next == lp->tail)
	{
		//아무것도 없어요
		tp = lp->head->next;
		*(lp->head->next) = temp;
		temp.prev = lp->head;
		temp.next = tp;
		*(tp->prev) = temp;
	}

	else
	{
		tp = lp->tail->prev;
		*(tp->next) = temp;
		*(lp->tail->prev) = temp;
		temp.prev = tp->next;
		temp.next = lp->tail;
	}

	lp->cnt++;
	return TRUE;
}

BOOL deleteList(List *lp, int num)
{
	Node *tp = NULL;
	Node *sp = NULL;
	int i;
	int findNum = searchList(lp, num);
	if (findNum == 0)
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
		tp = lp->head;
		for (i = 0; i < findNum; i++)
		{
			tp = tp->next;
		}
		sp = tp->prev;
		sp->next = tp->next;
		tp->next->prev = sp;
		free(sp);
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
		return 0;
	}

	for (i = 0; i < lp->cnt;i++)
	{
		if (tp->data == num)
		{
			return i;
		}
	}

	return -1;
}

