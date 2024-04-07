#include <iostream>
#include <string>
#include <vector>

using std::cout, std::vector, std::cin;

float setPoint;
float processMeasurement;

// Compute difference between the desired system state and the actual system state
float measureError( float setPoint, float processMeasurement )
{
     float error = setPoint - processMeasurement;
     return error;
}

// Compute PID controller response
float controllerOutput( float gain, float tauI, float tauD, float integratedError, float derivedError )
{
    float controllerOutput =+ gain * (((1/tauI) * integratedError) + (tauD * derivedError));
    return controllerOutput;
}

int main()
{
    // int randomNumberLimit = 200;
    // n = rand() % randomNumberLimit;

    // Take user input for setpoint
    cin >> setPoint;
    
    // processMeasurement = rand() % randomNumberLimit;
    processMeasurement = 150.0;
    
    // Initialize time steps
    float i = 0.0;
    float sampleRate = 1.5;

    // Initialize error terms
    float integratedError = 0.0;
    float derivedError = 0.0;

    while ( processMeasurement != setPoint )
    {
        
        float e = measureError( setPoint, processMeasurement );
        int dt = sampleRate;

        integratedError = e * dt;

        derivedError = e / dt;

        float co = controllerOutput( 1.0, 1.0, 0.50, integratedError, derivedError );
            
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