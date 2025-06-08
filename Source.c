#include <stdio.h>
#include "myheader.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SEATS 50
void displaying_seats(const struct bus* bus) 
{
    printf("Displaying seats:\n");
    printf("  ______\n");
    printf(" /                         |                          \\\n");

    int seat_counter = 1,row,seat;
    for(row=0;row<bus->seats_count/4;row++) 
	{
        printf(" |");
        for(seat=0;seat<2;seat++) 
		{
            if(seat_counter<=bus->seats_count) 
			{
                if(!bus->seats[seat_counter-1].is_booked) 
				{
                    printf("   %02d   |",seat_counter);
                } 
				else 
				{
                    printf(" [ X ]  |");
                }
                seat_counter++;
            }
        }
        printf("       |");
        for(seat=0;seat<3;seat++) 
		{
            if(seat_counter<=bus->seats_count) 
			{
                if(!bus->seats[seat_counter - 1].is_booked) 
				{
                    printf("   %02d   |",seat_counter);
                } 
				else 
				{
                    printf(" [ X ]  |");
                }
                seat_counter++;
            }
        }
        printf("\n");
    }
    printf(" \\____|____/\n");
}
void book_ticket(struct bus* bus) 
{
  int seat_number;
  int amount = 200.00;

  printf("Enter the seat number you want to book:");
  scanf("%d", &seat_number);

  if (seat_number < 1 || seat_number > bus->seats_count) 
  {
    printf("\n Invalid seat number! Please try again.");
    return;
  }

  struct seat* seat = &bus->seats[seat_number - 1];

  if (seat->is_booked) 
  {
    printf("\n Seat %d is already booked.", seat_number);
    return;
  }

  struct booking new_booking;

  printf("Enter passenger name: ");
  scanf("%s", new_booking.name);

  struct passenger new_passenger;
  strcpy(new_passenger.name, new_booking.name);

  printf("Enter passenger age: ");
  scanf("%d", &new_passenger.age);

  printf("Enter passenger gender: ");
  scanf("%s", new_passenger.gender);

  printf("Enter seat type: ");
  scanf("%s", new_passenger.seat_type);

  printf("Enter meal preference: ");
  scanf("%s", new_passenger.meal_preference);

  printf("Enter passenger location: ");
  scanf("%s", new_passenger.location);

  printf("Enter destination location: ");
  scanf("%s", new_passenger.destinated_location);

  printf("Enter luggage weight (in kg): ");
  scanf("%d", &new_passenger.luggage_weight);

  if (new_passenger.luggage_weight > 20) 
  {
    printf("\n Luggage weight exceeds the allowed limit. Seat cannot be booked.");
    return;
  }

  seat->is_booked = true;
  seat->passenger = (struct passenger*)malloc(sizeof(struct passenger));
  *seat->passenger = new_passenger;

  new_booking.payment.amount = seat->payment.amount;

  printf("Enter payment amount: ");
  scanf("%d", &new_booking.payment.amount);

  if (new_booking.payment.amount > amount) 
  {
    seat->payment.balance = new_booking.payment.amount - amount;
    printf("\n Balance amount: %d", seat->payment.balance);
  } 
  else 
  {
    printf("\n Please pay full amount to book your seat");
  }

  save_booking(&new_booking);
  save_passenger(&new_passenger);
  bus->num_booked_seats++;
  printf("\n Booking successful for seat %d.", seat_number);
}
void cancel_ticket(struct bus* bus) 
{
    int seat_number;
    printf("Enter the seat number you want to cancel: ");
    scanf("%d",&seat_number);
    if(seat_number<1||seat_number >bus->seats_count) 
	{
        printf("\n Invalid seat number! Please try again.");
        return;
    }
    struct seat* seat=&bus->seats[seat_number-1];
    if(seat->is_booked) 
	{
        free(seat->passenger);
        seat->is_booked=false;
        printf("\n Ticket for seat %d has been canceled.",seat_number);
        struct booking cancellation;
        cancellation.payment=seat->payment; 
        save_booking(&cancellation);
        bus->num_booked_seats--;
    } 
	else 
	{
        printf("\n Seat %d is not booked.",seat_number);
    }
}
void view_available_seats(const struct bus* bus) 
{
	int i;
    printf("\n Available seats in %s:",bus->name);
    printf("---------------------------\n");
    for(i=0;i<bus->seats_count;i++)
	 {
        if(!bus->seats[i].is_booked) 
		{
            printf("\n Seat No:%d",bus->seats[i].number);
        }
    }
    printf("---------------------------\n");
}
void view_booked_seats(const struct bus* bus)
{
	int i;
    printf("Booked seats in %s:\n",bus->name);
    printf("---------------------------\n");
    for(i=0;i<bus->seats_count;i++)
	 {
        if(bus->seats[i].is_booked) 
		{
            printf("\n Seat No: %d",bus->seats[i].number);
        }
    }
    printf("---------------------------\n");
}
void view_all_seats(const struct bus* bus) 
{
	int i;
    printf("All seats in %s:\n",bus->name);
    printf("---------------------------\n");
    for(i=0;i<bus->seats_count;i++) 
	{
        printf("\n Seat No:%d - %s",bus->seats[i].number,
               (bus->seats[i].is_booked ? "Booked" : "Available"));
    }
    printf("---------------------------\n");
}
void view_all_bookings(const struct bus* bus) 
{
	int i;
    printf("All bookings in %s:\n",bus->name);
    printf("---------------------------\n");
    for(i=0;i<bus->seats_count;i++)
	 {
        if(bus->seats[i].is_booked) 
		{
			printf("\n Booking for Seat No: %d",bus->seats[i].number);
            printf("\n Passenger Name: %s",bus->seats[i].passenger->name);
            printf("\n Age: %d",bus->seats[i].passenger->age);
            printf("\n Gender: %s",bus->seats[i].passenger->gender);
            printf("\n Seat Type: %s",bus->seats[i].passenger->seat_type);
            printf("\n Meal Preference: %s",bus->seats[i].passenger->meal_preference);
            printf("\n Location: %s",bus->seats[i].passenger->location);
            printf("\n Destinated Location: %s",bus->seats[i].passenger->destinated_location);
            printf("\n Luggage Weight: %d kg",bus->seats[i].passenger->luggage_weight);
            printf("\n Payment Amount: %d",bus->seats[i].payment.amount);
            printf("\n Payment Method: %s",bus->seats[i].payment.method);
            printf("---------------------------\n");
            //printf("\n Booking for Seat No: %d",bus->seats[i].number);
            //printf("\n Passenger Name: %s",bus->seats[i].passenger->name);
            //printf("\n Payment Amount: %d",bus->seats[i].payment.amount);
            //printf("\n Payment Method: %s",bus->seats[i].payment.method);
            //printf("---------------------------\n");
        }
    }
}
void view_all_cancellations(const struct bus* bus) 
{	
	int i;
    printf("All cancellations in %s:\n", bus->name);
    printf("---------------------------\n");
    for(i=0;i<bus->seats_count;i++) 
	{
        if(!bus->seats[i].is_booked) 
		{
            printf("\n Cancellation for Seat No: %d",bus->seats[i].number);
            printf("\n Refunded Amount: %d",bus->seats[i].payment.amount);
            printf("\n Payment Method: %s",bus->seats[i].payment.method);
            printf("---------------------------\n");
        }
    }
}
void sort_bookings_by_seat(struct bus* bus) 
{
	int i,j;
    for(i=0;i<bus->seats_count-1;i++) 
	{
        for(j=0;j<bus->seats_count-i-1;j++) 
		{
            if(bus->seats[j].is_booked && bus->seats[j + 1].is_booked &&
                bus->seats[j].number>bus->seats[j + 1].number)
				 {
                    struct seat temp=bus->seats[j];
                    bus->seats[j]=bus->seats[j + 1];
                    bus->seats[j + 1]=temp;
            }
        }
    }
}
int search_booking_by_name(const struct bus* bus, const char* name) 
{
	int i;
    for(i=0;i<bus->seats_count;i++)
	 {
        if(bus->seats[i].is_booked && strcmp(bus->seats[i].passenger->name,name)==0)
		 {
            return i;
        }
    }
    return -1;
}
void save_booking(const struct booking* booking)
{
    FILE* file=fopen("bookings.txt","a");
    if(file==NULL) 
	{
        printf("\n Error opening file for saving booking data.");
        return;
    }
    fprintf(file,"\n Seat:%d",booking->seat_number);
    fprintf(file,"\n Passenger Name:%s",booking->name);
    fprintf(file,"\n Payment Amount:%d",booking->payment.amount);
    fprintf(file,"\n Payment Method:%s",booking->payment.method);
    fclose(file);
}
void save_passenger(const struct passenger* passenger) 
{
    FILE* file=fopen("passengers.txt","a");
    if(file==NULL) 
	{
        printf("\n Error opening file for saving passenger data.");
        return;
    }
    fprintf(file,"\n %s %d %s %s %s %s %s %d",passenger->name,passenger->age,passenger->gender,passenger->seat_type,passenger->meal_preference,passenger->location,passenger->destinated_location,passenger->luggage_weight);
    fclose(file);
}
void load_bus_data(struct bus* bus) 
{
	int i;
    FILE* file=fopen("bus_data.txt","r");
    if(file==NULL) 
	{
        printf("\n Error opening file for loading bus data.");
        return;
    }
    fscanf(file,"%s %d %d",bus->name,&bus->seats_count,&bus->num_booked_seats);
    for(i=0;i<bus->seats_count;i++) 
	{
        struct seat* seat=&bus->seats[i];
        seat->number=i+1;
        fscanf(file,"%d %d %lf %s",&seat->is_booked,&seat->passenger,&seat->payment.amount,seat->payment.method);
        if(seat->is_booked) 
		{
            seat->passenger=malloc(sizeof(struct passenger));
            fscanf(file,"%s %d %s %s %s %s %s %d",seat->passenger->name,&seat->passenger->age,seat->passenger->gender,seat->passenger->seat_type,seat->passenger->meal_preference,seat->passenger->location,seat->passenger->destinated_location,&seat->passenger->luggage_weight);
        }
    }
    fclose(file);
}
void save_bus_data(const struct bus* bus)
{
	int i;
    FILE* file=fopen("bus_data.txt","w");
    if(file==NULL) 
	{
        printf("\n Error opening file for saving bus data.");
        return;
    }
    fprintf(file,"\n %s %d %d",bus->name,bus->seats_count,bus->num_booked_seats);
    for(i=0;i<bus->seats_count;i++) 
	{
        const struct seat* seat=&bus->seats[i];
        fprintf(file,"\n %d %d %lf %s",seat->number,seat->is_booked,seat->payment.amount,seat->payment.method);
        if(seat->is_booked) 
		{
            fprintf(file,"\n %s %d %s %s %s %s %s %d",seat->passenger->name,seat->passenger->age,seat->passenger->gender,seat->passenger->seat_type,seat->passenger->meal_preference,seat->passenger->location,seat->passenger->destinated_location,seat->passenger->luggage_weight);
        }
    }
    fclose(file);
}
