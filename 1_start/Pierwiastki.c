#include <stdio.h>
#include <math.h>

/* -lm przy kompilacji bo math to przy gcc */

int main(){
  float a,b,c;
  printf("Enter a,b,c for your quadratic equation (ax^2+bx+c = 0 ): ");
  scanf("%f%f%f",&a,&b,&c);
  float delta = (b*b - 4*a*c);
  float x1,x2;
  if(delta >=0){
    delta = sqrt(delta);
    x1 = (b - delta)/2*a;
    x2 = (b - delta)/2*a;
    printf("Pierwszy pierwiastek to %f \nDrugi pierwiastek to %f\n",x1,x2);
  }
  else
    {
      printf("Nie istnieje rozwiązanie rzeczywiste\n");
      printf("Rozwiazania zespolone:\nPierwsze rozwiązanie %f + %fi\nDrugie rozwiazanie %f + %fi\n",b/2*a,sqrt(-delta)/2*a,b/2*a,sqrt(-delta)/2*a);
    }
  
}

