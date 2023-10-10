/*====================== Includes ======================*/

#include <stdio.h>
#include "student.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

/*=============== Start Of Global Variable Definition Part ===============*/

FILE *my_file = NULL;
FILE *my_temp_file = NULL;
unsigned int c = 0;

/*=============== End Of Global Variable Definition Part ===============*/

/**
 * @brief   add student's data to 'student.txt' file
 * @param   the address of the object std
 */

void Add_a_new_student(student_t *std)
{
    const char search_id[_MAX_ID_LENGHT];
    bool check_id;

    my_file = fopen("student.txt", "a"); // open the file in append mood to avoid overwriting
    if (my_file == NULL)  //check if there a problem opening the file
    {
        printf("erorr!!\n");
    }
    else
    {

        printf("enter student name : ");
        fflush(stdin);
        gets(std->name);
        printf("enter student ID : ");
        fflush(stdin);
        gets(std->id);
        strcpy(search_id,std->id);
        check_id = is_id_exists(search_id);
        while(strlen(std->id) !=9 || check_id == 1)      //validate the id 
        {
            if(check_id == 1)
            {
                printf("this ID is already token !!\n");
            }
            else if(strlen(std->id)!=9)
            {
                printf("Student ID must be 9 digits! Please enter a valid ID.\n");
            }
            printf("enter student ID : ");
            fflush(stdin);
            gets(std->id);
            strcpy(search_id,std->id);
            check_id = is_id_exists(search_id);
        }
        printf("enter student cumulative gpa : "); 
        scanf("%f", &std->cgpa);    
        while(std->cgpa<0 || std->cgpa >4)      //validate the cumulative gpa
        {
            printf("student's cumulative gpa can't be less or more than 4.00 !! \n");
            printf("enter student cumulative gpa : ");
            scanf("%f", &std->cgpa);
        }
        printf("enter student level : ");
        scanf("%i", &std->level);
        my_file = fopen("student.txt", "a");
        c = fprintf(my_file, "%s : name [%s] - cumulative gpa [%0.2f] - level [%i]\n======================================================================================================================\n"
        , std->id, std->name, std->cgpa, std->level); //write the data in 'student.txt' file
        printf("data is stored successfully in \'student.txt\'");
    }
    fclose(my_file);  // close the file and end the access to it
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief   search for student in the 'student.txt' file by id
 * @param   the address of the object std
 * @ret_val  if student is found ==> the line where student's data is storied 
 *           if student is't found ==> -1
 */

int Search_students(student_t *std)
{
    my_file = fopen("student.txt", "r"); //open the file in read mood

    char search[_MAX_ID_LENGHT]; // a char array to sotre the id in it as a string data type to benefit from strncmp while searching
    char line[_MAX_LINE_LENGHT]; //  a char buffer  array to sotre lines form the 'student.txt' file
    int lineNumber = 0; // line counter
    char flag = 0; //flag to stop the loop

    printf("enter student's ID : ");
    fflush(stdin);
    scanf("%s",search);
    printf("\n");
    if (my_file == NULL)  //check if there a problem opening the file
    {
        printf("erorr!!\n");
    }
    else
    {
        while (fgets(line, sizeof(line), my_file) != NULL)  //fgets is a function used to read a line from a file and store it in line buffer array
        {                                                   // the loop will stop if processed all the lines or reached the end of the file.
            lineNumber++;
            if (strncmp(line, search, 9) == 0)    // comparing user's id to line id
            {
                flag = 1;
                printf("Found student on line %d . Data ==> %s \n", lineNumber, line);
                break;
            }
        }
        if (flag != 1)
        {
            printf("student [%s] not found :)\n", search);
            fclose(my_file);
            return -1;
        }
        else
        {
            fclose(my_file);
            return lineNumber;
        }
    }
    fclose(my_file);
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief   edit the data of certain student 
 * @param   the address of the object std
 */

void Edit_a_student(student_t *std)
{
    int delete_line;
    const char file[] = "student.txt";               // array to hold the name of the main file
    const char temp_file[] = "temp_____student.txt"; // array to hold the temporary of the main file
    char buffer[_MAX_LINE_LENGHT];
    bool keep_reading = true;
    int current_line = 1;

    delete_line = Search_students(std); // using Search_students function to ask the user for id and return the user data (if found) to edit

    if (delete_line > 0) //check if Search Students function returned a valid line number
    {
        my_file = fopen(file, "r"); //open the file in read mood
        my_temp_file = fopen(temp_file, "w"); //open a temporary file in write mood

        do
        {
            fgets(buffer, _MAX_LINE_LENGHT, my_file); 
            if (feof(my_file))  // check if we reached the end of the file (feof)
            {
                keep_reading = false;
            }
            else if (current_line != delete_line)
            {
                fputs(buffer, my_temp_file); // store all the lines form our main file 'student.txt' in the buffer array and write it in our temporary file 'temp_____student.txt'
            }                               // !! except of the line which contains the old data (the line which Search_students returned ) !!
            current_line++;

        } while (keep_reading);

        fclose(my_file);       // close the file and end the access to it
        fclose(my_temp_file); // close the file and end the access to it
        
        int ret1 = remove(file);           // delete the main file 'student.txt'
        int ret2 = rename(temp_file, file); // change the name of the temporary file from ('temp_____student.txt') to ('student.txt')
                                            // notice !! we just deleted the line which contains the old data
        my_file = fopen(file, "a");         // and we know will write the new data in the renamed file
        printf("enter student new name : ");
        fflush(stdin);
        gets(std->name);
        printf("enter student new ID : ");
        fflush(stdin);
        gets(std->id);
        printf("enter student new cumulative gpa : ");
        scanf("%f", &std->cgpa);
        printf("enter student new level : ");
        scanf("%i", &std->level);
        c = fprintf(my_file, "%s : name [%s] - cumulative gpa [%0.2f] - level [%i]\n======================================================================================================================\n", std->id, std->name, std->cgpa, std->level);
        printf("data is stored successfully in \'student.txt\'\n");
    }
    else
    {
        printf("Error !!\n");
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief   delete the data of certain student 
 * @param   the address of the object std
 */

void Delete_student(student_t *std)
{

    int delete_name;
    char yes_no; 
    char buffer[_MAX_LINE_LENGHT]; // to store the lines 
    bool keep_reading = true;  //flag to stop the loop
    int current_line = 1;
    const char file[] = "student.txt";
    const char temp_file[] = "temp_____student.txt";

    delete_name = Search_students(std); // use Search_students function to find our student 

    if (delete_name > 0) //check if Search Students function returned a valid line number
    {
        printf("are you sure you want to delete this student from the system ? \nif yes press (Y/y) if no press(N/n)\n");
        fflush(stdin);
        scanf("%c", &yes_no);
        if (yes_no == 'Y' || yes_no == 'y')  //check if the user is sure about deleting the sudent's data
        {
            my_file = fopen(file, "r");
            my_temp_file = fopen(temp_file, "w");           /*↓↓↓ the same steps as (Edit_a_student function) except of the writng part ↓↓↓*/

            do
            {
                fgets(buffer, _MAX_LINE_LENGHT, my_file);
                if (feof(my_file))
                {
                    keep_reading = false;
                }
                else if (current_line != delete_name)
                {
                    fputs(buffer, my_temp_file);
                }
                current_line++;

            } while (keep_reading);

            fclose(my_file);
            fclose(my_temp_file);
            int ret1 = remove(file);
            int ret2 = rename(temp_file, file);

            if (ret1 == 0 && ret2 == 0)
            {
                printf("student is deleted successfully. \n");
            }
            else
            {
                printf("Error !!\n");
            }
        }
        else if (yes_no == 'N' || yes_no == 'n')
        {
            printf("the program is finished :)\n");
        }
        else
        {
            printf("undefined choice !!\n");
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief   printing all the data in the 'student.txt' file 
 * @param   the address of the object std
 */

void show_all_student(student_t *std)
{
    char line[256];
    int lineNumber = 0;

    my_file = fopen("student.txt", "r");
    printf("=====================================================================\n\n");
    while (fgets(line, sizeof(line), my_file) != NULL)
    {
        lineNumber++;
        if(line[0]!='=')
        {
            printf("line %d ==> %s \n", lineNumber, line);
        }
    }
    printf("=====================================================================\n");
    fclose(my_file);
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief   deleting all the data from the 'student.txt' file 
 * @param   the address of the object std
 */

Delete_all_student(student_t *std)
{
    char yes_no1;

    printf("are you sure you want to delete all students's data in the system ?\nif yes press (Y/y) if no press(N/n)\n");
    fflush(stdin);
    scanf("%c", &yes_no1);
    if (yes_no1 == 'Y' || yes_no1 == 'y')
    {
        my_file = fopen("student.txt", "r");
        fclose(my_file);
        remove("student.txt");
        my_file = fopen("student.txt", "w");
        fclose(my_file);
        printf("all the data is deleted successfully \n");
    }
    else if (yes_no1 == 'N' || yes_no1 == 'n')
    {
        printf("the program is finished :)\n");
    }
    else
    {
        printf("undefined choice !!\n");
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief    check if the id is token or not 
 * @param    a copy from the id
 * @ret_val  a bool value true (if the id is token)
 *                        false (if the id is't toekn)
 */

bool is_id_exists(const char id[])
{
    FILE *my_file = fopen("student.txt", "r");
    char line[_MAX_LINE_LENGHT];
    bool ret_val= false;
    if (my_file == NULL) {
        printf("error opening the file.\n");
        return false;
    }
    
    while (fgets(line, sizeof(line), my_file) != NULL) {
        if (strncmp(line, id, 9) == 0) {
            ret_val=true;
            break;
        }
    }
    
    fclose(my_file);
    return ret_val;
}
