# include <stdio.h>
# include <stdlib.h>

typedef enum {Link, Thread} PointerTag;

//�����洢��־λ
//Link(0), ��ʾ���Һ��ӵ�ָ��
//T��read��1���� ��ʾָ��ǰ����̵�����

typedef struct BiThrNode
{
    char data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BiThrNode, *BiThrTree;

BiThrTree pre; //ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľڵ�
//����һ�Ŷ�������Լ���û�����ǰ������ķ�ʽ��������
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

//�������������
void InThreading(BiThrTree T)
{
    if(T)
    {
//        InThreading(T->lchild);  //�ݹ�����������

        //�ڵ㴦��
        if( !T->lchild)          //����ýڵ������ӣ�����ltagΪThread, ����lchildָ��ոշ��ʵĽڵ�
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
        InThreading(T->rchild);  //�ݹ��Һ���������
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

//�������������
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

//�������
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
    printf("ǰ������:  ");

    CreateBiThrTree( &T);

    InOrderThreading(&p, T);

    printf("�������:  ");
    FInOrderTraverse(p);
    printf("�������:  ");
    InOrderTraverse(p);
    return 0;
}
