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


Source sawtooth(float hz, int duration =2, int sample_rate = 44100){
  int duration_samples = duration * sample_rate;

  vector<float> phasor = ::phasor(hz, duration, sample_rate);
  Source result;
  result.reserve_channels_mem(duration_samples);

  for (int i = 0; i < duration_samples; ++i){
    for (int channel = 0; channel < result.num_channels; ++channel){
      result.channels[channel].push_back( (phasor[i] * 2 ) - 1 );
    }
  }

  return result;
}
