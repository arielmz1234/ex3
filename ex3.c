/******************
Name: Ariel Mizrahi
ID:
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
//comments about each function will in each implementation of the functions
void printMenu();
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes);
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int daysInYear, int numOfBrands, int NumOfTypes);
void getAdm(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int numOfBrands, int NumOfTypes);
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
                //Here we call all the functions that print us the wanted information for the day the user chose (checkDay)
                printf("In day number %d:\n", checkDay+1);
                getTotalSalesSum(cube,checkDay,NUM_OF_BRANDS,NUM_OF_TYPES);
                getBestSoldBrand(cube,checkDay,NUM_OF_BRANDS,NUM_OF_TYPES);
                getBestSoldType(cube,checkDay,NUM_OF_BRANDS,NUM_OF_TYPES);
                printf("\n");
                break;
            }
            case print: {
                /*Here we print the lines as requested and then call the function printCube
                 with the arguments cube and the dayCounter so the function will now what to print and until what day*/
                printf("*****************************************\n\n");
                printCube(cube,dayCounter,NUM_OF_BRANDS,NUM_OF_TYPES);
                printf("\n\n*****************************************\n");
                break;
            }
            case insights: {
                //Here we call all the functions that print us the wanted information for all the days that got inputs
                getBestSoldBrandOverall(cube,dayCounter,NUM_OF_BRANDS,NUM_OF_TYPES);
                getBestSoldTypeOverall(cube,dayCounter,NUM_OF_BRANDS,NUM_OF_TYPES);
                getBestSoldDayOverall(cube,dayCounter,DAYS_IN_YEAR,NUM_OF_BRANDS,NUM_OF_TYPES);
                break;
            }
            case deltas: {
                //We call the getAdm function with the arguments cube and dayCounter so the function will now what to check and until which day
                getAdm(cube,dayCounter,NUM_OF_BRANDS,NUM_OF_TYPES);
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
//getTotalSalesSum is used to print the total sales for a given day (the day argument)
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int numOfTypes) {
    //salesSum will hold the sum of all the sales of the day
    int salesSum = 0;
    //There are 2 running nested for loops to run over all the types of each car brands of the chosen day and to sum their sales
    for (int i = 0; i < numOfBrands; i++) {
        for (int j = 0; j < numOfTypes; j++) {
            salesSum += cube[day][i][j];
        }
    }
    printf("The sales total was %d\n", salesSum);
}
//getBestSoldBrand is used to print the total sales of the highest grossing brand for a given day (the day argument)
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int numOfTypes) {
    //currentMax will help find the highest sum of sales from all the brands, initialized at 0
    int currentMax = 0;
    //bestBrand will hold the index of the highest grossing brand of the given day, initialized at -1
    int bestBrand = -1;
    //brandSum will hold the total sum of the sales of the highest grossing brand, initialized at 0
    int brandSum = 0;
    /*In this 2 for loops we are checking for each brand what there sum of sales were for that day and give the value to currentMax,
     if I find that the currentMax is bigger then the brandSum which is first initialized to 0, I give brandSum the value that currentMax holds, and bestBrand
     the index of the brand that his sales were bigger then the previous brandSum and reset currentMax value to 0 for the next brand,
     if the currentMax isn't bigger than brandSum I reset him and check for the next brand without changing brandSum*/
    for (int i = 0; i < numOfBrands; i++) {
        for (int j = 0; j < numOfTypes; j++) {
            currentMax += cube[day][i][j];
        }
        if (currentMax > brandSum) {
            bestBrand = i;
            brandSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
    printf("The best sold brand with %d sales was %s\n",brandSum, brands[bestBrand]);
}
//getBestSoldType is used to print the total sales of the highest grossing type for a given day (the day argument)
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int numOfTypes) {
    //currentMax will help find the highest sum of sales from all the types, initialized at 0
    int currentMax = 0;
    //bestType will hold the index of the highest grossing type of the given day, initialized at -1
    int bestType = -1;
    //typeSum will hold the total sum of the sales of the highest grossing type, initialized at 0
    int typeSum = 0;
    /*In this 2 for loops we are checking for each type what there sum of sales were for that day and give the value to currentMax,
     if I find that the currentMax is bigger then the typeSum which is first initialized to 0, I give typeSum the value that currentMax holds, and bestType
     the index of the type that his sales were bigger then the previous typeSum and reset currentMax value to 0 for the next type,
     if the currentMax isn't bigger than typeSum I reset him and check for the next type without changing typeSum*/
    for (int i = 0; i < numOfTypes; i++) {
        for (int j = 0; j < numOfBrands; j++) {
            currentMax += cube[day][j][i];
        }
        if (currentMax > typeSum) {
            bestType = i;
            typeSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
    printf("The best sold type with %d sales was %s\n",typeSum, types[bestType]);
}
//printCube is used to print all the information for every day that got inputs
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int numOfTypes) {
    /*The first for loop runs through the brands and every time get the total sales of that brand,
     the second  and third nested loops will run in the first loop and get the total sales of that day,
     we want to check for each brand if he got any sales at all, if not we only print Sales for BrandName
     and move to the next brand as requested*/
    for (int i = 0; i < numOfBrands; i++) {
        //we don't want the totalSales to stack with other brand so each time we check another brand we reset totalSales
        int totalSales = 0;
        for (int j = 0; j < numOfTypes; j++) {
            for (int k = 0; k < day; k++) {
                totalSales += cube[k][i][j];
            }
        }
            if (totalSales == 0){
                printf("Sales for %s:\n", brands[i]);
            }
        /*We enter the else if we found that a brand sales weren't 0, then we print for each day his sales for each type of car
        the type of car is the index 0-3, and the day that we want to be printed is the day +1 because the day  1-365 are represented as 0-364 in the program*/
            else {
                printf("Sales for %s:\n", brands[i]);
                for (int t = 0; t < day; t++) {
                    printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", t+1,cube[t][i][0],cube[t][i][1],cube[t][i][2],cube[t][i][3]);
                }
            }
    }
}
//getBestSoldBrandOverall is used to print the total sales of the highest grossing brand until the last day that got values (day)
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int NumOfTypes){
    //brandSum will hold the sum of the sales of each brand, changes everytime other brand sales are higher than him, initialed at 0
    int brandSum = 0;
    //bestBrand will hold the index of the highest grossing brand until the last day that got values, initialed at -1
    int bestBrand = -1;
    //totalBrandSum will hold the sum of the sales of the highest grossing brand until the last day that got values, initialed at 0
    int totalBrandSum = 0;
    //totalSumArr is an array the size of NUM_OF_BRANDS that will hold the sum of each brand sales overall until the last day that got values
    int totalSumArr[numOfBrands];
    //initialize the arr to 0
    for (int i = 0; i <numOfBrands; i++) {
        totalSumArr[i] = 0;
    }
    //In this nested loops we give the total sales for each brand to each index of totalSumArr
    for (int i = 0; i < numOfBrands; i++) {
        for (int j = 0; j < day; j++) {
            for (int k = 0; k < NumOfTypes; k++) {
                totalSumArr[i] += cube[j][i][k];
            }
        }
    }
    /*Here we want to check what is the biggest value in the array(what is the highest grossing brand),
     every time we check if the array in the index i is bigger than the brandSum that is initialized at 0,
     if it is bigger we give his index to bestBrand and his value to brandSum*/
    for (int i = 0; i < numOfBrands; i++) {
        if (totalSumArr[i] > brandSum) {
            bestBrand = i;
            brandSum = totalSumArr[i];
        }
    }
    /*after we've exited the loop we got our index for the highest grossing brand and the value which is the sums array
     in the index of the highest grossing brand so now we can print as requested*/
    totalBrandSum = totalSumArr[bestBrand];
    printf("The best-selling brand overall is %s: %d$ \n",brands[bestBrand],totalBrandSum);
}
//getBestSoldTypeOverall is used to print the total sales of the highest grossing type until the last day that got values (day)
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int numOfBrands, int numOfTypes) {
    //typeSum will hold the sum of the sales of each type, changes everytime other type sales are higher than him, initialed at 0
    int typeSum = 0;
    //bestType will hold the index of the highest grossing type until the last day that got values, initialed at -1
    int bestType = -1;
    //totalTypeSum will hold the sum of the sales of the highest grossing type until the last day that got values, initialed at 0
    int totalTypeSum = 0;
    //totalSumArr is an array the size of NUM_OF_TYPES that will hold the sum of each type sales overall until the last day that got values
    int totalSumArr[numOfTypes];
    //initialize the arr to 0
    for (int i = 0; i <numOfTypes; i++) {
        totalSumArr[i] = 0;
    }
    //In this nested loops we give the total sales for each brand to each index of totalSumArr
    for (int i = 0; i < numOfTypes; i++) {
        for (int j = 0; j < day; j++) {
            for (int k = 0; k < numOfBrands; k++) {
                totalSumArr[i] += cube[j][k][i];
            }
        }
    }
      /*Here we want to check what is the biggest value in the array(what is the highest grossing type),
     every time we check if the array in the index i is bigger than the typeSum that is initialized at 0,
     if it is bigger we give his index to bestType and his value to typeSum*/
    for (int i = 0; i < numOfTypes; i++) {
        if (totalSumArr[i] > typeSum) {
            bestType = i;
            typeSum = totalSumArr[i];
        }
    }
    /*after we've exited the loop we got our index for the highest grossing type and the value which is the sums array
    in the index of the highest grossing type so now we can print as requested*/
    totalTypeSum = totalSumArr[bestType];
    printf("The best-selling type of car is %s: %d$ \n",types[bestType],totalTypeSum);
}
//getBestSoldDayOverall is used to print the total sales of the highest grossing day until the last day that got values (day)
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int daysInYear, int numOfBrands, int numOfTypes) {
    //daySum will hold the sum of the sales of each day, changes everytime other day sales are higher than him, initialed at 0
    int daySum = 0;
    //bestDay will hold the highest grossing day until the last day that got values, initialed at -1
    int bestDay = -1;
    //totalDaySum will hold the sum of the sales of the highest grossing day until the last day that got values, initialed at 0
    int totalDaySum = 0;
    //totalSumArr is an array the size of DAYS_IN_YEAR that will hold the sum of each day sales overall until the last day that got values
    int totalSumArr[daysInYear];
    //initialize the arr to 0
    for (int i = 0; i < daysInYear; i++) {
        totalSumArr[i] = 0;
    }
    /*In this nested loops we give the total sales for each day to each index of
    totalSumArr(here we don't necessarily give values to each day, only until the last day that got values)*/
    for (int i = 0; i < day; i++) {
        for (int j = 0; j < numOfBrands; j++) {
            for (int k = 0; k < numOfTypes; k++) {
                totalSumArr[i] += cube[i][j][k];
            }
        }
    }
    /*Here we want to check what is the biggest value in the array(what is the highest grossing day),
    every time we check if the array in the index i is bigger than the daySum that is initialized at 0,
    if it is bigger we give his index to bestDay and his value to daySum*/
    for (int i = 0; i < numOfTypes; i++) {
        if (totalSumArr[i] > daySum) {
            bestDay = i;
            daySum = totalSumArr[i];
        }
    }
    /*after we've exited the loop we got our index for the highest grossing day and the value which is the sums array
    in the index of the highest grossing day so now we can print as requested*/
   totalDaySum = totalSumArr[bestDay];
    printf("The most profitable day was day number %d: %d$ \n",bestDay+1,totalDaySum);
}
//getAdm is used to get the average delta metrics for each brand until the last day that got values (day)
void getAdm(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int numOfBrands, int numOfTypes){
    //First we want to check if day is bigger than 1
    if (day>1) {
        //This loop goes through every brand and gets his adm and prints it as requested
        for (int i = 0; i < numOfBrands; i++) {
            //For every brand I want the delta to be initialized at 0
            float delta = 0;
            /*In this loop I go through every day starting day 1(second day)
             and get the sum of all the day sales(curSales) and the sum of all the previous day sales(prevSales)*/
            for (int j = 1; j < day; j++) {
                int curSales = 0;
                int prevSales = 0;
                for (int k = 0; k < numOfTypes; k++) {
                    curSales += cube[j][i][k];
                    prevSales += cube[j-1][i][k];
                }
                //Delta will be curSales - prevSales, curSales and prevSales get new values for every day so delta sums all those values
                delta += curSales - prevSales;
            }
            //Here we calculate the adm of the brand in the index i and then print it as requested
            float adm = (delta / (day-1));
            printf("Brand: %s, Average Delta: %f\n",brands[i], adm);
            }
        }
    //If day isn't bigger than 1 that means there is 1 or fewer days that got values and I want to print 0 for every brand adm
    else {
        for (int i = 0; i < numOfBrands; i++) {
            printf("Brand: %s, Average Delta: 0.000000\n",brands[i]);
        }
    }

}


