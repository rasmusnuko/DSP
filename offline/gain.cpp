#include <vector>

#include "../source.h"

using namespace std;

Source gain(Source source, double gain){
  Source result = source;
  // For each channel in input
  for (int c = 0, c < result.num_channels, ++c){
    vector<double> chan = result.channels[c];
    for_each(chan.begin(), chan.end(), [](double i){ i *= gain; })
  }

    return result;
}
