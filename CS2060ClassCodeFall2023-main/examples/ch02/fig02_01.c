// fig02_01.c
//
//  CS2060
//
//I am using xcode
//

#include <stdio.h>

double calculateArea(int length, int width);
// function main begins program execution
int main(void) {
    int  length = 0;
    int width = 0;
    printf("Welcome to C!\n");
    puts("Enter the length");
    int scanfReturn = scanf("%d", &length);
    if (scanfReturn == 1) {
        puts("Enter the width");
        scanf("%d", &width);
        int area = length * width;
        printf("%d\n", area);
        double averageResult = (double)length / width;
        printf("%.1lf\n", averageResult);
    }
    return 0;
} // end function main





/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *r
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
