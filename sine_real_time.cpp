#include <iostream>
#include <cmath>

#include "olcNoiseMaker.h"

using namespace std;


int main()
{
   // Get all sound hardware
   vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

   // Display findings
   for (auto d : devices) << "Found Output Device:" << d << endl;

   // Create sound machine!
   olcNoiseMaker<short> sound(devices[0]);
}
