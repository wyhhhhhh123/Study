# include <stdio.h>
# include <stdlib.h>

typedef enum {Link, Thread} PointerTag;

//线索存储标志位
//Link(0), 表示左右孩子的指针
//T和read（1）， 表示指向前驱后继的线索

typedef struct BiThrNode
{
    char data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BiThrNode, *BiThrTree;

BiThrTree pre; //全局变量，始终指向刚刚访问过的节点
//创建一颗二叉树，约定用户遵照前序遍历的方式输入数据
void CreateBiThrTree(BiThrTree *T)
{
    char c;

    scanf("%c", &c);

    if(' ' == c)
    {
        *T = NULL;
    }
    else
    {
        *T = (BiThrNode *)malloc(sizeof(BiThrNode));
        (*T)->data = c;
        (*T)->ltag = Link;
        (*T)->rtag = Link;

        CreateBiThrTree(&(*T)->lchild);
        CreateBiThrTree(&(*T)->rchild);
    }
}

//中序遍历线索化
void InThreading(BiThrTree T)
{
    if(T)
    {
//        InThreading(T->lchild);  //递归左孩子线索化

        //节点处理
        if( !T->lchild)          //如果该节点无左孩子，设置ltag为Thread, 并把lchild指向刚刚访问的节点
        {
            T->ltag = Thread;
            T->lchild = pre;
        }
        if( !pre->rchild)
        {
            pre->rtag = Thread;
            pre->rchild = T;
        }

        pre = T;
        InThreading(T->lchild);
        InThreading(T->rchild);  //递归右孩子线索化
    }
}

void InOrderThreading(BiThrTree *p, BiThrTree T)
{
    *p = (BiThrTree)malloc(sizeof(BiThrNode));
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
        InThreading(T);
        pre->rchild = *p;
        pre->rtag = Thread;
        (*p)->rchild = pre;
    }
}

void visit(char c)
{
    printf("%c", c);
}

//中序遍历二叉树
void InOrderTraverse(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;

    while(p != T)
    {
        while(p->ltag == Link)
        {
            p = p->lchild;
        }
        visit(p->data);

        while(p->rtag == Thread && p->rchild != T)
        {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
}

//先序遍历
void FInOrderTraverse(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;

    while(p != T)
    {
        while(p->ltag == Link)
        {
            visit(p->data);
            p = p->lchild;
        }
        visit(p->data);
        if(p->ltag == Thread)
        {
            p = p->rchild;
        }
    }
}
int main(void)
{
    BiThrTree  p, T = NULL;
    printf("前序输入:  ");

    CreateBiThrTree( &T);

    InOrderThreading(&p, T);

    printf("先序遍历:  ");
    FInOrderTraverse(p);
    printf("中序遍历:  ");
    InOrderTraverse(p);
    return 0;
}
