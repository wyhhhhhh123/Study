# include <stdio.h>
# include <stdlib.h>

typedef enum {Link, Thread} PointerTag;

typedef struct node
{
    char data;
    struct node *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}node, *nodetree;

nodetree pre = NULL;

void CreateBiThrTree(nodetree *T)        //先序创建二叉树
{
    char c;
    scanf("%c", &c);

    if(' ' == c)
    {
        *T = NULL;
    }
    else
    {
         *T = (nodetree)malloc(sizeof(node));
        (*T)->data = c;
        (*T)->ltag = Link;
        (*T)->rtag = Link;

        CreateBiThrTree(&(*T)->lchild);
        CreateBiThrTree(&(*T)->rchild);
    }
}

void InOrderThreading(nodetree T)
{
    if(T)
    {
        if(!T->lchild)
        {
            T->lchild = pre;
            T->ltag = Thread;
        }
        if(!pre->rchild)
        {
            pre->rchild = T;
            pre->rtag = Thread;
        }

        InOrderThreading(T->lchild);
        InOrderThreading(T->rchild);
    }
}

void InThreading(nodetree *p, nodetree T)
{
    *p = (nodetree)malloc(sizeof(node));
    (*p)->ltag = Link;
    (*p)->rtag = Thread;
    (*p)->rchild = *p;
    if(!T)
    {
        (*p)->lchild = *p;
    }
    else
    {
        (*p)->lchild = T;
        pre = *p;
        InOrderThreading(T);
        pre->rchild = *p;
        pre->rtag = Thread;
        (*p)->rchild = pre;
    }
}

void visit(char c)
{
    printf("%c", c);
}

void FInOrderTraverse(nodetree T)
{
    nodetree p;
    p = T->lchild;

    while(p != T)
    {
        while(p->ltag == Link)
        {
            visit(p->data);
            p = p->lchild;
        }
        visit(p->data);
        p = p->rchild;
    }
}

int main(void)
{

    nodetree p, T = NULL;
    printf("前序输入:  ");

    CreateBiThrTree( &T);

    InThreading(&p, T);

    printf("先序遍历:  ");

    FInOrderTraverse(p);

    return 0;
}
