#include "NeuralNetwork.h"
#include <math.h>
#include <random>
#include "Matrix.h"

float NeuralNetwork::sigmoid(float x) {
    return 1 / (1 + (float) exp(-x));
}

float NeuralNetwork::dsigmoid(float y) {
    return y * (1 - y);
}

float NeuralNetwork::tanh(float x) {
    float y = (float) tanh(x);
    return y;
}

float NeuralNetwork::dtanh(float x) {
    float y = 1 / (pow((float) cosh(x), 2));
    return y;
}

float NeuralNetwork::mut(float val, float rate) {
    if ((float) (rand() % 100) < rate) {
        return val + ((rand() % 200) / 100.0) - 1;
    }
    else {
        return val;
    }
}

NeuralNetwork::NeuralNetwork(int input, int hidden, int output, float lr) {
    this->inputNodes = input;
    this->hiddenNodes = hidden;
    this->outputNodes = output;

    this->ihWeights = Matrix::random(hiddenNodes, inputNodes);
    this->hoWeights = Matrix::random(outputNodes, hiddenNodes);
    this->hBias = Matrix::random(hiddenNodes, 1);
    this->oBias = Matrix::random(outputNodes, 1);
}

void NeuralNetwork::mutate(float rate, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float val = this->output.get(i, j);
            this->output.set(i, j, mut(val, rate));
        }
    }
}

void NeuralNetwork::setLearingrate(float rate) {
    this->learningRate = rate;
}

float* NeuralNetwork::feedforward(float *inputArray, int length) {
    this->input = Matrix::fromArray(inputArray, length);

    //generating hidden inputs
    this->hidden = Matrix::product(ihWeights, input);
    this->hidden.add(hBias);

    //activation function for hidden nodes!
    for (int i = 0; i < hidden.rows; i++) {
        for (int j = 0; j < hidden.cols; j++) {
            float val = hidden.get(i, j);
            hidden.set(i, j, sigmoid(val));
        }
    }

    //generating hidden output
    this->output = Matrix::product(hoWeights, hidden);
    this->output.add(oBias);

    //activation function for ouput nodes!
    for (int i = 0; i < output.rows; i++) {
        for (int j = 0; j < output.cols; j++) {
            float val = output.get(i, j);
            output.set(i, j, sigmoid(val));
        }
    }

    //generating the output array
    return this->output.toArray();
}

void NeuralNetwork::train(float inputArray[], float targetArray[], int length) {
    feedforward(inputArray, length);

    Matrix targets = Matrix::fromArray(targetArray, 1);
    Matrix outputErrors = Matrix::subtract(targets, this->output);

    //java version of matrix map function
    Matrix gradient = this->output.copy();
    for (int i = 0; i < gradient.rows; i++) {
        for (int j = 0; j < gradient.cols; j++) {
            float val = gradient.get(i, j);
            gradient.set(i, j, dsigmoid(val));
        }
    }

    gradient.multiply(outputErrors);  //elementWise
    gradient.multiply(learningRate);  //Scalar

    Matrix hiddenT = Matrix::transpose(hidden);
    Matrix DhoWeights = Matrix::product(gradient, hiddenT);

    hoWeights.add(DhoWeights);

    oBias.add(gradient);

    Matrix hoWeightsT = Matrix::transpose(hoWeights);
    Matrix hiddenErrors = Matrix::product(hoWeightsT, outputErrors);

    //java version of matrix map function
    Matrix hiddenGradient = hidden.copy();
    for (int i = 0; i < hiddenGradient.rows; i++) {
        for (int j = 0; j < hiddenGradient.cols; j++) {
            float val = hiddenGradient.get(i, j);
            hiddenGradient.set(i, j, dsigmoid(val));
        }
    }

    hiddenGradient.multiply(hiddenErrors);
    hiddenGradient.multiply(learningRate);

    Matrix inputT = Matrix::transpose(input);
    Matrix DihWeights = Matrix::product(hiddenGradient, inputT);

    ihWeights.add(DihWeights);

    hBias.add(hiddenGradient);

    //delete& targets;
    //delete& outputErrors;
    //delete& gradient;
    //delete& hiddenT;
    //delete& DhoWeights;
    //delete& hoWeightsT;
    //delete& hiddenErrors;
    //delete& hiddenGradient;
    //delete& inputT;
    //delete& DihWeights;
}
