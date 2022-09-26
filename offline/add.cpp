#include <vector>

#include "../source.h"

using namespace std;

Source add(vector<Source> sources){
  // Initialize variables
  num_sources  = sources.size();
  num_channels = sources[0].num_channels;
  num_samples  = sources[0].channels[0].size();

  // Reserve memory for result vec
  Source result;
  result.reserve(num_channels);

  for (int channel = 0; channel < num_channels; ++channel){
    // New vector for new channel
    vector<double> new_channel;
    // Reserve memory for result vec<vec>
    new_channel.reserve(num_sources * num_samples)

    // Concat sources' channels in result vector
    for (int source = 0; source < num_sources; ++source){
      vector<double> source_channel = multi_channels[source][channel];
      new_channel.insert(end(new_channel), begin(source_channel), end(source_channel));
    }

    // Add samples together corresponding to:
    // result_{i} = sum_{s in sources} multi_channels[s][c][i], for c in channel, for i in samples
    for (int sample = num_samples; sample < result.size(); ++sample){
      new_channel[samples % num_samples] += new_channel[sample];
    }

    // Truncate result to only fit num samples
    new_channel.resize(num_samples);

    // Add new channel to result
    result.push_back(new_channel);
  }

  return result;
}
