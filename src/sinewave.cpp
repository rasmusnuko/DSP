/*
 * Sine generator from phasor
 */

#include <cmath>
#include "source.cpp"

using namespace std;

vector<float> phasor(float hz, int duration, int sample_rate){
  float period_samples   = sample_rate / hz;
  int duration_samples = sample_rate * duration;

  vector<float> result;
  result.reserve(duration * sample_rate);

  float value = 0;
  for (int i = 0; i < duration_samples; i++){
    result.push_back(value);
    value = std::fmod(value + (1 / period_samples), 1);
  }
  
  return result;
}


Source sine(float hz, int duration = 2, int sample_rate = 44100){
  int duration_samples = duration * sample_rate;

  vector<float> phasor = ::phasor(hz, duration, sample_rate);
  Source result;
  result.reserve_channels_mem(duration_samples);

  for (int i = 0; i < duration_samples; ++i){
    for (int channel = 0; channel < result.num_channels; ++channel){
      result.channels[channel].push_back(sin(2 * M_PI * phasor[i]));
    }
  }

  return result;
}

//int main(int argc, char** argv){
//  int hz = 2000;
//  int sample_rate = 44100;
//  printf("Phasor values for %ihz, %ihz sample rate\n", hz, sample_rate);
//  vector<float> phasor = ::phasor(2000, 1, 44100);
//  for (int i = 0; i < 200; ++i){
//    printf("%.4f\t", phasor[i]);
//  }
//  printf("\n\n\n");
//
//  printf("Sine values for %ihz, %ihz sample rate\n", hz, sample_rate);
//  Source sine = ::sine(hz, 1, sample_rate);
//
//  for (int i = 0; i < 200; ++i){
//    printf("%.4f\t", sine.channels[0][i]);
//  }
//  printf("\n");
//
//  return 0;
//}
