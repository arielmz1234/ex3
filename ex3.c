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
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day);
int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int day = 0;
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
                addData(cube,days);
                break;
            }
            case addAll: {
                int index = 0;
                int isAssigned[NUM_OF_BRANDS] = {0,0,0,0,0};
                printf("No data for brands ");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("%s ", brands[i]);
                }
                printf("\n");
                while (index < NUM_OF_BRANDS) {
                    int assignedBrands[NUM_OF_BRANDS] ={-1,-1,-1,-1,-1};
                    assignedBrands[index] = addData(cube,days);
                    if (assignedBrands[index] != -1) {
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
                        for (int j = 0; j < NUM_OF_BRANDS; j++) {
                            if (assignedBrands[j] == i) {
                                isAssigned[i] = 1;
                            }
                        }
                        if (isAssigned[i] == 0) {
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
                getTotalSalesSum(cube,day);
                getBestSoldBrand(cube,day);
                getBestSoldType(cube,day);
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
void getTotalSalesSum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day) {
    int salesSum = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            salesSum += cube[day][i][j];
        }
    }
    printf("The sales total was %d\n", salesSum);
}
void getBestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day) {
    int bestbrand = 0;
    int brandSum = 0;
    int currentMax = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            currentMax += cube[day][i][j];
        }
        if (currentMax > brandSum) {
            bestbrand = i;
            brandSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
    printf("The best sold brand with %d sales was %s\n",brandSum, brands[bestbrand]);
}
void getBestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day) {
    int bestype = 0;
    int typeSum = 0;
    int currentMax = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            currentMax += cube[day][j][i];
        }
        if (currentMax > typeSum) {
            bestype = i;
            typeSum = currentMax;
            currentMax = 0;
        }
        else {
            currentMax = 0;
        }
    }
    printf("The best sold type with %d sales was %s\n",typeSum, types[bestype]);
}

