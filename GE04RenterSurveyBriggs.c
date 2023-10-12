//Ethan Briggs
//I am using xcode
//Program that takes in 5 users ratings for 3 categories, then displays the ratings and average of ratings.

#include <stdio.h>

//declarization of all constants to be used
int unsigned const MIN_RATING = 1;
unsigned int const MAX_RATING = 5;
unsigned int const RENTER_SURVEY_CATEGORIES = 3;
unsigned int const NUM_OF_RATERS = 5;

//prototypes for all functions to be used in the program
void printCategories(const char *categories[], size_t totalCategories);
void getRatings(int raters, int categories, int min, int max, int twoDArr[][categories]);
int getValidInt(int min, int max);
void printSurveyResults(int raters, int categories, int twoDArr[][categories], const char *categoriesLabels[]);
void calculateCategoryAverages(int raters, int categories, int twoDArr[][categories], double categoryAverages[]);
void printCategoryData(int categories, const char *categoriesLabels[], double categoryAverages[]);

int main(void) {
    const char *surveyCategories[RENTER_SURVEY_CATEGORIES] = {"Check-in Process", "Cleanliness", "Amenities"};

    puts("We want to know how your experience was renting our property. Using the rating system 1 to 5 enter your rating for each category.");
    printCategories(surveyCategories, RENTER_SURVEY_CATEGORIES);
    puts("");

    int twoDArray[NUM_OF_RATERS][RENTER_SURVEY_CATEGORIES];
    double categoryAverages[RENTER_SURVEY_CATEGORIES];

    getRatings(NUM_OF_RATERS, RENTER_SURVEY_CATEGORIES, MIN_RATING, MAX_RATING, twoDArray);

    printSurveyResults(NUM_OF_RATERS, RENTER_SURVEY_CATEGORIES, twoDArray, surveyCategories);

    calculateCategoryAverages(NUM_OF_RATERS, RENTER_SURVEY_CATEGORIES, twoDArray, categoryAverages);

    printCategoryData(RENTER_SURVEY_CATEGORIES, surveyCategories, categoryAverages);

    return 0;
}

void printCategories(const char *categories[], size_t totalCategories) {
    //loop to display each category horizontally
    printf("%s", "Rating Categories:\t");
    for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory) {
        printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
    }
    puts(""); // start new line of output
}

void getRatings(int raters, int categories, int min, int max, int twoDArr[][categories]) {
    for (int i = 0; i < raters; ++i) {
        puts("");
        printf("Renter %d:\n", i + 1); // Print the current renter number
        for (int j = 0; j < categories; ++j) {
            puts("Enter your rating for");
            printf("category %d:\n", j + 1);
            twoDArr[i][j] = getValidInt(min, max); // Store the rating in the 2D array
        }
    }
}

int getValidInt(int min, int max) {
    int userInput = 0;
    int valid = 0;

    //loop until valid input is entered
    while (!valid) {
        userInput = 0;
        //if the value entered is not an integer
        if (scanf("%d", &userInput) != 1) {
            // Clear the input buffer
            while (getchar() != '\n');
            puts("Error: you didn't enter the rating correctly.");
        } else if (userInput >= min && userInput <= max) {
            valid = 1;
        } else {
            // Clear the input buffer if the input is out of range
            while (getchar() != '\n');
            puts("Error: the rating is out of range.");
        }
    }
    return userInput;
}

void printSurveyResults(int raters, int categories, int twoDArr[][categories], const char *categoriesLabels[]) {
    puts("");
    puts("Survey results");
    printCategories(categoriesLabels, categories);
    for (int i = 0; i < raters; ++i) {
            printf("Survey %d:\t", i + 1); // Print the current survey number
        for (int j = 0; j < categories; ++j) {
                printf("             %d     ", twoDArr[i][j]); // Print the rating
            if (j < categories - 1) {
                    printf("\t\t"); // Add tabs to align columns
            }
        }
        printf("\n"); // Add a newline after each survey
    }
    puts("");
}

// Initialize categoryAverages array to all zeros
void calculateCategoryAverages(int raters, int categories, int twoDArr[][categories], double categoryAverages[]) {
    for (int j = 0; j < categories; ++j) {
        double categoryTotal = 0.0; // Initialize the total for the current category
        for (int i = 0; i < raters; ++i) {
            categoryTotal += twoDArr[i][j]; // Add the rating for the current rater in the current category
        }
        categoryAverages[j] = categoryTotal / raters; // Calculate and store the average for the current category
    }
}


void printCategoryData(int categories, const char *categoriesLabels[], double categoryAverages[]) {
    printCategories(categoriesLabels, categories); // Print category labels using printCategories function

    printf("Rating Averages\t");
    for (int i = 0; i < categories; ++i) {
        printf("          %.1f\t          ", categoryAverages[i]);
    }
    puts(""); // Start a new line
}
