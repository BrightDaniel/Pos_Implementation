#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_NAME_LENGTH 30
#define MAX_CUSTOMERS 10
#define FILENAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

typedef struct {
    char itemName[MAX_NAME_LENGTH];
    int quantity;
    float subtotal;
} OrderItem;

void placeOrders(MenuItem menu[], int numItems);
void saveOrdersToFile(OrderItem orders[][MAX_ITEMS], int numCustomers);
void analyzeOrders(OrderItem orders[][MAX_ITEMS], int numCustomers, MenuItem menu[], int numItems);

int main() {
    MenuItem menu[MAX_ITEMS] = {
        {"Beef burger", 8.5}, {"Grilled beef steak", 9}, {"Sous vide chicken breast", 7},
        {"Grilled chicken", 7}, {"Grilled lamb Kofta", 5.5}, {"Minced lamb", 8.5},
        {"Teriyaki salmon(grilled)", 9.5}, {"Honey garlic salmon", 9.5}, {"Shrimp stew", 8},
        {"Grilled garlic shrimp", 10}, {"Vegan BBQ complex", 7}, {"Fry seasonal veg(Vegan)", 6},
        {"Halloumi", 7}, {"Pesto pasta", 2}, {"Lard fried potato", 5},
        {"Vegan pasta salad", 2}, {"Sweet potato fries(Vegan)", 5}, {"Rice", 1}
    };

    placeOrders(menu, MAX_ITEMS);

    return 0;
}

void placeOrders(MenuItem menu[], int numItems) {
    int numCustomers, itemIndex, quantity;
    float total = 0;

    printf("Enter the number of customers attending the event: ");
    scanf("%d", &numCustomers);

    // Clear the input buffer
    while (getchar() != '\n');

    // Array to store details of each customer's order
    OrderItem orders[MAX_CUSTOMERS][MAX_ITEMS];

    for (int i = 0; i < numCustomers; i++) {
        printf("\nCustomer %d:\n", i + 1);
        float customerTotal = 0;

        int orderIndex = 0;
        while (1) {
            printf("Enter item (or type 'check-out' to finish): ");

            char buffer[MAX_NAME_LENGTH];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

            if (strcmp(buffer, "check-out") == 0) {
                break;
            }

            int found = 0;
            for (int j = 0; j < numItems; j++) {
                if (strcmp(buffer, menu[j].name) == 0) {
                    found = 1;
                    itemIndex = j;
                    break;
                }
            }

            if (found) {
                printf("Enter quantity: ");
                scanf("%d", &quantity);

                // Update the order details
                strcpy(orders[i][orderIndex].itemName, menu[itemIndex].name);
                orders[i][orderIndex].quantity = quantity;
                orders[i][orderIndex].subtotal = menu[itemIndex].price * quantity;

                customerTotal += orders[i][orderIndex].subtotal;
                orderIndex++;
            } else {
                printf("Invalid item. Please enter a valid item.\n");
            }

            // Clear the input buffer
            while (getchar() != '\n');
        }

        // Display the summary for each customer
        printf("\nSummary for Customer %d:\n", i + 1);
        for (int j = 0; j < orderIndex; j++) {
            printf("%s: %d %s, Subtotal: £%.2f\n", orders[i][j].itemName, orders[i][j].quantity, 
                (orders[i][j].quantity > 1) ? "items" : "item", orders[i][j].subtotal);
        }
        printf("Total amount spent by Customer %d: £%.2f\n", i + 1, customerTotal);

        // Save the order information to a file
        saveOrdersToFile(orders, i + 1);

        total += customerTotal;
    }

    // Display the total summary
    printf("\nTotal amount spent by all customers: £%.2f\n", total);

    // Analyze orders
    printf("\nAnalysis Results for Customer Orders:\n");
    analyzeOrders(orders, numCustomers, menu, numItems);
}

void saveOrdersToFile(OrderItem orders[][MAX_ITEMS], int numCustomers) {
    char filename[FILENAME_LENGTH];
    sprintf(filename, "customer_orders_%d.txt", numCustomers);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "Summary for Customer %d:\n", numCustomers);
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (strlen(orders[numCustomers - 1][i].itemName) > 0) {
            fprintf(file, "%s: %d %s, Subtotal: £%.2f\n", orders[numCustomers - 1][i].itemName,
                    orders[numCustomers - 1][i].quantity,
                    (orders[numCustomers - 1][i].quantity > 1) ? "items" : "item",
                    orders[numCustomers - 1][i].subtotal);
        }
    }
    fprintf(file, "Total amount spent by Customer %d: £%.2f\n", numCustomers,
            orders[numCustomers - 1][0].subtotal);

    fclose(file);
}

void analyzeOrders(OrderItem orders[][MAX_ITEMS], int numCustomers, MenuItem menu[], int numItems) {
    // Initialize variables for analysis
    float totalMoney = 0;
    int totalItems = 0;
    int veganItems = 0;
    int grillItems = 0;
    int stoveItems = 0;

    for (int i = 0; i < numCustomers; i++) {
        for (int j = 0; j < MAX_ITEMS; j++) {
            // Update analysis variables
            totalMoney += orders[i][j].subtotal;
            totalItems += orders[i][j].quantity;

            // Check if the item is vegan
            if (strstr(orders[i][j].itemName, "(Vegan)") != NULL) {
                veganItems += orders[i][j].quantity;
            }

            // Check if the item is related to the grill or stove
            if (strstr(orders[i][j].itemName, "Grilled") != NULL) {
                grillItems += orders[i][j].quantity;
            } else if (strstr(orders[i][j].itemName, "Fry") != NULL || strstr(orders[i][j].itemName, "Lard") != NULL) {
                stoveItems += orders[i][j].quantity;
            }
        }
    }

    // (a) Average money spent per person
    float averageMoneyPerPerson = (numCustomers > 0) ? totalMoney / numCustomers : 0;
    printf("(a) Average money spent per person: £%.2f\n", averageMoneyPerPerson);

    // (b) Percentage of vegan dishes in total orders
    float percentageVegan = (totalItems > 0) ? (veganItems / (float)totalItems) * 100 : 0;
    printf("(b) Percentage of vegan dishes in total orders: %.2f%%\n", percentageVegan);

    // (c) Identify items related to the grill and stove
    printf("(c) Items related to the grill: %d\n", grillItems);
    printf("(c) Items related to the stove: %d\n", stoveItems);

    // Compare and suggest based on consumption percentage
    float grillPercentage = (totalItems > 0) ? (grillItems / (float)totalItems) * 100 : 0;
    float stovePercentage = (totalItems > 0) ? (stoveItems / (float)totalItems) * 100 : 0;

    if (stovePercentage > 25 && grillPercentage <= 25) {
        printf("(c-1) Remove stove products\n");
    } else if (grillPercentage > 25 && stovePercentage <= 25) {
        printf("(c-2) Remove grill products\n");
    } else if (stovePercentage > 25 && grillPercentage > 25) {
        printf("(c-3) Maintain both types of products\n");
    }
}
