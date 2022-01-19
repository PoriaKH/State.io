//
// Created by PoriaKP on 1/18/2022.
//

#include <stdio.h>
#include "main.h"

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