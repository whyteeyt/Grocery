/*Name: Gan Yi Thung
  Student ID: 20318885
  Assignment Title: Grocery Store Database
  Date: 15 Dec 2020
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item {
    int id;
    char name [20];
    double cost;
    char category;
    struct item *next;
};

typedef struct item Item;	/* synonym for struct item */

/* prototypes */
char choose(void);

void add1(Item *head, int idx, char namex[20], double costx, char categoryx);
void delete2(Item *head, int idx);
int change3(Item *head);
void search4(Item *head, char namex[20]);
void display5(Item *head);

int check(Item *head, int idx, char namex[20]);
int check2(Item *head, int idx);
void print(Item *head);
void swap(Item *temp, Item *current);
Item* copy(Item* head);

void ascid(Item *duplicate);
void dscid(Item *duplicate);
void ascname(Item *duplicate);
void dscname(Item *duplicate);
void asccost(Item *duplicate);
void dsccost(Item *duplicate);
void asccat(Item *duplicate);
void dsccat(Item *duplicate);

int main (void)
{	
	/* variables */
	char file_name[100];
	char newfile[100];
	int choice;	/* user's choice */
	int saveflag = 0;
	int save = 0;

	/* creating nodes */
	Item *head = malloc(sizeof(Item));
	head = NULL;	/* no nodes initially */
	Item *temp = head;
	temp = (Item *)malloc(sizeof(Item));

	/* variables entered by user */
	int idx;
	char namex[20];
	double costx;
	char catx;
	
	printf("Welcome to Gan Yi Thung (20318885)'s grocery store!!\n");
	printf("Please enter the file you'd like to load into stock: \n>> ");
	fgets(file_name, sizeof(file_name), stdin);

	/* replace \n in fgets with NULL character */
	for(int i = sizeof(file_name); i > 0; i--){
		if(file_name[i] == '\n')   
			file_name[i] = '\0';
	}

	FILE *foodPtr; /*food.txt file pointer*/

	/* open the file, exits if failed to open file */
	foodPtr = fopen(file_name, "r");

	if(foodPtr == NULL){
		printf("Haizzz failed to open [%s] T^T\n", file_name);
	} /*end if*/

	else{
	printf("\n[%s] has been properly loaded into the database!\n", file_name);
		
		
	/*--- stroring into linked list ---*/
	while(!feof(foodPtr)){
			
		if(head == NULL){
			head = temp;
			fscanf(foodPtr, "%d\t%s\t%lf\t%c\n", &temp->id, temp->name, &temp->cost, &temp->category);
			temp->next = malloc(sizeof(Item));
			temp = temp->next;
			temp->next = NULL;
		} /* special for head only */
		
		else{
			fscanf(foodPtr, "%d\t%s\t%lf\t%c\n", &temp->id, temp->name, &temp->cost, &temp->category);
			if(feof(foodPtr)) break;
			temp->next = malloc(sizeof(Item));
			temp = temp->next;
			temp->next = NULL;
		} /* end else */
	} /* end while */
		
	fclose(foodPtr);
		
		while((choice = choose()) != '6'){
			
			switch(choice){
				case '1':
					printf("Please enter info for item to be added: \n");
					printf("ID: ");
					scanf("%d", &idx);
					getchar();
					printf("Name: ");
					scanf("%s", namex);
					getchar();
					printf("Cost: ");
				  	scanf("%lf", &costx);
					getchar();
				    printf("Category: ");
				    scanf(" %c", &catx);
					getchar();

				    if(check(head, idx, namex) == 0){	
					add1(head, idx, namex, costx, catx);
					saveflag = 1;
					break;
					}

					break;
					
				case '2':
					printf("ID of product you wish to delete: ");
					scanf("%d", &idx);
					getchar();
					
					if(check2(head, idx) != 0){	
					delete2(head, idx);
					saveflag = 1;
					}
					else printf("Sorry, item with ID number [%d] not found in database.\n", idx);
					
					break;
					
				case '3': ;
					if(change3(head) != 0) saveflag = 1;
					break;
					
				case '4':
					printf("Name of item you wish to search for: ");
					scanf("%s", namex);
					getchar();
					search4(head, namex);
					break;
					
				case '5':
					display5(head);
					break;
					
				default: 
					printf("\nIllegal Choice!!!\n");
					break;

				}	/* end switch */
		} /* end while */ 
		
		if(saveflag == 1){
			printf("Would you like to save the changes made to the database?\n[1] Yes\n[2] No\n>> ");
			scanf("%d", &save);

			if (save == 1){
				printf("\nPlease enter the file you'd like to save the new database: \n>> ");
				scanf("%s", newfile);
				
				while(strcmp(file_name, newfile) == 0){
					printf("\nPlease enter a NEW file name. \n>> ");
					scanf("%s", newfile);
				} /* end while */
				
				FILE *newPtr; /*file pointer*/

				/* open the file, exits if failed to open file */
				newPtr = fopen(newfile, "w");
				if(newPtr == NULL) printf("Haizzz failed to open [%s] T^T\n", newfile);
					
				else{
					for(temp = head; temp != NULL; temp = temp->next){
					fprintf(newPtr, "%d %s %.2f %c\n", temp->id, temp->name, temp->cost, temp->category);
					}
						
					fclose(newPtr);
						
					printf("\nThe file has been saved to [%s].", newfile);
						
				} /* end inner else*/
					
			} /* end inner if */
			
		} /* end outer if */
		
		printf("\nThanks for shopping. Byebyeee~~\n");
		
	} /* end else */

return 0;
} /* end main */

char choose(void)
{
	char user_choice = 0;	/*variable to store user's choice*/

	/* display menu */
	printf("\nPlease make one of the following selections:\n");
	printf("[1] Add new item\n");
	printf("[2] Delete item\n");
	printf("[3] Change the cost of an item\n");
	printf("[4] Search for item\n");
	printf("[5] Display inventory details\n");
	printf("[6] Quit\n");

	printf("\nEnter your choice: ");
	scanf(" %c", &user_choice);
	
	return user_choice;
}

int check(Item *head, int idx, char namex[20]){
	int flag = 0;
	Item *temp;

	for(temp = head; temp != NULL; temp = temp->next){
		if(temp->id == idx) {
			printf("Sorry, an item with the ID number %d is already in the database.\n", idx);
			flag++;
		}

		if(strcmp(temp->name, namex) == 0){
			printf("Sorry, an item with the name %s is already in the database.\n\n", namex);
			flag++;
		}
	} /* end for */

	return flag;
} /* end check func */

int check2(Item *head, int idx){
	int flag = 0;
	Item *temp;

	for(temp = head; temp != NULL; temp = temp->next){
		if(temp->id == idx) 
			flag++;
	} /* end for */
	return flag;
} /* end check2 func */

void add1(Item *head, int idx, char namex[20], double costx, char catx)
{
	Item *new;
	Item *temp;
	new = malloc(sizeof (Item));
		
	if(new == NULL){
       printf("Unable to allocate memory.");
	}
	
    else{
        new->id = idx;
		for(int i = 0; i<20; i++)
		new->name[i] = namex[i];
		new->cost = costx;
		new->category = catx;	
		
        new->next = NULL; 

        temp = head;

        /* make temp to last*/
        while(temp != NULL && temp->next != NULL){
           temp = temp->next;
		} 

        temp->next = new; 

        printf("[%s] has been successfully added to database.\n", new->name);
    }
} /* end add1 func */

void delete2(Item *head, int idx){
	Item *temp = head;
	Item *last = head;
	Item *seclast = head;

	int tempid = 0;
	char namex[20];
	double costx;
	char catx;

	/* identifying seclast and last */
	while(last->next != NULL){
		seclast = last;
		last = last->next;
	}
	
	/* identifying node to delete(temp)*/
	while(temp->id != idx){
		temp = temp->next;
	}
	
	/* swap temp and last then delete last*/
	swap(temp, last);
	
	printf("[%s] has been deleted. \n", last->name);
	
	seclast->next = NULL; /* disconnect seclast and last */
	free(last);
	
} /* end delete2 func */

int change3(Item *head){
	int idx = 0;
	double costx = 0;
	int flag = 0;

	printf("\nPlease enter ID of product to update the cost: ");
	scanf("%d", &idx);
	getchar();
	
	for(Item *temp = head; temp != NULL; temp = temp->next){
		if(temp->id == idx){
			printf("New price: ", temp->name);
			scanf("%lf", &costx);

			temp->cost = costx;

			printf("[%s] now costs [%.2f].\n", temp->name, temp->cost);
			flag = 1;
			return flag;
		} /* end if */
	} /* end for */
	
	printf("Sorry product with ID [%d] not found in database.\n", idx);
	return flag;

} /* end change3 func */


void search4(Item *head, char namex[20]){

	for(Item *temp = head; temp != NULL; temp = temp->next){
		if(strcmp(temp->name, namex) == 0){
			printf("\nProduct info:\nID: %d\nName: %s\nCost: %.2f\nCategory: %c\n", temp->id, temp->name, temp->cost, temp->category);
			return;
		}
	}
	
	printf("Sorry we do not have [%s] in the store.\n", namex);

 } /* end search4 func*/
 
void display5(Item *head){
 	int sortchoice;
 	int sort;
 	int ad;
		
 	printf("Would you like it to be sorted?\n[1] Yes\n[2] No\n>>  ");
 	scanf("%d", &sortchoice);
	getchar();
	if(sortchoice != 1 && sortchoice != 2) {
		printf("Illegal!!\n");
		return;
	}
		
		
 	if(sortchoice == 2){
 		printf("\nHere is the listing of all the products in stock without sorting:\n");
		print(head);
 	} /* end if */

 	else if (sortchoice == 1){
 		printf("\nHow would you like it to be sorted?\n");
 		printf("[1] ID of product\n[2] Name of product\n[3] Cost of product\n[4] Product category\n>> ");
 		scanf("%d", &sort);
		getchar();
		if(!(sort >= 1 && sort <= 4)) {
			printf("Illegal!!\n");
			return;
		}
			
 		printf("\nWould you like it to be [1]Ascending or [2]Descending?\n>> ");
 		scanf("%d", &ad);
		getchar();
		if(ad != 1 && ad != 2) {
			printf("Illegal!!\n");
			return;
		}
			
		Item *duplicate = copy(head);
 		if(sort == 1 && ad == 1) ascid(duplicate);
		if(sort == 1 && ad == 2) dscid(duplicate);
		if(sort == 2 && ad == 1) ascname(duplicate);
		if(sort == 2 && ad == 2) dscname(duplicate);
		if(sort == 3 && ad == 1) asccost(duplicate);
		if(sort == 3 && ad == 2) dsccost(duplicate);
		if(sort == 4 && ad == 1) asccat(duplicate);
		if(sort == 4 && ad == 2) dsccat(duplicate);
			
 		} /* end else if */
 } /* end display5 func */
 
void print(Item *head){
	printf(" _______________________________________________________________________\n");
	printf("|\tID\t\tName\t\tCost\t\tCategory\t|\n");
	printf("|_______________________________________________________________________|\n");
 	for(Item *temp = head; temp != NULL; temp = temp->next){
 		printf("|\t%d\t\t%s\t\t%.2f\t\t%c\t\t|\n", temp->id, temp->name, temp->cost, temp->category);
 	} /* end for */
	printf("|_______________________________________________________________________|\n");
 } /* end print func */
 
void swap(Item *temp, Item *current){
	int idx; /* temporary variables */
	char namex[20]={};
	double costx;
	char catx;
	
	idx = current->id;
	current->id = temp->id;
	temp->id = idx;
				
	strcpy(namex, current->name);
	strcpy(current->name, temp->name);
	strcpy(temp->name, namex);

	costx = current->cost;
	current->cost = temp->cost;
	temp->cost = costx;

	catx= current->category;
	current->category = temp->category;
	temp->category = catx;
} /* end swap func */
 
Item *copy(Item* head){
	/* duplicate list for sorting */
    Item *temp = head;
    Item *newhead = NULL; 
    Item *new = NULL;    
 
    for(Item *temp = head; temp != NULL; temp = temp->next){
        if (newhead == NULL){
            newhead = malloc(sizeof(Item));	/* allocate space for newhead */
			
            newhead->id = temp->id;
			strcpy(newhead->name, temp->name);
			newhead->cost = temp->cost;
			newhead->category = temp->category;
			
            newhead->next = NULL;
            new = newhead;
        } /* special for head only */
        else{
            new->next = malloc(sizeof(Item));
            new = new->next;
			
            new->id = temp->id;
			strcpy(new->name, temp->name);
			new->cost = temp->cost;
			new->category = temp->category;
			
            new->next = NULL;
        }
    } /* end for */
 
    return newhead;
} /* end copy func */
 
 void ascid(Item *duplicate){ 
	Item *temp = NULL;
	
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->id > temp->id)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end ascid func*/

void dscid(Item *duplicate){ 
	Item *temp = NULL;
	
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->id < temp->id)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end dscid func*/

void ascname(Item *duplicate){ 
	Item *temp = NULL;
	
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(strcmp(current->name, temp->name) > 0)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end ascname func*/

void dscname(Item *duplicate){ 
	Item *temp = NULL;
		
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(strcmp(current->name, temp->name) < 0)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end dscname func*/

void asccost(Item *duplicate){ 
	Item *temp = NULL;
		
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->cost > temp->cost)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end asccost func*/

void dsccost(Item *duplicate){ 
	Item *temp = NULL;
		
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->cost < temp->cost)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end dsccost func*/

void asccat(Item *duplicate){ 
	Item *temp = NULL;
		
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->category > temp->category)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end asccat func*/

void dsccat(Item *duplicate){ 
	Item *temp = NULL;
		
	for(Item *current = duplicate; current != NULL; current = current->next){
		for(temp = current->next; temp != NULL; temp = temp->next){
			if(current->category < temp->category)
				swap(temp, current);
		} /* end inner for */
	} /* end outer for */
	
	print(duplicate);
	
} /* end dsccat func*/