#include <vector>

std::vector<std::vector<double> > gain(std::vector<std::vector<double> > channels, double gain){
  num_channels = channels.size();
  // For each channel in input
  for (int c = 0, c < num_channels, ++c){
    // For each sample in channel
    for (int i = 0, i < channels[c].size(); ++i){
      // Multiply sample_{i} by gain
      channels[c][i] *= gain;
    }
  }

  return channels;
}
