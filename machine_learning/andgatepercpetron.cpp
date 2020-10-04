#include <iostream>
#include <random>
#include <vector>

/// Class for Perceptron
class Perceptron {
 public:
    /// Array to store the weights
    std::vector<double> weights;
    double lr;

    Perceptron(int inputLength, double learningRate) {
        this->weights.resize(inputLength, 0);

        /* Using a random device and a uniform distibuiton to randomize
         * the inital weights
         */
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < this->weights.size(); i++) {
            this->weights[i] = dist(rng);  // Randomize each weight
        }

        this->lr = learningRate;
    }

    /// Activation function
    double sing(double value) { return value > 0 ? 1 : 0; }

    /// Predict function, give a array of inputs and calculate the outputs using
    /// the weights
    double guess(std::vector<double> inputs) {
        double sum = 0;

        for (int i = 0; i < inputs.size(); i++) {
            sum += inputs[i] * this->weights[i];
        }

        return sing(sum);
    }

    /// Train function, give the inputs arryan and the target to train the
    /// perceptron
    void train(std::vector<double> inputs, double target) {
        double attempt = guess(inputs);
        double error = target - attempt;

        for (int i = 0; i < weights.size(); i++) {
            this->weights[i] += error * inputs[i] * this->lr;
        }
    }
};

/// Auxliar class to comport a logic gate
class Gate {
 public:
    double a, b, label;
    double bias = 1;
    Gate() {}

    Gate(int a, int b, int label) {
        this->a = a;
        this->b = b;
        this->label = label;
    }
};

int main(int argc, char** argv) {
    // Create random device to train the perceptron
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> idist(0, 3);

    int population = 4;
    double trainedRate = 0;
    double untrainedRate = 0;

    int epoch = 10000;

    Perceptron perceptron(3, 0.01);

    std::vector<Gate> gates;
    gates.resize(population);

    // Define a AND gate
    gates[0] = Gate(0, 0, 0);  // False & False = False
    gates[1] = Gate(0, 1, 0);  // False & True = False
    gates[2] = Gate(1, 0, 0);  // True & False = False
    gates[3] = Gate(1, 1, 1);  // True & True = True

    /*
     *  A single perceptron is a linear "neural network", so it can solve linear
     * problems like AND or OR gates:
     *
     *    AND      OR
     *  |#|0|1| |#|0|1|
     *  |0|F|F| |0|F|T|
     *  |1|F|T| |1|T|T|
     *
     *  You can easly trace aline and separate all Falses from Trues.
     *  Non-linear problems cannot be solved using a single perceptron,
     *  We need a multi layer network, like a feed foward or an convulotional
     * network.
     *
     *  Note: XOR and XNOR are not linear functions, so a perceptron can't
     * predict them
     *
     *    XOR    XNOR
     *  |#|0|1| |#|0|1|
     *  |0|F|T| |0|T|F|
     *  |1|T|F| |1|F|T|
     *
     *  At top and left represent the inputs and T stands for true and F for
     * false
     *
     *  There no way to draw a line that separate True and False. however in AND
     * and OR its possible, so percptron can predic correctly.
     *
     */

    for (int i = 0; i < epoch; i++) {
        std::vector<double> inputs;

        int gate = idist(rng);

        inputs.push_back(gates[gate].a);
        inputs.push_back(gates[gate].b);
        inputs.push_back(gates[gate].bias);

        double target = gates[gate].label;

        perceptron.train(inputs, target);
    }

    for (auto gate : gates) {
        std::vector<double> inputs;
        inputs.push_back(gate.a);
        inputs.push_back(gate.b);
        inputs.push_back(gate.bias);

        double target = gate.label;

        double result = perceptron.guess(inputs);

        std::cout << gate.a << " and " << gate.b << " = " << result
                  << " Expected: " << gate.label << std::endl;
    }

    std::cout << "Done" << std::endl;
    return 0;
}