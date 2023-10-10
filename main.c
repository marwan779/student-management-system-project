
/*
                    Documentation Part
===================================================================
 @file           : testing.c
 @author         : marwan mohamed
 @brief          : contains the main user interface
===================================================================

*/
/*====================== Includes ======================*/

#include <stdio.h>
#include "student.h"
#include "student.c"
#include <string.h>
/*=============== Start Of Global Variable Definition Part ===============*/

unsigned char choice;
student_t std;
int ret_val;

/*=============== End Of Global Variable Definition Part ===============*/

int main()
{
    printf("========================\n");
    printf("[1] Add a new student. \n[2] Search students. \n[3] Edit a student. \n[4] Delete a student. \n[5] Show all students. \n[6] Delete all students. \n[7] Exit the program.\n");
    printf("========================\n");
    printf("Enter your choice : ");
    scanf("%i", &choice);
    switch (choice)
    {
    case 1:
        Add_a_new_student(&std);
        break;
    case 2:
        ret_val = Search_students(&std);
        break;
    case 3:
        Edit_a_student(&std);
        break;
    case 4:
        Delete_student(&std);
        break;
    case 5:
        show_all_student(&std);
        break;
    case 6:
        Delete_all_student(&std);
        break;
    case 7:
        printf("the program is finished :)\n");
        break;
    default:
        printf("undefined choice !!\n");
    }
}