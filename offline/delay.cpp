#include <vector>
#include <cmath>

#include "../source.h"

using namespace std;

Source delay(Source source, int delay_amount){
  Source result = copy_source(source);
  vector<double> delay = vector<double>(delay_amount, 0);
  for (int channel = 0; channel < result.num_channels; ++channel){
    vector<double> v = result.channels[channel];
    v.insert(v.begin, delay);
  }
  return result;
}

Source delay_ms(Source source, double delay_time){
  int amount_samples = round((delay_time/1000) * source.sample_rate);
  return delay(source, amount_samples);
}
