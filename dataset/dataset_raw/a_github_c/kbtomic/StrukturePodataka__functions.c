#include "functions.h"

pointerHash InitializeHashTable(int size)
{
    pointerHash table;
    table = (pointerHash)malloc(sizeof(HashTable));
    if (!table)
    {
        printf("Problem with memory allocation!\n");
        return table;
    }
    table->size = size;
    table->hashList = (position*)malloc(sizeof(position) * size);
    if (!table->hashList)
    {
        printf("Problem with memory allocation!\n");
        return table->hashList;
    }
    for (int i = 0; i < table->size; i++)
        table->hashList[i] = NULL;
    return table;
}
int CountKey(char* lastName)
{
    int lengthOfLastName = strlen(lastName);
    int sum = 0, i = 0;
    if (lengthOfLastName < LAST_NAME_LENGTH)
    {
        for (i = 0; i < lengthOfLastName; i++)
            sum += lastName[i];
    }
    else
    {
        for (i = 0; i < LAST_NAME_LENGTH; i++)
            sum += lastName[i];
    }
    return (sum % SIZE_OF_TABLE);
}
int InputStudentsFromFile(char* fileName, pointerHash hashTable)
{
    FILE* fp = NULL;
    fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("Can't open file!\n");
        return fp;
    }
    char fileFirstName[MAX_STRING_LENGTH];
    char fileLastName[MAX_STRING_LENGTH];
    char fileRegistrationNumber[MAX_STRING_LENGTH];

    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s\n", fileFirstName, fileLastName, fileRegistrationNumber);
        AddToHashTable(AllocateMemoryForStudent(fileFirstName, fileLastName, fileRegistrationNumber), hashTable);
    }
    fclose(fp);
    return 0;
}
position AllocateMemoryForStudent(char* firstName, char* lastName, char* registrationNumber)
{
    position newStudent = NULL;
    newStudent = (position)malloc(sizeof(ListElement));
    if (!newStudent)
    {
        printf("Problem with memory allocation!\n");
        return newStudent;
    }
    newStudent->next = NULL;
    strcpy(newStudent->firstName, firstName);
    strcpy(newStudent->lastName, lastName);
    strcpy(newStudent->registrationNumber, registrationNumber);
    return newStudent;
}
int AddToHashTable(position newStudent, pointerHash hashTable)
{
    int hashKey = CountKey(newStudent->lastName, hashTable->size);
    if (!hashTable->hashList[hashKey])
        hashTable->hashList[hashKey] = newStudent;
    else
    {
        position currentStudent = hashTable->hashList[hashKey];
        if (currentStudent && (strcmp(newStudent->lastName, currentStudent->lastName) < 0 || (strcmp(newStudent->lastName, currentStudent->lastName) == 0 && strcmp(newStudent->firstName, currentStudent->firstName) < 0)))
        {
            hashTable->hashList[hashKey] = newStudent;
            newStudent->next = currentStudent;
        }
        else 
        {
            while (currentStudent->next)
            {
                if (strcmp(newStudent->lastName, currentStudent->next->lastName) < 0 || (strcmp(newStudent->lastName, currentStudent->next->lastName) == 0 && strcmp(newStudent->firstName, currentStudent->next->firstName) < 0))
                {
                    newStudent->next = currentStudent->next;
                    currentStudent->next = newStudent;
                    break;
                }
                currentStudent = currentStudent->next;
            }
            if (!currentStudent->next)
            {
                newStudent->next = currentStudent->next;
                currentStudent->next = newStudent;
            }
        }
    }
    return 0;
}
int PrintHashTable(pointerHash hashTable)
{
    printf("Hash table of students:\n\n");
    for (int i = 0; i < hashTable->size; i++)
    {
        int printMeOnce = 1;
        position current = hashTable->hashList[i];
        while (current)
        {
            if (printMeOnce == 1)
            {
                printf("Key:%d\n", i);
                printMeOnce++;
            }
            printf("%s %s\n\n", current->firstName, current->lastName);
            current = current->next;
        }
    }
    return 0;
}
int FindStudent(char* lastName, char* firstName, pointerHash hashTable)
{
    int hashKey = CountKey(lastName);
    position currentStudent = hashTable->hashList[hashKey];
    int isFound = 0;
    while (currentStudent && !isFound)
    {
        if (strcmp(currentStudent->lastName, lastName) == 0 && strcmp(currentStudent->firstName, firstName) == 0)
        {
            printf("Registration number for %s %s is:%s\n", currentStudent->firstName, currentStudent->lastName, currentStudent->registrationNumber);
            isFound = 1;
        }
        currentStudent = currentStudent->next;
    }
    if (!isFound)
    {
        printf("Student does not exist!\n");
    }
    return 0;
}
