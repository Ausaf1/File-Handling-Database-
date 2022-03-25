#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student
{
    int roll;
    char name[30];
    int sub1;
    int sub2;
    int sub3;
};

void insert();
void deleteStudent();
void update();
void display();

void insert()
{
    system("cls");
    char another;
    FILE *fp;
    struct student s;
    do
    {
        printf("\t\t\t\tAdd Student details\t\t\t\t\n");
        fp = fopen("student", "ab");
        printf("\nEnter name of student: ");
        fflush(stdin);
        gets(s.name);
        printf("\nEnter roll number : ");
        scanf("%d", &s.roll);
        printf("\nEnter marks of subject 1 : ");
        scanf("%d", &s.sub1);
        printf("\nEnter marks of subject 2 : ");
        scanf("%d", &s.sub2);
        printf("\nEnter marks of subject 3 : ");
        scanf("%d", &s.sub3);
        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\tCan't open file\n");
        }
        else
        {
            printf("\t\t\tRecord stored successfully\n");
        }
        fwrite(&s, sizeof(struct student), 1, fp);
        fclose(fp);
        printf("Do you wan't to add another record?(y/n): ");
        scanf("%s", &another);
    } while (another == 'y' || another == 'Y');
}

void deleteStudent()
{
    FILE *fp, *fp1;
    struct student s;
    int roll_no, flag = 0;
    fp = fopen("student", "r");
    fp1 = fopen("temp.txt", "w");
    printf("\n\t\t\t\tSearch Student\t\t\t\n");
    printf("\nEnter Roll no of student to be deleted from record: ");
    fflush(stdin);
    scanf("%d", &roll_no);
    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\tCan't open file\n");
        fclose(fp);
        return;
    }
    while (fread(&s, sizeof(struct student), 1, fp))
    {
        if (s.roll == roll_no)
        {
            flag = 1;
        }
        else
        {
            fwrite(&s, sizeof(struct student), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    if (flag == 1)
    {
        remove("student");
        rename("temp.txt", "student");
        printf("\n\t\t\tRecord deleted successfully\n");
    }
    else
    {
        printf("\n\t\t\tStudent not found\n");
    }
}

void update()
{
    FILE *fp, *fp1;
    struct student s;
    int roll_no, flag = 0;
    fp = fopen("student", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\tCan't open file\n");
        fclose(fp);
        return;
    }
    printf("\n\t\t\t\tSearch Student\t\t\t\n");
    printf("\nEnter Roll no of student whose data to be updated: ");
    fflush(stdin);
    scanf("%d", &roll_no);
    while (fread(&s, sizeof(struct student), 1, fp) && flag == 0)
    {
        if (s.roll == roll_no)
        {
            flag = 1;
            printf("\n\t\t\tData of student having roll no %d\n", roll_no);
            printf("NAME\t   ROLL NUMBER\t    SUBJECT 1\t    SUBJECT 2\t    SUBJECT 3\t     PERCENTAGE\n");
            printf("%s\t\t %d\t\t %d\t\t %d\t\t %d\t\t %.2f\n", s.name, s.roll, s.sub1, s.sub2, s.sub3, (s.sub1 + s.sub2 + s.sub3) / 3.0);
            printf("\t\t\t------------------------------\n");
            printf("\nUpdated name(same if this data is not to be updated): ");
            fflush(stdin);
            gets(s.name);
            printf("\nUpated Roll no(same if this data is not to be updated): ");
            scanf("%d", &s.roll);
            printf("\nUpated marks of subject 1(same if this data is not to be updated): ");
            scanf("%d", &s.sub1);
            printf("\nUpated marks of subject 2(same if this data is not to be updated): ");
            scanf("%d", &s.sub2);
            printf("\nUpated marks of subject 3(same if this data is not to be updated): ");
            scanf("%d", &s.sub3);
            fseek(fp, -(long)sizeof(struct student), 1);
            fwrite(&s, sizeof(struct student), 1, fp1);
            printf("\n\t\t\tRecord updated successfully\n");
        }
        else
        {
            fwrite(&s, sizeof(struct student), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    if (flag == 1)
    {
        remove("student");
        rename("temp.txt", "student");
    }
    else
    {
        printf("\n\t\t\tStudent not found\n");
    }
}

void display()
{
    FILE *fp;
    struct student s;
    fp = fopen("student", "rt");
    printf("\t\t\t\tStudent details\t\t\t\t\n");
    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\tCan't open file\n");
    }
    else
    {
        printf("\n\t\t\tStudents Details\n");
        printf("\t\t\t------------------------------\n");
        printf("NAME\t   ROLL NUMBER\t    SUBJECT 1\t    SUBJECT 2\t    SUBJECT 3\t     PERCENTAGE\n");
        while (fread(&s, sizeof(struct student), 1, fp) == 1)
        {
            printf("%s\t\t %d\t\t %d\t\t %d\t\t %d\t\t %.2f\n", s.name, s.roll, s.sub1, s.sub2, s.sub3, (s.sub1 + s.sub2 + s.sub3) / 3.0);
            printf("\t\t\t------------------------------\n");
        }
        fclose(fp);
    }
}

int main()
{
    printf("\n------Ausaf Ahmad_20BCS017------\n");
    int choice;
    while (1)
    {
        printf("\n\n*********Main Menu*********\n");
        printf("------------------------------------------\n");
        printf("      1    -->    INSERT               \n");
        printf("      2    -->    DELETE              \n");
        printf("      3    -->    UPDATE              \n");
        printf("      4    -->    DISPLAY              \n");
        printf("      5    -->    EXIT              \n");
        printf("------------------------------------------\n");

        printf("Enter your choice\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            insert();
            system("cls");
            break;
        case 2:
            system("cls");
            deleteStudent();
            printf("\t\t\t\tPress any key to exit\n");
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            update();
            printf("\t\t\t\tPress any key to exit\n");
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            display();
            printf("\t\t\t\tPress any key to exit\n");
            getch();
            system("cls");
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\nInvalid choice\n");
            break;
        }
    }
    return 0;
}