//Ethan Briggs
//  main.c
//  CS2060
//
//I am using xcode
//

#include <stdio.h>

//initialization of all constants to be used in program
int const SENTINAL_NEG1 = -1;
int unsigned const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400;
double const DISCOUNT = 50;

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
         interval1Nights, unsigned int interval2Nights, double rate, double discount);

int getValidInt(int min, int max, int sentinel);

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
          interval2Nights, double rate, double discount);

void printNightsCharges(unsigned int nights, double charges);

int main(void) {
    printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

    int totalNumOfNights = 0;
    double totalNumOfCharges = 0.0;
    int nightsEntered = 0;

    do{
        nightsEntered = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

        if (nightsEntered != SENTINAL_NEG1) {

            double charge = calculateCharges(nightsEntered, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

            if (charge >= 0) {
                totalNumOfNights += nightsEntered;
                totalNumOfCharges += charge;
                printNightsCharges(nightsEntered, charge);
            }

            else {
                printf("Error: you didn't enter the number of nights correctly.\n");
            }
        }
    }
    while (nightsEntered != SENTINAL_NEG1); {

        if (totalNumOfNights > 0) {
               printf("Total nights: %d\n", totalNumOfNights);
               printf("Total charges: $%.2lf\n", totalNumOfCharges);
        }

        else {
               printf("No rentals made.\n");
        }
    }
    return 0;
}

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
         interval1Nights, unsigned int interval2Nights, double rate, double discount) {

    printf("Rental Property can be rented for %d to %d nights\n", MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS);
    printf("$%.2lf rate a night for the first %d nights\n", RENTAL_RATE, INTERVAL_1_NIGHTS);
    int nextNight = INTERVAL_1_NIGHTS + 1;
    printf("$%.2lf discount rate a night for nights %d to %d\n", DISCOUNT, nextNight, INTERVAL_2_NIGHTS);
    double largerDiscount = DISCOUNT * 2;
    printf("%.2lf discount rate a night for each remaining night over %d\n", largerDiscount, INTERVAL_2_NIGHTS);
}

int getValidInt(int min, int max, int sentinel) {
    int userInput = 0;
    int valid = 0;

    while (!valid) {
        puts("Enter the number of nights you want to stay.");
        if (scanf("%d", &userInput) != 1) {
            //clear the input buffer
            while (getchar() != '\n');
        }

        else if((userInput == sentinel) || (userInput >= min && userInput <= max)) {
            valid = 1;
        }

        else {
            puts("Error: you didn't enter the number of nights correctly.");
        }
    }
    return userInput;
}
