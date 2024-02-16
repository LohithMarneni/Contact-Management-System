#include<stdio.h>											
#include<stdlib.h>											
#include<string.h>											
typedef struct contact{										
	int fav;					
	char name[50];
    char phone[20];											
    char email[60];
    struct contact *prev,*next;
}Contact;
typedef struct priv_contact{								
	char name[50];
	char phone[20];											
	char email[60];
	struct priv_contact *prev,*next;						
}Private;
Private *p_head=NULL,*p_tail=NULL;								
Contact *head=NULL,*tail=NULL;								
const char *PASS="srmap123";
int duplication_check(char a[]){
	Contact *temp;
	temp=head;
	while(temp!=NULL&&strcmp(temp->name,a)!=0){
	temp=temp->next;										
	}
	if(temp==NULL)
	return 0;
	else
	return 1;	
}															
void add_contact(){											
	Contact *newnode=NULL;
	newnode=(Contact*)malloc(sizeof(Contact));				
	if(newnode==NULL){
	printf("Memory allocation failed\n");
	printf("Please try again\n");							
	return ;
	}
	newnode->next=newnode->prev=NULL;
	newnode->fav=0;
	printf("\nEnter 1 to add in favourites(else enter zero): ");
	scanf("%d",&newnode->fav);
	if(newnode->fav==1){									
	printf("\n**It is a favourite contact now\n");		
	}
	printf("Enter the name: ");
    while((getchar())!='\n');								
    scanf(" %49[^\n]", newnode->name);						
	if(duplication_check(newnode->name)){
    printf("\n--------contact already present--------\n");			
	return ;
	}										
	printf("Enter the phone number: ");
    while((getchar())!='\n');									
	scanf("%19[^\n]", newnode->phone); 					
	printf("Enter the EmailId:");							
    while((getchar())!='\n');								
	scanf("%59[^\n]", newnode->email); 					
	if(head==NULL){											
	head=tail=newnode;
	}
	else{
	tail->next=newnode;
	newnode->prev=tail;									
	tail=newnode;											
    }
	printf("\n--Contact added successfully--\n");
	return ;
}
void add_private_contact(){
	char password[50];
	printf("Enter password:\n");	
	while((getchar())!='\n');									
	scanf("%49s",password);									
	if(strcmp(password,PASS)==0){
	Private *newnode=NULL;
	newnode=(Private*)malloc(sizeof(Private));				
	if(newnode==NULL){
	printf("Memory allocation failed\n");
	printf("Please try again\n");							
	return ;
	}
	newnode->next=newnode->prev=NULL;
	printf("Enter the name: ");
    while((getchar())!='\n');								
	scanf(" %49[^\n]", newnode->name); 							
	printf("Enter the phone number: ");
    while((getchar())!='\n');									
	scanf(" %19[^\n]", newnode->phone); 					
	printf("Enter the EmailId:");							
    while((getchar())!='\n');								
	scanf(" %59[^\n]", newnode->email); 					
	if(p_head==NULL){										
	p_head=p_tail=newnode;
	}
	else{
    p_tail->next=newnode;
    newnode->prev=p_tail;								
    p_tail=newnode;
    }
	printf("\n--Private Contact added successfully--\n");
	return ;
}
	else{
	printf("Password incorrect\n");
	printf("Please try again:\n");							
	return ;
	}
}
void display_contact(Contact *temp){
	printf("\nName: %s\n",temp->name);						
    printf("Phone: %s\n",temp->phone);
    printf("Email ID: %s\n",temp->email);
    printf("--------------------\n");
    return ;
}
void priv_display_contact(Private *temp){
	printf("\nName: %s\n",temp->name);						
    printf("Phone: %s\n",temp->phone);
    printf("Email ID: %s\n",temp->email);
    printf("--------------------\n");
    return ;
}
void display_contacts(){
	if(head==NULL)											
	printf("\n####No contacts are stored####\n");
	else{
	printf("\n***Contacts created are *************\n");	
	Contact* temp=head;
	while(temp!=NULL){
	display_contact(temp);									
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
	if(p_head==NULL)										
	printf("\n####No Private contacts are stored####\n");
	else{
	printf("\n***Private Contacts created are *************\n");
	Private* temp=p_head;
	while(temp!=NULL){
	priv_display_contact(temp);							
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
void priv_create_file(){											
    char password[50];
	printf("Enter password:\n");
	while((getchar())!='\n');										
	scanf("%s",password);											
	if(strcmp(password,PASS)==0){												
	if(p_head==NULL){
	printf("\n#### No Private contacts are stored ####\n");			
	return;
	}
    else{
	FILE *fptr;
	fptr=fopen("priv_contacts.txt","a");							
	if(fptr==NULL){
	printf("Failed to open the file\n");
	printf("Please try again\n");									
	return ;
	}
	Private *temp=p_head;
	fprintf(fptr,"\n***Contacts created are *************\n");
	while(temp!=NULL){
	fprintf(fptr,"\nName: %s\n",temp->name);
    fprintf(fptr,"Phone: %s\n",temp->phone);					
    fprintf(fptr,"Email: %s\n",temp->email);
    fprintf(fptr,"--------------------\n");
    temp=temp->next;
	}
	printf("###### Contacts are sucessfully stored in file 'priv_contact.txt' ######\n");
	printf("\n###### kindly open the folder to access contacts\n");
	fclose(fptr);													
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
	int flag=0;								
	if(head==NULL)
	printf("\n#### No contacts are stored ####\n");
	else{
	Contact *temp=head;
	printf("\n******** Favourite Contacts created are**\n");
	while(temp!=NULL){
	if(temp->fav==1){
	flag=1;								
	display_contact(temp);
	}
	temp=temp->next;
	}
	if(flag==0)
	printf("\nNo favorite contacts created till now\n");
}
	return ;
}
void delete_contact(){										
	if(head==NULL){
	printf("\n#### No contacts are stored ####\n");			
	return;
	}
	char name[50];
	printf("Enter the name: ");
    while((getchar())!='\n');
	scanf("%49[^\n]",name); 								
	Contact* current=head;
	while(current!=NULL&&strcmp(current->name,name)!= 0)	
	current=current->next;
	if(current==NULL) 
	printf("\n## Contact not found ##\n");
	else {
		if(current->prev==NULL&&current->next==NULL){
			head=NULL;
		}
		else if(current->prev==NULL) {
			head=current->next;
			head->prev=NULL;
		}
		else if(current->next==NULL) {
			current->prev->next=NULL;
		}
		else {
			current->prev->next=current->next;
			current->next->prev=current->prev;
		}
		free(current);
		printf("## Contact deleted successfully ##\n");
	}
}
void modify_contact(){											
	if(head==NULL){
	printf("\n#### No contacts are stored ####\n");				
	return;
	}
	char name[50];
    printf("\nEnter name to modify: ");							
    while((getchar())!='\n');
	scanf("%49[^\n]",name); 
    Contact *current=head;
    while(current!=NULL&&strcmp(current->name,name)!=0)			
    current=current->next;
    if(current==NULL)
    printf("\n## Contact not found##\n");						
    else{
    	int ch;
    	printf("Enter 1 to modify name:\n");
    	printf("Enter 2 to modify number:\n");
    	printf("Enter 3 to modify email_Id:\n");
    	printf("Enter 4 to modify all data:\n");
    	scanf("%d",&ch);										
    	if(ch==1){
		printf("\nEnter the new name: ");
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->name); 						
		printf("##Contact modified successfully##\n");
		}
		else if(ch==2){
    	printf("\nEnter the new phone number: ");		
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->phone);						
		printf("##Contact modified successfully##\n");
		}
		else if(ch==3){
    	printf("\nEnter the new email_Id: ");					
    	while((getchar())!='\n');
		scanf("%49[^\n]",current->email);
		printf("##Contact modified successfully##\n");
    	}
    	else if(ch==4){											
    	printf("Enter new name: ");
    	while((getchar())!='\n');
		scanf(" %49[^\n]",current->name); 						
		printf("Enter the phone number: ");
    	while((getchar())!='\n');
		scanf(" %19[^\n]",current->phone); 						
		printf("Enter the EmailId:");
    	while((getchar())!='\n');
		scanf(" %59[^\n]",current->email);
		printf("##Contact modified successfully##\n");
		}
		else{
		printf("#####Invalid Choice#####\n");					
		printf("#####Please Try Again#####\n");
		}
	}
}
void number_of_contacts(){									
    Contact *temp;
        temp=head;
        int count=0;
        int favourite=0;
    while(temp!=NULL){
        if(temp->fav==1)										
        favourite++;
        count++;
        temp=temp->next;
    }
	printf("\nNumber of contacts created:%d\n",count);				
	printf("Number of favourite contacts created:%d\n",favourite);
	return ;
}
void create_file(){							
    if(head==NULL){
	printf("\n#### No contacts are stored ####\n");			
	return;
	}
    else{
	FILE *fptr;
	fptr=fopen("contacts.txt","a");						
	if(fptr==NULL){
	printf("Failed to open the file\n");
	printf("Please try again\n");						
	return ;
	}
	Contact *temp=head;
	fprintf(fptr,"\n***Contacts created are *************\n");
	while(temp!=NULL){
		fprintf(fptr,"\nName: %s\n",temp->name);
    	fprintf(fptr,"Phone: %s\n",temp->phone);		
    	fprintf(fptr,"Email: %s\n",temp->email);
    	fprintf(fptr,"--------------------\n");
    	temp=temp->next;
	}
	printf("###### Contacts are sucessfully stored in file 'contact.txt' ######\n");
	printf("\n Kindly open the folder to access the contacts\n");
	fclose(fptr);														
	return ;
    }
}
void display_by_name(){													
		Contact *temp;
		temp=head;
		if(head==NULL)
		printf("###### No Contacts created ######\n");					
		else{
			char nam[30];
			printf("Enter name to search\n");							
			while((getchar())!='\n');
			scanf(" %29[^\n]",nam);
			while(temp!=NULL&&strcmp(temp->name,nam)!=0){
			temp=temp->next;											
			}
			if(temp==NULL)
			printf("###### No contact found ######\n");					
			else{
			printf("###### Contact found Sucessfully ######\n");		
			if(temp->fav==1)
			printf("It is a favourite contact\n");
			display_contact(temp);
			}
		}
		return ;
}
int main(){				
	int choice,a=1;		
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
        while((getchar())!='\n'); 			
    	}									
		switch(choice){					
			case 1:
				add_contact();				
				break;
			case 2:
				display_contacts();			
				break;
			case 3:
			    delete_contact();			
				break;
			case 4:
				modify_contact();			
				break;
			case 5:
				display_fav();				
				break;
			case 6:
				number_of_contacts();		
				break;
			case 7:
				create_file();				
				break;	
			case 8:
				display_by_name();			
				break;	
			case 9:
				add_private_contact();		
				break;
			case 10:
				priv_display_contacts();	
				break;
			case 11:
				priv_create_file();			
				break;				
			case 12:
				a=0;						
				break;
			default:
				printf("\n-----Invalid choice-----\n");		
				printf("Please try again\n");
		}
	}
	printf("\n**Thank You");
	return 0;
}