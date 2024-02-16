#include<stdio.h>											//header file required for input,output functions
#include<stdlib.h>											//header file required for dynamic memory allocation
#include<string.h>											//header file required for string operations
typedef struct contact{										// declaring the structure to access globally
	int fav;					
	char name[50];
    char phone[20];											// variables to store the required data for contact
    char email[60];
    struct contact *prev,*next;
}Contact;
typedef struct priv_contact{								// declaring the structure to access globally
	char name[50];
	char phone[20];											// variables to store the required data for contact
	char email[60];
	struct priv_contact *prev,*next;						
}Private;
Private *p_head=NULL,*p_tail=NULL;							// declaring and intializing private contact head,tail pointer to "NULL"		
Contact *head=NULL,*tail=NULL;								// declaring and intializing head,tail pointer to "NULL"
const char *PASS="srmap123";
int duplication_check(char a[]){
	Contact *temp;
	temp=head;
	while(temp!=NULL&&strcmp(temp->name,a)!=0){
	temp=temp->next;										// traversing each contact
	}
	if(temp==NULL)
	return 0;												// no duplicate contact
	else
	return 1;												// duplicate contact exist
}															// intializing the password as a constant
void add_contact(){											// defining the function to add contact
	Contact *newnode=NULL;
	newnode=(Contact*)malloc(sizeof(Contact));				// dynamic memory allocation
	if(newnode==NULL){
	printf("Memory allocation failed\n");
	printf("Please try again\n");							// if memory allocation is failed
	return ;
	}
	newnode->next=newnode->prev=NULL;
	newnode->fav=0;
	printf("\nEnter 1 to add in favourites(else enter zero): ");
	scanf("%d",&newnode->fav);
	if(newnode->fav==1){									// if the contact is favourite contact
	printf("\n***It is a favourite contact now***\n");		
	}
	printf("Enter the name: ");
    while((getchar())!='\n');								// Remove trailing newline
    scanf(" %49[^\n]", newnode->name);						// Taking input from the user
	if(duplication_check(newnode->name)){
    printf("\n--------contact already present--------\n");			// check whether the contact already exists or not
	return ;
	}										
	printf("Enter the phone number: ");
    while((getchar())!='\n');								// Remove trailing newline	
	scanf("%19[^\n]", newnode->phone); 					// Taking input from the user
	printf("Enter the EmailId:");							
    while((getchar())!='\n');								// Remove trailing newline
	scanf("%59[^\n]", newnode->email); 					// Taking input from the user
	if(head==NULL){											// if the contact is the first contact
	head=tail=newnode;
	}
	else{
	tail->next=newnode;
	newnode->prev=tail;									// if the contact is not first contact
	tail=newnode;										// using tail pointer so that insertion at end can be done in O(1) time complexity.	
    }
	printf("\n--Contact added successfully--\n");
	return ;
}
void add_private_contact(){
	char password[50];
	printf("Enter password:\n");	
	while((getchar())!='\n');								// Remove trailing newline	
	scanf("%49s",password);									// Taking input from the user
	if(strcmp(password,PASS)==0){
	Private *newnode=NULL;
	newnode=(Private*)malloc(sizeof(Private));				// dynamic memory allocation
	if(newnode==NULL){
	printf("Memory allocation failed\n");
	printf("Please try again\n");							// if memory allocation is failed
	return ;
	}
	newnode->next=newnode->prev=NULL;
	printf("Enter the name: ");
    while((getchar())!='\n');								// Remove trailing newline
	scanf(" %49[^\n]", newnode->name); 						// Taking input from the user	
	printf("Enter the phone number: ");
    while((getchar())!='\n');								// Remove trailing newline	
	scanf(" %19[^\n]", newnode->phone); 					// Taking input from the user
	printf("Enter the EmailId:");							
    while((getchar())!='\n');								// Remove trailing newline
	scanf(" %59[^\n]", newnode->email); 					// Taking input from the user
	if(p_head==NULL){										// if the contact is the first contact
	p_head=p_tail=newnode;
	}
	else{
    p_tail->next=newnode;
    newnode->prev=p_tail;								// if the contact is not first contact
    p_tail=newnode;
    }
	printf("\n--Private Contact added successfully--\n");
	return ;
}
	else{
	printf("Password incorrect\n");
	printf("Please try again:\n");							// if admin enter wrong password
	return ;
	}
}
void display_contact(Contact *temp){
	printf("\nName: %s\n",temp->name);						// defining display function to display contact details
    printf("Phone: %s\n",temp->phone);
    printf("Email ID: %s\n",temp->email);
    printf("--------------------\n");
    return ;
}
void priv_display_contact(Private *temp){
	printf("\nName: %s\n",temp->name);						// defining display function to display contact details
    printf("Phone: %s\n",temp->phone);
    printf("Email ID: %s\n",temp->email);
    printf("--------------------\n");
    return ;
}
void display_contacts(){
	if(head==NULL)											// if  contacts are not created yet
	printf("\n####No contacts are stored####\n");
	else{
	printf("\n*************Contacts created are *************\n");	
	Contact* temp=head;
	while(temp!=NULL){
	display_contact(temp);									// calling display_contact function to display details of contact
	temp=temp->next;
	}
	}
	return ;
}
void priv_display_contacts(){
	char password[50];
	printf("Enter password:\n");
	while((getchar())!='\n');
	scanf("%49s",password);
	if(strcmp(password,PASS)==0){
	if(p_head==NULL)										// if  contacts are not created yet
	printf("\n####No Private contacts are stored####\n");
	else{
	printf("\n*************Private Contacts created are *************\n");
	Private* temp=p_head;
	while(temp!=NULL){
	priv_display_contact(temp);							// calling display_contact function to display details of contact
	temp=temp->next;
	}
	}
	return ;
}	else{
	printf("Password incorrect\n");
	printf("Please try again:\n");
	return ;
	}
}
void priv_create_file(){											// defining function to create and store all contacts in the file
    char password[50];
	printf("Enter password:\n");
	while((getchar())!='\n');										// removing trail new line
	scanf("%s",password);											// asking password from the user
	if(strcmp(password,PASS)==0){									// verifying if the password entered is correct or wrong			
	if(p_head==NULL){
	printf("\n#### No Private contacts are stored ####\n");			// if no contacts created
	return;
	}
    else{
	FILE *fptr;
	fptr=fopen("priv_contacts.txt","a");							// opening the file in 'a' mode so that old contacts are not overwritten
	if(fptr==NULL){
	printf("Failed to open the file\n");
	printf("Please try again\n");									// if unable to open file
	return ;
	}
	Private *temp=p_head;
	fprintf(fptr,"\n*************Contacts created are *************\n");
	while(temp!=NULL){
	fprintf(fptr,"\nName: %s\n",temp->name);
    fprintf(fptr,"Phone: %s\n",temp->phone);					// prints the details of contact in the file
    fprintf(fptr,"Email: %s\n",temp->email);
    fprintf(fptr,"--------------------\n");
    temp=temp->next;
	}
	printf("###### Contacts are sucessfully stored in file 'priv_contact.txt' ######\n");
	printf("\n###### kindly open the folder to access contacts\n");
	fclose(fptr);													// closes the file after storing the details of the contacts
	return ;
    }
}	
	else{
	printf("Password incorrect\n");
	printf("Please try again:\n");
	return ;
	}
}
void display_fav(){
	int flag=0;								// defining function to display only favourite contacts
	if(head==NULL)
	printf("\n#### No contacts are stored ####\n");
	else{
	Contact *temp=head;
	printf("\n******** Favourite Contacts created are********\n");
	while(temp!=NULL){
	if(temp->fav==1){
	flag=1;								// checking if the contact is favourite or not
	display_contact(temp);
	}
	temp=temp->next;
	}
	if(flag==0)
	printf("\nNo favorite contacts created till now\n");
}
	return ;
}
void delete_contact(){										// defining function to delete contact
	if(head==NULL){
	printf("\n#### No contacts are stored ####\n");			// if there is no contacts
	return;
	}
	char name[50];
	printf("Enter the name: ");
    while((getchar())!='\n');
	scanf("%49[^\n]",name); 								// Remove trailing newline 
	Contact* current=head;
	while(current!=NULL&&strcmp(current->name,name)!= 0)	// traversing the contacts whether contact exist or not
	current=current->next;
	if(current==NULL) 
	printf("\n## Contact not found ##\n");
	else {
		if(current->prev==NULL&&current->next==NULL){
			// If contact is the only node in the list
			head=NULL;
		}
		else if(current->prev==NULL) {
			// If contact is in the first node
			head=current->next;
			head->prev=NULL;
		}
		else if(current->next==NULL) {
			 // If contact is in the last node
			current->prev->next=NULL;
		}
		else {
			// If contact is in middle nodes
			current->prev->next=current->next;
			current->next->prev=current->prev;
		}
		free(current);
		printf("## Contact deleted successfully ##\n");
	}
}
void modify_contact(){											// defining function to modify the contact
	if(head==NULL){
	printf("\n#### No contacts are stored ####\n");				// if contacts are not created
	return;
	}
	char name[50];
    printf("\nEnter name to modify: ");							// takes name from the user to modify the contact
    while((getchar())!='\n');
	scanf("%49[^\n]",name); 
    Contact *current=head;
    while(current!=NULL&&strcmp(current->name,name)!=0)			// traversing the contacts whether contact exist or not
    current=current->next;
    if(current==NULL)
    printf("\n## Contact not found##\n");						// if contact not found
    else{
    	int ch;
    	printf("Enter 1 to modify name:\n");
    	printf("Enter 2 to modify number:\n");
    	printf("Enter 3 to modify email_Id:\n");
    	printf("Enter 4 to modify all data:\n");
    	scanf("%d",&ch);										// takes input from the user according to the choice
    	if(ch==1){
		printf("\nEnter the new name: ");
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->name); 						// takes new name for the contact from the user
		printf("##Contact modified successfully##\n");
		}
		else if(ch==2){
    	printf("\nEnter the new phone number: ");		
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->phone);						// takes new number for the contact from the user
		printf("##Contact modified successfully##\n");
		}
		else if(ch==3){
    	printf("\nEnter the new email_Id: ");					// takes new email fot the contact fromt the user
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->email);
		printf("##Contact modified successfully##\n");
    	}
    	else if(ch==4){											// for updating all the details
    	printf("Enter new name: ");
    	while((getchar())!='\n');
		scanf(" %49[^\n]",current->name); 						// Remove trailing newline
		printf("Enter the phone number: ");
    	while((getchar())!='\n');
		scanf(" %19[^\n]",current->phone); 						// Remove trailing newline
		printf("Enter the EmailId:");
    	while((getchar())!='\n');
		scanf(" %59[^\n]",current->email);
		printf("##Contact modified successfully##\n");
		}
		else{
		printf("#####Invalid Choice#####\n");					// if user enter invalid choice
		printf("#####Please Try Again#####\n");
		}
	}
}
void number_of_contacts(){										// defining the function to count how may contacts are created
    Contact *temp;
        temp=head;
        int count=0;
        int favourite=0;
    while(temp!=NULL){
        if(temp->fav==1)										// if the contact is favourite
        favourite++;
        count++;
        temp=temp->next;
    }
	printf("\nNumber of contacts created:%d\n",count);				// output how many contacts are created
	printf("Number of favourite contacts created:%d\n",favourite);
	return ;
}
void create_file(){							// defining function to create and store all contacts in the file
    if(head==NULL){
	printf("\n#### No contacts are stored ####\n");			// if no contacts created
	return;
	}
    else{
	FILE *fptr;
	fptr=fopen("contacts.txt","a");						// opening the file in 'a' mode so that old contacts are not overwritten
	if(fptr==NULL){
	printf("Failed to open the file\n");
	printf("Please try again\n");						// if unable to open file
	return ;
	}
	Contact *temp=head;
	fprintf(fptr,"\n*************Contacts created are *************\n");
	while(temp!=NULL){
		fprintf(fptr,"\nName: %s\n",temp->name);
    	fprintf(fptr,"Phone: %s\n",temp->phone);		// prints the details of contact in the file
    	fprintf(fptr,"Email: %s\n",temp->email);
    	fprintf(fptr,"--------------------\n");
    	temp=temp->next;
	}
	printf("###### Contacts are sucessfully stored in file 'contact.txt' ######\n");
	printf("\n Kindly open the folder to access the contacts\n");
	fclose(fptr);														// closes the file after storing the details of the contacts
	return ;
    }
}
void display_by_name(){													// defining function to serach contact by name
		Contact *temp;
		temp=head;
		if(head==NULL)
		printf("###### No Contacts created ######\n");					// if there is no contacts
		else{
			char nam[30];
			printf("Enter name to search\n");							// takes name from the user for searching
			while((getchar())!='\n');
			scanf(" %29[^\n]",nam);
			while(temp!=NULL&&strcmp(temp->name,nam)!=0){
			temp=temp->next;											// traversing each contact
			}
			if(temp==NULL)
			printf("###### No contact found ######\n");					// if not found
			else{
			printf("###### Contact found Sucessfully ######\n");		// if found displaying the details of the contcat
			if(temp->fav==1)
			printf("It is a favourite contact\n");
			display_contact(temp);
			}
		}
		return ;
}
int main(){				// main function
	int choice,a=1;		// declaring choice variable
	printf("---------------------------Welcome to Contact Store---------------------------\n");
	while(a==1){
		printf("\n 1 to add contact\n");
		printf(" 2 to display contacts\n");
		printf(" 3 to delete contact\n");
		printf(" 4 to modify contact\n");
		printf(" 5 to display favourite contacts only \n");
		printf(" 6 to display number of contacts created till now\n");
		printf(" 7 to save all the contacts in a file\n");
		printf(" 8 to search contact and display if exists\n");
		printf(" 9 to add private contact\n");
		printf("10 to display private contacts\n");
		printf("11 to save private contacts in a file\n");
		printf("12 to exit\n");			
		printf("enter the choice: ");
		while(scanf("%d",&choice)!=1){
        printf("Invalid input. Please enter a valid choice:\n");
        while((getchar())!='\n'); 			// Clear the input buffer
    }										// taking choice from the user
		switch(choice){						// constructed a switch case as per the choices
			case 1:
				add_contact();				// calling function to add contact
				break;
			case 2:
				display_contacts();			// calling function to display contacts
				break;
			case 3:
			    delete_contact();			// calling function to delete contact
				break;
			case 4:
				modify_contact();			// calling function to modify contact
				break;
			case 5:
				display_fav();				// calling function to display favourite contacts
				break;
			case 6:
				number_of_contacts();		// calling function to count number if contacts present
				break;
			case 7:
				create_file();				// calling function to create a file and store the data
				break;	
			case 8:
				display_by_name();			// calling function for searching the contact by name
				break;	
			case 9:
				add_private_contact();		// calling function to add privte contact
				break;
			case 10:
				priv_display_contacts();	// calling function to display private contacts
				break;
			case 11:
				priv_create_file();			// calling function to create a file to save privte contacts
				break;				
			case 12:
				a=0;						// make a=0 to terminate the while loop and exit from the program
				break;
			default:
				printf("\n-----Invalid choice-----\n");		// if user enter invalid choice
				printf("*******Please try again*******\n");
		}
	}
	printf("\n*******Thank You*******");
	return 0;
}
