#include <vector>

std::vector<std::vector<double> > add(std::vector<std::vector<std::vector<double> > > multi_channels){
  // Initialize variables
  num_sources  = multi_channels.size();
  num_channels = multi_channels[0].size();
  num_samples  = multi_channels[0][0].size();

  // Reserve memory for result vec
  std::vector<std::vector<double> > result;
  result.reserve(num_channels);

  for (int channel = 0; channel < num_channels; ++channel){
    // Reserve memory for result vec<vec>
    result[channel].reserve(num_sources * num_samples)

    // Concat sources' channels in result vector
    for (int source = 0; source < num_sources; ++source){
      result[channel].insert(std::end(result[channel]),
                             std::begin(multi_channels[source][channel]),
                             std::end(multi_channels[source][channel]))
    }

    // Add samples together corresponding to:
    // result_{i} = sum_{s in sources} multi_channels[s][c][i], for c in channel, for i in samples
    for (int sample = num_samples; sample < result.size(); ++sample){
      result[channel][samples % num_samples] += result[channel][sample];
    }
  }

  // Truncate result
  result.resize(num_samples);

  return result;
}
