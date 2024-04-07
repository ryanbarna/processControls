#include <iostream>
#include <string>
#include <cmath>

using std::cout, std::cin, std::abs;

double setPoint;
double processMeasurement;

// Compute difference between the desired system state and the actual system state
double measureError( double setPoint, double processMeasurement )
{
     double error = setPoint - processMeasurement;
     return error;
}

// Compute PID controller response
double controllerOutput( double gain, double tauI, double tauD, double integratedError, double derivedError )
{
    double controllerOutput =+ gain * (((1/tauI) * integratedError) + (tauD * derivedError));
    return controllerOutput;
}

int main()
{
    // int randomNumberLimit = 200;
    // n = rand() % randomNumberLimit;

    // Take user input for setpoint
    cout << "Enter the desired process setpoint (i.e. 50.0)" << "\n";
    cin >> setPoint;
    
    // processMeasurement = rand() % randomNumberLimit;
    processMeasurement = 150.0;
    
    // Initialize time steps
    int i = 0;
    double dt = 1.5;

    // Initialize error terms
    double integratedError = 0.0;
    double derivedError = 0.0;

    while ( abs(setPoint - processMeasurement) > 0.1 )
    {
        double e = measureError( setPoint, processMeasurement );

        integratedError = e * dt;

        derivedError = e / dt;

        double co = controllerOutput( 1.0, 1.0, 0.5, integratedError, derivedError );
            
        processMeasurement = processMeasurement + co;
        i++;

        cout << e << "\n";
        cout << "Controller Response: " << co << "\n";
        cout << "Setpoint: " << setPoint << ", Process Measurement: " << processMeasurement << "\n";
        cout << "Iteration: " << i;
        cout << "\n";
    }

    cout << "Iterations " << i << "\n";

    return 0;
}