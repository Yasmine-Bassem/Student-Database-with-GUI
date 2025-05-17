#ifndef _SDB_H
#define _SDB_H



#define MAX_NAME_LENGTH 20

#include <stdio.h>
#include <stdbool.h>
#include "platform_types.h"

#include "GTKHelpers.h"
#include <string.h>
#include <stdlib.h>


typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 English;
    uint32 Arabic;
    uint32 Maths;
    uint32 Total;
    char Student_Name[MAX_NAME_LENGTH];
    struct SimpleDb *NodeLink;
} student;

extern student *listhead;

#include "repository.h"

bool SDB_AddEntry(student **List, uint32 id, const char* name, uint32 year);

 /**
  * @brief get how many students in your database have added
  * @param (list) pointer to struct student
  */
void SDB_GetUsedSize(student *List, uint32* size);

 /**
  * @brief user chooses to add entry data in the database
           to add one student which is his (Name,id, year,)
           and then add to your database
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning
  */
bool SDB_DeletEntry(student **List, uint32 id);
 /**
  * @brief print the data of the user by searching on his data by the given id
  * @param (id) parameter to pass  student id
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning
  */
bool SDB_ReadEntry(student *List, uint32 id, student* result);
/**
  * @brief it gets the number of ids in the count and the list of all ids in list array
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning
  */
bool SDB_GetList(student *List, uint32* idArray, uint32* count);
 /**
  * @brief Checks if the given id the is Exist
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning.
  */
bool SDB_IsIdExist(student *List, uint32 id);
  /**
  * @brief To Display Student's Marks
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning.
  */
bool DisplayMarks(student *List, uint32 id, uint32* english, uint32* arabic,
                uint32* maths, uint32* total, char* name, uint32* year);
  /**
  * @brief To Enter student's Marks
  * @param (list) pointer to struct student
  * @retval return 1 The function is working  return 0 If there is a warning
  */
bool EnterMarks(student **List, uint32 id, uint32 english, uint32 arabic, uint32 maths);

#endif // _SDB_H
