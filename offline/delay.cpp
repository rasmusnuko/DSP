#include <vector>

std::vector<std::vector<double> > delay(std::vector<std::vector<double> > channels, int delay_amount){
  num_channels = channels.size();
  // For each channel in input
  for (int c = 0; c < num_channels; c++){
    // Extend channel so that it can fit the delay after original signal
    channels.resize(channels[c].size() + delay_amount);
    // For each sample_{i} where i >= delay_amount, add value from sample_{i - delay_amount}
    for (int i = delay_amount; i < channels[c].size(); i++){
      channels[c][i] += channels[c][i-delay_amount];
    }
  }
  return channels
}
