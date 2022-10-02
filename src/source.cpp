#include <vector>

/*
 * Update channels to correspond to set amount of channels
 */
void Source::update_channels(){
  this->channels = std::vector<std::vector<float> >();
  this->channels.reserve(num_channels);
  for (int c = 0; c < this->num_channels; ++c){
    this->channels.push_back(std::vector<float>());
  }
}

/*
 * Constructor
 */
Source::Source():
  num_channels(2),
  sample_rate(44100),
  bit_depth(16),
  channels(vector<std::vector<float> >())

  this->update_channels();
}

/*
 * Copies a Source
 */
Source Source::copy(){
  Source result;
  result.num_channels = this->num_channels;
  result.sample_rate  = this->sample_rate;
  result.bit_depth    = this->bit_depth;
  result.channels     = this->channels;

  return result;
}

/*
 * Generate test Source of a sine wave
 */
Source Source::sine_test(int num_channels = 2, float frequency = 220, int duration = 2){
    // Make new source and reserve memory
    Source sine = Source(num_channels);
    printf("Sine source generated\n");
    sine.num_channels = num_channels;
    printf("Source num channels: %i\n", sine.num_channels);
    printf("Source allocated Cs: %lu\n", sine.channels.size());
    printf("Source sample rate:  %i\n", sine.sample_rate);
    printf("Source bit depth:    %i\n", sine.num_channels);
    int total_samples = duration * sine.sample_rate;

    // Reserving memory in all channels for total amount of samples
    for (int c = 0; c < sine.num_channels; ++c){
      sine.channels[c].reserve(total_samples);
    }
    printf("Memory allocated for %i samples pr channel", total_samples);
    

    // Sine wave
    int max_amplitude = pow(2, sine.bit_depth - 1) - 1;
    for(int i = 0; i < total_samples; i++){
        float amplitude = ((float)i / sine.sample_rate) * max_amplitude;
        float value = sin((2 * 3.14159 * i * frequency) / sine.sample_rate);
        // Write to all channels
        for (int c = 0; c < sine.num_channels; ++c){
          sine.channels[c].push_back(amplitude * value / 2);
        }
    }

    printf("Generated sine source");

    return sine;
}
