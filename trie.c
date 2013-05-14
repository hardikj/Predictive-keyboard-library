#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define NR 27

typedef int bool;
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


//function for creating a leaf node 
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
		puts(top->key);		
	}	
	else
	{
			
		n->next = top;
		top = n;
	}
	return top;
}	

stack* pop(stack *top)
{
	stack *n;
	if(top == NULL)
	{
		printf("stack is empty");
		return top;
	}
	n = top;
	puts(top->key);
	top = top->next;
	free(n);

return top;
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

stack* Tostack(node *trie, stack *top)
{
    int count;
    if(trie)
    {
        if(trie->NotLeaf!= true)
        {
			printf("word goes in stack ->");
            puts(trie->word);
		    top = push(top,trie->word);					   //this will be pushed to stack
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
		printf("trie is emplty\n");
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
	printf("Word already exists in trie !!!"); 
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

void DisplayTrie(node *trie, int nivel) 
{ 
	int count; 
	if(trie) 
 	{ 
		if (trie->NotLeaf != true) // if node is a leaf(a word is stored in) 
 		{ 	// display the string at his level 
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
				puts(key);
				for(i=0;i<20;i++)
					key[i]=0;
				i=0;
			}
		}
	fclose(f);
return trie;
}



int main() 
{ 
	stack *top,*n;
 	node *trie; 
	char UserInputWord[20], cont_insert=' '; 
    char dump;
	int option = 0; //stores the user's input(the chosen option) 
 	trie = NULL;
	top = NULL; 
	label_menu: 
	while( option != 8) 
 		{ 
		//display menu 
 		printf("\n Menu: \n"); 
 		printf("___________________________________________\n"); 
 		printf("\n1. Create tree\n 2. Insert node\n 3. Search for node\n 4. Display tree\n 5.complete\n 6. Populate tree\n 7. pop \n8. Exit \n"); 
		//get user input 
 		printf("\n\n\nInput choice: "); 
 		scanf("%d",&option); 
		switch (option) 
 		{ 
			case 1: //Create tree 
				while(cont_insert != 'n') 
 				{ 
					// get user input string 
 					printf("\nInsert word :");
					scanf("%c",&dump); 
 					gets(UserInputWord); 
 					trie = Insert(trie,UserInputWord); 
 				printf("\n Continue ? <y/n>"); 
 				scanf("%c",&cont_insert); 
				} 
			break; 

			case 2: //Insert node 
				printf("\nInsert word :"); 
				scanf("%c",&dump);
				gets(UserInputWord); 
				trie = Insert(trie,UserInputWord); 
			break; 

			case 3: //Search for node 
				printf("Searched word :"); 
				scanf("%c",&dump); 
				gets(UserInputWord); 
 				Find(trie,UserInputWord); 
			break; 


			case 4: //Display tree 
				DisplayTrie(trie,0); 
			break; 

			case 5: // autocomplete
				printf("Searched word :"); 
                scanf("%c",&dump); 
                gets(UserInputWord);
				top = Complete(trie,UserInputWord,top);
			break;
			case 6:// popoulate tree
				trie = pTrain(trie);
				break;
			case 7: 
				top = pop(top);
				break;
			case 8: //Exit
			exit(1); 
			break; 

			default: 
			printf("Choose from the displayed options (1-5) !!!"); 
			goto label_menu; 
 		}//end switch 
	 }//end while 
return 0; 
}  
