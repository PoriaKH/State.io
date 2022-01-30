//
// Created by PoriaKP on 1/18/2022.
//

#include <stdio.h>
#include "main.h"
#include <math.h>
void sort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[j] < a[i])
            {
                int temp=a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}
Sint16 avg(Sint16 a,Sint16 b)
{
    return (a+b)/2;
}

double len_cal(Sint16 x1,Sint16 x2,Sint16 y1,Sint16 y2)
{
    double d_x = x1 - x2;
    double d_y = y1 - y2;
    double d_d = (d_x * d_x) + (d_y * d_y) ;
    return sqrt(d_d);
}
int counter (int n)
{
    int fin = 0;
    while(n>0){
        n /= 10;
        fin++;
    }
    return fin;
}