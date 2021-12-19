The code implements car parking slot assignment in "Useless Mall".
# Assumptions :
    -The parking lot has one level.
    -Three types of vehicles can be accomodated - Car, two-wheeler and truck.
    -Each type of vehicle can be assgined to a slot that is of the respective type.
    -There are 20 slots available for each type of vehicle.
    -The entry and exit time are to be entered in 24-hour format.
        -> If the entry/exit time of a vehicle is lesser than XX.30 enter it as XX.
                For example:
                If the entry/exit time of a vehicle 13.10 hours enter it as 13.
        -> If the entry/exit time a vehicle is greater than or equal to XX.30 enter it as XX+1.
                For example:
                If the entry/exit time of a vehicle 14.45 hours enter it as 15.

When a vehicle enters the parking lot of the mall, the code will print a valid parking spot (if any).
When a vehicle leaves the parking lot, the code prints the amount to be paid.

# Design:
    -Parking spots are assigned to vehicles based on their type from 1 to 20.
        -> Cars gets assigned from C-1 to C-20;
        -> Two-wheelers het assigned from T-1 to T-20;
        -> Trucks get assigned from t-1 to t-20.
    -In-case a parking spot with lower number is empty, vehicle gets assigned to it.
    -Vehicles can leave the parking lot at any desire time.
    -Parking rates are decided as follows:
        -> Lesser than 2 hours      -   50 INR
        -> Between 2 to 5 hours     -   70 INR
        -> Between 5 to 10 hours    -   100 INR
        -> Between 10 to 15 hours   -   120 INR
        -> Greater than 15 hours    -   200 INR

# Execute:
    To run the program, enter the following commands in the terminal under the same directory as of the "park_copy.cpp" file.

        $ g++ -o op park_copy.cpp       //to create an object file park_copy.o and linking it to output file op
        $ ./op
    
        OR 

        $ g++ park_copy.cpp
        $ ./a.out