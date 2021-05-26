/*
* Name: Cicelia Siu, 5005247749, Assignment 8
* Description: main.cpp 
* Input: the landerInput.txt file to get the current lander's information.
        the sim##.txt file to get their simulations
* Output: What happens after each simulation change. if the file ends, then it outputs all still in air.
*/

#include "lander.h"
#include "priorityQ.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    // file 
    string inputStr;
    ifstream infile;
    // open lander input file
	cout << endl << "Lander Input File: ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Lander Input File: ";
		cin >> inputStr;
		infile.open (inputStr);
	}

    // get lander input information
    priorityQ <lander> landerQ;
    double mass, max_thrust, max_fuel, alt, fuel, id;
    
    while (infile >> mass)
    {
        infile >> max_thrust;
        infile >> max_fuel;
        infile >> alt;
        infile >> fuel;
        infile >> id;
        landerQ.insert(lander(mass, max_thrust, max_fuel, alt, fuel, id));
        //DEBUG::
        lander tmp = landerQ.getHighestPriority();
    }
    //close lander input file
    infile.close();

    // open simulation file
	cout << endl << "Simulation File: ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Simulation File: ";
		cin >> inputStr;
		infile.open (inputStr);
	}
    
    //get info from sim.txt file
    string changeFlowS;
    double changeFlowD;
        // if infile >> still works (aka not the eof), then keep going, else go to next
    while (infile >> changeFlowS)
    {
        //cout << "DEBUG:: sim string input: "<< changeFlowS << endl;
        if (isdigit(changeFlowS[0]))
        {
            changeFlowD = stod(changeFlowS);
            //cout << "DEBUG:: sim double input: "<< changeFlowD << endl << endl;
            if (changeFlowD >=0)    
            {
                if (changeFlowD <= 1) // changeFlowD is from simFile
                {
                    //output rocket infor
                    lander tmpLander;
                    tmpLander = landerQ.getHighestPriority();
                    landerQ.deleteHighestPriority();
                    cout << "Rocket " << tmpLander.get_id() << endl;
                    cout << "Fuel: " << tmpLander.get_fuel_amount() << endl;
                    cout << "Altitude: " << tmpLander.get_altitude() << endl;
                    cout << "Velocity: " << tmpLander.get_velocity() << endl;
                    cout << endl;
                    
                    //change
                    tmpLander.change_flow_rate(changeFlowD);
                    tmpLander.simulate();
                    if (tmpLander.get_status() == 'l')
                    {
                        cout << "Rocket ID: " << tmpLander.get_id() << " has successfully landed and all astronauts are accounted for :)" << endl;
                        // landerQ.deleteHighestPriority();
                    }
                    else if (tmpLander.get_status() == 'c')
                    {
                        cout << "Rocket ID: " << tmpLander.get_id() << " has crashed :( At least nobody was on board" << endl;
                        // landerQ.deleteHighestPriority();
                    }
                    
                    else 
                    {
                        //cout << "Airborne" << tmpLander.get_status() << endl;
                        // landerQ.deleteHighestPriority();   
                        landerQ.insert(tmpLander);
                        
                    }

                    if (landerQ.isEmpty())
                    {
                        cout << "All are on the ground somewhere." << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "There are landers still trying to land..." << endl;
    while (!landerQ.isEmpty())
    {
        lander tmpLander;
        tmpLander = landerQ.getHighestPriority();
        landerQ.deleteHighestPriority();
        cout << "Lander ID : " << tmpLander.get_id() << " Altitude: " << tmpLander.get_altitude() << " mission aborted." << endl;
    }

    // close simulation file
    infile.close();
    return 0;
}