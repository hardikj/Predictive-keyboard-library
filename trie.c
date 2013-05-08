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

node *Insert(node *trie, char keyWord[20]) 
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
		for (int count = 0 ; count < 27;count++) 
 			parent->pChildren[count] = oldChildren->pChildren[count]; 
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

int main() 
{ 
 	node *trie; 
	char UserInputWord[20], cont_insert=' '; 
	int option = 0; //stores the user's input(the chosen option) 
 	trie = NULL; 
	label_menu: 
	while( option != 5) 
 		{ 
		//display menu 
 		printf("\n Menu: \n"); 
 		printf("___________________________________________\n"); 
 		printf("1. Create tree\n 2. Insert node\n 3. Search for node\n 4. Display tree\n 5. Exit\n"); 
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
 					gets(UserInputWord); 
 					trie = Insert(trie,UserInputWord); 
 				printf("\n Continue ? <y/n>"); 
 				scanf("%c",&cont_insert); 
				} 
			break; 

			case 2: //Insert node 
				printf("\nInsert word :"); 
				gets(UserInputWord); 
				insert(trie,UserInputWord); 
			break; 

			case 3: //Search for node 
				printf("Searched word :");  
				gets(UserInputWord); 
 				Find(trie,UserInputWord); 
			break; 


			case 4: //Display tree 
				DisplayTrie(trie,0); 
			break; 

			case 5: //Exit 
			break; 

			default: 
			printf("Choose from the displayed options (1-5) !!!"); 
			goto label_menu; 
 		}//end switch 
	 }//end while 
return 0; 
}  
