# Point of Sale (POS) System for a Fast-Food Chain

## Overview
A Point of Sale (POS) system is a vital component for merchants, enabling them to conduct in-person sales efficiently. It encompasses a set of devices, software, and payment services that manage customer purchases, accept payments, provide receipts, and aid in inventory tracking. Initially starting with a centralized cash machine, modern POS systems have evolved to incorporate tablets and smartphones for order placement and payment.

## Task 1: Tablet and Smartphone Ordering

### Program Overview
The program for Task 1 aims to implement a part of the POS system allowing customers to use tablets or smartphones for placing orders and making payments. The implementation utilizes a state machine for better control and planning.

### Program Features
1. Requests the number of customers attending the event.
2. Prompts customers to place orders for multiple items until a designated "ending" command is provided (e.g., check-out).
3. Custom acronyms are used for each item for streamlined ordering.

### Menu
| Item                        | Price |
|-----------------------------|-------|
| Beef burger                 | £8.5  |
| Grilled beef steak          | £9    |
| Sous vide chicken breast    | £7    |
| Grilled chicken             | £7    |
| Grilled lamb Kofta          | £5.5  |
| Minced lamb                 | £8.5  |
| Teriyaki salmon (grilled)   | £9.5  |
| Honey garlic salmon         | £9.5  |
| Shrimp stew                 | £8    |
| Grilled garlic shrimp       | £10   |
| Vegan BBQ complex           | £7    |
| Fry seasonal veg (Vegan)    | £6    |
| Halloumi                    | £7    |
| Pesto pasta                 | £2    |
| Lard fried potato           | £5    |
| Vegan pasta salad           | £2    |
| Sweet potato fries (Vegan)  | £5    |
| Rice                        | £1    |

3. Displays a summary of the purchase and the total price once the customer places the "ending" command.

## Task 2: Centralized Order Recording

### Program Overview
Task 2 extends the code from Task 1 by incorporating File I/O functions to centrally record all customer orders. The report generated is formatted for readability.

### Program Features
1. The program can record orders from multiple customers.
2. Orders are saved in a readable format, providing insights into each customer's spending.

## Task 3: Central Office Analysis

### Program Overview
Task 3 focuses on enabling the central office to act based on the collected customer order records. Various criteria are examined, and results are generated for decision-making.

### Program Features
1. Generates five customer orders using the code from Task 2.
2. Utilizes string handling functions for efficient coding.
3. Examines and presents the following results:
   - (a) Average money spent per person.
   - (b) Percentage of vegan dishes in total orders.
   - (c) Identifies items related to the grill and stove, suggesting actions based on consumption percentages.

### Analysis Results
(a) **Average money spent per person:** Displays the average amount spent by each customer.

(b) **Percentage of vegan dishes in total orders:** Calculates and displays the percentage of vegan dishes in all orders.

(c) **Kitchen Ware Analysis:** Identifies items related to the grill and stove. Suggests actions based on consumption percentages:
   - (c-1) Remove stove products if consumed by more than 25%.
   - (c-2) Remove grill products if consumed by more than 25%.
   - (c-3) Maintain both if both types are consumed by more than 25% of customers.

**Note:** The results are generated based on the orders recorded centrally in Task 2.

## Running the Code
Compile the code files using:
```bash
gcc -o pos_system task_1.c task_2.c task_3.c
```
Run the executable:
```bash
./pos_system
```
Ensure the tasks are executed sequentially to get accurate and meaningful results.
