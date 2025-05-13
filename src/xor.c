#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct Data {
  int x1;
  int x2;
  int y;
};

struct Params {
  float weight1;
  float weight2;
  float bias1;

  float weight3;
  float weight4;
  float bias2;

  float weight5;
  float weight6;
  float bias3;
};

float randw() { return ((rand()/(float)RAND_MAX) - 0.5f) * 0.2f; }

float tan_h(float x)
{
  return (exp(x) - exp(-x))/(exp(x) + exp(-x));
}


float mse(struct Params params,  struct Data arr[4])
{
  float temp = 0;
  for(int i = 0; i < 4; i++)
  {
    float output_1  = (params.weight1 * arr[i].x1) + (params.weight2 * arr[i].x2) + params.bias1;

    float output_2 = (params.weight3 * arr[i].x1) + (params.weight4 * arr[i].x2) + params.bias2;
    output_1 = tan_h(output_1);

    output_2 = tan_h(output_2);
    float pred = params.weight5 * output_1 + params.weight6 * output_2 + params.bias3;

    pred = tan_h(pred);
     float tempError = arr[i].y - pred;

    tempError *= tempError;
    
    temp += tempError; 
  }

  return temp/4.0f;
}

int main(void)
{
  srand((unsigned)time(NULL));
  // for you ignorant fucks xor logic gate is just binary addition...
  // 0 + 0, 1 + 0 is all intuitive but 1 + 1 = 0 cus integer overflow, this xor gates truth table is non linear is not modellable by a single neuron or perceptron :)
  struct Data arr[4] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
  };

  struct Params params;

  params.weight1 = randw();

  params.weight2 = randw();

  params.weight3 = randw();

  params.weight4 = randw();
  
  params.weight5 = randw();

  params.weight6 = randw();

  params.bias1 = randw();

  params.bias2 = randw();

  params.bias3 = randw();
  
  float h = 1e-3;
  float learning_rate = 1e-1;
  for(int i = 0; i < 10000*10; i++)
  {
        float fa = mse(params, arr); 

        // --- Calculate Gradients using numerical 
        struct Params temp_params;
        float fb; // To store the MSE with the perturbed parameter

        // Gradient for weight1
        temp_params = params;
        temp_params.weight1 += h;
        fb = mse(temp_params, arr);
        float gradient_w1 = (fb - fa) / h;

        // Gradient for weight2
        temp_params = params;
        temp_params.weight2 += h;
        fb = mse(temp_params, arr);
        float gradient_w2 = (fb - fa) / h;

        // Gradient for bias1
        temp_params = params;
        temp_params.bias1 += h;
        fb = mse(temp_params, arr);
        float gradient_b1 = (fb - fa) / h;

        // Gradient for weight3
        temp_params = params;
        temp_params.weight3 += h;
        fb = mse(temp_params, arr);
        float gradient_w3 = (fb - fa) / h;

        // Gradient for weight4
        temp_params = params;
        temp_params.weight4 += h;
        fb = mse(temp_params, arr);
        float gradient_w4 = (fb - fa) / h;

        // Gradient for bias2
        temp_params = params;
        temp_params.bias2 += h;
        fb = mse(temp_params, arr);
        float gradient_b2 = (fb - fa) / h;

        // Gradient for weight5
        temp_params = params;
        temp_params.weight5 += h;
        fb = mse(temp_params, arr);
        float gradient_w5 = (fb - fa) / h;

        // Gradient for weight6
        temp_params = params;
        temp_params.weight6 += h;
        fb = mse(temp_params, arr);
        float gradient_w6 = (fb - fa) / h;

        // Gradient for bias3 (the output layer bias)
        temp_params = params;
        temp_params.bias3 += h;
        fb = mse(temp_params, arr);
        float gradient_b3 = (fb - fa) / h;


        // --- Update Parameters using Gradient Descent ---
        params.weight1 -= learning_rate * gradient_w1;
        params.weight2 -= learning_rate * gradient_w2;
        params.bias1 -= learning_rate * gradient_b1;

        params.weight3 -= learning_rate * gradient_w3;
        params.weight4 -= learning_rate * gradient_w4;
        params.bias2 -= learning_rate * gradient_b2;

        params.weight5 -= learning_rate * gradient_w5;
        params.weight6 -= learning_rate * gradient_w6;
        params.bias3 -= learning_rate * gradient_b3; 

        printf("cost: %f \n", mse(params,  arr));
  }
  return 0;
}
