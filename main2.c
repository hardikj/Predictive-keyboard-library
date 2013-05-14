#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#define NR 27

#define true 1
#define false 0

typedef struct trie_node{

    bool NotLeaf;
    struct trie_node *pChildren[NR];
    char word[20];
}node;

typedef struct stack{   //structure for stracks

    struct stack *next;
    char key[20];

}stack;

typedef struct ll
{
    char a;
    struct ll *next;
    struct ll *prev;
}ll;

typedef struct master
{
    struct ll *start;
    struct ll *end;
    int count;
}mn;

void traverse(mn *m);
mn *insert_end(mn *m,char ch);
//------------------------------------------------------  Trie function --------------------------
node *NewLeaf(char keyWord[20]) 
{ 
    node *t_node; 
    int count; 
    //allocating the necessary memory 
    t_node = (node *)malloc(sizeof(node)); 
    for(count = 0; count < 27; count++) //the terminal nodes don't have children 
        t_node->pChildren[count] = NULL; 
    
    t_node->NotLeaf = false; // the node is a leaf 
    strcpy(t_node->word,keyWord); //store in the structure(node->word) the string 
    return t_node; 
}

//function for creating a intern node 
node *NewIntern() 
{ 
    node *t_node; 
    int count; 
    //allocating the necessary memory 
    t_node = (node *)malloc(sizeof(node)); 
    for(count = 0; count < 27; count++) // initial the intern node don't have children 
        t_node->pChildren[count] = NULL;
    
    t_node->NotLeaf = true; //it isn't a leaf 
    t_node->word[0] = 0; //so we store the null string in node 
    return t_node; 
} 

stack* push(stack *top, char key[])
{
    stack *n;
    n = (stack *)malloc(sizeof(node));
    n->next=NULL;
    strcpy(n->key,key);
    if(top == NULL)
    {
        top = n;    
    }   
    else
    {
            
        n->next = top;
        top = n;
    }
    return top;
}   

stack* pop(stack *top,mn *m,ll *temp)
{
    stack *n;
    char a[20];
    int i=0;
    if(top == NULL)
    {
        printw("-");
        return top;

    }
    n = top;
    if(n->key)
        strcpy(a,n->key);
    else
        printw("sorry");

    while((temp != NULL)&&(temp->a != ' ')) 
    {
            temp = temp->prev;        
    }

    m->end = temp;

    //printw("%s",a);

    while(a[i] !='\0')
    {
        m = insert_end(m,a[i]);
        i++;
    }
    
    clear();
    refresh();
    traverse(m);
    top = top->next;
    free(n);

return top;
}


stack* Tostack(node *trie, stack *top)
{
    int count;
    if(trie)
    {
        if(trie->NotLeaf!= true)
        {
            //printw("word goes in stack ->");
            //puts(trie->word);
            top = push(top,trie->word);                    //this will be pushed to stack
        }


        for(count = 26; count >=0 ; count--)
            top = Tostack(trie->pChildren[count],top);
    }
return top;
}

stack* Complete(node *trie, char keyWord[20], stack *top)
{
    node *index,*next, *data;
    int i,count = 0;    
    
    next = trie;
    if(next == NULL)
    {
        printw("");
    }
    else
        index = next;

    while((index->NotLeaf==true)&&(count < strlen(keyWord))&&(index->pChildren[keyWord[count]-'a']!=NULL))
    {

        next = index->pChildren[keyWord[count]-'a'];
        index = next;
        count++;
    }

    if(next == NULL)
        return top;
    else
    if(count>=strlen(keyWord))
    {
        
        top = Tostack(next,top);    
    }

return top; 
}

node* Insert(node *trie, char keyWord[20]) 
{ 
    node *next, *index, *parent; 
    node *new_leaf, *data, *new_index; 
    node *oldChildren, *newWord, *intern;

    int inWordIndex, prefixLenght, lenght = strlen(keyWord); 

    next = trie; 
    if(next == NULL) //trie empty 
    { 
        trie = NewIntern(); 
        new_leaf = NewLeaf(keyWord); 
        trie->pChildren[keyWord[0]-'a'] = new_leaf; 
        return trie; 
    } 
    else 
        index = next;

    inWordIndex = 0; 
    while((inWordIndex < lenght) &&(index->NotLeaf == true)&&(index->pChildren[keyWord[inWordIndex]-'a'] != NULL)) 
    { 
        parent = next; 
        next = index->pChildren[keyWord[inWordIndex]-'a']; 
        index = next; 
        inWordIndex++; 
    }


    if((inWordIndex < lenght) && (index->pChildren[keyWord[inWordIndex]-'a'] == NULL) && (index->NotLeaf == true)) 
    { 
        new_index = NewLeaf(keyWord); 
        index->pChildren[keyWord[inWordIndex]-'a'] = new_index; 
        return trie; 
    } 
    else 
    data=next;

    if(!strcmp(data->word,keyWord)) 
    printw("");//printw("Word already exists in trie !!!"); 
    else 
    { 
        oldChildren = parent->pChildren[keyWord[inWordIndex-1]-'a']; 
        newWord = NewLeaf(keyWord); 
        prefixLenght= strlen(keyWord); 
        if(data->word[0] != '\0') 
            if(strlen(data->word) < prefixLenght)
                prefixLenght = strlen(data->word);

    }
    
    bool createIntern = false; 
    while((inWordIndex <= prefixLenght)&&(((data->word[0] != '\0' )&& (data->word[inWordIndex-1] == keyWord[inWordIndex-1])) || (data->word[0] == '\0'))) 
    { 
        intern = NewIntern(); 
        parent->pChildren[keyWord[inWordIndex-1]-'a'] = intern; 
        parent->NotLeaf = true; 
        parent = intern; 
        inWordIndex++; 
        createIntern = true; 
    }

    if(createIntern) 
    inWordIndex--; 

    if((inWordIndex != prefixLenght) || ((inWordIndex == prefixLenght)&&(strlen(keyWord) == strlen(data->word)))) 
    { 
        parent->pChildren[data->word[inWordIndex]-'a'] = oldChildren; 
        parent->pChildren[keyWord[inWordIndex]-'a'] = newWord; 
    } 
    else   
        if(data->word[0] != '\0') 
            if(strlen(data->word) <= prefixLenght) 
            { 
                parent->pChildren[26] = oldChildren; 
                parent->pChildren[keyWord[prefixLenght]-'a'] = newWord; 
            } 
    
            else 
            { 
                parent->pChildren[26] = newWord; 
                parent->pChildren[data->word[prefixLenght]-'a'] = oldChildren; 
            } 
        else
        {    
            for (int count = 0 ; count < 27; count++) 
               {
                parent->pChildren[count] = oldChildren->pChildren[count]; 
               }
            parent->pChildren[26] = newWord; 
        } 
return trie; 
}

node* pTrain(node *trie)    //populating words from the dictionary
{
    char ch,key[20];
    int i=0;
    FILE *f;
    f = fopen("words.txt","r");
    
    if(f==NULL)
    {
        return trie;
    }
    while(ch!=EOF )
        {
            ch = fgetc(f);
            if(ch != '\n')
            {
                key[i] = ch;
                i++;
            }
            else
            {   
                trie = Insert(trie,key);
                //puts(key);
                for(i=0;i<20;i++)
                    key[i]=0;
                i=0;
            }
        }
    fclose(f);
return trie;
}

void Find(node *trie, char keyWord[20]) 
{ 

    node *next, *index, *data; 
    int count; 

    next = trie; 
    if(next == NULL) //trie is empty 
    { 
        printf("Word not found in trie !!!!\n");
        exit(1); 
    } 
    else 
        index = next;// index - the current node from trie 

    count = 0; // start searching for the first letter of the word(index of letter in word is 0) 
    while((index->NotLeaf == true) && (count < strlen(keyWord)) && (index->pChildren[keyWord[count]-'a'] != NULL)) 
    { 
        next = index->pChildren[keyWord[count]-'a'];
        index = next; 
        count ++ ; 
    } 
    if(next == NULL) 
        printf("Word not found in trie !!!!\n"); 
    else    
    { 
        data = next; 
        //the string is in a leaf 
        if(!strcmp(data->word,keyWord)) 
            printf("Key exists --- Word found in trie !!!\n"); 
        else//the string is in the blank pointer(prefix for others words stored in trie) 
            if((data->pChildren[26]) && !strcmp(data->pChildren[26]->word,keyWord)) 
                printf("Key exists --- Word found in trie !!!!\n") ; 

        else 
            printf("Word not found in trie !!!!\n"); 
    } 
}

void DisplayTrie(node *trie, int nivel) 
{ 
    int count; 
    if(trie) 
    { 
        if (trie->NotLeaf != true) // if node is a leaf(a word is stored in) 
        {   // display the string at his level 
            for (count = 0; count <= nivel; count++) 
                 printf(" "); 
                 puts(trie->word);
                 printf("\n"); 
        } 
        // display all the words stored through trie children 
        for (count = 26; count >= 0; count--) 
        DisplayTrie(trie->pChildren[count], nivel + 4); 
    } 
}

//-----------------------------------------------------------------editor func--------------------------
mn *initialise(mn *m)
{
    m = (mn *)malloc(sizeof(mn));
    m->start = NULL;
    m->end = NULL;
    m->count = 0;
    return m;
}

ll *new_node(ll *n,char ch)
{
    n =(ll *)malloc(sizeof(ll));
    n->a = ch;
    n->next = NULL;
    n->prev = NULL;  
    return n;
}
mn *insert_end(mn *m,char ch)
{
    ll *n;
    ll *temp;
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
    ll *temp;
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
        ll *temp;
        temp = m->end;
        m->end =(m->end)->prev;
        (m->end)->next = NULL;
        temp->prev = NULL;
        free(temp);
        //printw("%c",(m->end)->a);
        //printw("%c",temp);
    }
    return m;  
}

void strrev(char *str)
{
        if( str == NULL )
                return;

        char *end_ptr = &str[strlen(str) - 1];
        char temp;
        while( end_ptr > str )
        {
                temp = *str;
                *str++ = *end_ptr;
                *end_ptr-- = temp;
        }

}

void get_key(mn *m, stack *top, node *trie)
{
	ll *temp;
    top = NULL;
	char c,ch,key[20],buffer[20];
	int i=0;
    temp = m->end;
	while((temp != NULL)&&(temp->a != ' ')) 
	{
			
			key[i] = temp->a;
			temp = temp->prev;
			i++;
		
	}
	for(i=0;i<strlen(key);i++)
		{
			if(isalpha(key[i]))
				{
					buffer[i] = key[i];
				}
		}
	strcpy(buffer,key);
	strrev(buffer);
	for(i=0;i<20;i++)
      key[i]=0;   	
	strcpy(key,buffer);
    top = Complete(trie,key,top); //stack is build till this point
    if(top)
        //printw("ok1");
        top = pop(top,m,temp); //pop
        
        c = getch();
    if(c==9)
    {
        while(c==9)
        {
            top = pop(top,m,temp);//pop
            c = getch();
            
        }
    }

    else
    {
        ch = c;
        m = insert_end(m,ch);
        clear();
        refresh();
        traverse(m);
    }
}	




mn* start(mn *m)
{ 
    stack *top;
    node *trie;
    ll *temp;
    char dump,c;
	int ch;
    top = NULL;
    trie = NULL;
    temp = NULL;
    printw("\n\t\t\t\t\t\tprint 1 to all the populate data\n");
    scanw("%d",&ch);
    refresh();
    printw("\t\t\t\t\t\t\t%d thanks",ch);
    if(ch == 1)
        trie = pTrain(trie);
    while(ch != 27)
    {
        
        ch = getch();
		c = ch;

        switch(ch)
		{
			case 127:
        	{	   
				m = delete_node(m);
				clear();
                refresh();
                traverse(m);
				break;
			}
			
			case 9:
			{        
			    get_key(m,top,trie);
				break;
			}		
			default:
			{    
				m = insert_end(m,c);
				clear();
				refresh();
				traverse(m);    
			}
		}
	}
		
		clear();
		refresh();
        printw("press any key to exit");
        refresh();
	
}

void menu() 
{ 
    stack *top,*n;
    node *trie; 
    char UserInputWord[20], cont_insert=' '; 
    char dump;
    int option =48; //stores the user's input(the chosen option) 
    trie = NULL;
    top = NULL; 
    label_menu: 
    while( option != 56) 
        { 
        //display menu 
        printw("\n Menu: \n"); 
        printw("___________________________________________\n"); 
        printw("\n1. Create tree\n 2. Insert node\n 3. Search for node\n 4. Display tree\n 5.complete\n 6. Populate tree\n 7. pop \n8. Exit \n"); 
        //get user input 
        printw("\n\n\nInput choice: "); 
        scanw("%d",&option); 
        switch (option) 
        { 
            case 49: //Create tree 
                while(cont_insert != 'n') 
                { 
                    // get user input string 
                    printw("\nInsert word :");
                    scanw("%c",&dump); 
                    getstr(UserInputWord); 
                    trie = Insert(trie,UserInputWord); 
                printw("\n Continue ? <y/n>"); 
                scanw("%c",&cont_insert); 
                } 
            break; 

            case 50: //Insert node 
                printw("\nInsert word :"); 
                scanw("%c",&dump);
                getstr(UserInputWord); 
                trie = Insert(trie,UserInputWord); 
            break; 

            case 51: //Search for node 
                printw("Searched word :"); 
                scanw("%c",&dump); 
                getstr(UserInputWord); 
                Find(trie,UserInputWord); 
            break; 


            case 52: //Display tree 
                DisplayTrie(trie,0); 
            break; 

            case 53: // autocomplete
                printw("Searched word :"); 
                scanw("%c",&dump); 
                getstr(UserInputWord);
                top = Complete(trie,UserInputWord,top);
            break;
            case 54:// popoulate tree
                trie = pTrain(trie);
                break;
            case 56: //Exit
                exit(1); 
                break; 

            default: 
            printw("Choose from the displayed options (1-5) !!!"); 
            goto label_menu; 
        }//end switch 
     }//end while 
}  



int main()
{

    int ch;
    initscr();
    noecho();
    cbreak();
    mn *m;
    m = initialise(m);
    printw("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tHello welcome to the editor we support Auto complition! \n");
    printw("\n\t\t\t\t\t\tYou can start writing now\n");
    start_color();          /* Start color          */
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh();
    printw("\n\t\t\t\t\t\tPlease choose between following options\n");
    printw("\n\t\t\t\t\t\t1. Enter editor");
    printw("\n\t\t\t\t\t\t2. Enhance Dictionary or tree\n");
    ch = getch();

    switch(ch)
        {
            case 49: clear();
                    refresh();
                    m = start(m);
                    break;
            case 50: menu();
                    break;

        }

  //  m = start(m);
    
    getch();
    endwin();

    return 0;
}
