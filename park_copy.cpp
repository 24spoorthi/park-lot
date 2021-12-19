/*
The following code implements car parking slot assignment in "Useless Mall".
*/
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

#define MAX_CAR 20          //Maximun number of available parking slot for Cars
#define MAX_TWO_WHEEL 20    //Maximun number of available parking slot for Two-wheelers
#define MAX_TRUCK 20        //Maximun number of available parking slot for Trucks

int num_cars = 0;   //Variable to keep the track of number of Cars in the parking lot
int num_two = 0;    //Variable to keep the track of number of Two-wheelrs in the parking lot
int num_truck = 0;  //Variable to keep the track of number of Trucks in the parking lot

//The following class holds infomation about a vehicle entering the parking lot
class vehicle_info{

    private:
        string vehicle_num;         //String variable to hold vehicle number
        int entry_time, exit_time;  //integer variable to hold entry and exit times respectively
        char vehicle_type;          //character variable to hold the vehicle type - 'C' for car, 'T' for Two-wheeler and 't' for truck
        int park_alloted;           //integer variable to hold the parking alloted
    public:
        //Member funtions:
        string get_vehicle_num();           // member funtion to return vehicle number
        int get_entry_time();               // member funtion to return entry time
        int get_exit_time();                // member funtion to return exit time
        char get_veh_type();                // member funtion to return vehicle type
        int get_park_allot();               // member funtion to return parking number alloted
        void set_park_allot(int);           // member funtion to set the parking number
        void set_exit_time(int);            // member funtion to set the exit time
        vehicle_info(){}                    //Default Constructor
        vehicle_info(char[15],int,char);    //Parameterised Constructor to intialize the vehicle num, entry time, exit time and vehicle type at the time of the entry of the vehicle in the parking lot
        ~vehicle_info();                    //Destructor

        /* 
        Member function to print the details about a vehicle pointed by the vehicle_info* pointer.
        Paramter: A pointer to an instance of the class
        Return : void
        */
        void print_info(vehicle_info* );    

        /* 
        Member function to print the amount to be paid by a vehicle at the time of exit from the parking lot.
        Paramter: A pointer to an instance of the class
        Return : void
        */
        void print_park_rate(vehicle_info* );

        vehicle_info* next; //Pointer to next vehicle the arrived in the parking lot.
};

/*
pointer of the instance vehicle_info that points to the first vehicle entering the parking lot. If the first vehicle leaves the parking lot,
then head will point to the very next vehicle that arrived in the parking lot and hasn't left.

The vehicles entring the parking lot is implemented in a queue fashion to get the slots assigned.
A list of vehicles of the vehicles present in the parking lot is maintained based on their entry. 
The vehicle that enters the parking lot first will be recorded first in the list.
*/
vehicle_info *head; 

//The following class holds the information about a particular parking slot.
typedef class park_slot_availability{
    public:
        char park_type;                     //Character variable indicating the type of vehicle that can be parked in the slot
        int park_num;                       //integer variable indicating the number of the parking slot
        int park_avail;                     //integer variable indicating whether this slot is empty or filled (1 indicating available to be accomodated else 0)
        park_slot_availability* next_slot;  //pointer to next parking slot 

        /* 
        Member function to update the parking lot inforamtion upon the entry of a vehicle.
        Paramter: A pointer to an instance of the class indicating a particular vehicle
        Return : void
        */
        void update_entry_slot(vehicle_info* );
        /* 
        Member function to update the parking lot inforamtion upon the exit of a vehicle.
        Return : void
        */
        void update_exit_slot();

}park_slot_avail;

/*
The parking lot is assumed to accomodate three types of vehicles - Car, Two-wheelers and trucks.
Each of these vehicles can be assigned to respective type of parking slot. For example, A car cannot be parked in a slot the is meant for trucks.

To impement this, three different priority queues and created - separately for car, truck and two-wheeler, wherein, 
lesser the number of the parking slot, higher is its priority to get assigned to a vehicle of its type.
*/

park_slot_avail *car_head;      //pointer of the instance "park_slot_availability" class that points to the first parking slot meant to accomodate car.
park_slot_avail *two_head;      //pointer of the instance "park_slot_availability" class that points to the first parking slot meant to accomodate two-wheeler.
park_slot_avail *truck_head;    //pointer of the instance "park_slot_availability" class that points to the first parking slot meant to accomodate truck.

/*
Function to print the information about the parking lot - 
Number of vehicles of each type present, total capacity of each type of vehicle and number of empty slot.
Return - void
*/
void parking_lot_info();

/*
Function to input the vehicle number from the user and call print_info(vehicle_info* ) to display the information about a particular vehicle.
Input : Vehicle number of type string.
Return - void
*/
void vehicle_information();

/*
Function to add a new vehicle at the end of the list of vehicles present in the parking lot.
Parameter : pointer of the type vehicle_info that has to be added to the list.
Return - void
*/
void new_vehicle(vehicle_info*);

/*
Function to delete a vehicle's entry from the list of vehicles present in the parking lot.
Return - void
*/
void del_vehicle(vehicle_info*);

/*
Function to intialize the details of a parking slot - type of the parking, parking number and it's availability is set to 1 at the time of initialisation.
Parameter : interger indicating the number that has to be assigned to the parking slot.
Return - a pointer of the type park_slot_avail that points to a new parking slot with number assigned to it.
*/
park_slot_avail* new_slot(int);

/*
Function to intialize the parking slots priority queue for a particular type of vehicle
Parameter : character indicating the type of priority queue that has to be initialized.
Return - pointer of the type park_slot_avail pointing the first slot in the parking slot priority queue of a particular vehicle type
*/
park_slot_avail* init_park_slots(char);

/*
Function to return the number of empty slots present in the parking lot for a particular type of vehicle
Parameter - character indicating the type of vehicle 
Return : interger indicating the number of empty slots in the parking lot based on the type of vehicle
*/
int avail_count(char);

/*
Function to assign a parking slot to a vehicle indicated by vehicle_info* if there are any else print necessary message.
Parameters :
    1. pointer of the type park_slot_avail indicating the first parking slot of a particular vehicle
    2. pointer of the type vehicle_info indicating the vehicle that just arrived at the mall's parking lot.
Return - void
*/
void park_number(park_slot_avail* ,vehicle_info* );

/*
Utility funtion to perform necessary operations upon the entry of a vehicle
Return - void
*/
void vehicle_entry();

/*
Function to upddate the availability of a parking spot to 1 (i.e. can be occupied further) when a vehicle leaves the parking lot.
Parameter :
    1. integer indicating the vehicle at what spot is leaving the parking spot.
    2. pointer of the type park_slot_avail pointing to the start of the parking queue of particular type.
Return - void
*/
void change_avail(int , park_slot_avail* );

/*
Fuction to call change_avail(int , park_slot_avail*) and release spot for futher accomodation based on the parameter.
Parameter : 
    1. character indicating the type of vehicle
    2. interger indicating the parking number alloted
Return - void
*/
void free_slot(char , int );

/*
Utility funtion to perform necessary operations upon the exit of a vehicle
Return - void
*/
void vehicle_exit();

/*
Utility funtion to print the details of all the vehicles, in ascending order of their arrival, in the parking lot.
Return - void
*/
void print_all_vehicles();

//Function definitions:

/*
Parameterised constructor of the class vehicle_info to intialise class members
*/
vehicle_info :: vehicle_info(char num[15], int ent_time, char type){
    vehicle_num = num;
    entry_time = ent_time;
    vehicle_type = type;
    exit_time = 0;
}

string inline vehicle_info:: get_vehicle_num(){
    return vehicle_num;
}
int inline vehicle_info :: get_entry_time(){
    return entry_time;
}
int inline vehicle_info :: get_exit_time(){
    return exit_time;
}
char inline vehicle_info :: get_veh_type(){
    return vehicle_type;
}
int inline vehicle_info :: get_park_allot(){
    return park_alloted;
}
void inline vehicle_info :: set_park_allot(int num){
    park_alloted = num;
}
void inline vehicle_info :: set_exit_time(int time){
    exit_time = time;
}

void vehicle_info :: print_info(vehicle_info* ptr){
    cout<<"=====================================";
    cout<<"\nVehicle number:\t"<<ptr->vehicle_num;
    cout<<"\nVehicle entry time:\t"<<ptr->entry_time;
    cout<<"\nVehilce type:\t"<<ptr->vehicle_type;
    cout<<"\nVehicle is at:\t"<<ptr->vehicle_type<<ptr->park_alloted;
    cout<<"\n=====================================";
}

void vehicle_info :: print_park_rate(vehicle_info* ptr){
    int time,ex_time;
    cout<<"\nEnter exit time:";
    cin>>ex_time;
    ptr->set_exit_time(ex_time);
    time = ptr->get_exit_time() - ptr->get_entry_time();
    cout<<"\nYou have to pay: ";
    if(time < 2)
        cout<<"50 INR"<<endl;
    else if(time >= 2 && time < 5)
        cout<<"70 INR"<<endl;
    else if(time >= 5 && time < 10)
        cout<<"100 INR"<<endl;
    else if(time >= 10 && time < 15)
        cout<<"120 INR"<<endl;
    else    
        cout<<"200 INR"<<endl;
}

void park_slot_avail :: update_entry_slot(vehicle_info* v){
    int avail = avail_count(v->get_veh_type());
    if(avail > 0){
        if((v->get_veh_type()) == 'C'){
            num_cars++;
            park_number(car_head,v);
        }
        else if((v->get_veh_type()) == 'T'){
            num_two++;
            park_number(two_head,v);
        }
        else{
            num_truck++;
            park_number(truck_head,v);
        }
        cout<<"\nPark the vehicle in:"<<(v->get_veh_type())<<"-"<<(v->get_park_allot());
    }
}

void park_slot_avail :: update_exit_slot(){
    vehicle_info* ptr = head;
    char veh_num[15];    
    cin.ignore();
    cout<<"Enter vehicle number:";
    cin.getline(veh_num,15);
    while(ptr != NULL){
        if(ptr->get_vehicle_num() == veh_num)
        {
            ptr->print_park_rate(ptr);
            free_slot(ptr->get_veh_type(),ptr->get_park_allot());
            del_vehicle(ptr);
            return;
        }
        ptr = ptr->next;
    }
}

void parking_lot_info(){
    cout<<"=========PARKING LOT INFORMATION=========";
    cout<<"\nTotal number of vehicles in the parking lot are:\t"<<(num_cars + num_truck + num_two);
    cout<<"\nTotal number of cars:\t"<<num_cars;
    cout<<"\nTotal number of two_wheelers:\t"<<num_two;
    cout<<"\nTotal number of trucks:\t"<<num_truck;
    cout<<"\nNumber of car slots left:\t"<<(MAX_CAR - num_cars);
    cout<<"\nNumber of two wheeler slots left:\t"<<(MAX_TWO_WHEEL - num_two);
    cout<<"\nNumber of truck slots left:\t"<<(MAX_TRUCK - num_truck);
}

void vehicle_information(){
    if(head == NULL)
    {
        cout<<"\nThere are no vehicles in the parking lot";
        return;
    }
    cout<<"Enter the vehicle number";
    string veh_num;
    cin>>veh_num;
    vehicle_info* ptr = head;
    while(ptr != NULL)
    {
        if(ptr->get_vehicle_num() == veh_num)
        {    
            ptr->print_info(ptr);
            return;
        }
        ptr=ptr->next;
    }
    cout<<"Vehicle not in the parking lot\n";
}

park_slot_avail* new_slot(int numb,char type){
    park_slot_avail* nptr = new park_slot_avail();
    nptr->park_type = type;
    nptr->park_num = numb;
    nptr->park_avail = 1;
    nptr->next_slot = NULL;
    return nptr;
}

park_slot_avail* init_park_slots(char type)
{
    park_slot_avail* temp = new_slot(1,type);
    park_slot_avail* first = temp;
    park_slot_avail* ptr;
    for(int i = 2 ; i <= 20 ; i++){
        ptr = new_slot(i,type);
        temp->next_slot = ptr;
        temp = ptr;
    }
    return first;
}

int avail_count(char type){
    if(type == 'C')
        return (int)MAX_CAR - num_cars;
    else if(type == 'T')
        return (int)MAX_TWO_WHEEL - num_two;
    return (int)MAX_TRUCK - num_truck;
}

void print_all_vehicles()
{
    if(head == NULL)
    {
        cout<<"\nThere are no vehicles in the parking lot";
        return;
    }
    vehicle_info* ptr = head;
    while(ptr!=NULL)
    {
        ptr->print_info(ptr);
        ptr = ptr->next;
    }
}

void new_vehicle(vehicle_info* ptr){
    if(head == NULL)
    {
        head = ptr;
        head->next = NULL;
    }
    vehicle_info* tptr = head;
    while( tptr->next!= NULL)
        tptr = tptr->next;
    tptr->next = ptr;
    ptr->next = NULL;
}

void park_number(park_slot_avail* start,vehicle_info* v){
    while(start != NULL)
    {
        if(start->park_avail == 1)
        {
            start->park_avail = 0;
            v->set_park_allot(start->park_num);
            return;
        }
        start = start->next_slot;
    }
    cout<<"\nNo more parking slots available";
}

void vehicle_entry(){
    char num[15];
    int ent_time;
    char type ;
    cin.ignore();
    cout<<"Enter the vehicle number: ";
    cin.getline(num,15);
    cout<<"Enter vehicle type (C-Car, T-Two_wheeler, t - Truck):";
    type = getchar();
    cout<<"Enter entry time:";
    cin>>ent_time;    
    vehicle_info* v = new vehicle_info(num,ent_time,type);
    park_slot_avail* p = new park_slot_avail();
    p->update_entry_slot(v);
    new_vehicle(v);
}

void del_vehicle(vehicle_info* dptr){
    if(dptr == head)
        head = head->next;
    vehicle_info* bptr = head;
    while(bptr->next != dptr)
        bptr = bptr->next;
    bptr->next = dptr->next;
}

void change_avail(int num, park_slot_avail* start)
{
    park_slot_avail* ptr = start;
    for(int i = 1 ; i <= 20 ; i++)
    {
        if(num == i)
            break;
        else
            ptr = ptr->next_slot;
    }
    ptr->park_avail = 1;
}

void free_slot(char type, int i){
    if(type == 'C'){
        num_cars--;
        change_avail(i,car_head);
    }
    else if(type == 'T'){
        num_two--;
        change_avail(i,two_head);
    }
    else{
        num_truck--;
        change_avail(i,truck_head);
    }
}

void print_park(park_slot_avail* s){
    park_slot_avail* t = s;
    while(t != NULL)
    {
        cout<<t->park_avail<<" "<<t->park_num<<" "<<t->park_type;
        t = t->next_slot;
    }
}

void vehicle_exit(){
    if(head == NULL)
    {
        cout<<"\nNo Vehicles to exit";
        return;
    }
    park_slot_avail* v = new park_slot_avail();
    v->update_exit_slot();
}

//Driver Code

void print_wel_mess(){
    cout<<"\n========Welcome to Useless Mall=========\n";
    cout<<"Weekend ho gaya toh muh uthake aa gye xD\n\n";
    cout<<"Enter:\n1 for entry of vehicle\n2 for exit\n3 to get info about all the vehicles in the parking lot\n4 to get information about a particular vehicle\n5 for parking_lot_info";
}

int main(int argc, char const *argv[])
{
    int choice;

    head = NULL;
    car_head = init_park_slots('C');
    two_head = init_park_slots('T');
    truck_head = init_park_slots('t');

    print_wel_mess();

    while(1){
        cout<<"\nEnter choice:\t";
        cin>>choice;
        switch (choice)
        {
            case 1:
                vehicle_entry();
                break;
            case 2:
                vehicle_exit();
                break;
            case 3:
                print_all_vehicles();
                break;
            case 4:
                vehicle_information();
                break;          
            case 5:
                parking_lot_info();
                break; 
            default:
                exit(0);
        }
    }
    return 0;
}