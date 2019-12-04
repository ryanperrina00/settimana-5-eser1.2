//Authors : Davide Merli, Ryan Perrina, Manuel Luzietti, Giulia Tedeschi
//Week    : 05
//Exercise: 01
//Version : 1
//Date    : 2019/12/08

#include <stdio.h>              //standard input/output
#include <stdbool.h>            //for boolean variables
#include <string.h>             //for strcpy() function
#include<stdlib.h>
//constant values declaration
#define NUM_EXAMS 5
#define MAX_STUDENTS 10
void checkpointer (struct teachings* ptr)
{
    if(ptr==NULL)                               //check if there is enough space to contain the dim number
    {
        printf("Sorry, not enough space!\n\n");
        exit(1);                                //if not, end program
    }
}
int main()
{
    //variables declaration
    char choice;
    int n_students=0, n_exam=0, searchSerialNumber, check, stud;
    bool found;

    //student structure declaration
    struct students
    {
        int serial_number;
        char name[16], surname[16];
        int year;
        //exam structure declaration
        struct exams
        {
            int exam_code;
            int grade;
        }study_plan[NUM_EXAMS];
    }*student;
    struct students* temp,*ptr;


    //teachings structure declaration
    struct teachings
    {
        int teaching_code;
        char description[15];
        int teaching_year;
        int credits;
    }*teaching;           //0: Programming, 1: Calculus, 2: Algorithms, 3: Geometry, 4: English
    struct teachings *t;

    //teaching structure initialization

    teaching=(struct teachings*)malloc(sizeof(struct teachings)*NUM_EXAMS);
    checkpointer(teaching);
    struct teachings* p;
    p=teaching;
    p->teaching_code=1;
    strcpy(p->description, "Programming");
    p->teaching_year=2019;
    p->credits=12;
    p++;
    p->teaching_code=2;
    strcpy(p->description,"Calculus");
    p->teaching_year=2019;
    p->credits=12;
    p++;
    p->teaching_code=3;
    strcpy(p->description, "Algorithms");
    p->teaching_year=2019;
    p->credits=12;
    p++;
    p->teaching_code=4;
    strcpy(p->description, "Geometry");
    p->teaching_year=2019;
    p->credits=6;
    p++;
    p->teaching_code=5;
    strcpy(p->description, "English");
    p->teaching_year=2019;
    p->credits=6;

    printf("Welcome to the UNIBO database!");
    while(true)                 //cycle will continue until user inserts 5, which ends the program
    {
        CHOOSE: printf("\nWhat do you want to do:\n\n"      //asking user what operation he wants to execute
            "1) Insert new student\n"
            "2) Print student info\n"
            "3) Modify study plan\n"
            "4) Compute average of all students\n"
            "5) Exit program\n");
        scanf("%c",&choice);                                //input choice variable
        fflush(stdin);                                      //cleaning standard input

        switch(choice)      //check which operation the user has chosen to do
        {
            case '1':       //check if choice is equal to 1
                student=(struct students*)malloc(sizeof(struct students)*2);
                checkpointer(student);
                temp=student;
                ptr=student;
                printf("Insert student serial number           : ");
                scanf("%d", &(temp->serial_number));  //serial number input
                fflush(stdin);                                      //cleaning standard input

                for(int i=0;i<n_students;i++)   //cycle will check if the inserted number already exists in the database
                {
                    if(ptr->serial_number==temp->serial_number)
                    {
                        printf("\nERROR!\nThis serial number already exists!\n");
                        goto CHOOSE;            //if so, go back to the program menu
                    }
                    ptr++;
                }
                printf("Insert student name (max 15 letters)   : ");
                scanf("%s",&(temp->name));        //student name input
                fflush(stdin);                                  //cleaning standard input
                printf("Insert student surname (max 15 letters): ");
                scanf("%s",&(temp->surname));     //student surname input
                fflush(stdin);                                  //cleaning standard input
                YEAR: printf("Insert year of registration            : ");
                check=scanf("%d",&(temp->year));  //year of registration of student input
                fflush(stdin);                                  //cleaning standard input
                if(!check || temp->year<1980 || temp->year>2019)    //check if year is plausible
                {
                    printf("\nERROR! Invalid year!\n\n");
                    goto YEAR;                                  //if not, user is asked to insert a different year
                }
                for(int i=0;i<NUM_EXAMS;i++)        //cycle will print initialize the exam grades to 0
                    temp->study_plan[i].grade=0;  //initializing grade
                n_students++;                       //increasing student counting variable
                temp++;
                break;                              //end case 1

              case '2':       //check if choice is equal to 2
                printf("\nInsert student serial number: ");
                scanf("%d",&searchSerialNumber);    //insert serial number to look for in the database
                fflush(stdin);                      //cleaning standard input
                ptr=student;
                p=teaching;
                for(int i=0;i<n_students;i++)   //cycle will search inserted serial number
                {
                    if(searchSerialNumber==ptr->serial_number)    //check if number is found
                    {
                        //if so, print student info
                        printf("\n");
                        printf("Name                : %s\n", ptr->name);
                        printf("Surname             : %s\n", ptr->surname);
                        printf("Year of registration: %d\n", ptr->year);
                        printf("Grades              :\n");
                        for(int j=0;j<NUM_EXAMS;j++)    //cycle will print exam names and grade
                            {
                                printf("  Exam                : %-11s\n", p->description);
                                printf("  Grade               : %d\n", ptr->study_plan[j].grade);
                                p++;
                            }
                        ptr++;
                        found=true;     //initializing boolean variable to true value
                        break;          //exit cycle
                    }
                    else
                        found=false;    //initializing boolean variable to true value
                }

                if(found==false)    //check if student has been found
                    printf("\nERROR! Student not found!\n");    //if they have not, print error
                break;                              //end case 2

               case '3':       //check if choice is equal to 3
                printf("\nInsert student serial number: ");
                scanf("%d",&searchSerialNumber);        //insert serial number to look for in the database
                fflush(stdin);
                ptr=student;                        //cleaning standard input
                for(int i=0;i<n_students;i++)       //cycle will search inserted serial number
                {
                    found= ptr->serial_number==searchSerialNumber ? true : false; //if student is found, initialize
                                                                //boolean variable to true, otherwise initialize it to false
                    stud=i;         //setting the student position in the array
                    if(found==true) //check if student has been found
                        break;
                        ptr++;      //if so, end cycle
                }

                if(found==false)    //check if student has been found
                    printf("\nStudent not found!\n");   // if they have not, print error
                else    //otherwise...
                {
                    do  //cycle will allow user to insert new grades or modify them
                    {
                        printf("\nInsert exam code (0 to exit):\n");
                        p=teaching;
                        for(int i=0;i<NUM_EXAMS;i++) {   //cycle will print the possible choices
                            printf("%d) %s\n", i+1, p->description);
                            p++;
                            }   //printing exam name
                        check=scanf("%d",&choice);      //input choice variable
                        fflush(stdin);                  //cleaning standard input
                        if(choice<0 || choice>5 || !check)  //check if the inserted choice is correct
                        {
                            printf("\nERROR! Invalid choice!\n");
                            continue;                   //if it is not, print error
                        }
                        else if(choice!=0)              //otherwise, check if it is different from 0
                        {
                            printf("Insert exam grade: ");
                            scanf("%d", &ptr->study_plan[choice-1].grade); //input grade
                            fflush(stdin);                                          //cleaning standard input
                            if(ptr->study_plan[choice-1].grade>30 || ptr->study_plan[choice-1].grade<0)
                            {
                                printf("\nERROR! Invalid grade!\n");
                                ptr->study_plan[choice-1].grade=0; //if the inserted grade is incorrect, reset it to 0
                                continue;                                   //repeat cycle
                            }
                        }
                    }while(choice!=0); //cycle ends if the user inserts 0 as their choice
                }
                break;                              //end case 3

              case '4':    //check if choice is equal to 4
                ptr=student;
                p=teaching;
                for(int i=0;i<n_students;i++)   //cycle will print students average
                {
                    //local variables declaration
                    float average=0;
                    int count_credit=0;
                    for(int j=0;j<NUM_EXAMS;j++)    //cycle will count the exams with a grade different from 0
                    {
                        if(ptr->study_plan[j].grade!=0)   //check if grade is equal to 0
                        {
                            average+=ptr->study_plan[j].grade*p->credits;    //if it is not, sum grade*credits
                            count_credit+=p->credits;                          //increase counting credits variable
                        }
                    p++;
                    }
                    //printing student serial number and average
                    printf("\n\n%02d)", i+1);
                    printf("\n  Serial number   : %d", ptr->serial_number);
                    printf("\n  Average         : %.2f", count_credit==0 ? 0 : average/count_credit);
                ptr++;
                }
                printf("\n");
                break;                              //end case 4

            case '5':       //check if choice is equal to 5
                printf("\nProgram closing.\n");
                free(student);
                free(teaching);
                exit(1);    //if so, end program

            default:        //check if choice is none of the above
                printf("\nERROR! Invalid choice!\n");
                continue;   //if so, repeat cycle
        }
    }
}
