//Ethan Briggs
//I am using xcode

#include <stdio.h>

//initialization of all constants to be used in program
int const SENTINAL_NEG1 = -1;
int unsigned const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400;
double const DISCOUNT = 50;

//prototypes for every function to be used in program except for main
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
         interval1Nights, unsigned int interval2Nights, double rate, double discount);

int getValidInt(int min, int max, int sentinel);

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
          interval2Nights, double rate, double discount);

void printNightsCharges(unsigned int nights, double charges, int summary);

int main(void) {
    //calls the function to print all the rental information
    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

    int totalNumOfNights = 0;
    double totalChargeOfRentals = 0.0;
    int nightsEntered = 0;

    //while the input from the user is not -1
    while (nightsEntered != SENTINAL_NEG1) {
        // Store the return value of getValidInt in nightsEntered
        nightsEntered = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

        if (nightsEntered != SENTINAL_NEG1) {
            // Calculate the charge for the number of nights entered by calling calculateCharges
            double charge = calculateCharges(nightsEntered, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

            //add nights entered to total number of nights
            totalNumOfNights += nightsEntered;
            //add charge to total charge
            totalChargeOfRentals += charge;

            // Call printNightsCharges to print individual night's charge
            printNightsCharges(nightsEntered, charge, 0);
        }
    }

        // Print the summary when -1 is entered using printNightsCharges
    if (totalNumOfNights == 0) {
        printf("There were no rentals.\n");
    }

    else {
            // Print the summary when -1 is entered using printNightsCharges
        printNightsCharges(totalNumOfNights, totalChargeOfRentals, 1);
    }
    return 0;
}

//prints the rental information such as rates and allowed stay period
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
         interval1Nights, unsigned int interval2Nights, double rate, double discount) {

    printf("Rental Property can be rented for %d to %d nights\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
    printf("$%.2lf rate a night for the first %d nights\n", RENTAL_RATE, INTERVAL_1_NIGHTS);
    int nextNight = INTERVAL_1_NIGHTS + 1;
    printf("$%.2lf discount rate a night for nights %d to %d\n", DISCOUNT, nextNight, INTERVAL_2_NIGHTS);
    double largerDiscount = DISCOUNT * 2;
    printf("%.2lf discount rate a night for each remaining night over %d\n", largerDiscount, INTERVAL_2_NIGHTS);
}

//returns a valid user input
int getValidInt(int min, int max, int sentinel) {
    int userInput = 0;
    int valid = 0;

    //loop until valid input is entered
    while (!valid) {
        userInput = 0;
        puts("Enter the number of nights you want to stay.");
        //if the value entered is not an integer
        if (scanf("%d", &userInput) != 1) {
            //clear the input buffer
            while (getchar() != '\n');
            puts("Error: you didn't enter the number of nights correctly.");
        }

        //if the input is valid
        else if((userInput == sentinel) || (userInput >= min && userInput <= max)) {
            valid = 1;
        }

        //if the input is an integer but invalid
        else {
            puts("Error: you didn't enter the number of nights correctly.");
        }
    }
    return userInput;
}

//calculates the charge
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
          interval2Nights, double rate, double discount) {
    double charge = 0.0;

    //charge original rate
    if (nights <= interval1Nights) {
        charge = nights * rate;
    }

    //charge original rate until interval 1 nights, then charge discount rate per night
    else if (nights <= interval2Nights) {
        charge = interval1Nights * rate + ((nights - interval1Nights) * (rate - discount));
    }

    //charge original rate until interval 1 nights, then discount rate until interval 2 nights, then discount * 2 for the remaining nights
    else {
        charge = interval1Nights * rate + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - (2 * discount)));
    }

    return charge;
}

//prints charges for both individual stays as well as a rental summary when the user inputs -1
void printNightsCharges(unsigned int nights, double charges, int summary) {
    //print the summary for individual stays
    if(!summary) {
        puts("Rental Charges");
        puts("");
        puts("Nights          Charge");
        printf("%d               $%.2lf\n", nights, charges);
    }

    //print the rental summary
    else {
        puts("Rental Property Owner Total Summary");
        puts("");
        puts("Nights          Charge");
        printf("%d               $%.2lf\n", nights, charges);
    }
}
