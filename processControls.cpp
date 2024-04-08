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
double controllerOutput( double gain, double tauI, double tauD, double error, double integratedError, double derivedError )
{
    double controllerOutput = gain * (error + ((1/tauI) * integratedError) + (tauD * derivedError));
    return controllerOutput;
}

int main()
{
    // Take user input for setpoint
    cout << "Enter the desired process setpoint (i.e. 50.0):" << "\n";
    cin >> setPoint;
    
    processMeasurement = 150.0;
    
    // Initialize time steps
    int i = 0;
    double dt = 1.5;

    // Initialize error terms
    double integratedError = 0.0;
    double derivedError = 0.0;

    // Iteratively apply the control algorithm
    // Stop when system is within 0.1 units of the setpoint
    while ( abs(setPoint - processMeasurement) > 0.1 )
    {
        double e = measureError( setPoint, processMeasurement );

        // Integrate and derive the system error
        integratedError = e * dt;
        derivedError = e / dt;

        // Compute and apply controller response to the process measurement
        double co = controllerOutput( 1.0, 4.0, 0.1, e, integratedError, derivedError ); 
        processMeasurement = processMeasurement + co;
        i++;

        // Introduce external process changes
        if ( i >= 1 && i <= 8)
        {
            processMeasurement += 1;
        }

        // Print
        cout << "Controller Response: " << co << "\n";
        cout << "Setpoint: " << setPoint << ", Process Measurement: " << processMeasurement << "\n";
        cout << "Iteration: " << i;
        cout << "\n";
    }

    cout << "Total iterations " << i << "\n";

    return 0;
}