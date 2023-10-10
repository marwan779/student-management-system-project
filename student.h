
/*
                    Documentation Part
===================================================================
    @file           : student.h
    @author         : marwan mohamed
    @brief          : Contains the Prototypes of the functions
===================================================================

*/



/*====================== Start Of File Gaurd ======================*/

#ifndef _STUDENT_H
#define _STUDENT_H

/*====================== Includes ======================*/
#include <stdio.h>
#include <stdbool.h>

/*====================== Macros ======================*/

#define _MAX_NAME_LENGHT 50
#define _MAX_LINE_LENGHT 500
#define _MAX_ID_LENGHT 9

/*====================== Declaration Of Structures ======================*/

typedef struct
{
   char name[_MAX_NAME_LENGHT];
   unsigned char id[_MAX_ID_LENGHT];
   float cgpa;
   unsigned int level;
} student_t;

/*================ Prototypes Of Functions ================*/

void Add_a_new_student(student_t *std);
int Search_students(student_t *std);
void Edit_a_student(student_t *std);
void Delete_student(student_t *std);
void show_all_student(student_t *std);
void Delete_all_student(student_t *std);
bool is_id_exists(const char id[]);

/*====================== End Of File Gaurd ======================*/

#endif