#ifndef MYHEADER_H
#define MYHEADER_H
#include <stdbool.h>
#define MAX_SEATS 50
#include <stdlib.h>
struct payment
{
    int amount;
    char method[20];
    bool is_paid;
    int balance;
};
struct booking
{
    char name[50];
    int seat_number;
    struct payment payment; 
};
struct passenger 
{
    char name[50];
    int age;
    char gender[10];
    char seat_type[20];
    char meal_preference[20];
    char location[20];
    char destinated_location[20];
    int luggage_weight;
    int distance;
};
struct seat 
{
    int number;
    bool is_booked;
    struct passenger* passenger;
    struct payment payment; 
};
struct bus 
{
    char name[50];
    int seats_count;
    int num_booked_seats;
    struct seat seats[MAX_SEATS];
};
void displaying_seats(const struct bus* bus);
void book_ticket(struct bus* bus);
void cancel_ticket(struct bus* bus);
void view_available_seats(const struct bus* bus);
void view_booked_seats(const struct bus* bus);
void view_all_seats(const struct bus* bus);
void view_all_bookings(const struct bus* bus);
void view_all_cancellations(const struct bus* bus);
void sort_bookings_by_seat(struct bus* bus);
int search_booking_by_name(const struct bus* bus, const char* name);
void save_booking(const struct booking* booking);
void save_passenger(const struct passenger* passenger);
void load_bus_data(struct bus* bus);
void save_bus_data(const struct bus* bus);
int main() 
{
	int i;
	printf("\t\t|                  RED BUS                    |\n");
    printf("\t\t|           - The safest journey              |\n");
    printf("\t\t|                 to travel                   |\n");
    printf("\t\t---------------------------------------------- \n");
    printf("\t\t--------------------------------- -------------\n");
    struct bus my_bus={"My bus",MAX_SEATS,0};
    for(i=0;i<MAX_SEATS;i++) 
	{
        my_bus.seats[i].number=i+1;
        my_bus.seats[i].is_booked=false;
        my_bus.seats[i].passenger=NULL;
    }
    int choice;
    do {
        printf("\nWelcome to Red bus\n",my_bus.name);
        printf("1. Display seats\n");
        printf("2. Book a ticket\n");
        printf("3. Cancel a ticket\n");
        printf("4. View available seats\n");
        printf("5. View booked seats\n");
        printf("6. View all seats\n");
        printf("7. View all bookings\n");
        printf("8. View all cancellations\n");
        printf("9. Sort bookings by seat number\n");
        printf("10. Search booking by name\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
		{
            case 1:
                displaying_seats(&my_bus);
                break;
            case 2:
                book_ticket(&my_bus);
                break;
            case 3:
                cancel_ticket(&my_bus);
                break;
            case 4:
                view_available_seats(&my_bus);
                break;
            case 5:
                view_booked_seats(&my_bus);
                break;
            case 6:
                view_all_seats(&my_bus);
                break;
            case 7:
                view_all_bookings(&my_bus);
                break;
            case 8:
                view_all_cancellations(&my_bus);
                break;
            case 9:
                sort_bookings_by_seat(&my_bus);
                printf("Bookings sorted by seat number.\n");
                break;
            case 10: 
			{
                char search_name[50];
                printf("Enter name to search: ");
                scanf("%s",search_name);
                int index=search_booking_by_name(&my_bus,search_name);
                if(index!=-1) 
				{
                    printf("\n Booking found!");
                    printf("\n Name:%s",my_bus.seats[index].passenger->name);
                    printf("\n Seat Number: %d",my_bus.seats[index].number);
                }
				else 
				{
                    printf("Booking not found for the given name.\n");
                }
                break;
            }
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 11);
    return 0;
}
#endif
