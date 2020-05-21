#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node1
{
    char c;
    int p;
    struct node1 *n1;
}node1;

typedef struct node2
{
    double d;
    struct node2 *n2;
}node2;

void push1(node1 **h, char ch)
{
    node1 *t=malloc(sizeof(node1));
    t->n1=*h;
    t->c=ch;
    if(ch=='=')
        t->p=1;
    if(ch=='(')
        t->p=2;
    if((ch=='+')||(ch=='-'))
        t->p=3;
    if((ch=='*')||(ch=='/'))
        t->p=4;
    *h=t;
}

void push2(node2 **h, double dd)
{
    node2 *t=malloc(sizeof(node2));
    t->n2=*h;
    t->d=dd;
    *h=t;
}


void output(node2 *h)
{
    if(h)
    {
        printf("%lf ",h->d);
        output(h->n2);
    }
}

char del1(node1 **h)
{
    char ch=(*h)->c;
    *h=(*h)->n1;
    return ch;
}

double del2(node2 **h)
{
    double a=(*h)->d;
    *h=(*h)->n2;
    return a;
}

double dat(char s[],int *i)
{
    char sa[100];
    int k=0,m=*i;
    int a=1;
    if(s[m]=='-')
    {
        a=-1;
        ++(m);
    }
    while(!((s[*i]=='+')||(s[*i]=='*')||(s[*i]=='/')||(s[*i]=='(')||(s[*i]==')')||(s[*i]=='=')||(s[*i]=='-')))
    {
        sa[k]=s[*i];
        printf("%c",s[*i]);
        if((s[*i]=='e')||(s[*i]=='E'))
        {
            ++(*i);
            sa[++k]=s[*i];
            printf("%c",s[*i]);
        }
        ++(*i);
        ++k;
    }
    sa[k]='\0';
    printf(" ");
    return a*atof(sa);
}

double oper(double a, double b,char c)
{
    if(c=='+')
        return a+b;
    if(c=='-')
        return b-a;
    if(c=='*')
        return a*b;
    if(c=='/')
        return b/a;
}

int main()
{
    int n=1000;
    char s[n],ch;
    scanf("%s",s);
    printf("\n\n");
    n=strlen(s);
    node2 *x=NULL;
    node1 *y=NULL;
    node1 *z;
    int i=0,k,pr;
    double a,b;
    if(s[0]=='-')
        push2(&x,dat(s,&i));
    while(i<n)
    {
        if(s[i]=='(')
            if(s[i+1]=='-')
            {
                ++i;
                push2(&x,dat(s,&i));
                if(s[i]!=')')
                {
                    push1(&y,'(');
                    --i;
                }
            }
            else
                push1(&y,s[i]);
        else if(s[i]==')')
        {
            while((y->c)!='(')
            {
                a=del2(&x);
                b=del2(&x);
                ch=del1(&y);
                printf("%c ",ch);
                push2(&x,oper(a,b,ch));
            }
            del1(&y);
        }
        else if((s[i]=='+')||(s[i]=='-')||(s[i]=='*')||(s[i]=='/')||(s[i]=='='))
        {
                if(s[i]=='='){
                    pr=1;
                }
                else if((s[i]=='+')||(s[i]=='-'))
                    pr=3;
                else if((s[i]=='*')||(s[i]=='/'))
                    pr=4;
                if((y!=NULL)&&(y->p >= pr))
                {
                    while((y!=NULL)&&(y->p >= pr)&&((x->n2)!=NULL))
                    {
                        a=del2(&x);
                        b=del2(&x);
                        ch=del1(&y);
                        if((ch=='/')&&(a==0))
                        {
                            printf("error! division at 0");
                            return -1;
                        }
                        else
                        push2(&x,oper(a,b,ch));
                        printf("%c ",ch);}
                        push1(&y,s[i]);

                }
                else
                    push1(&y,s[i]);
        }
        else
        {
            push2(&x,dat(s,&i));
            --i;
        }
        ++i;
    }
    printf("\n\n");
    output(x);
    return 0;
}
