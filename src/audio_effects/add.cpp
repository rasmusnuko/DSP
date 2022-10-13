#include "../source.cpp"

using namespace std;

Source add(vector<Source> sources){
  // Initial information
  int num_sources  = sources.size();
  int num_channels = sources[0].num_channels;
  int num_samples  = sources[0].channels[0].size();

  // Result source
  Source result;
  result.channels.reserve(num_channels);

  // result[channel][sample] is the sum of all values
  // across sources with that channel and sample.
  for (int channel = 0; channel < num_channels; ++channel){
    float value = 0;
    for (int source = 0; source < num_sources; ++source){
      for (int sample = 0; sample < num_samples; ++sample){
        value += sources[source].channels[channel][sample];
      }
    }

    result.append(channel, value);
  }
  
  return result;
}


Source add(Source a, Source b){
  vector<Source> sources;
  sources.push_back(a);
  sources.push_back(b);

  return add(sources);
}
