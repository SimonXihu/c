#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

typedef struct TREE
{
	char ch;
	struct TREE* lchild;
	struct TREE* rchild;
}Tree;

void binarytree_print(Tree* root)
{
	if(root == NULL)
	{
		return;
	}
	printf("%c ",root->ch);
	binarytree_print(root->lchild);
	binarytree_print(root->rchild);
	
}

void CaculateLeafNum(Tree* root,int* num)
{
	if(root == NULL)
	{
		return;
	}
	if(root->lchild == NULL && root->rchild == NULL)
	{
		(*num)++;
	}
	CaculateLeafNum(root->lchild,num);
	CaculateLeafNum(root->rchild,num);
}

int CaculateTreeDepth(Tree* root)
{
	if(root == NULL)
	{
		return 0;
	}
	
	int leftDepth = CaculateTreeDepth(root->lchild);
	int rightDepth = CaculateTreeDepth(root->rchild);
	
	int depth = leftDepth > rightDepth ? leftDepth +1 : rightDepth + 1;
	return depth;
}
void test01()
{
	Tree A,B,C,D,E,F,G,H;
	
	A.ch = 'A';
	B.ch = 'B';
	C.ch = 'C';
	D.ch = 'D';
	E.ch = 'E';
	F.ch = 'F';
	G.ch = 'G';
	H.ch = 'H';
	
	H.lchild = NULL;
	H.rchild = NULL;
	G.lchild = &H;
	G.rchild = NULL;
	F.lchild = NULL;
	F.rchild = &G;
	E.lchild = NULL;
	E.rchild = NULL;
	D.lchild = NULL;
	D.rchild = NULL;
	C.lchild = &D;
	C.rchild = &E;
	B.lchild = NULL;
	B.rchild = &C;
	A.lchild = &B;
	A.rchild = &F;
	
	binarytree_print(&A);
	printf("\n");
	
	int num = 0;
	CaculateLeafNum(&A,&num);
	printf("CaculateLeafNum:num = %d\n",num);
	printf("CaculateTreeDepth: %d\n",CaculateTreeDepth(&A));
}
int main(int argc,char* argv[])
{
	printf("-----tree test main -----\n");
	test01();
	return 0;
}