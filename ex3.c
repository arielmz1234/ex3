/******************
Name: Ariel Mizrahi
ID: 213458821
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
void printMenu();
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *salesSum);
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int *bestbrand, int *brandSum);
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *typeSum);
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestBrand,int *totalBrandSum);
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *TotalTypeSum);
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestDay, int *totalDaySum);
void getAdm(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    //dayCounter will hold the latest day that is available for getting data from the user
    int dayCounter = 0;
    //First I Want to initialize the cube, so I run on every index in the cube and initialize it to -1 as requested
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
    int choice;
    //choice will hold the choice the user inputs
    printMenu();
    scanf("%d", &choice);
    //I want the program to continue until the user inputs 7(done), so this is the while loop condition
    while(choice != done){
        switch(choice) {
            case addOne: {
                //In this case I only want to add one car brand sales for the latest day which is the value dayCounter holds
                addData(cube,dayCounter);
                break;
            }
            case addAll: {
                int counter = 0;
                /*isAssigned array is an array with the size of the NUM_OF_BRANDS that will help me later to understand
                 if a brand received an input from the user*/
                int isAssigned[NUM_OF_BRANDS] = {-1,-1,-1,-1,-1};
                //The initial print for the no data for brands and then a loop that prints all the brand names as requested
                printf("No data for brands ");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("%s ", brands[i]);
                }
                printf("\n");
                /*This while loop is the loop in which we enter values to the available day for all brand,
                 the only way we want to leave the loop is if all 5 brands got values,
                 counter will only grow if a brand with no value got a new value so when all brands got values that means counter got to NUM_OF_BRANDS,
                 and we can exit the loop
                 */
                while(counter < NUM_OF_BRANDS) {
                    //isFound checks if a brand already got values, if so isFound is true(1), isFound is initialed at 0
                    int isFound = 0;
                    /*Here I call addData on the cube and the available day,
                     *and carBrandVal received the output of the function which is the brand number of the brand that got input values*/
                    int carBrandVal = addData(cube,dayCounter);
                    // In this loop I want to check if a brand is already assigned if so isFound is true(1)
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (carBrandVal == isAssigned[i]) {
                            isFound = 1;
                            break;
                        }
                    }
                    //If the brand already got values in the array I want to continue the loop as if nothing happened and enter those values instead of the old ones
                    if (!isFound) {
                        isAssigned[carBrandVal] = carBrandVal;
                        counter++;
                    }
                    /*If counter grew to NUM_OF_BRANDS that means the last brand got inputs
                     and no need to continue the rest of the loop that prints more lines,
                     only when were done and all the brands got inputs for that day we can add 1 to the dayCounter*/
                    if (counter == NUM_OF_BRANDS) {
                        dayCounter++;
                        break;
                    }
                    printf("No data for brands ");
                    /*Here we want to print again all the brands but exclude the brands that already got their inputs
                     so we print only the brand names that their index wasn't changed in the isAssigned array*/
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (isAssigned[i] == -1) {
                            printf("%s ", brands[i]);
                        }
                    }
                    printf("\n");
                }
                break;
            }
            case stats: {
                //checkDay will hold the day we want to check his stats
                int checkDay;
                //isDayValid will hold true(1) if the day that was input is a day that got values and false(0) if not
                int isDayValid = 1;
                printf("What day would you like to analyze?\n");
                scanf("%d", &checkDay);
                //In my code day 1 means day 0, so I subtract 1 from the checkDay
                checkDay--;
                /*Here I want to check if the checkDay is invalid,
                 if the day is bigger then the last available day(dayCounter)-1,
                 that means that there are no values that day and the checkDay is invalid, if the user input 0 as the check day (meaning -1 because of the subtraction)
                 that's also invalid*/
                if (checkDay > dayCounter-1 || checkDay == -1) {
                    isDayValid = 0;
                }
                /*So this loop continues to run until the user inputs a valid day,
                 inside this loop we preform the inverse checks as before but now we check if the checkDay is valid,
                 so when it is we change the isDayValid flag to true and leave the loop*/
                while (!isDayValid) {
                    printf("Please enter a valid day.\nWhat day would you like to analyze?\n");
                    scanf("%d", &checkDay);
                    checkDay--;
                    if (checkDay <= dayCounter-1 && checkDay != -1) {
                        isDayValid = 1;
                    }

                }
                //salesSum will be changed in the getTotalSalesSum function to the sum of all sales in the checkDay day and is now initialized to 0
                int salesSum = 0;
                //bestBrand will be changed in the getBestSoldBrand function to the index of the highest grossing brand in the checkDay day and is now initialized to -1
                int bestBrand =-1;
                //brandSum will be changed in the getBestSoldBrand function to the highest grossing brand sales sum in the checkDay day and is now initialized to 0
                int brandSum = 0;
                //bestType will be changed in the getBestSoldType function to the index of the highest grossing type in the checkDay day and is now initialized to -1
                int bestType = -1;
                //typeSum will be changed in the getBestSoldType function to the highest grossing type sales sum in the checkDay day and is now initialized to 0
                int typeSum = 0;
                /*In the following lines of code we print the message as requested
                 and call the functions with the arguments cube and the checkDay so the function will now what to print and at what day,
                 the other arguments each function get are the pointers of each variable we want to change so we can change him in the function*/
                printf("In day number %d:\n", checkDay+1);
                getTotalSalesSum(cube,checkDay,&salesSum);
                printf("The sales total was %d\n", salesSum);
                getBestSoldBrand(cube,checkDay,&bestBrand,&brandSum);
                printf("The best sold brand with %d sales was %s\n",brandSum, brands[bestBrand]);
                getBestSoldType(cube,checkDay, &bestType, &typeSum);
                printf("The best sold type with %d sales was %s\n",typeSum, types[bestType]);
                printf("\n");
                break;
            }
            case print: {
                /*Here we print the lines as requested and then call the function printCube
                 with the arguments cube and the dayCounter so the function will now what to print and until what day*/
                printf("*****************************************\n\n");
                printCube(cube,dayCounter);
                printf("\n\n*****************************************\n");
                break;
            }
            case insights: {
                //bestBrand will be changed in the getBestSoldBrandOverall function to the index of the highest grossing brand overall and is initialized to -1
                int bestBrand = -1;
                //totalBrandSum will be changed in the getBestSoldBrandOverall function to the sales sum of the  highest grossing brand overall and is initialized to 0
                int totalBrandSum = 0;
                //bestType will be changed in the getBestSoldTypeOverall function to the index of the highest grossing type overall and is initialized to -1
                int bestType = -1;
                //totalTypeSum will be changed in the getBestSoldTypeOverall function to the sales sum of the  highest grossing type overall and is initialized to 0
                int totalTypeSum = 0;
                //bestDay will be changed in the getBestSoldDayOverall function to the highest grossing day  and is initialized to -1
                int bestDay = -1;
                //totalDaySum will be changed in the getBestSoldDayOverall function to the sales sum of the highest grossing day  and is initialized to 0
                int totalDaySum = 0;
                /*In the following lines of code we print the message as requested
                and call the functions with the arguments cube and the dayCounter so the function will now what to print and until which day,
                the other arguments each function get are the pointers of each variable we want to change so we can change him in the function*/
                getBestSoldBrandOverall(cube,dayCounter,&bestBrand,&totalBrandSum);
                printf("The best-selling brand overall is %s: %d$ \n",brands[bestBrand],totalBrandSum);
                getBestSoldTypeOverall(cube,dayCounter,&bestType,&totalTypeSum);
                printf("The best-selling type of car is %s: %d$ \n",types[bestType],totalTypeSum);
                getBestSoldDayOverall(cube,dayCounter,&bestDay,&totalDaySum);
                printf("The most profitable day was day number %d: %d$ \n",bestDay+1,totalDaySum);
                break;
            }
            case deltas: {
                //We call the getAdm function with the arguments cube and dayCounter so the function will now what to check and until which day
                getAdm(cube,dayCounter);
                break;
            }
            default:
                printf("Invalid input\n");

        }
        printMenu();
        scanf("%d", &choice);
    }
        printf("Goodbye!\n");
        return 0;

}
//addData is used to add data to the next available day (the day argument) of the brand the user chooses
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day){
    /*All of those variables will hold the user inputs and if the user entered a valid car brand
     those values will go into the cube in the next available day to the car brand the user has chosen*/
    int carBrand;
    int SUVSales;
    int SedanSales;
    int CoupeSales;
    int GTSales;
    printf("Please complete the data\n");
    scanf("%d" "%d" "%d" "%d" "%d" , &carBrand, &SUVSales, &SedanSales, &CoupeSales, &GTSales);
    if (carBrand <= 4 && carBrand >= 0) {
        cube[day][carBrand][0] = SUVSales;
        cube[day][carBrand][1] = SedanSales;
        cube[day][carBrand][2] = CoupeSales;
        cube[day][carBrand][3] = GTSales;
        //I want to return the car brand that got values, so I can use it in the main
        return carBrand;
    }
    else {
        printf("This brand is not valid\n");
        //If the car brand wasn't valid the function return -1
        return -1;
    }
}
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
//getTotalSalesSum gets the arguments cube, day so it will know in which day to check, and a pointer to salesSum so I can use the sales sum of that day in main
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *salesSum) {
    //There are 2 running nested for loops, to run over all the types of each car brands of the chosen day and to sum their sales
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            *salesSum += cube[day][i][j];
        }
    }
}
/*getBestSoldBrand gets the arguments cube, day so it will know in which day to check,
 a pointer to bestBrand, so I can use the index of the highest grossing brand of that day in main,
 and brandSum so, I can use the sum of all the highest grossing brand sales in main*/
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int *bestBrand, int *brandSum) {
    //currentMax will help find the highest sum of sales from all the brands, initialized at 0
    int currentMax = 0;
    /*In this 2 for loops we are checking for each brand what there sum of sales were for that day and give the value to currentMax,
     if I find that the currentMax is bigger then the brandSum which is first initialized to 0 in the main, I give brandSum the value that currentMax holds, and bestBrand
     the index of the brand that his sales were bigger then the previous brandSum and reset currentMax value to 0 for the next brand,
     if the currentMax isn't bigger than brandSum I reset him and check for the next brand without changing brandSum*/
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            currentMax += cube[day][i][j];
        }
        if (currentMax > *brandSum) {
            *bestBrand = i;
            *brandSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
}
/*getBestSoldType gets the arguments cube, day so it will know in which day to check,
 a pointer to bestType, so I can use the index of the highest grossing type of that day in main,
 and typeSum so, I can use the sum of all the highest grossing type sales in main*/
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *typeSum){
    //currentMax will help find the highest sum of sales from all the types, initialized at 0
    int currentMax = 0;
    /*In this 2 for loops we are checking for each type what there sum of sales were for that day and give the value to currentMax,
     if I find that the currentMax is bigger then the typeSum which is first initialized to 0 in the main, I give typeSum the value that currentMax holds, and bestType
     the index of the type that his sales were bigger then the previous typeSum and reset currentMax value to 0 for the next type,
     if the currentMax isn't bigger than typeSum I reset him and check for the next type without changing typeSum*/
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            currentMax += cube[day][j][i];
        }
        if (currentMax > *typeSum) {
            *bestType = i;
            *typeSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
}
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day) {
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        int totalSales = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            for (int k = 0; k < day; k++) {
                totalSales += cube[k][i][j];
            }
        }
            if (totalSales == 0){
                printf("Sales for %s:\n", brands[i]);
            }
            else {
                printf("Sales for %s:\n", brands[i]);
                for (int t = 0; t < day; t++) {
                    printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", t+1,cube[t][i][0],cube[t][i][1],cube[t][i][2],cube[t][i][3]);
                }
            }
    }
}
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestBrand,int *totalBrandSum){
    int brandSum = 0;
    int totalSumArr[NUM_OF_BRANDS]= {0};
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < day; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                totalSumArr[i] += cube[j][i][k];
            }
        }
    }
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (totalSumArr[i] > brandSum) {
            *bestBrand = i;
            brandSum = totalSumArr[i];
        }
    }
    *totalBrandSum = totalSumArr[*bestBrand];
}
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *TotalTypeSum) {
    int typeSum = 0;
    int totalSumArr[NUM_OF_TYPES]= {0};
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < day; j++) {
            for (int k = 0; k < NUM_OF_BRANDS; k++) {
                totalSumArr[i] += cube[j][k][i];
            }
        }
    }
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (totalSumArr[i] > typeSum) {
            *bestType = i;
            typeSum = totalSumArr[i];
        }
    }
    *TotalTypeSum = totalSumArr[*bestType];
}
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestDay, int *totalDaySum) {
    int daySum = 0;
    int totalSumArr[DAYS_IN_YEAR]= {0};
    for (int i = 0; i < day; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                totalSumArr[i] += cube[i][j][k];
            }
        }
    }
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        if (totalSumArr[i] > daySum) {
            *bestDay = i;
            daySum = totalSumArr[i];
        }
    }
   *totalDaySum = totalSumArr[*bestDay];
}
void getAdm(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day){
    if (day>1) {
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            float delta = 0;
            for (int j = 1; j < day; j++) {
                int curSales = 0;
                int prevSales = 0;
                for (int k = 0; k < NUM_OF_TYPES; k++) {
                    curSales += cube[j][i][k];
                    prevSales += cube[j-1][i][k];
                }
                delta += curSales - prevSales;
            }
            float adm = (delta / (day-1));
            printf("Brand: %s, Average Delta: %f\n",brands[i], adm);
            }
        }
    else {
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            printf("Brand: %s, Average Delta: 0.000000\n",brands[i]);
        }
    }

}


