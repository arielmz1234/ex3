/******************
Name:
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
void printMenu();
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *salesSum);
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int *bestbrand, int *brandSum);
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *typeSum);
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestBrand,int *totalBrandSum);
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *TotalTypeSum);
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestDay, int *totalDaySum);
void getADM(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int dayCounter = 0;
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice) {
            case addOne: {
                addData(cube,dayCounter);
                break;
            }
            case addAll: {
                int index = 0;
                int isAssigned[NUM_OF_BRANDS] = {-1,-1,-1,-1,-1};
                printf("No data for brands ");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("%s ", brands[i]);
                }
                printf("\n");
                while(index < NUM_OF_BRANDS) {
                    int isFound = 0;
                    int carBrandVal = addData(cube,dayCounter);
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (carBrandVal == isAssigned[i]) {
                            isFound = 1;
                            break;
                        }
                    }
                    if (!isFound) {
                        isAssigned[carBrandVal] = carBrandVal;
                        index++;
                    }
                    if ( index == NUM_OF_BRANDS) {
                        dayCounter++;
                        break;
                    }
                    printf("No data for brands ");
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
                int checkDay;
                int isDayValid = 1;
                printf("What day would you like to analyze?\n");
                scanf("%d", &checkDay);
                checkDay--;
                if (checkDay > dayCounter-1 || checkDay == -1) {
                    isDayValid = 0;
                }
                while (!isDayValid) {
                    printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
                    scanf("%d", &checkDay);
                    checkDay--;
                    if (checkDay <= dayCounter-1 && checkDay != -1) {
                        isDayValid = 1;
                    }

                }
                int salesSum = 0;
                int bestBrand =-1;
                int brandSum = 0;
                int bestType = -1;
                int typeSum = 0;
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
                printf("*****************************************\n\n");
                printCube(cube,dayCounter);
                printf("\n\n*****************************************\n");
                break;
            }
            case insights: {
                int bestBrand;
                int totalBrandSum;
                int bestType;
                int totalTypeSum;
                int bestDay;
                int totalDaySum;
                getBestSoldBrandOverall(cube,dayCounter,&bestBrand,&totalBrandSum);
                printf("The best-selling brand overall is %s: %d$ \n",brands[bestBrand],totalBrandSum);
                getBestSoldTypeOverall(cube,dayCounter,&bestType,&totalTypeSum);
                printf("The best-selling type of car overall is %s: %d$ \n",types[bestType],totalTypeSum);
                getBestSoldDayOverall(cube,dayCounter,&bestDay,&totalDaySum);
                printf("The most profitable day was day number %d: %d$ \n",bestDay+1,totalDaySum);
                break;
            }
            case deltas: {
                getADM(cube,dayCounter);
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
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day){
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
        return carBrand;
    }
    else {
        printf("This brand is not valid\n");
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
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *salesSum) {
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            *salesSum += cube[day][i][j];
        }
    }
}
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int *bestBrand, int *brandSum) {
    int currentMax = 0;
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
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *typeSum){
    int currentMax = 0;
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
void getADM(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day){
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


