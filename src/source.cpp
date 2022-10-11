/*
 * SOURCE is the implementation of a sound source.
 * A source will have a number of channels, i.e. left and right channels.
 * A source will have a sample rate, i.e. 44100hz.
 * A source will have a bit depth, i.e. 16bits per sample.
 *
 * Source objects are the main thing in this DSP toy implementation.
 * WAV.CPP will allow us to load a wav file into a Source object and
 * export a Source object to a wav file.
 *
 * The different audio effects will take a Source object and return a
 * modified / new Source object as a result.
 *
 * The synthesis models will return Source objects as well.
 */

#include <cmath>
#include <vector>

#ifndef SOURCE
#define SOURCE

using namespace std;

class Source{
  public:
    int num_channels;
    int sample_rate;
    int bit_depth;
    vector<vector<float> > channels;

    /*
     * Update channels to correspond to set amount of channels
     */
    void update_channels(int num_channels = 2){
      this->channels = vector<vector<float> >();
      this->channels.reserve(num_channels);
      for (int c = 0; c < this->num_channels; ++c){
        this->channels.push_back(vector<float>());
      }
    }

    /*
     * Replace a channel with another vector
     */
    void replace(int channel, vector<float> data){
      this->channels[channel] = data;
    }

    /*
     * Append data point onto channel
     */
    void append(int channel, float data){
      this->channels[channel].push_back(data);
    }

    /*
     * Append data vector onto channel
     */
    void append(int channel, vector<float> data){
      vector<float>::iterator channel_end = this->channels[channel].end();
      this->channels[channel].insert(channel_end, data);
    }

    /*
     * Update the amount of memory for each channel in source
     */
    void reserve_channels_mem(int size){
      for (int c = 0; c < this->num_channels; ++c){
        this->channels[c].reserve(size);
      }
    }

    /*
     * Constructor
     */
    Source(int num_channels = 2, int sample_rate = 44100, int bit_depth = 16){
      this->num_channels = num_channels;
      this->sample_rate = sample_rate;
      this->bit_depth = bit_depth;

      this->update_channels();
    }

    /*
     * Copies a Source
     */
    Source copy(){
      Source result;
      result.num_channels = this->num_channels;
      result.sample_rate  = this->sample_rate;
      result.bit_depth    = this->bit_depth;
      result.channels     = this->channels;
    
      return result;
    }
};


/*
 * Convolution of two Source objects
 */
Source operator*(Source u, Source v){
  assert(u.num_channels == v.num_channels);
  assert(u.sample_rate  == v.sample_rate);
  assert(u.bit_depth    == v.bit_depth);

  Source result = Source(u.num_channels, u.sample_rate, u.bit_depth);
  int result_size = u.channels[0].size() + v.channels[0].size() - 1;
  result.reserve_channels_mem(result_size);

  for (int c = 0; c < result.num_channels; ++c){
    for (int i = 0; i < result_size; ++i){
      float index_sum = 0;
      for (int j = 0; j < v.channels[c].size(); ++j){
        if (i - j >= 0){
          index_sum += u.channels[c][i - j] * v.channels[c][j];
        }
      }
      result.insert(c, index_sum);
    }
  }
  return result;
}

/*
 * Convolution of Source and vector<int>
 */
Source operator*(Source u, vector<int> v){
  Source result = Source(u.num_channels, u.sample_rate, u.bit_depth);
  int result_size = u.channels[0].size() + v.size() - 1;
  result.reserve_channels_mem(result_size);

  for (int c = 0; c < result.num_channels; ++c){
    for (int i = 0; i < result_size; ++i){
      float index_sum = 0;
      for (int j = 0; j < v.size(); ++j){
        if (i - j >= 0){
          index_sum += u.channels[c][i - j] * v[j];
        }
      }
      result.insert(c, index_sum);
    }
  }
  return result;
}

/*
 * Convolution of vector<int> and Source
 */
Source operator*(vector<int> u, Source v){
  return v * u; 
}
#endif

