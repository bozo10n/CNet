#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

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

float sigmoid(float x)
{
  return  1/(1 + exp(-x));
}


float mse(float weight1, float weight2, float weight3, float weight4, float weight5, float weight6,  float bias1, float bias2,  struct Data arr[4])
{
  float temp = 0;
  for(int i = 0; i < 4; i++)
  {
    float output_1  = (weight1 * arr[i].x1) + (weight2 * arr[i].x2) + bias1;

    float output_2 = (weight3 * arr[i].x1) + (weight4 * arr[i].x2) + bias2;
    output_1 = sigmoid(output_1);

    output_2 = sigmoid(output_2);
    float pred = weight5 * output_1 + weight6 * output_2;
    
    float tempError = arr[i].y - pred;

    tempError *= tempError;
    
    temp += tempError; 
  }

  return temp/4.0f;
}

int main(void)
{
  // for you ignorant fucks xor logic gate is just binary addition...
  // 0 + 0, 1 + 0 is all intuitive but 1 + 1 = 0 cus integer overflow, this xor gates truth table is non linear is not modellable by a single neuron or perceptron :)
  struct Data arr[4] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
  };

  struct Params params;

  params.weight1 = 1e-3;

  params.weight2 = 1e-3;

  params.weight3 = 1e-3;

  params.weight4 = 1e-3;
  
  params.weight5 = 1e-3;

  params.weight6 = 1e-3;

  params.bias1 = 1e-3;

  params.bias2 = 1e-3;
  float h = 1e-5;
  float learning_rate = 1e-3;
  for(int i = 0; i < 1000000 + 1000; i++)
  {
    float fa =  mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5, params.weight6, params.bias1, params.bias2,  arr);

    float gradient1 = (mse(params.weight1+h, params.weight2, params.weight3, params.weight4, params.weight5, params.weight6, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient2 = (mse(params.weight1, params.weight2+h, params.weight3, params.weight4, params.weight5, params.weight6, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient3 = (mse(params.weight1, params.weight2, params.weight3+h, params.weight4, params.weight5, params.weight6, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient4 = (mse(params.weight1, params.weight2, params.weight3, params.weight4+h, params.weight5, params.weight6, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient5 = (mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5+h, params.weight6, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient6 = (mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5, params.weight6+h, params.bias1, params.bias2,  arr) - fa)/h;
    float gradient7 = (mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5, params.weight6, params.bias1+h, params.bias2,  arr) - fa)/h;
   
    float gradient8 = (mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5, params.weight6, params.bias1+h, params.bias2,  arr) - fa)/h;
   
    params.weight1 = params.weight1 - learning_rate * gradient1;
    
    params.weight2 = params.weight2 - learning_rate * gradient2;
    params.weight3 = params.weight3 - learning_rate * gradient3;
   
    params.weight4 = params.weight4 - learning_rate * gradient4;
    params.weight5 = params.weight5 - learning_rate * gradient5;
    params.weight6 = params.weight6 - learning_rate * gradient6;
    

    params.bias1 = params.bias1 - learning_rate * gradient7;

    params.bias2 -= learning_rate * gradient8;
    printf("cost: %f \n", mse(params.weight1, params.weight2, params.weight3, params.weight4, params.weight5,  params.weight6, params.bias1, params.bias2,  arr));
  }
  return 0;
}
