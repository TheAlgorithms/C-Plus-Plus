#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

/*
-Takes 2 vectors as input
-Input values and corresponding output values of dataset
-Initialise the slope(m) and intrectept(b) with random values
-Calculate the error (predicted-calculates)
-calculate the values of slope and intercpet in order to minimise the error using gradient descent
-update the slope and intercept.
-perform abopve 2 steps for 50 interations(epochs)

with this data slope and intyercept converges with 50 epochs, increase this value if using a bigger data set
*/
vector <float> lin_reg(vector<float> X, vector<float> y)
{
   float  b = -520.0;
   float  m = 600.0;
   float lr = 0.001;  //learning rate
   int epochs = 50;
   vector<float> out_parameters;
   

   for(int i = 0; i<epochs; i++)
   {
    int cost = 0;
    int slope_m = 0;
    int slope_b = 0;

      //y = mx + b
    for(int j = 0; j<X.size(); j++)
    {
        slope_b = slope_b -(2*(y[j]-(m*X[j])-b));
        slope_m = slope_m -(2* (y[j]- (m*X[j]-b))) * X[j];
        cost = cost + pow((y[j] - m*X[j] - b),2);

    }
    //update the slope and intercept values 
    b = b-(lr * slope_b);
    m = m-(lr* slope_m);
   }
   out_parameters.push_back(b);
   out_parameters.push_back(m);

   return out_parameters;
}

int main()
{
   
   vector<float> input_data = {-0.71239066, -0.43714566, -0.45375238,  0.95283061,  0.23785784,
        0.86121137, -0.24332625,  0.18494595, -0.72099967, -0.42989708,
        2.01522083,  0.39724133,  0.20780005, -0.23242587, -0.76862702,
        0.45315861,  0.63988397,  0.3595323 , -1.61510796,  1.74924179,
       -0.78898902, -0.51196509, -0.92833523,  2.15038297, -0.2073497 ,
       -1.63909341, -0.33861825, -0.32212366, -0.48137142, -0.52316421,
        0.72196506,  0.76591105,  0.45348104, -1.26160595, -2.18711527,
       -1.18541881,  0.21745166,  1.33031692, -1.08718159,  0.56226171,
       -1.51284512, -0.00238903, -0.27813452,  0.45181234,  1.19070527,
        0.92234415,  0.81499544, -0.6209797 ,  0.9137407 ,  1.13833305,
        1.47868574, -0.65105648, -0.37591996, -0.77466003,  0.50113729,
        1.3501879 ,  0.72916547, -0.08165156, -0.85414295,  0.46565797,
       -0.04450308, -0.05753239,  1.89274222, -1.04537713,  0.56465429,
       -1.92415945, -0.76403397,  0.12730328, -0.02677165, -0.14521133,
        0.56284679,  0.31735092,  0.71097479,  0.75376638, -0.37011608,
        1.34510171,  0.53233789, -0.98416078,  1.350306  , -0.34660679,
        0.51432886,  0.10126979, -0.65751727,  0.83090566, -0.31726597,
       -0.98027432,  1.39923842,  0.54791831, -0.53032741,  0.49087183,
        0.34875059,  2.05369324,  0.60628866, -0.38445769, -1.94539068,
       -0.31485808,  1.84961257, -1.12050687, -0.33267578, -0.75745323};
   vector<float> output_data = {-34.32, -9.42, -19.09, 20.44, 27.76, -2.91, -14.2, 5.4, -26.43, -34.91, 37.34, 12.85, 25.03, -18.96, -23.47, 37.78, 6.7, -5.57, -49.22, 15.95, -42.97, 6.09, -25.32, 62.82, 12.49, -32.71, -18.83, -29.39, -28.69, 4.39, 46.35, 24.39, 37.98, -34.58, -61.87, -46.44, -6.89, 39.7, -35.24, 8.37, -39.68, 8.27, -4.41, -3.01, 57.82, 24.65, 18.11, -52.28, 35.92, 15.84, 24.01, -25.12, -43.93, 17.39, 15.03, 37.83, 6.33, 5.07, -5.57, 19.84, 7.04, -18.94, 34.8, -57.14, 31.05, -75.73, -44.31, 21.24, -0.19, -28.57, -7.39, 25.22, 32.54, 0.29, -18.64, 39.35, 2.54, -48.63, 54.28, -10.22, -5.67, 23.46, -0.07, 5.63, -9.69, -44.66, 32.71, 18.12, -16.14, 45.04, 22.75, 37.11, 12.48, -35.85, -28.64, -27.98, 64.18, -60.72, 22.23, -2.4};

 
   vector<float> trained_parameter = lin_reg(input_data,output_data);
   
   cout<<"Trained Paramters"<<endl;
   cout<<"b: "<<trained_parameter[0]<<endl;
   cout<<"m: "<<trained_parameter[1]<<endl;
    return 0;

}
