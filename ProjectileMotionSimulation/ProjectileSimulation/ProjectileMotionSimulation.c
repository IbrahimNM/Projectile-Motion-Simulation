#include <stdio.h>
#include "math.h"

#define GRAVITY 9.8
#define PI  3.141592654


void calculateAverageDisplacement(double, double, FILE*);
void driver_averageDisplacementWithError(double , double , FILE*);
double get_maximumError(double, double);
double AverageDisplacementWithError(double, double, double);
int main(){

	printf("\tThis is a projectile Simulation\n");
    
    // Declare essential varibles
    double initialVelocity = 100.00;
    double error = 0.00;
    double radias = 0.00;
    
    FILE *fp;
    FILE *fp2;
    
    // create a file
    fp = fopen("OriginalData.txt", "w");
    fp2 = fopen("ErrorData.txt", "w");
    
    // Write to a file
      fprintf(fp,"The following data is for initial velocity of %.2fms and Error of ±0.0%% \nTheta\tDisplacment\n",initialVelocity);
    fprintf(fp2,"The following data is for initial velocity of %.2fms and Error of ±%.2f%% \nTheta\tDisplacment\n",initialVelocity, error);
    
    
    // print calculated displacment IDEAL [1-89]
    calculateAverageDisplacement(initialVelocity, error, fp);
    driver_averageDisplacementWithError(initialVelocity, error, fp2);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // what If the target can be destroyed within 5 meters radias,                                   //
    // Q1: what is the maximum error rate the cannon can have to insure that the target is destroyed?//
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Use original data to pick a random position RANDOM
    // Call AverageDisplacementWithError() with verious error [1.00 -> 99.00]
    
    // Subtarct each with original, if different is more than 5.00 Report maximum error
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // what If the target can be destroyed within 5 meters radias,                                    //
    // Q2: what is the amount of error rate the cannon can have to insure that the target is destroyed//
    //     in the shortest time?                                                                      //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Use the same techneque from Question No. 1
    printf("Reported error rate that will destroy the target in a shortest time is %.2f", errorTemp);
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // what If the target can be destroyed within 5 meters radias,                                    //
    // Q3:                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    printf("\tDone.\n");
    // close file
    fclose(fp);
    fclose(fp2);
    return 0;
}
double get_maximumError(double inititialVelocity, double radias){
    // original displacement
    double displacement = (pow(initialVelocity, 2)/ GRAVITY)*sin(2* (45.00*(PI/180.0)));
    
    // Run through errors
    double maxError = 1.00;
    for(int i = 1; i <= 100; i++){
        // if the difference is outside the specified radias, report current error.
        if ((displacement - AverageDisplacementWithError(initialVelocity, 45.00, errorTemp)) >= radias){
            return maxError;
        }
        maxError++;
    }
}
void driver_averageDisplacementWithError(double inititialVelocity, double error, FILE* errorOutput){
    
    double average = 0.00;
    double standerdDeviation = 0.00;
    double currentDisplacement = 0.00;
    
    // Generate displacement data with error NON-IDEAL [1-89]
    printf("\t\tStart: Non-ideal case\n");
    for (int i = 1; i <= 89; i++){
        currentDisplacement = AverageDisplacementWithError(inititialVelocity, i, error);
        fprintf(errorOutput, "%d\t%f\n", i , currentDisplacement);
        average += currentDisplacement;
    }
    
    // Print average in file
    fprintf(errorOutput,"Average of this data is: %f", average/89.00);
    
    printf("\t\tFinish: Non-ideal case\n");

}
double AverageDisplacementWithError(double initialVelocity, double currentAngle, double error){

    // Find initial and final value of angle based on error.
    double startingValue = currentAngle-(currentAngle*(error/100.0));
    double endingValue = currentAngle+(currentAngle*(error/100.0));
    double totalDisplacements = 0.00;
    int Steps = 0;
    
    // from minimum to maximum values within an error
    while(startingValue < endingValue){
    
        // find all displacement within the range, add 'em to find average
        totalDisplacements += (pow(initialVelocity, 2)/ GRAVITY)*sin(2* (startingValue*(PI/180.0)));
        // increament theta
        startingValue += 0.01;
        // update steps
        Steps++;
    }
    
    return totalDisplacements/ Steps;
}

// Use the driven displacement equaiton to calculate R = [(V^2/ Gravity)* sin(2*theta)]
void calculateAverageDisplacement(double initialVelocity, double error, FILE* output){
    // veriables needed
    double displacement = 0.00;
    double average = 0.00;
    double current = 0.00;
    
    printf("\t\tStart: ideal case\n");
    // go through all angles [1.00 -> 89.99]
    // Displacement equation [1.00 -> 1.99], then [1.00] = average of[1.00 -> 1.99]
    for ( int i = 1; i <= 89; i++){
        
        // Reset median & average
        average = 0.00;
        
        // Go through angles with a decimel [i.00-0.5 -> i.50]
        for(int j = 0; j <= 100; j++){
            
            // Update angle
            current = (i-0.50) + ((double)j/100.00);
            
            // Find displacement in all decimal places [i.00 + (j/100.0)] start from [i.00 -> i.99]
            displacement = (pow(initialVelocity, 2)/ GRAVITY)*sin(2* (current*(PI/180.0)));
            average += displacement;
            
           
        }
        
        // Info. to a file format [average  Theta : median]
        fprintf(output, "%d\t%f\n",i, average/101.00);
        
        
    }
    printf("\t\tFinish: ideal case\n");
    
}
