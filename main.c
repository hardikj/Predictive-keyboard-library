#include <stdio.h>
#include <malloc.h>
#include <ncurses.h>


typedef struct node
{
    char a;
    struct node *next;
    struct node *prev;
}node;

typedef struct master
{
    struct node *start;
    struct node *end;
    int count;
}mn;

mn *initialise(mn *m)
{
    m = (mn *)malloc(sizeof(mn));
    m->start = NULL;
    m->end = NULL;
    m->count = 0;
    return m;
}

node *new_node(node *n,char ch)
{
    n =(node *)malloc(sizeof(node));
    n->a = ch;
    n->next = NULL;
    n->prev = NULL;  
    return n;
}

mn *insert_end(mn *m,char ch)
{
    node *n;
    node *temp;
    n = new_node(n,ch);
    if(m->start == NULL)
    {
        m->start = n;
        m->end = n;
    } 

    else
    {
        n->prev = m->end;
        //m->end = (node *)malloc(sizeof(node));
        (m->end)->next = n;
        m->end = n; 
    }
return m;
}

void traverse(mn *m)
{
    node *temp;
    temp = m->start;
    while(temp != NULL)
    {
        printw("%c",temp->a);
        refresh();
        temp = temp->next;
     }
    
    
}

mn *delete_node(mn *m)
{
    if((m->start)->next == NULL)
    {
        clear();
        m->start = NULL;
    }
    else
    {    
        node *temp;
        temp = m->end;
        m->end =(m->end)->prev;
        (m->end)->next = NULL;
        temp->prev = NULL;
        free(temp);
        //printw("%c",(m->end)->a);
        //printw("%c",temp);
        //printw("check");
    }
    return m;  
}



mn *start(mn *m)
{ 
    node *temp;
    char dump,ch= 'T';
    while(ch != 27)
    {
        //scanf("%c",&ch);
        ch = getch();
        if (ch == 127)
        {    
            
            m = delete_node(m);
        }
        else
        {    
        m = insert_end(m,ch);
        }
        clear();
        refresh();
        traverse(m);    
        //printw("%c",ch);
    }
        printw("\npress any key to exit");
        refresh();
}
int main()
{
    initscr();
    noecho();
    cbreak();
    mn *m;
    m = initialise(m);
    printw("hello welcome to the editor we support auto complition! \n");
    printw("You can start writing now\n");
    refresh();
    m = start(m);
    getch();
    endwin();

    return 0;
}
