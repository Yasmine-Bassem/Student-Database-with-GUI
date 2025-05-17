#include "repository.h"

#include "stdlib.h"

#include<iostream>


void repo_save(student **head){
    FILE *fptr;
    uint32 n_students = 0;
    uint32 counter = 0, i;
    student* s_head = *head;
    str tempStr;

    SDB_GetUsedSize(*head, &n_students);
    fptr = fopen("data.csv","w");

    fprintf(fptr,"%d\n",n_students);

    while(s_head != NULL && counter<n_students){
        strcpy(tempStr, s_head->Student_Name);

        for (i=0;i<32;i++) if(tempStr[i]==' ') tempStr[i]='~';

        fprintf(fptr ,"%s %d %d %d %d %d\n",
                    tempStr,
                    s_head->Student_ID,
                    s_head->Student_year,
                    s_head->English,
                    s_head->Arabic,
                    s_head->Maths
                 );

        counter += 1;
        s_head = s_head->NodeLink;
    }

    fclose(fptr);

}

void repo_restore(student **head){
    FILE *fptr;
    uint32 n_students = 0, counter, i;

    uint32 Student_ID;
    uint32 Student_year;
    uint32 English;
    uint32 Arabic;
    uint32 Maths;
    str Student_Name;

    fptr = fopen("data.csv","r");

    if (fptr  == NULL){
        std::cout<<"Can not read cache data"<<std::endl;
    }else{
        fscanf(fptr,"%d\n",&n_students);

        for(counter=0; counter<n_students;counter++){
            fscanf(fptr ,"%s %d %d %d %d %d\n",
                    Student_Name,
                    &Student_ID,
                    &Student_year,
                    &English,
                    &Arabic,
                    &Maths
                 );

            for (i=0;i<32;i++) if(Student_Name[i]=='~') Student_Name[i]=' ';


            SDB_AddEntry(head,Student_ID, Student_Name, Student_year );
            EnterMarks(head, Student_ID, English, Arabic, Maths);
        }


        fclose(fptr);
    }
}

