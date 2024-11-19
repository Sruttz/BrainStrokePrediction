#include <EloquentTinyML.h>
#include "BrainStrokeModel1.h"

// Define input and output sizes
#define NUMBER_OF_INPUTS 10  // Adjust based on your input features
#define NUMBER_OF_OUTPUTS 2   // Adjust based on your output classes

#define TENSOR_ARENA_SIZE 5*1024  // Adjust based on model size

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
    ml.begin(BrainStrokeESP32);
}

float fResult[NUMBER_OF_OUTPUTS] = {0};
float fRes = NULL;

// Define the input data as a 2D array
float inputData[4][NUMBER_OF_INPUTS] = {
    {1.0, 1.61427033, -0.32618577, 4.13675323, 1.0, 1.0, 0.0, -0.00052277, 0.58938961, 2.0},
    {0.0, 0.24624988, -0.32618577, -0.24173547, 1.0, 1.0, 1.0, 1.44852918, 0.86922187, 3.0},
    {0.0, -1.56306748, -0.32618577, -0.24173547, 0.0, 1.0, 1.0, 0.10974807, -1.60508439, 0.0},
    {0.0, 1.17297341, -0.32618577, 4.13675323, 1.0, 1.0, 0.0, 2.95371498, -0.35320325, 2.0}
};

void loop() {
    for (int i = 0; i < 4; i++) { // Loop through each input set
        initfResult(fResult);
        fRes = ml.predict(inputData[i], fResult);
        
        Serial.print("\nThe output value returned for input ");
        Serial.print(i + 1); // Print which input is being processed
        Serial.print(" is:\n");
        Serial.println(fRes);
        displayOutput(fResult);
    }

    delay(5000); // 5 seconds delay between predictions
}

void initfResult(float *fResult) {
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        fResult[i] = 0.0f;
    }
}

void displayOutput(float *fResult) {
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        Serial.print(fResult[i]);
        Serial.print(" ");
    }
    Serial.println(); // New line for better output readability
}
