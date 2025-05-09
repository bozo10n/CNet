#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
# define N 1000

struct Data{
  int x;
  int y;
};

float cost(float weight, struct Data arr[5])
{
    float error = 0;
    for(int j = 0; j < 5; j++)
    {
      float pred = arr[j].x * weight;
      float temp = arr[j].y - pred;
      temp *= temp;
      error += temp;
    }
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

  for(int i = 0; i < N; i++)
  {
    printf("epoch: %d ", i);
    
    printf("cost: %f\n", cost(weight, arr));
  }
  
   return 0;
}
