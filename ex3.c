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
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS]);
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *salesSum);
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day,int *bestbrand, int *brandSum);
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int *bestType, int *typeSum);
void printCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
int getLatestDay(int days[NUM_OF_BRANDS]);
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestBrand,int *totalBrandSum);
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestType, int *TotalTypeSum);
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestDay, int *totalDaySum);
void getADM(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
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
                int addedBrand = addData(cube,days);
                if(addedBrand != -1) {
                    days[addedBrand]++;
                }
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
                    int carBrandVal = addData(cube,days);
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
                        for (int i = 0; i < NUM_OF_BRANDS; i++) {
                            days[i]++;
                        }
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
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    if (checkDay > days[i]) {
                        isDayValid = 0;
                    }
                }
                while (!isDayValid) {
                    printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
                    scanf("%d", &checkDay);
                    checkDay--;
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (checkDay > days[i]) {
                            isDayValid = 0;
                        }
                    }
                }
                int salesSum;
                int bestBrand =-1;
                int brandSum = 0;
                int bestType = -1;
                int typeSum = 0;
                getTotalSalesSum(cube,checkDay,&salesSum);
                printf("The sales total was %d\n", salesSum);
                getBestSoldBrand(cube,checkDay,&bestBrand,&brandSum);
                printf("The best sold brand with %d sales was %s\n",brandSum, brands[bestBrand]);
                getBestSoldType(cube,checkDay, &bestType, &typeSum);
                printf("The best sold type with %d sales was %s\n",typeSum, types[bestType]);
                break;
            }
            case print: {
                int latestDay = getLatestDay(days);
                printf("*****************************************\n\n");
                for (int i = 0; i < latestDay; i++) {
                    printCube(cube,i);
                }
                printf("\n*****************************************\n");
            }
            case insights: {
                int bestBrand;
                int totalBrandSum;
                int bestType;
                int totalTypeSum;
                int bestDay;
                int totalDaySum;
                getBestSoldBrandOverall(cube,days,&bestBrand,&totalBrandSum);
                printf("The best-selling brand overall is %s: %d$ \n",brands[bestBrand],totalBrandSum);
                getBestSoldTypeOverall(cube,days,&bestType,&totalTypeSum);
                printf("The best-selling type overall is %s: %d$ \n",types[bestType],totalTypeSum);
                getBestSoldDayOverall(cube,days,&bestDay,&totalDaySum);
                printf("The most profitable day was day number %d: %d$ \n",bestDay+1,totalDaySum);
                break;
            }
            case deltas: {
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
int addData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS]){
    int carBrand;
    int SUVSales;
    int SedanSales;
    int CoupeSales;
    int GTSales;
    printf("Please complete the data\n");
    scanf("%d" "%d" "%d" "%d" "%d" , &carBrand, &SUVSales, &SedanSales, &CoupeSales, &GTSales);
    if (carBrand <= 4 && carBrand >= 0) {
        cube[days[carBrand]][carBrand][0] = SUVSales;
        cube[days[carBrand]][carBrand][1] = SedanSales;
        cube[days[carBrand]][carBrand][2] = CoupeSales;
        cube[days[carBrand]][carBrand][3] = GTSales;
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
            if (cube[day][i][0] == -1) {
                printf("Sales for: %s\n", brands[i]);
            }
            else {
                printf("Sales for: %s\n", brands[i]);
                printf("Day %d SUV: %d Sedan: %d Coupe: %d GT: %d\n", day+1,cube[day][i][0],cube[day][i][1],cube[day][i][2],cube[day][i][3]);
        }

    }
}
    int getLatestDay(int days[NUM_OF_BRANDS]){
        int latestDay = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (days[i] > latestDay) {
                latestDay = days[i];
            }
        }
        return latestDay;
    }
void getBestSoldBrandOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestBrand,int *totalBrandSum){
    int brandSum = 0;
    int totalSumArr[NUM_OF_BRANDS]= {0};
    int latestDay = getLatestDay(days);
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < latestDay; j++) {
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
void getBestSoldTypeOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestType, int *TotalTypeSum) {
    int typeSum = 0;
    int totalSumArr[NUM_OF_TYPES]= {0};
    int latestDay = getLatestDay(days);
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < latestDay; j++) {
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
void getBestSoldDayOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days[NUM_OF_BRANDS], int *bestDay, int *totalDaySum) {
    int daySum = 0;
    int latestDay = getLatestDay(days);
    int totalSumArr[DAYS_IN_YEAR]= {0};
    for (int i = 0; i < latestDay; i++) {
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

}


