//Chap 10 Structures
//Explore and add comments

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20
#define MAXEMPS 3
#define PROPERTY_NAME_LOCATION_SIZE 80

// Defining a structure
// Update to use typedef
typedef struct  employee {
    char firstName[NAME_SIZE];
    char lastName[NAME_SIZE];
    unsigned int age;
    double hourlySalary;
} Employee;

typedef struct rentalSetUp {
    int minNights;
    int maxNights;
    int minRate;
    int maxRate;
    int interval1Nights;
    int interval2Nights;
    int rentalRate;
    int discount;
    char propertyName[PROPERTY_NAME_LOCATION_SIZE];
    char propertyLocation[PROPERTY_NAME_LOCATION_SIZE];
} RentalSetUp;


void enterEmployees(struct employee* employeeArr, int maxEmployees);
void passStructByValue(struct employee aEmployee);
void passStructByReference(struct employee* employeePtr);
void setUpProperty(RentalSetUp *property);
void displayOrganization(const RentalSetUp *property);


int main(void)
{

    //PART 1 declare a struct

    struct employee defaultEmployee;
    puts("\n\nPart 1 declare struct employee defaultEmployee");

    char stringtest[6] = { '\0'};

    puts("Print after declaration defaultEmployee\n");



    //What is stored?
    printf("sizeof  defaultEmployee= %lu\n", sizeof(defaultEmployee));
    printf("Employee's first name: %s\n", defaultEmployee.firstName);
    printf("Employee's last name: %s\n", defaultEmployee.lastName);
    printf("Employee's age = %d\n", defaultEmployee.age);
    printf("Employee's hourly salary = %3.2f\n", defaultEmployee.hourlySalary);

    //initialize
    strncpy(defaultEmployee.firstName, "Debug", NAME_SIZE);
    strncpy(defaultEmployee.lastName, "Horror", NAME_SIZE);
    defaultEmployee.age = 0;
    defaultEmployee.hourlySalary = 0;

    printf("defalutemployee %d\n", defaultEmployee);
    printf("defalutemployee %p\n", defaultEmployee);

    puts("\nPrint after intialization of defaultEmployee");

    printf("Employee's first name: %s\n", defaultEmployee.firstName);
    printf("Employee's last name: %s\n", defaultEmployee.lastName);
    printf("Employee's age = %d\n", defaultEmployee.age);
    printf("Employee's hourly salary = %3.2f\n", defaultEmployee.hourlySalary);


    //Part 2
    puts("\n\nPart 2 Declare and Initalize struct employee defaultEmployee = { Joe, Smith, 23, 15}");

    // declare and initialize two employees
    struct employee aEmployee = { "Stack ", "Terror", 37, 65.00 };
    struct employee bEmployee = { "Binary ", "Beasts" };

    puts("\nPrint after intializing employeea ");

    puts("Print after declaration defaultEmployee");
    printf("aEmployee's first name: %s\n", aEmployee.firstName);
    printf("aEmployee's last name: %s\n", aEmployee.lastName);
    printf("aEmployee's age = %d\n", aEmployee.age);
    printf("aEmployee's hourly salary = %3.2f\n", aEmployee.hourlySalary);


    //compare members
    if (aEmployee.age > bEmployee.age)
    {
        puts("aEmployee age is greater than bEmployee age");
    }
    else if (aEmployee.age < bEmployee.age)
    {
        puts("aEmployee age is less than bEmployee age");
    }
    else
    {
        puts("aEmployee age is = bEmployee age");
    }

    // memeber assignments
    bEmployee.hourlySalary = aEmployee.hourlySalary;
    printf("Now bEmployee's hourly salary = %3.2f\n", bEmployee.hourlySalary);
    printf("&bEmployee.hourlySalary = %p", &bEmployee.hourlySalary);

    //Part 3 Pointer to employee struct
    puts("\n\nPart 3 Declare and Initalize employeePtr ");

    // Intialize employee pointer to aEmployee
    struct employee* employeePtr = &aEmployee;

    // Arrow operators for pointers to structures
    printf("EmployeePtr first name -> %s\n", employeePtr->firstName);
    printf("EmployeePtr last name -> %s\n", employeePtr->lastName);
    printf("EmployeePtr age -> %d\n", employeePtr->age);
    printf("EmployeePtr hourly salary -> %3.2f\n", employeePtr->hourlySalary);

    // assign bEmployee address
    puts("\nAssigne employeePtr = &bEmployee and access with (*employeePtr). ");
    employeePtr = &bEmployee;
    // equivalent to arrow operators
    printf("(*employeePtr).firstName  %s\n", (*employeePtr).firstName);
    printf("(*employeePtr).lastName %s\n", (*employeePtr).lastName);
    printf("(*employeePtr).age %d\n", (*employeePtr).age);
    printf("(*employeePtr).hourlySalary %3.2f\n", (*employeePtr).hourlySalary);


    //part 4 passing to functions
    puts("\n\nPart 4 Passing to Functions");

    passStructByValue(aEmployee);
    puts("\nAfter passing by value");
    printf("aEmployee's first name: %s\n", aEmployee.firstName);
    printf("aEmployee's last name: %s\n", aEmployee.lastName);
    printf("aEmployee's age = %d\n", aEmployee.age);
    printf("aEmployee's hourly salary = %3.2f\n", aEmployee.hourlySalary);

    passStructByReference(&aEmployee);
    puts("\nAfter passing by reference");
    printf("aEmployee's first name: %s\n", aEmployee.firstName);
    printf("aEmployee's last name: %s\n", aEmployee.lastName);
    printf("aEmployee's age = %d\n", aEmployee.age);
    printf("aEmployee's hourly salary = %3.2f\n", aEmployee.hourlySalary);


    //part 5 Array of Employees
    puts("\n\nPart 5 Array of Structures");
    // Intialize array of employees
    struct employee employees[MAXEMPS];
    enterEmployees(employees, MAXEMPS);

    RentalSetUp property1 = {0, 0, 0, 0, 0, 0, NULL, NULL};

    setUpProperty(&property1);
    displayOrganization(&property1);

    return 0;
}

void enterEmployees(struct employee* employeeArr, int max)
{

    for (int i = 0; i < max; i++)
    {
        printf("\nEnter details of employees %d\n\n", i + 1);

        printf("%s", "Enter first name: ");
        scanf("%s", employeeArr[i].firstName);

        printf("%s", "Enter last name: ");
        scanf("%s", employeeArr[i].lastName);

        printf("%s", "Enter age: ");
        scanf("%i", &employeeArr[i].age);

        printf("%s", "Enter Hourly Salary: ");
        scanf("%lf", &employeeArr[i].hourlySalary);
    }
}

void passStructByValue(struct employee employeeTest) {
    puts("In function call - change values in the structure");
    strncpy(employeeTest.firstName, "Dyanmic", NAME_SIZE);
    employeeTest.hourlySalary = 100.00;
}

void passStructByReference(Employee* employeeTestPtr) {
    puts("In function call - change values in the structure");

    //Use fgets to read the first name
    puts("Enter new first name: ");
    fgets(employeeTestPtr->firstName, NAME_SIZE, stdin);

    //Use fgets to read the last name
    puts("Enter new last name: ");
    fgets(employeeTestPtr->lastName, NAME_SIZE, stdin);

    // removes the newline character and replaces with null character
    for (size_t i = 0; i < NAME_SIZE; ++i) {
        if (employeeTestPtr->firstName[i] == '\n') {
            employeeTestPtr->firstName[i] = '\0';
        }

        if (employeeTestPtr->lastName[i] == '\n') {
            employeeTestPtr->lastName[i] = '\0';
        }

    }

    printf("Enter new hourly salary: ");
    scanf("%lf", &employeeTestPtr->hourlySalary);

    // Clear the input buffer
    while (getchar() != '\n');

    printf("Employee's first name = %s\n", employeeTestPtr->firstName);
    printf("Employee's last name = %s\n", employeeTestPtr->lastName);
    printf("Employee's hourly salary = %3.2f\n\n", employeeTestPtr->hourlySalary);
}

void setUpProperty(RentalSetUp *property) {
    printf("Enter minNights: ");
    scanf("%d", &property->minNights);
    while (getchar() != '\n'); // Clear the input buffer

    printf("Enter maxNights: ");
    scanf("%d", &property->maxNights);
    while (getchar() != '\n');

    printf("Enter minRate: ");
    scanf("%d", &property->minRate);
    while (getchar() != '\n');

    printf("Enter maxRate: ");
    scanf("%d", &property->maxRate);
    while (getchar() != '\n');

    printf("Enter interval1Nights: ");
    scanf("%d", &property->interval1Nights);
    while (getchar() != '\n');

    printf("Enter interval2Nights: ");
    scanf("%d", &property->interval2Nights);
    while (getchar() != '\n');

    printf("Enter rentalRate: ");
    scanf("%d", &property->rentalRate);
    while (getchar() != '\n');

    printf("Enter discount: ");
    scanf("%d", &property->discount);
    while (getchar() != '\n');

    printf("Enter property name: ");
    fgets(property->propertyName, sizeof(property->propertyName), stdin);
    property->propertyName[strcspn(property->propertyName, "\n")] = '\0';

    printf("Enter property location: ");
    fgets(property->propertyLocation, sizeof(property->propertyLocation), stdin);
    property->propertyLocation[strcspn(property->propertyLocation, "\n")] = '\0';

    for (size_t i = 0; i < NAME_SIZE; ++i) {
        if (property->propertyName[i] == '\n') {
            property->propertyName[i] = '\0';
        }

        if (property->propertyLocation[i] == '\n') {
            property->propertyLocation[i] = '\0';
        }

    }
}

void displayOrganization(const RentalSetUp *property) {
    printf("Property Information:\n");
    printf("Min Nights: %d\n", property->minNights);
    printf("Max Nights: %d\n", property->maxNights);
    printf("Min Rate: %d\n", property->minRate);
    printf("Max Rate: %d\n", property->maxRate);
    printf("Interval 1 Nights: %d\n", property->interval1Nights);
    printf("Interval 2 Nights: %d\n", property->interval2Nights);
    printf("Rental Rate: %d\n", property->rentalRate);
    printf("Discount: %d\n", property->discount);
    printf("Property Name: %s\n", property->propertyName);
    printf("Property Location: %s\n", property->propertyLocation);
}
