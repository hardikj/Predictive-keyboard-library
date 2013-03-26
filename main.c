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
    n = create_node(n,ch);
    if(m->head = NULL)
    {
        m->head = n;
        m->end = n;
    } 
    else
    {
        n->put 
        m->end = n; 
    }
}

mn *start(mn *m)
{
    char dump,ch= 'T';
    while(ch != 27)
    {
        ch = getch();
        m = insert_end(m,ch);
    }
        printf("\npress any key to exit");
        
}
int main()
{
        initscr();
        noecho();
        cbreak();
	mn *m;
	m = initialise(m);
	printf("hello welcome to the editor we support auto complition! \n");
	printf("You can start writing now\n");

        m = start(m);
        getch();
        endwin();

	return 0;
}
