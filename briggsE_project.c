//Ethan Briggs

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



//Maximum length of a string
#define  STRING_LENGTH 80
//Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3
//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1
//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2
#define RATING_MIN 1
#define RATING_MAX 5

//creates the struct to store info for a rental property
typedef struct rentalPropertyInfo {
    int interval1Nights;
    int interval2Nights;
    int nightlyRentalRate;
    int discount;
    char propertyName[STRING_LENGTH];
    char propertyLocation[STRING_LENGTH];
    int numOfRenters;
    int totalRevenue;
    int totalNights;
    int surveyResults[VACATION_RENTERS] [RENTER_SURVEY_CATEGORIES];
    const char *surveyCategories[RENTER_SURVEY_CATEGORIES];
    double ratingAverages[RENTER_SURVEY_CATEGORIES];
} RentalPropertyInfo;

//function prototypes
bool userLogIn(void);
void getPropertyRatings(RentalPropertyInfo *RentalPropertyInfoPtr);
bool scanInt(const char *strPtr, int *value);
int getValidData(int min, int max, bool ifCalledInRentalMode);
void setUpProperty(RentalPropertyInfo *propertyPtr);
void removeNewLine(char *strPtr);
void displayRentalInfo(RentalPropertyInfo *RentalPropertyInfoPtr);
bool is2DArrayEmpty(int arr[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES]);
void printSurveyResults(RentalPropertyInfo *RentalPropertyInfoPtr);
void calculateCategoryAverages(RentalPropertyInfo *RentalPropertyInfoPtr);
double calculateCharges(unsigned int nights, RentalPropertyInfo *RentalPropertyInfoPtr);
void rentalMode(RentalPropertyInfo *RentalPropertyInfoPtr);
void printNightsCharges(unsigned int nights, int charges, unsigned int numOfRenters, bool calledInReport);
bool rentalModeLoop(RentalPropertyInfo *RentalPropertyInfoPtr);
void rentalReportMode(RentalPropertyInfo *RentalPropertyInfoPtr);
void printCategoryData(RentalPropertyInfo *RentalPropertyInfoPtr);
void printCategories(RentalPropertyInfo *RentalPropertyInfoPtr);

int main(void) {
    //if the user is able to log in
    if (userLogIn()) {
        puts("Login Successful");
        RentalPropertyInfo property;
        setUpProperty(&property);
        rentalMode(&property);
        rentalReportMode(&property);


    }
    //otherwise
    else {
        //print an exit message
        puts("Exiting AirUccs");
    }
    return 0;
}

bool userLogIn(void) {
    //initialize variables to be used
    int i = 0;
    bool loggedIn = false;
    char userID[STRING_LENGTH] = "";
    char userPasscode[STRING_LENGTH] = "";
    puts("AirUCCS Rental Property Owner Login");

    //while the user has not logged in and is under the number of max attempts
    while (!loggedIn && i < LOGIN_MAX_ATTEMPTS) {
        puts("Enter your airUCCS id");
        fgets(userID, STRING_LENGTH, stdin);
        removeNewLine(userID);
        puts("Enter your airUCCS passcode");
        fgets(userPasscode, STRING_LENGTH, stdin);
        removeNewLine(userPasscode);
        //if the user id and password is correct
        if (strcmp(userID, CORRECT_ID) == 0 && strcmp(userPasscode, CORRECT_PASSCODE) == 0) {
            loggedIn = true;
        }
        else {
            i++;
        }
    }

    return loggedIn;
}

void getPropertyRatings(RentalPropertyInfo *propertyPtr) {
    printf("We want to know how you experience was renting our property. Using the rating system %d\n to %d enter your rating for each category: \n", RATING_MIN, RATING_MAX);
    //loops through and prints survey categories
    for (size_t surveyCategory = 0; surveyCategory < RENTER_SURVEY_CATEGORIES; ++surveyCategory) {
        printf("\t%zu: %s\n", surveyCategory + 1, propertyPtr->surveyCategories[surveyCategory]);
    }
    puts("");
    //loops through captures ratings for each category
    for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; ++j) {
        puts("Enter your rating for");
        printf("Category %zu:\n", j + 1);
        //assigns ratings to survey results and validates rating
        propertyPtr->surveyResults[propertyPtr->numOfRenters][j] = getValidData(RATING_MIN, RATING_MAX, false);
    }
}

//sets up the property with the use of the struct
void setUpProperty(RentalPropertyInfo *propertyPtr) {
    //initialize all values in to surveyResults to 0, so we can use a is2DArrayEmpty function to check if survey results have been inputted by user yet
    for (size_t i = 0; i < VACATION_RENTERS; ++i) {
            for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; ++j) {
                propertyPtr->surveyResults[i][j] = 0;
            }
    }
    //initialive structure elements
    propertyPtr->surveyCategories[0] = "Check-in Process";
    propertyPtr->surveyCategories[1] = "Cleanliness";
    propertyPtr->surveyCategories[2] = "Amenities";
    propertyPtr->numOfRenters = 0;
    propertyPtr->totalNights = 0;
    propertyPtr->totalRevenue = 0;
    puts("Enter the number of nights until first discount");
    propertyPtr->interval1Nights = getValidData(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, false);
    puts("Enter the number of nights until the second discount");
    propertyPtr->interval2Nights = getValidData(propertyPtr->interval1Nights + 1, MAX_RENTAL_NIGHTS, false);
    puts("Enter the nightly rental rate");
    propertyPtr->nightlyRentalRate = getValidData(MIN_RATE, MAX_RATE, false);
    puts("Enter the discount");
    propertyPtr->discount = getValidData(MIN_RATE, propertyPtr->nightlyRentalRate, false);
    puts("Enter property name");
    fgets(propertyPtr->propertyName, STRING_LENGTH, stdin);
    puts("Enter property location");
    fgets(propertyPtr->propertyLocation, STRING_LENGTH, stdin);
}


bool scanInt(const char *strPtr, int *value) {
    bool returnValue = false;
    char *endPtr = NULL;
    errno = 0;
    //converts the string to a long
    long intTest = strtol(strPtr, &endPtr, 10);

    if (strPtr == endPtr) {
        puts("Not a number");
    }
    else if (*endPtr != '\0') {
        puts("Extra character at end of input");
    }
    else if (errno == ERANGE){
        puts("Out of long range");
    }
    else {
        //caste the long into an integer
        *value = (int)intTest;
        returnValue = true;
    }
    return returnValue;
}

//returns a valid integer within min and max bounds inclusive
int getValidData(int min, int max, bool CalledInRentalMode) {
    int value = 0;
    char inputStr[STRING_LENGTH];
    bool validInput = false;
    do {
        //call fgets and store in inputStr
        fgets(inputStr, STRING_LENGTH, stdin);

        removeNewLine(inputStr);

        validInput = scanInt(inputStr, &value);
        //if the function has been called inside of the RentalMode
        if (CalledInRentalMode) {
            if (validInput) {
                if ((value < min || value > max) && value != SENTINAL_NEG1) {
                    validInput = false;
                    puts("Error: you didn't enter the number of nights correctly");
                }
            }
        }

        //if the function has been called somewhere else
        else {
            if (validInput) {
                if (value < min || value > max) {
                    validInput = false;
                }
            }
        }

    }
    //while the input is not valid
    while (!validInput);

    return value;
}

//removes newline characters and replaces with null characters
void removeNewLine(char *strPtr) {
    for (size_t i = 0; i < STRING_LENGTH; ++i) {
        if (strPtr[i] == '\n') {
            strPtr[i] = '\0';
        }
    }
}

//displays the rental info
void displayRentalInfo(RentalPropertyInfo *RentalPropertyInfoPtr) {
    puts("");
    printf("Rental Property: %s", RentalPropertyInfoPtr->propertyName);
    printf("Location: %s", RentalPropertyInfoPtr->propertyLocation);
    printf("Rental property can be rented for %d to %d nights.\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
    printf("$%d rate a night for the first %d nights\n", RentalPropertyInfoPtr->nightlyRentalRate, RentalPropertyInfoPtr->interval1Nights);
    printf("$%d discount rate a night for nights %d to %d\n", RentalPropertyInfoPtr->discount, RentalPropertyInfoPtr->interval1Nights + 1, RentalPropertyInfoPtr->interval2Nights);
    printf("$%d discount rate a night for each remaining night over %d\n", RentalPropertyInfoPtr->discount * 2, RentalPropertyInfoPtr->interval2Nights);
    //if there have been no ratings entered yet
    if (is2DArrayEmpty(RentalPropertyInfoPtr->surveyResults)) {
        puts("No ratings currently\n");
    }
    //otherwise call printSurveyResults
    else {
        printSurveyResults(RentalPropertyInfoPtr);
    }
}

bool is2DArrayEmpty(int arr[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES]) {
    bool isEmpty = true;

    //loop through number of vacation renters
    for (size_t i = 0; i < VACATION_RENTERS && isEmpty; i++) {
        for (int j = 0; j < RENTER_SURVEY_CATEGORIES && isEmpty; j++) {
            if (arr[i][j] != 0) {
                //if there is a value that is not zero, then there have been ratings entered
                isEmpty = false;
            }
        }
    }
    //returns a bool indicating if the array is empty or not
    return isEmpty;
}


void printSurveyResults(RentalPropertyInfo *RentalPropertyInfoPtr) {
    puts("");
    puts("Survey results");
    printCategories(RentalPropertyInfoPtr);
    //loop through the number of renters
    for (size_t i = 0; i < RentalPropertyInfoPtr->numOfRenters; ++i) {
        //print the renter survey number
        printf("Survey %zu:\t", i + 1);
        //loop through the number of categories
        for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; ++j) {
            printf("                %d      ", RentalPropertyInfoPtr->surveyResults[i][j]); // Print the rating

        }
        printf("\n"); // Add a newline after each survey
    }
    puts("");
}

void calculateCategoryAverages(RentalPropertyInfo *RentalPropertyInfoPtr) {
    //loop through the number of categories
    for (size_t j = 0; j < RENTER_SURVEY_CATEGORIES; ++j) {
        double categoryTotal = 0.0;
        int rentersWithRating = 0;

        //loop through number of renters
        for (int i = 0; i < RentalPropertyInfoPtr->numOfRenters; ++i) {
            //if the survey results at that index is greater than 0
            if (RentalPropertyInfoPtr->surveyResults[i][j] > 0) {
                //add the
                categoryTotal += RentalPropertyInfoPtr->surveyResults[i][j];
                rentersWithRating++;
            }
        }

        // Calculate the average for the current category if at least one renter provided a rating
        if (rentersWithRating > 0) {
            //divide total by number of renters that have rated
            RentalPropertyInfoPtr->ratingAverages[j] = categoryTotal / rentersWithRating;
        }
        //otherwise initalize them to 0
        else {
            RentalPropertyInfoPtr->ratingAverages[j] = 0.0;
        }
    }
}

double calculateCharges(unsigned int nights, RentalPropertyInfo *RentalPropertyInfoPtr) {
    double charge = 0.0;

    //charge original rate
    if (nights <= RentalPropertyInfoPtr->interval1Nights) {
        charge = nights * RentalPropertyInfoPtr->nightlyRentalRate;
    }

    //charge original rate until interval 1 nights, then charge discount rate per night
    else if (nights <= RentalPropertyInfoPtr->interval2Nights) {
        charge = RentalPropertyInfoPtr->interval1Nights * RentalPropertyInfoPtr->nightlyRentalRate + ((nights - RentalPropertyInfoPtr->interval1Nights) * (RentalPropertyInfoPtr->nightlyRentalRate - RentalPropertyInfoPtr->discount));
    }

    //charge original rate until interval 1 nights, then discount rate until interval 2 nights, then discount * 2 for the remaining nights
    else {
        charge = RentalPropertyInfoPtr->interval1Nights * RentalPropertyInfoPtr->nightlyRentalRate + ((RentalPropertyInfoPtr->interval2Nights - RentalPropertyInfoPtr->interval1Nights) * (RentalPropertyInfoPtr->nightlyRentalRate - RentalPropertyInfoPtr->discount)) + ((nights - RentalPropertyInfoPtr->interval2Nights) * (RentalPropertyInfoPtr->nightlyRentalRate - (2 * RentalPropertyInfoPtr->discount)));
    }

    //return the charge
    return charge;
}

void printNightsCharges(unsigned int nights, int charges, unsigned int numOfRenters, bool calledInReport) {
    //if the method is called in the rental report
    if (!calledInReport) {
        puts("");
        puts("Nights          Charges");
        printf("%d               $%d\n", nights, charges);
        puts("");
    }

    //otherwise
    else {
        puts("");
        puts("Renters          Nights          Charges");
        printf("%d                 %d               $%d\n", numOfRenters, nights, charges);
        puts("");
    }
}

bool rentalModeLoop(RentalPropertyInfo *RentalPropertyInfoPtr) {
    bool sentinelNotEntered = true;
    int nightsEntered = 0;
    while (nightsEntered != SENTINAL_NEG1) {
        //display the rental info
        displayRentalInfo(RentalPropertyInfoPtr);
        //prompt the user for the number of nighs
        puts("Enter the number of nights you want to stay");
        nightsEntered = getValidData(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, true);

        //if the sentinal value is not entered
        if (nightsEntered != SENTINAL_NEG1) {
            double charge = calculateCharges(nightsEntered, RentalPropertyInfoPtr);
            //add the nights entered to the total nights
            RentalPropertyInfoPtr->totalNights += nightsEntered;
            //add the charge to the total revenue
            RentalPropertyInfoPtr->totalRevenue += charge;
            //print the charges for the number of nights
            printNightsCharges(nightsEntered, charge, RentalPropertyInfoPtr->numOfRenters, false);
            //get the ratings from user
            getPropertyRatings(RentalPropertyInfoPtr);
            //increment renters
            RentalPropertyInfoPtr->numOfRenters++;
        }
        else {
            sentinelNotEntered = false; // Sentinel entered
        }
    }
    //returns whether or not the sentinval value was entered
    return sentinelNotEntered;
}

//loops until the sentinal value is enter and the user is able to log in
void rentalMode(RentalPropertyInfo *RentalPropertyInfoPtr) {
    bool repeat = true;
    while (repeat) {
        repeat = rentalModeLoop(RentalPropertyInfoPtr);
        //if the sentinel value is entered and the user can not log in
        if (!repeat && !userLogIn()) {
            //repeat rental mode
            repeat = true;
        }
    }
}

void rentalReportMode(RentalPropertyInfo *RentalPropertyInfoPtr) {
    puts("");
    puts("Rental Property Report");
    printf("Name: %s", RentalPropertyInfoPtr->propertyName);
    printf("Location: %s", RentalPropertyInfoPtr->propertyLocation);
    puts("");
    printf("%s","Rental Property Totals");
    printNightsCharges(RentalPropertyInfoPtr->totalNights, RentalPropertyInfoPtr->totalRevenue, RentalPropertyInfoPtr->numOfRenters, true);
    calculateCategoryAverages(RentalPropertyInfoPtr);
    printCategoryData(RentalPropertyInfoPtr);
    puts("Exiting AirUCCS");

}

void printCategoryData(RentalPropertyInfo *RentalPropertyInfoPtr) {
    for (size_t surveyCategory = 0; surveyCategory < RENTER_SURVEY_CATEGORIES; ++surveyCategory) {
        printf("%zu. %s:\t%.1f\n", surveyCategory + 1, RentalPropertyInfoPtr->surveyCategories[surveyCategory], RentalPropertyInfoPtr->ratingAverages[surveyCategory]);
    }
    puts(""); // start new line of output
}

void printCategories(RentalPropertyInfo *RentalPropertyInfoPtr) {
    //loop to display each category
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < RENTER_SURVEY_CATEGORIES; ++surveyCategory) {
        printf("\t%zu.%s\t", surveyCategory + 1, RentalPropertyInfoPtr->surveyCategories[surveyCategory]);
    }
    puts("");
}
