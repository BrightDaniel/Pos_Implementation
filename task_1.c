task 1 complete:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_NAME_LENGTH 30
#define MAX_CUSTOMERS 10

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

        total += customerTotal;
    }

    // Display the total summary
    printf("\nTotal amount spent by all customers: £%.2f\n", total);
}
