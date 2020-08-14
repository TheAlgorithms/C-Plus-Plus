/**
 * @file neural_network.cpp
 * @author [Deep Raval](https://github.com/imdeep2905)
 * 
 * @brief Implementation of [NeuralNetwork (aka Multilayer Perceptron)] (https://en.wikipedia.org/wiki/Multilayer_perceptron). 
 * 
 * @details
 * A multilayer perceptron (MLP) is a class of feedforward artificial neural network (ANN). The term MLP is used ambiguously, 
 * sometimes loosely to any feedforward ANN, sometimes strictly to refer to networks composed of multiple layers of perceptrons 
 * (with threshold activation). Multilayer perceptrons are sometimes colloquially referred to as "vanilla" neural networks, 
 * especially when they have a single hidden layer.
 * 
 * An MLP consists of at least three layers of nodes: an input layer, a hidden layer and an output layer. Except for the 
 * input nodes, each node is a neuron that uses a nonlinear activation function. MLP utilizes a supervised learning technique 
 * called backpropagation for training. Its multiple layers and non-linear activation distinguish MLP from a linear 
 * perceptron. It can distinguish data that is not linearly separable.
 * 
 * See [Backpropagation](https://en.wikipedia.org/wiki/Backpropagation) for training algorithm.
 * 
 * \note This implementation uses mini-batch gradient descent as optimizer and MSE as loss function. Bias is also not included.
 */

#include "vector_ops.hpp" // Custom header file for vector operations

#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

/** \namespace machine_learning
 * \brief Machine learning algorithms
 */
namespace machine_learning {
    /** \namespace neural_network
     * \brief Neural Network or Multilayer Perceptron
     */   
    namespace neural_network {
        /** \namespace activations
         * \brief Various activation functions used in Neural network
         */         
        namespace activations {
            /**
             * Sigmoid function
             * @param X Value 
             * @return Returns sigmoid(x)
             */  
            double sigmoid (const double &x) {
                return 1.0 / (1.0 + std::exp(-x));
            }

            /**
             * Derivative of sigmoid function
             * @param X Value 
             * @return Returns derivative of sigmoid(x)
             */  
            double dsigmoid (const double &x) {
                return x * (1 - x);
            }

            /**
             * Relu function
             * @param X Value 
             * @returns relu(x)
             */  
            double relu (const double &x) {
                return std::max(0.0, x);
            }

            /**
             * Derivative of relu function
             * @param X Value 
             * @returns derivative of relu(x)
             */  
            double drelu (const double &x) {
                return x >= 0.0 ? 1.0 : 0.0;
            }

            /**
             * Tanh function
             * @param X Value 
             * @return Returns tanh(x)
             */  
            double tanh (const double &x) {
                return 2 / (1 + std::exp(-2 * x)) - 1;
            }

            /**
             * Derivative of Sigmoid function
             * @param X Value 
             * @return Returns derivative of tanh(x)
             */  
            double dtanh (const double &x) {
                return 1 - x * x;
            }
        } // namespace activations
        namespace util_functions {
            /**
             * Square function
             * @param X Value 
             * @return Returns x * x
             */  
            double square(const double &x) {
                return x * x;
            }
            /**
             * Identity function
             * @param X Value 
             * @return Returns x 
             */  
            double identity(const double &x) {
                return x;
            }
        } // namespace util_functions
        namespace {
            class Layer {
                public:
                    // To store activation function and it's derivative
                    double (*activation_function)(const double &); 
                    double (*dactivation_function)(const double &);
                    int neurons; // To store number of neurons (used in summary)
                    std::string activation; // To store activation name (used in summary)
                    std::vector <std::valarray <double>> kernal; // To store kernal (aka weights)
                    
                    /**
                     * Constructor for Layer class
                     * @param neurons number of neurons
                     * @param activation activation function for layer
                     * @param kernal_shape shape of kernal 
                     * @param random_kernal flag for whether to intialize kernal randomly
                     */
                    Layer(const int &neurons, 
                          const std::string &activation,
                          const std::pair<size_t, size_t> &kernal_shape,
                          const bool &random_kernal) {
                        // Choosing activation (and it's derivative)
                        if (activation == "sigmoid") {
                            activation_function = neural_network::activations::sigmoid;
                            dactivation_function = neural_network::activations::sigmoid;
                        }
                        else if (activation == "relu") {
                            activation_function = neural_network::activations::relu;
                            dactivation_function = neural_network::activations::drelu;
                        }
                        else if (activation == "tanh") {
                            activation_function = neural_network::activations::tanh;
                            dactivation_function = neural_network::activations::dtanh;
                        }
                        else if (activation == "none") {
                            // Set identity function in casse of none is supplied
                            activation_function = neural_network::util_functions::identity;
                            dactivation_function = neural_network::util_functions::identity;
                        }
                        else {
                            // If supplied activation is invalid
                            std::cout << "ERROR: Invalid argument for layer -> constructor -> activation, ";
                            std::cout << "Expected from {none, sigmoid, relu, tanh} got ";
                            std::cout << activation << std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        this -> activation = activation; // Setting activation name
                        this -> neurons = neurons; // Setting number of neurons
                        // Initialize kernal according to flag
                        if(random_kernal) {
                            uniform_random_initialization(kernal, kernal_shape, -1.0, 1.0);
                        }
                        else {
                            unit_matrix_initialization(kernal, kernal_shape);
                        }
                    }
                    /**
                     * Constructor for Layer class
                     * @param neurons number of neurons
                     * @param activation activation function for layer
                     * @param kernal values of kernal (useful in loading model)
                     */
                    Layer (const int &neurons, 
                           const std::string &activation, 
                           const std::vector <std::valarray<double>> &kernal) {
                        // Choosing activation (and it's derivative)
                        if (activation == "sigmoid") {
                            activation_function = neural_network::activations::sigmoid;
                            dactivation_function = neural_network::activations::sigmoid;
                        }
                        else if (activation == "relu") {
                            activation_function = neural_network::activations::relu;
                            dactivation_function = neural_network::activations::drelu;
                        }
                        else if (activation == "tanh") {
                            activation_function = neural_network::activations::tanh;
                            dactivation_function = neural_network::activations::dtanh;
                        }
                        else if (activation == "none") {
                            // Set identity function in casse of none is supplied
                            activation_function = neural_network::util_functions::identity;
                            dactivation_function = neural_network::util_functions::identity;
                        }
                        else {
                            // If supplied activation is invalid
                            std::cout << "ERROR: Invalid argument for layer -> constructor -> activation, ";
                            std::cout << "Expected from {none, sigmoid, relu, tanh} got ";
                            std::cout << activation << std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        this -> activation = activation; // Setting activation name
                        this -> neurons = neurons; // Setting number of neurons
                        this -> kernal = kernal;  // Setting supplied kernal values                 
                    }
            };
        } // Unnamed namespace
        class NeuralNetwork {
            private:
                std::vector <Layer> layers; // To store layers
                /**
                 * Private Constructor for class NeuralNetwork. This constructor
                 * is used internally to load model.
                 * @param config vector containing pair (neurons, activation)
                 * @param kernals vector containing all pretrained kernals
                 */                
                NeuralNetwork(const std::vector <std::pair<int, std::string>> &config,
                              const std::vector <std::vector<std::valarray<double>>> &kernals) {
                    // First layer should not have activation
                    if(config.begin() -> second != "none") {
                        std::cout << "ERROR: First layer can't have activation other than none";
                        std::cout << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    // Network should have atleast two layers
                    if(config.size() <= 1) {
                        std::cout << "ERROR: Invalid size of network, ";
                        std::cout << "Atleast two layers are required";
                        std::exit(EXIT_FAILURE);
                    }
                    // Reconstructing all pretrained layers
                    for(size_t i = 0; i < config.size(); i++) {
                        layers.emplace_back(Layer(config[i].first, 
                                               config[i].second,
                                               kernals[i])); 
                    } 
                    std::cout << "INFO: Network constructed successfully" << std::endl;                  
                }
                /**
                 * Private function to get detailed predictions (i.e.
                 * activated neuron values). This function is used in
                 * backpropagation, single predict and batch predict.
                 * @param X input vector
                 */
                std::vector<std::vector<std::valarray <double>>> 
                __detailed_single_prediction (const std::vector<std::valarray <double>> &X) {
                    std::vector<std::vector < std::valarray <double> >> details;
                    std::vector < std::valarray <double> > current_pass = X;
                    details.push_back(X);
                    for(const auto &l : layers) {
                        current_pass = multiply(current_pass, l.kernal);
                        current_pass = apply_function(current_pass, l.activation_function);
                        details.push_back(current_pass);
                    }
                    return details;
                }
            public:
                /**
                 * Default Constructor for class NeuralNetwork. This constructor
                 * is used to create empty variable of type NeuralNetwork class.
                 */   
                NeuralNetwork() = default;
                /**
                 * Constructor for class NeuralNetwork. This constructor
                 * is used by user.
                 * @param config vector containing pair (neurons, activation)
                 */   
                explicit NeuralNetwork(const std::vector <std::pair<int, std::string>> &config) {
                    // First layer should not have activation
                    if(config.begin() -> second != "none") {
                        std::cout << "ERROR: First layer can't have activation other than none";
                        std::cout << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    // Network should have atleast two layers
                    if(config.size() <= 1) {
                        std::cout << "ERROR: Invalid size of network, ";
                        std::cout << "Atleast two layers are required";
                        std::exit(EXIT_FAILURE);
                    }
                    // Sepratly creating first layer so it can have unit matrix 
                    // as kernal.
                    layers.push_back(Layer(config[0].first, 
                                           config[0].second, 
                                           {config[0].first, config[0].first},
                                           false));
                    // Creating remaining layers
                    for(size_t i = 1; i < config.size(); i++) {
                        layers.push_back(Layer(config[i].first, 
                                               config[i].second,
                                               {config[i - 1].first, config[i].first},
                                               true));
                    }
                    std::cout << "INFO: Network constructed successfully" << std::endl;
                }

                /**
                 * Function to get X and Y from csv file (where X = data, Y = label)
                 * @param file_name csv file name
                 * @param last_label flag for whether label is in first or last column
                 * @param normalize flag for whether to normalize data 
                 * @return returns pair of X and Y
                 */  
                std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>>
                get_XY_from_csv(const std::string &file_name, 
                                     const bool &last_label, 
                                     const bool &normalize) {
                    std::ifstream in_file; // Ifstream to read file
                    in_file.open(file_name.c_str(), std::ios::in); // Open file
                    std::vector <std::vector<std::valarray<double>>> X, Y; // To store X and Y
                    std::string line; // To store each line
                    std::getline(in_file, line, '\n'); // Ignore first line
                    // While file has information
                    while(!in_file.eof() && std::getline(in_file, line, '\n'))
                    {
                        std::valarray <double> x_data, y_data; // To store single sample and label
                        std::stringstream ss(line); // Constructing stringstream from line
                        std::string token; // To store each token in line (seprated by ',')
                        while(std::getline(ss, token, ',')) { // For each token
                            // Insert numerical value of token in x_data
                            x_data = insert_element(x_data, std::stod(token));
                        } 
                        // If label is in last column
                        if(last_label) {
                            y_data.resize(this -> layers.back().neurons);
                            // If task is classification
                            if(y_data.size() > 1) {
                                y_data[x_data[x_data.size() - 1]] = 1;
                            }
                            // If task is regrssion (of single value)
                            else {
                                y_data[0] = x_data[x_data.size() - 1];
                            } 
                            x_data = pop_back(x_data); // Remove label from x_data
                        }
                        else {
                            y_data.resize(this -> layers.back().neurons);
                            // If task is classification
                            if(y_data.size() > 1) {
                                y_data[x_data[x_data.size() - 1]] = 1;
                            }
                            // If task is regrssion (of single value)
                            else {
                                y_data[0] = x_data[x_data.size() - 1];
                            } 
                            x_data = pop_front(x_data); // Remove label from x_data
                        }
                        // Push collected X_data and y_data in X and Y
                        X.push_back({x_data});
                        Y.push_back({y_data});
                    }
                    in_file.close();
                    // Normalize training data if flag is set
                    if(normalize) {
                        // Scale data between 0 and 1 using min-max scaler
                        X = minmax_scaler(X, 0.01, 1.0);
                    }
                    return make_pair(X, Y); // Return pair of X and Y
                }

                /**
                 * Function to get prediction of model on single sample.
                 * @param X X data
                 * @return returns predictions as vector
                 */  
                std::vector<std::valarray <double>> 
                single_predict (const std::vector<std::valarray <double>> &X) {
                    // Get activations of all layers
                    auto activations = this -> __detailed_single_prediction(X);
                    // Return activations of last layer (actual predicted values)
                    return activations.back();
                }

                /**
                 * Function to get prediction of model on batch
                 * @param X X data
                 * @return returns predicted values as vector
                 */  
                std::vector < std::vector <std::valarray<double>>>
                batch_predict (const std::vector <std::vector <std::valarray <double>>> &X) {
                    // Store predicted values
                    std::vector < std::vector <std::valarray<double>>> predicted_batch(X.size());
                    for(size_t i = 0; i < X.size(); i++) { // For every sample
                        // Push predicted values
                        predicted_batch[i] = this -> single_predict(X[i]);
                    }
                    return predicted_batch; // Return predicted values
                }

                /**
                 * Function to fit model on supplied data
                 * @param X X data
                 * @param Y Y data
                 * @param epochs number of epochs
                 * @param learning_rate learning rate 
                 * @param batch_size batch size for gradient descent (default = 32)
                 * @param shuffle flag for whether to shuffle data
                 */  
                void fit(const std::vector < std::vector <std::valarray<double>>>  &X_, 
                         const std::vector < std::vector <std::valarray<double>>>  &Y_, 
                         const int &epochs, 
                         const double &learning_rate,
                         const size_t &batch_size = 32,
                         const bool &shuffle = true) {
                    std::vector < std::vector <std::valarray<double>>> X = X_, Y = Y_;
                    // Both label and input data should have same size
                    if (X.size() != Y.size()) {
                        std::cout << "ERROR : X and Y in fit have different sizes" << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    std::cout << "INFO: Training Started" << std::endl;
                    for (int epoch = 1; epoch <= epochs; epoch++) { // For every epoch
                        // Shuffle X and Y if flag is set
                        if(shuffle) {
                            equal_shuffle(X, Y);
                        }
                        auto start = std::chrono::high_resolution_clock::now(); // Start clock
                        double loss = 0, acc = 0; // Intialize performance metrics with zero
                        // For each starting index of batch
                        for(size_t batch_start = 0; batch_start < X.size(); batch_start += batch_size) {
                            for(size_t i = batch_start; i < std::min(X.size(), batch_start + batch_size); i++) {
                                    std::vector <std::valarray<double>> grad, cur_error, predicted;
                                    auto activations = this -> __detailed_single_prediction(X[i]);
                                    // Gradients vector to store gradients for all layers
                                    // They will be averaged and applied to kernal
                                    std::vector<std::vector<std::valarray<double>>> gradients;
                                    gradients.resize(this -> layers.size());
                                    // First intialize gradients to zero
                                    for(size_t i = 0; i < gradients.size(); i++) {
                                        zeroes_initialization(gradients[i], get_shape(this -> layers[i].kernal));
                                    }
                                    predicted = activations.back(); // Predicted vector
                                    cur_error = predicted - Y[i]; // Absoulute error
                                    // Calculating loss with MSE
                                    loss += sum(apply_function(cur_error, neural_network::util_functions::square));
                                    // If prediction is correct
                                    if(argmax(predicted) == argmax(Y[i])) {
                                        acc += 1;
                                    }
                                    // For every layer (except first) starting from last one
                                    for(size_t j = this -> layers.size() - 1; j >= 1; j--) {
                                        // Backpropogating errors
                                        cur_error = hadamard_product(cur_error, 
                                                                    apply_function(activations[j + 1], 
                                                                    this -> layers[j].dactivation_function));
                                        // Calculating gradient for current layer
                                        grad = multiply(transpose(activations[j]), cur_error);
                                        // Change error according to current kernal values
                                        cur_error = multiply(cur_error, transpose(this -> layers[j].kernal));
                                        // Adding gradient values to collection of gradients
                                        gradients[j] = gradients[j] + grad / double(batch_size);
                                    }
                                    // Applying gradients
                                    for(size_t j = this -> layers.size() - 1; j >= 1; j--) {
                                        // Updating kernal (aka weights)
                                        this -> layers[j].kernal = this -> layers[j].kernal -
                                                            gradients[j] * learning_rate;
                                    }
                                }
                        }
                        auto stop = std::chrono::high_resolution_clock::now(); // Stoping the clock
                        // Calculate time taken by epoch
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                        loss /= X.size(); // Averaging loss
                        acc /= X.size(); // Averaging accuracy
                        std::cout.precision(4); // set output precision to 4 
                        // Printing training stats
                        std::cout << "Training: Epoch " << epoch << '/' << epochs; 
                        std::cout << ", Loss: " << loss;
                        std::cout << ", Accuracy: " << acc;
                        std::cout << ", Taken time: " << duration.count() / 1e6 << " seconds";
                        std::cout << std::endl;
                    }
                    return;
                }

                /**
                 * Function to fit model on data stored in csv file
                 * @param file_name csv file name
                 * @param last_label flag for whether label is in first or last column
                 * @param epochs number of epochs
                 * @param learning_rate learning rate 
                 * @param normalize flag for whether to normalize data 
                 * @param batch_size batch size for gradient descent (default = 32)
                 * @param shuffle flag for whether to shuffle data
                 */                
                void fit_from_csv (const std::string &file_name, 
                                     const bool &last_label,
                                     const int &epochs, 
                                     const double &learning_rate,
                                     const bool &normalize,
                                     const size_t &batch_size = 32,
                                     const bool &shuffle = true) {
                    // Getting training data from csv file                    
                    auto data = this -> get_XY_from_csv(file_name, last_label, normalize);
                    // Fit the model on training data
                    this -> fit(data.first, data.second, epochs, learning_rate, batch_size, shuffle);
                    return;
                }

                /**
                 * Function to evaluate model on supplied data
                 * @param X X data (input data)
                 * @param Y Y data (label)
                 */  
                void evaluate(const std::vector< std::vector <std::valarray <double>>> &X, 
                                const std::vector< std::vector <std::valarray <double>>> &Y) {
                    std::cout << "INFO: Evaluation Started" << std::endl;
                    double acc = 0, loss = 0; // intialize performance metrics with zero
                    for(size_t i = 0; i < X.size(); i++) { // For every sample in input
                        // Get predictions
                        std::vector<std::valarray<double>> pred = this -> single_predict(X[i]);
                        // If predicted class is correct 
                        if(argmax(pred) == argmax(Y[i])) {
                            acc += 1; // Increment accuracy
                        }
                        // Calculating loss - Mean Squared Error
                        loss += sum(apply_function((Y[i] - pred), 
                                    neural_network::util_functions::square) * 0.5);
                    }
                    acc /= X.size(); // Averaging accuracy
                    loss /= X.size(); // Averaging loss
                    // Prinitng performance of the model
                    std::cout << "Evaluation: Loss: " << loss;
                    std::cout << ", Accuracy: " << acc << std::endl;
                    return;
                }

                /**
                 * Function to evaluate model on data stored in csv file
                 * @param file_name csv file name
                 * @param last_label flag for whether label is in first or last column
                 * @param normalize flag for whether to normalize data 
                 */                
                void evaluate_from_csv (const std::string &file_name, 
                                     const bool &last_label,
                                     const bool &normalize) {
                    // Getting training data from csv file
                    auto data = this -> get_XY_from_csv(file_name, last_label, normalize);
                    // Evaluating model
                    this -> evaluate(data.first, data.second);
                    return;
                }                

                /**
                 * Function to save current model.
                 * @param file_name file name to save model (*.model)
                 */
                void save_model (const std::string &_file_name) {
                    std::string file_name = _file_name;
                    // Adding ".model" extension if it is not already there in name
                    if(file_name.find(".model") == file_name.npos) {
                        file_name += ".model";
                    }
                    std::ofstream out_file; // Ofstream to write in file
                    // Open file in out|trunc mode
                    out_file.open(file_name.c_str(), std::ofstream::out | std::ofstream::trunc);
                    /*
                        Format in which model is saved:

                        total_layers
                        neurons(1st Layer) activation_name(1st Layer)
                        kernal_shape(1st Layer)
                        kernal_values
                        .
                        .
                        .
                        neurons(Nth Layer) activation_name(Nth Layer)
                        kernal_shape(Nth Layer)
                        kernal_value

                        For Example, pretrained model with 3 layers:

                        3
                        4 none
                        4 4
                        1 0 0 0 
                        0 1 0 0 
                        0 0 1 0 
                        0 0 0 1 
                        6 relu
                        4 6
                        -1.88963 -3.61165 1.30757 -0.443906 -2.41039 -2.69653 
                        -0.684753 0.0891452 0.795294 -2.39619 2.73377 0.318202 
                        -2.91451 -4.43249 -0.804187 2.51995 -6.97524 -1.07049 
                        -0.571531 -1.81689 -1.24485 1.92264 -2.81322 1.01741 
                        3 sigmoid
                        6 3
                        0.390267 -0.391703 -0.0989607 
                        0.499234 -0.564539 -0.28097 
                        0.553386 -0.153974 -1.92493 
                        -2.01336 -0.0219682 1.44145 
                        1.72853 -0.465264 -0.705373 
                        -0.908409 -0.740547 0.376416 

                    */
                    // Saving model in the same format
                    out_file << layers.size();
                    out_file << std::endl;
                    for(const auto &layer : this -> layers) {
                        out_file << layer.neurons << ' ' << layer.activation << std::endl;
                        const auto shape = get_shape(layer.kernal);
                        out_file << shape.first << ' ' << shape.second << std::endl;
                        for(const auto &row : layer.kernal) {
                            for(const auto &val : row) {
                                out_file << val << ' ';
                            }
                            out_file << std::endl;
                        }
                    }
                    std::cout << "INFO: Model saved successfully with name : ";
                    std::cout << file_name << std::endl;
                    return;
                }

                /**
                 * Function to load earlier saved model.
                 * @param file_name file from which model will be loaded (*.model)
                 * @return instance of NeuralNetwork class with pretrained weights
                 */
                NeuralNetwork load_model (const std::string &file_name) {
                    std::ifstream in_file; // Ifstream to read file
                    in_file.open(file_name.c_str()); // Openinig file
                    std::vector <std::pair<int, std::string>> config; // To store config
                    std::vector <std::vector<std::valarray<double>>> kernals; // To store pretrained kernals
                    // Loading model from saved file format
                    size_t total_layers = 0; 
                    in_file >> total_layers;
                    for(size_t i = 0; i < total_layers; i++) {
                        int neurons = 0;
                        std::string activation;
                        size_t shape_a = 0, shape_b = 0;
                        std::vector<std::valarray<double>> kernal;
                        in_file >> neurons >> activation >> shape_a >> shape_b;
                        for(size_t r = 0; r < shape_a; r++) {
                            std::valarray<double> row(shape_b);
                            for(size_t c = 0; c < shape_b; c++) {
                                in_file >> row[c];
                            }
                            kernal.push_back(row);
                        }
                        config.emplace_back(make_pair(neurons, activation));;
                        kernals.emplace_back(kernal);
                    }
                    std::cout << "INFO: Model loaded successfully" << std::endl;
                    return NeuralNetwork(config, kernals); // Return instance of NeuralNetwork class
                }

                /**
                 * Function to print summary of the network.
                 */
                void summary () {
                    // Printing Summary 
                    std::cout << "===============================================================" << std::endl;
                    std::cout << "\t\t+ MODEL SUMMARY +\t\t\n";
                    std::cout << "===============================================================" << std::endl;
                    for(size_t i = 1; i <= layers.size(); i++) { // For every layer
                        std::cout << i << ")";
                        std::cout << " Neurons : " << layers[i - 1].neurons; // number of neurons
                        std::cout << ", Activation : " << layers[i - 1].activation; // activation
                        std::cout << ", Kernal Shape : " << get_shape(layers[i - 1].kernal); // kernal shape
                        std::cout << std::endl;
                    }
                    std::cout << "===============================================================" << std::endl;
                    return;
                }
        
        };
    } // namespace neural_network
} // namespace machine_learning

/**
 * Function to test neural network
 */
static void test() {
    // Creating network with 3 layers for "iris.csv"
    machine_learning::neural_network::NeuralNetwork myNN =
    machine_learning::neural_network::NeuralNetwork({
        {4, "none"}, // First layer with 3 neurons and "none" as activation
        {6, "relu"}, // Second layer with 6 neurons and "relu" as activation
        {3, "sigmoid"} // Third layer with 3 neurons and "sigmoid" as activation
    });
    // Printing summary of model
    myNN.summary();
    // Training Model
    myNN.fit_from_csv("iris.csv", true, 100, 0.3, false, 32, true);
    // Testing predictions of model
    assert(argmax(myNN.single_predict({{5,3.4,1.6,0.4}})) == 0);
    assert(argmax(myNN.single_predict({{6.4,2.9,4.3,1.3}})) == 1);
    assert(argmax(myNN.single_predict({{6.2,3.4,5.4,2.3}})) == 2);
    return;
}

/** Driver Code */
int main() {
    // Testing
    test();
    return 0;
}
