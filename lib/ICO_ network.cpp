#include <vector>

#include "ICO_network.h"

ICO_network::ICO_network(const int _numNeurons, const float _learningRate)
    : numNeurons(_numNeurons), learningRate(_learningRate), targetAngle(0.0f) {
    for (int i = 0; i < numNeurons; i++){
        w.push_back(1);
        x.push_back(0);
        accInputs.push_back(0);
    }
    // Gyro DC Offset is a constant input of 1
    x[1] += 1; 
}

void ICO_network::processTargetAngle(const float phi){
    learningStep(phi);
    setTargetAngle(phi);
    for(int i = 0; i < numNeurons; i++){
        accInputs[i] = 0;
    }
}

void ICO_network::processDPhi(const float dphi){
    setDphi(dphi);
    accumulateDPhi();
}

float ICO_network::getTargetAngle(){
    return targetAngle;
}

void ICO_network::setDphi(const float dphi){
    x[0] = dphi;
}

void ICO_network::accumulateDPhi(){
    for (int i = 0; i < numNeurons; i++){
        targetAngle += x[i] * w[i];
        accInputs[i] += x[i];   
    }
}

void ICO_network::learningStep(const float phi){
    float error = phi - targetAngle;
    for (int i = 0; i < numNeurons; i++){
        w[i] += learningRate * error * accInputs[i];
    }
}

void ICO_network::setTargetAngle(const float phi){
    targetAngle = phi;
}