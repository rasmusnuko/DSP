#ifndef SOURCE_H
#define SOURCE_H

#include <vector>

class Source{
  public:
    int num_channels;
    int sample_rate;
    int bit_depth;
    std::vector<std::vector<float> > channels;

    void update_channels();

    Source(int num_channels = 2, int sample_rate = 44100, int bit_depth = 16);

    Source copy();

    Source sine_test(int num_channels = 2, float frequency = 220, int duration = 2);
};

#endif
