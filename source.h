#ifndef SOURCE_H
#define SOURCE_H

#include <vector>

typedef struct Source{
  int num_channels;
  int sample_rate;
  int bit_depth;
  std::vector<std::vector<double> > channels;

  // Constructor
  Source(){
    // Default values
    num_channels = 2;
    sample_rate = 44100;
    bit_depth = 16;

    // Reserve memory for channels
    channels.reserve(num_channels);

    // Populate channels with double vectors
    for (int c = 0; c < num_channels; ++c){
      channels.push_back(std::vector<double>());
    }
  }
} Source;

/*
 * Copies a Source. Is called as:
 * Source new_copy = original_source.copy();
 */
inline Source copy_source(Source source){
  Source result;
  result.num_channels = source.num_channels;
  result.sample_rate = source.sample_rate;
  result.bit_depth = source.bit_depth;
  result.channels = source.channels;

  return result;
}

#endif
