#include <stdio.h>
#include <stdlib.h>
# define N 5

struct Data{
  int x;
  int y;
};

int main(void)
{
  struct Data arr[N] = {
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
    float pred = arr[i].x * weight;

    printf("cost: %f ", arr[i].y - pred);
    printf("Prediction: %f ", pred);
    printf("Actual: %d\n", arr[i].y);
    
  }
  
   return 0;
}
