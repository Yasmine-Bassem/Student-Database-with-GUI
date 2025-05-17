#include "SDB.h"


/**
  * @brief To check if the identifier is not a duplicate
  * @param (id) parameter to pass  student id
  * @param (list) pointer to struct student
  * @retval return 1 if the id is existed and return 0 if the id not found.
  */



static bool ID_CHECK(uint32 id, student *List)
{
    bool status=true;
    student *TempNode=List;
    if(NULL==List)
    {
        status=false;
    }
    else
    {
        while( (NULL!=TempNode) && (id!=TempNode->Student_ID) )
        {
            TempNode=TempNode->NodeLink;
        }
        if(NULL == TempNode )
        {
            status=false;
        }
        else
        {
            show_message("Duplicate ID","This ID already exists. Please enter the ID again");
        }
    }

    return status;
}
/**************************************************************************************/

bool SDB_AddEntry(student **List, uint32 id, const char* name, uint32 year) {
    student *TempNode = new student();
    if (!TempNode) return false;

    if (ID_CHECK(id, *List)) {
        delete TempNode;
        return false;
    }

    TempNode->Student_ID = id;
    strncpy(TempNode->Student_Name, name, MAX_NAME_LENGTH-1);
    TempNode->Student_Name[MAX_NAME_LENGTH-1] = '\0';
    TempNode->Student_year = year;
    TempNode->English = 0;
    TempNode->Arabic = 0;
    TempNode->Maths = 0;
    TempNode->Total = 0;
    TempNode->NodeLink = NULL;

    if (*List == NULL) {
        *List = TempNode;
    } else {
        student *LastNode = *List;
        while (LastNode->NodeLink != NULL) {
            LastNode = LastNode->NodeLink;
        }
        LastNode->NodeLink = TempNode;
    }

    repo_save(List);

    return true;
}

bool SDB_DeletEntry(student **List, uint32 id) {
    if (NULL==*List) {
        show_message("Error","the data is empty !!!");
        return false;
    }

    student *TempNode = *List;
    student *PrevNode = NULL;

    while (TempNode != NULL && TempNode->Student_ID != id) {
        PrevNode = TempNode;
        TempNode = TempNode->NodeLink;
    }

    if (TempNode == NULL) {
        show_message("Error", "Student ID not found!");
        return false;
    }

    if (PrevNode == NULL) {
        *List = TempNode->NodeLink;
    } else {
        PrevNode->NodeLink = TempNode->NodeLink;
    }

    delete TempNode;
    show_message("Success","the data is delete successfully");

    repo_save(List);
    return true;
}

bool SDB_ReadEntry(student *List, uint32 id, student* result) {
    student *TempNode = List;
    while (TempNode != NULL) {
        if (TempNode->Student_ID == id) {
            *result = *TempNode;
            return true;
        }
        TempNode = TempNode->NodeLink;
    }
    return false;
}

bool SDB_GetList(student *List, uint32* idArray, uint32* count) {
    *count = 0;
    student *TempNode = List;
    while (TempNode != NULL) {
        idArray[(*count)++] = TempNode->Student_ID;
        TempNode = TempNode->NodeLink;
    }
    return (*count > 0);
}

bool SDB_IsIdExist(student *List, uint32 id) {
    student *TempNode = List;
    while (TempNode != NULL) {
        if (TempNode->Student_ID == id) {
            return true;
        }
        TempNode = TempNode->NodeLink;
    }
    return false;
}

void SDB_GetUsedSize(student *List, uint32* size) {
    *size = 0;
    student *TempNode = List;
    while (TempNode != NULL) {
        (*size)++;
        TempNode = TempNode->NodeLink;
    }
}

bool EnterMarks(student **List, uint32 id, uint32 english, uint32 arabic, uint32 maths) {
    student *TempNode = *List;
    while (TempNode != NULL) {
        if (TempNode->Student_ID == id) {
            TempNode->English = english;
            TempNode->Arabic = arabic;
            TempNode->Maths = maths;
            TempNode->Total = english + arabic + maths;

            repo_save(List);
            return true;
        }
        TempNode = TempNode->NodeLink;
    }
    return false;
}

bool DisplayMarks(student *List, uint32 id, uint32* english, uint32* arabic,
                uint32* maths, uint32* total, char* name, uint32* year) {
    student *TempNode = List;
    while (TempNode != NULL) {
        if (TempNode->Student_ID == id) {
            *english = TempNode->English;
            *arabic = TempNode->Arabic;
            *maths = TempNode->Maths;
            *total = TempNode->Total;
            strncpy(name, TempNode->Student_Name, MAX_NAME_LENGTH-1);
            name[MAX_NAME_LENGTH-1] = '\0';
            *year = TempNode->Student_year;
            return true;
        }
        TempNode = TempNode->NodeLink;
    }
    return false;
}
