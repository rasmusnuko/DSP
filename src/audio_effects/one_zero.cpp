#include <../source.cpp>

Source one_zero(Source source, float value){
  Source result = source.copy();

  for (int s = 0; s < source.channels[0].size(); ++s){
    for (int c = 0; c < source.numChannels; ++c){
      result.channels[c][s] += value * result.channels[c][s-1];
    }
  }

  return result;
}

