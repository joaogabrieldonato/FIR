#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include "FIR.h"

using namespace std;
using namespace chrono;

FIR bs(0.595, 0.595);

int nin = 0;
float r = 2500;

int main () 
{
  time_t err = system_clock::to_time_t(system_clock::now());
  cout << "Teste realizado em: " << ctime(&err);

  int rpm = 0;   
  while (1)
  {
    rpm = (int)bs.filt(r);
    cout << rpm << endl;
    nin++;
    if(rpm==r)
    {      cout << "\nQuantidade de interacoes: " << nin;
      break;
    }
  }
   
  return 0;
}