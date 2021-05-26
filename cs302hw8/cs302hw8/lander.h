/*
* Name: Cicelia Siu, 5005247749, Assignment 8
* Description: lander.h for Assignment  ; 
* 	gives function declaration and implementation for lander class
* Input: N/A
* Output: N/A
*/

#include <string>
#include <cstdlib>
#include <iostream>
//#include "priorityQ.h"
using namespace std;

class lander
{
public:
    lander(double = 0, double = 0, double = 0, double = 0, double = 0, int = 0);
    double get_velocity() const;
    double get_altitude() const;
    double get_fuel_amount() const;
    int get_id() const;
    double get_mass() const;
    char get_status() const;
    bool change_flow_rate(double);
    void simulate();
    bool operator<(const lander&) const;

private:
    double flow_rate;
    double velocity;
    double altitude;
    double fuel_amount;
    bool stillLanding;
    int id;
    int timesSimulated;
    double LANDER_MASS;
    double MAX_FUEL_CONSUMPTION_RATE;
    double MAX_THRUST;
};

/*
* lander(double mass, double max_thrust, double max_fuel, double alt,double fuel, int id): constructor for a new lander
* parameters: mass, max_thrust, max_fuel, alt fuel - double for their respective variables
*            id - int for the lander's id
* return value: N/A
*/
lander::lander(double mass, double max_thrust, double max_fuel, double alt,double fuel, int id)
{
    LANDER_MASS = mass;
    MAX_THRUST = max_thrust;
    MAX_FUEL_CONSUMPTION_RATE = max_fuel;
    altitude = alt;
    stillLanding = true; 
    fuel_amount = fuel;
    this->id = id;
    flow_rate = 0;
    velocity = 0;
    timesSimulated = 0;
}

/*
* get_velocity():  returns the velocity field
* parameters: N/A
* return value: double
*/
double lander::get_velocity() const
{
    return velocity;
}

/*
* get_altitude():  returns the altitude field
* parameters: N/A
* return value: double
*/
double lander::get_altitude() const
{
    return altitude;
}

/*
* get_fuel amount():  returns the fuel amount field
* parameters: N/A
* return value: double
*/
double lander::get_fuel_amount() const
{
    return fuel_amount;
}

/*
* get_id():  returns the id field
* parameters: N/A
* return value: int
*/
int lander::get_id() const
{
    return id;
}

/*
* get_mass():  returns the mass field
* parameters: N/A
* return value: double
*/
double lander::get_mass() const
{
    return LANDER_MASS;
}

/*
* get_staus():  returns ’a’ if still airborne, returns ’c’ if not airborn and the
* velocity is less than or equal to -2 (lander crashed), and returns ’l’ if not airborne and velocity is greaterthan -2 (lander has landed)
* parameters: N/A
* return value: char - a, l, or c
*/
char lander::get_status() const
{
    if (stillLanding)
    {
        return 'a';   
    }
    else if (velocity < -2)  //and not airborne
    {
        return 'c';
    }
    else
    {   
        return 'l';
    }
}


/*
* change_flow_rate(double r):  if r is between 0 and 1 (inclusive), then set flow rate
* with r if fuel amount is larger than 0 and the returntrue, return
* falseif r is not between 0 and 1(inclusive) and do not set flowrate
* parameters: r - double from the sim file
* return value: true or false
*/
bool lander::change_flow_rate(double r)
{
    if ((r>=0) && (r<=1))
    { 
        if (r>=0)
            flow_rate = r;
            //cout << flow_rate << " flow rate " << endl;
        return true;
    }
    else
    {
        return false;
    }
}


/*
* simulate():  calculates invstantious velocity, updates the velocity, altitude, fuel amount, and times stimulated
* parameters: N/A
* return value: N/A
*/
void lander::simulate()
{
    const double TIME = 1.0;
    // calculate instantaneous velocity
    double v, vn, an;
    // cout <<flow_rate<< "*" << MAX_THRUST << " / " << LANDER_MASS << " + "<< fuel_amount  << endl;
    v = flow_rate*MAX_THRUST;
    vn = LANDER_MASS+fuel_amount;
    // cout << v  << " v / vn " << vn << endl;
    v = v/vn;
    v = TIME*v;
    v = v - 1.62;
    //cout << "v : " << v << endl;
    // increment/update velocity field by v
    velocity += v;
    // increment/update altitude field by TIME×velocity field
    an = TIME*velocity;
    altitude = altitude + an;
    //cout << "alt : " << altitude << endl;
    // update stillLanding field if necessary
    if (altitude <= 0)
        stillLanding = false;
    // decrement/update fuelamount by TIME×MAXFUELRATE× |v|
    if (flow_rate > 0)
    {
        double decBy = abs(v);
        decBy = decBy * MAX_FUEL_CONSUMPTION_RATE;
        decBy = decBy * TIME;
        fuel_amount = fuel_amount - decBy;
    }
    //cout << "fuel: " << fuel_amount << endl;
    // set fuelamount to 0 if the amount in the above step results to negative for fuelamount
    if (fuel_amount < 0)
        fuel_amount = 0;
   // increment/update timesSimulated by 1
   timesSimulated++;
//    cout << "After: fuel: " << fuel_amount << " stim: " << timesSimulated;
//    cout << "  altitude: " << altitude << " velocity : " << velocity << endl;
   
}


/*
* operator<(const lander& rhs): compare the priority of two lander objects (the* this object and the rhs object).
* parameters: rhs - the lander class being compared to the left
* return value: If left has hightest priority, then return true. If right, or the same then returns false
*/
bool lander::operator<(const lander& rhs) const
{
    
    //DEBUG: cout <<  "op < " << endl;
    
    if (timesSimulated != rhs.timesSimulated)
    {
        //cout << "\nsimulated: " << timesSimulated << " " << rhs.timesSimulated << endl;
        if(timesSimulated < rhs.timesSimulated)
            return true;
        //else
        return false;
    }
    else if (this->altitude != rhs.get_altitude())
    {
        //cout << "\nalt: " << altitude << " " << rhs.get_altitude() << endl;
        if(altitude < rhs.get_altitude())
            return true;
        //else 
        return false;
    }
    else if (fuel_amount != rhs.get_fuel_amount())
    {
        //cout << "\nfuel: " << fuel_amount<< " " << rhs.get_fuel_amount() << endl;
        if (fuel_amount < rhs.get_fuel_amount())
            return true;
        //else
        return false;
    }
    else if (LANDER_MASS != rhs.get_mass())
    {
        //cout << "\nmass: " << LANDER_MASS << " " << rhs.get_mass() << endl;
        if (LANDER_MASS > rhs.get_mass())
            return true;
        //else
        return false;
    }
    else if (id != rhs.get_id())
    {
        //cout << "\nid: " << id << " " << rhs.get_id() << endl;
        if (id < rhs.get_id())
            return true;
        //else
        return false;
    }
    else
    {
        //cout << "same obj " << endl;
        return false;
    }
    
}