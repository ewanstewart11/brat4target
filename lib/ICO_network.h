#pragma once

#include <vector>

class ICO_network {

public:
    ICO_network(const int _numNeurons, const float _learningRate);
    void processTargetAngle(const float phi);
    void processDPhi(const float dphi);
    float getTargetAngle();

private:
    int numNeurons{};
    float learningRate{};
    std::vector<float> w{};
    std::vector<float> x{};
    std::vector<float> accInputs{};
    float targetAngle{};

    void setDphi(const float dphi);
    void accumulateDPhi();
    void learningStep(const float phi);
    void setTargetAngle(const float phi);
    
};