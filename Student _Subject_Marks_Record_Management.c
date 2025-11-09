#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct user{
    int password;
    char str[100];
    int count;
}x;

int  Admin(){
    printf("\n        ===== L  O  G  I  N  =====  \n");
    printf(" \n      A D M I N     :    ");
    scanf("%s",x.str);
    printf("\n   P A S S W O R D  :    ");
    scanf("%d",&x.password);
    printf("\n\nChecking ");
    for(int i=0;i<5;i++){
        fflush(stdin);
        sleep(1);
        printf(". ");
    }
    printf("\n");
}

void getFileName(char *k){
    if(strcmp(x.str,"PSPC") == 0 && x.password == 1111 )
        strcpy(k,"pspc.txt");
    else if (strcmp(x.str,"BEEE") == 0 && x.password == 2222 )
        strcpy(k,"bee.txt");
    else if (strcmp(x.str,"MATHS") == 0 && x.password == 3333 )
        strcpy(k,"maths.txt");
    else
        strcpy(k,"Invalid.txt");
}

int Menubar(){
    int choice;
    printf("\n| ~~~~~ S T U D E N T  -  S U B J E C T   M A R K S    R E C O R D  -  M A N A G E M E N T ~~~~~ |\n");
    printf("\n1. ADD STUDENT RECORD");
    printf("\n2. RECORD UPDATE");
    printf("\n3. DISPLAY ENTIRE RECORD");
    printf("\n4. SEARCH STUDENT RECORD");
    printf("\n5. DELETE STUDENT RECORD");
    printf("\n6. EXIT\n");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);
    return choice;
}

struct studentrecord{
        int roll;
        char name[50];
        float marks;
    }s;


void addStudent(){
    FILE *p;
    char k[50];
    getFileName(k);
    p = fopen(k,"r");

    if (p == NULL) {
        //printf("Error opening file!\n");
        p = fopen(k,"w");
        fclose(p);
        p = fopen(k,"r");
        return;
    }

    struct studentrecord s;
    int roll,found = 1;
    printf("\nEnter Roll Number: ");
    scanf("%d",&roll);
    while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
        if(roll == s.roll){
            printf("\nRoll No %d student already exist..\n",roll);
            found = 0;
            break;
        }
    }
    if(found){
    p = fopen(k,"a");
    s.roll = roll ;
    printf("Enter Name: ");
    scanf("%s",s.name);
    printf("Enter %s Marks: ",x.str);
    scanf("%f",&s.marks);
    fprintf(p, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(p);
    printf("\nRecord Added Successfully\n");
    fclose(p);
    }
}

void update(){
    int roll,found = 0;
    FILE *p , *temp;
    char k[50];
    getFileName(k);
    p = fopen(k,"r");
    temp = fopen("temp.txt","w");

    if(p == NULL || temp == NULL){
        printf("Error: File not opened...");
        return;
    }
    printf("Enter the student Roll number you want to update that student record: ");
    scanf("%d",&roll);

    while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
        if(s.roll == roll){
            found = 1;
            printf("\nRecord Found\n");
            printf("Enter new name: ");
            scanf("%s",s.name);
            printf("Enter new marks: ");
            scanf("%f",&s.marks);
        }
        fprintf(temp,"%d %s %.2f\n",s.roll,s.name,s.marks);
    }
    fclose(p);
    fclose(temp);
    remove(k);
    rename("temp.txt",k);

    if(found){
        printf("Record Updated Successfully..\n");
    }
    else{
        printf("Record not found..!\n");
    }

}

void display(){     
    FILE *p;
    char k[50];
    getFileName(k);
    p = fopen(k,"r");
    if(p == NULL){
        printf("Error: File not opened...");
        return;
    }
    printf("\n~~~~~ S T U D E N T - R E C O R D s ~~~~~\n\n");
    int i=1;
    while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
        printf("\n\ns t u d e n t - %d\n",i);
        printf("\nRoll No: %d\nStudent Name: %s\n%s Marks: %.2f\n",s.roll,s.name,x.str,s.marks);
        printf("-----------------------------\n");
        i+=1;
    }
    x.count = i-1;
    printf("\nTotal No of Students in this file is %d\n",x.count);
    fclose(p);
    printf("\n~~~ E N D - O F - F I L E ~~~\n\n");
}

void search(){

    printf("\nWhat options you want to search\n");
    printf("1. By Roll Number\n");
    printf("2. By Name");

    int option;
    printf("\nEnter your option: ");
    scanf("%d",&option);

    if(option == 1){
        int roll,found = 0;
        FILE *p;
        char k[50];
        getFileName(k);
        p = fopen(k,"r");

        if(p == NULL){
            printf("Error: File not opened...");
            return;
        }
        printf("Enter the student Roll number you want to search: ");
        scanf("%d",&roll);

        while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
            if(s.roll == roll){
                found = 1;
                printf("\n--- R E C O R D - F O U N D ---\n");
                printf("Roll No: %d\nName: %s\nPSPC Marks: %.2f\n",s.roll,s.name,s.marks);
            }
        }
        if(found){
            printf("\nRecord found\n");
        }
        else{
            printf("\nRoll No not found\n");
        }
    }
    else if (option == 2) {
        char name[50],found = 0;
        FILE *p;
        char k[50];
        getFileName(k);
        p = fopen(k,"r");

        if(p == NULL){
            printf("Error: File not opened...");
            return;
        }
        printf("Enter the student Name you want to search: ");
        scanf("%s",name);

        while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
            if(strcmp(s.name,name) == 0){
                found = 1;
                printf("\n--- R E C O R D - F O U N D ---\n");
                printf("Roll No: %d\nName: %s\nPSPC Marks: %.2f\n",s.roll,s.name,s.marks);
            }
        }
        if(found){
            printf("\nRecord Found\n");
        }  
        else{
            printf("\nName not found\n");
        }
    }  
    else{
        printf("\nPlease Enter Valid Option..\n");
    }
}

void deleterecord(){
    printf("\nWhat options you want to delete\n");
    printf("1. By Roll Number\n");
    printf("2. By Name");

    int option;
    printf("\nEnter your option: ");
    scanf("%d",&option);

    if(option == 1){
        int roll,found = 0;
        FILE *p , *temp;
        char k[50];
        getFileName(k);
        p = fopen(k,"r");

        temp = fopen("temp.txt","w");
        if(p == NULL || temp == NULL){
            printf("Error: File not opened...");
            return;
        }
        printf("Enter the student Roll number: ");
        scanf("%d",&roll);

        while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
            if(s.roll == roll){
                found = 1;
                continue;
            }
            fprintf(temp,"%d %s %.2f\n",s.roll,s.name,s.marks);
        }
        
        fclose(p);
        fclose(temp);

        remove(k);
        rename("temp.txt",k);

        if(found){
            printf("\nRecord Deleted Successfully\n");
        }
        else{
            printf("\nRoll No not found\n");
        }
    }
    else if (option == 2) {
        char name[50],found = 0;
        FILE *p , *temp;
        char k[50];
        getFileName(k);
        p = fopen(k,"r");
    
        temp = fopen("temp.txt","w");

        if(p == NULL){
            printf("Error: File not opened...");
            return;
        }
        printf("Enter the student Name : ");
        scanf("%s",name);

        while(fscanf(p,"%d %s %f",&s.roll,s.name,&s.marks) != EOF){
            if(strcmp(s.name,name) == 0){
                found = 1;
                continue;
            }
            fprintf(temp,"%d %s %.2f\n",s.roll,s.name,s.marks);
        }

        // fclose(p);
        // fclose(temp);

        // remove(k);
        // rename("temp.txt",k);
        fclose(p);
        fclose(temp);

        if (remove(k) != 0)
            perror("Error deleting original file");

        if (rename("temp.txt", k) != 0)
            perror("Error renaming temp file");
        

        if(found){
            printf("\nRecord Deletted Successfully\n");
        } 
        else{
            printf("\nName not found\n");
        }
    }  
    else{
        printf("\nPlease Enter Valid Option..!\n");
    }
}
    
void project(){
    while(1){
        Admin();
    if((strcmp(x.str,"PSPC") == 0 && x.password == 1111) || 
       (strcmp(x.str,"BEEE") == 0 && x.password == 2222) ||
       (strcmp(x.str,"MATHS") == 0 && x.password == 3333)){
    printf("\nAccess Granted...\n");
    while(1){
        int catch = Menubar();
        switch (catch) {       
            case 1:
                addStudent(); break;
            case 2:
                update(); break;
            case 3:
                display(); break;
            case 4:
                search(); break;
            case 5:
                deleterecord(); break;
            case 6:
                printf("\nExiting Program..\n\n"); exit(0); 
            default:
                printf("\nEnter Valid Option..\n");
        }
    }
    }
    else{
        printf("\nInvalid Username or Password  try again..!\n\n");
    }
    }
}


int main(){
    project();
}

