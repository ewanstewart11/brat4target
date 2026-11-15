#include <vector>

class ICO_network{

    public:

    ICO_network(const int& _numNeurons, const float& _learningRate){

        numNeurons = _numNeurons;
        learningRate = _learningRate;

        for (int i = 0; i < numNeurons; i++){
            w.push_back(1);
            x.push_back(0);
            accInputs.push_back(0);
        }

        //Gyro DC Offset is a constant input of 1
        x[1] += 1;
        
    }

    //will be called onTargetDetected
    void processTargetAngle(const float& phi){
        learningStep(phi);
        setTargetAngle(phi);
        for(int i = 0; i < numNeurons; i++){
            accInputs[i] = 0;
        }
    }

    //will be called onGyroTurn
    void processDPhi(const float& dphi){
        setDphi(dphi);
        accumulateDPhi();
    }

    //getter for target angle
    float getTargetAngle(){
        return targetAngle;
    }

    private:

    //2 in this case
    int numNeurons{};

    float learningRate{};

    //weights
    std::vector<float> w{};

    //inputs
    std::vector<float> x{};

    //accumulation of inputs between target detections for use in the learning step
    std::vector<float> accInputs{};

    float targetAngle{};

    void setDphi(const float& dphi){
        x[0] = dphi;
    }

    //accumulates the angle between target detections
    void accumulateDPhi(){
        targetAngle += x[0] * w[0] + x[1] * w[1];
        for (int i = 0; i < numNeurons; i++){
            accInputs[i] += x[i];
        }
    }

    //I think I have derived this correctly but was a bit unsure about accumulating the inputs between target detections.
    void learningStep(const float& phi){
        float error = phi - targetAngle;
        for (int i = 0; i < numNeurons; i++){
            w[i] += learningRate * error * accInputs[i];
        }
    }

    //reset target angle to the detected target after the learning step
     void setTargetAngle(const float& phi){
        targetAngle = phi;
    }

};