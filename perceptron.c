#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
# define N 1000000000

struct Data{
  int x;
  int y;
};

float cost(float weight, struct Data arr[5])
{
    float error = 0;
    float pavg = 0;
    for(int j = 0; j < 5; j++)
    {
      float pred = arr[j].x * weight;

      pavg += pred;
       float temp = arr[j].y - pred;
      temp *= temp;
      error += temp;
    }

 printf("pred: %f  ", pavg/5.0f);
    return error/5.0f;
}

int main(void)
{
  struct Data arr[5] = {
    {1, 3},
    {3, 9},
    {9, 27},
    {27, 81},
    {81, 243}
  };

  float weight = 0.00000045;

  // y = x * w + b

  for(int i = 0; i < 100000; i++)
  {
    weight += 1e-4f;
    printf("epoch: %d ", i);
    float result = cost(weight, arr);
    printf("cost: %f\n", result);
  }
  
   return 0;
}
