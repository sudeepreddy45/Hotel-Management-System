#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 200

typedef struct {
    int roomNumber;
    char customerName[50];
    int isBooked;
    float price;
} Room;

Room hotel[MAX_ROOMS];
int totalRooms = 0;

void initializeRooms(int n) {
    totalRooms = n;
    for (int i = 0; i < totalRooms; i++) {
        hotel[i].roomNumber = i + 1;
        hotel[i].isBooked = 0;
        hotel[i].price = (rand() % 3000) + 1000; // Random price between 1000 and 4000
        strcpy(hotel[i].customerName, "");
    }
}

void bookRoom() {
    int roomNum;
    printf("Enter room number to book (1-%d): ", totalRooms);
    scanf("%d", &roomNum);

    if (roomNum < 1 || roomNum > totalRooms || hotel[roomNum - 1].isBooked) {
        printf("Room not available or already booked!\n");
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", hotel[roomNum - 1].customerName);
    hotel[roomNum - 1].isBooked = 1;
    printf("Room %d successfully booked for %s. Price: $%.2f\n", roomNum, hotel[roomNum - 1].customerName, hotel[roomNum - 1].price);
}

void checkoutRoom() {
    int roomNum;
    printf("Enter room number to check out (1-%d): ", totalRooms);
    scanf("%d", &roomNum);

    if (roomNum < 1 || roomNum > totalRooms || !hotel[roomNum - 1].isBooked) {
        printf("Invalid room number or room is not booked!\n");
        return;
    }

    hotel[roomNum - 1].isBooked = 0;
    printf("Room %d successfully checked out. Thank you, %s!\n", roomNum, hotel[roomNum - 1].customerName);
    strcpy(hotel[roomNum - 1].customerName, "");
}

void displayRooms() {
    printf("\nRoom Status:\n");
    printf("Room No\tStatus\tCustomer\tPrice ($)\n");
    for (int i = 0; i < totalRooms; i++) {
        printf("%d\t%s\t%s\t%.2f\n", hotel[i].roomNumber,
               hotel[i].isBooked ? "Booked" : "Available",
               hotel[i].isBooked ? hotel[i].customerName : "-",
               hotel[i].price);
    }
}

void totalEarnings() {
    float total = 0;
    for (int i = 0; i < totalRooms; i++) {
        if (hotel[i].isBooked) {
            total += hotel[i].price;
        }
    }
    printf("Total Earnings from booked rooms: $%.2f\n", total);
}

void findCheapestRoom() {
    int cheapestIndex = -1;
    for (int i = 0; i < totalRooms; i++) {
        if (!hotel[i].isBooked && (cheapestIndex == -1 || hotel[i].price < hotel[cheapestIndex].price)) {
            cheapestIndex = i;
        }
    }
    if (cheapestIndex != -1) {
        printf("Cheapest available room is %d with price: $%.2f\n", hotel[cheapestIndex].roomNumber, hotel[cheapestIndex].price);
    } else {
        printf("No available rooms!\n");
    }
}

int main() {
    int choice, n;
    printf("Enter number of rooms in the hotel: ");
    scanf("%d", &n);
    initializeRooms(n);

    while (1) {
        printf("\nHotel Management System\n");
        printf("1. Book a Room\n2. Check-out Room\n3. View Room Status\n4. View Total Earnings\n5. Find Cheapest Available Room\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookRoom(); break;
            case 2: checkoutRoom(); break;
            case 3: displayRooms(); break;
            case 4: totalEarnings(); break;
            case 5: findCheapestRoom(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
