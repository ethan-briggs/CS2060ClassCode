//Ethan Briggs

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>



//Maximum length of a string
#define  STRING_LENGTH 80

typedef struct pet {
    char name[STRING_LENGTH];
    int age;
    struct pet *next;
} Pet;

//function prototypes
int comparePetNames(const char* str1, const char* str2);
void insertPet(Pet **head);
void displayPets(Pet* head);
void removeNewLine(char *strPtr);
void removeAllPets(Pet** head);
void writeToFile(Pet* head, const char* filename);
void removePet(Pet** head, const char* petName);

int main(void) {
    Pet *petList = NULL;
    char addPet[STRING_LENGTH];

    do {
        insertPet(&petList);
        addPet[0] = 'a';
        //makes sure the user enters a y or n
        while (addPet[0] != 'y' && addPet[0] != 'n') {
            printf("Do you want to add another pet? Please enter (y)es or (n)o:");
            fgets(addPet, STRING_LENGTH, stdin);
            addPet[0] = tolower(addPet[0]);
            removeNewLine(addPet);
        }
    }
    while (addPet[0] == 'y' || addPet[0] == 'Y');

    // Display the list of pets
    displayPets(petList);

    if (petList != NULL) {
        writeToFile(petList, "pet.txt");
    }

    char remove[] = "y";
    while (remove[0] == 'y' || remove[0] == 'Y') {
        remove[0] = 'a';
        //makes sure the user enters a y or n
        while(remove[0] != 'y' && remove[0] != 'n') {
            puts("Do you want to delete a pet from the list? Please enter (y)es or (n)o: ");
            fgets(remove, STRING_LENGTH, stdin);
        }
        if (remove[0] == 'y' || remove[0] == 'Y') {
            char petName[STRING_LENGTH];
            puts("Enter the pet's name to delete");
            fgets(petName, STRING_LENGTH, stdin);
            removeNewLine(petName);
            removePet(&petList, petName);
            if (petList == NULL) {
                remove[0] = 'n';
            }
            displayPets(petList);
        }
    }
    removeAllPets(&petList);
    displayPets(petList);


    return 0;
}

//parameters:two strings to be compared
//outputs: an integer from the return of comparing the strings
int comparePetNames(const char* str1, const char* str2) {
    char name1[STRING_LENGTH];
    char name2[STRING_LENGTH];
    //copy strings into name1 and name2
    strcpy(name1, str1);
    strcpy(name2, str2);
    //loop trough name1 and convert all characters to lowercase
    for (size_t i = 0; name1[i]; i++) {
        name1[i] = tolower(name1[i]);
    }
    //loop trough name2 and convert all characters to lowercase
    for (size_t i = 0; name2[i]; i++) {
        name2[i] = tolower(name2[i]);
    }
    //return the value of calling string compare on the two names
    return strcmp(name1, name2);

}

//parameters: double pointer to the list of pets
void insertPet(Pet **head) {
    //allocate memory for the pet
    Pet *newPet = (Pet *)malloc(sizeof(Pet));
    puts("Enter the name of the pet");
    //store pet name in struct
    fgets(newPet->name, STRING_LENGTH, stdin);
    removeNewLine(newPet->name);
    puts("Enter the age of the pet");
    char age[STRING_LENGTH];
    //store pet age in struct
    fgets(age, sizeof(age), stdin);
    //conver the string to long then caste to int
    newPet->age = (int)strtol(age, NULL, 10);

    newPet->next = NULL;

    //if the list is empty or the pet should be first in the list
    if (*head == NULL || comparePetNames(newPet->name, (*head)->name) < 0) {
        //the next value is the the current
        newPet->next = *head;
        //set head to the new pet
        *head = newPet;
    }

    else {
        // Traverse the list to find the correct position for the new pet
        Pet* current = *head;
        while (current->next != NULL && comparePetNames(newPet->name, current->next->name) > 0) {
            current = current->next;
        }

        // Insert the new pet at the correct position
        newPet->next = current->next;
        current->next = newPet;
    }
}

//paramter: pointer to the list
void displayPets(Pet* head) {
    //if the list is empty
    if (head == NULL) {
        puts("There aren't any names in the list\n");
    }
    //otherwise
    else {
        puts("List of Pets in alphabetical order:\n");
        //while the list is not empty
        while (head != NULL) {
            printf("%s is %d years old\n", head->name, head->age);
            //move the head
            head = head->next;
        }
    }
}

//pointer to a character array
void removeNewLine(char *strPtr) {
    //loop through string
    for (size_t i = 0; i < STRING_LENGTH; ++i) {
        //if newlince character is found
        if (strPtr[i] == '\n') {
            //replace with null character
            strPtr[i] = '\0';
        }
    }
}

//parameter: double pointer to list
void removeAllPets(Pet** head) {
    //while the head is not equal to null
    while (*head != NULL) {
        Pet* temp = *head;
        //move head to the next element
        *head = (*head)->next;
        //deallocate memory
        free(temp);
    }
}

//parameters: list and filename
void writeToFile(Pet* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    //while the head is not equal to null
    while (head != NULL) {
        fprintf(file, "Name: %s, Age: %d\n", head->name, head->age);
        //move head to next element
        head = head->next;
    }
    //close the file
    fclose(file);
    printf("Pet information written to %s\n", filename);
}

//parameters:double pointer to list
void removePet(Pet** head, const char* petName) {

    //If the pet to be removed is at the head/beginning
    if (strcmp((*head)->name, petName) == 0) {
        Pet* temp = *head;
        *head = (*head)->next;
        //deallocate memory
        free(temp);
    }

    //Move through the list to find the pet to be removed
    else {
        //set current element to the head
        Pet* current = *head;
        //while the next value is not null and the return value of string compare function is not 0
        while (current->next != NULL && strcmp(current->next->name, petName) != 0) {
            //set current element to the next element
            current = current->next;
        }

        // If the pet is found, remove it
        if (current->next != NULL) {
            //create a temporary pointer to
            Pet* temp = current->next;
            //set next value after current to be the value that is currently after that
            current->next = current->next->next;
            //deallocate memory for that element
            free(temp);
        }
        //otherwise
        else {
            printf("%s was not found in the list of pets!", petName);
        }
    }
}
