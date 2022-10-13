/*
 * Sine generator from phasor
 */

#define TABLE_SIZE 256

#include <cmath>
#include "source.cpp"
#include "wav.cpp"

using namespace std;

/*
 * Generate Source object given: wavetable,
 *                               frequency (hz),
 *                               duration (seconds),
 *                               sample rate (hz)
 *                               number of channels
 */
Source gen_source(vector<float> table,
                  float frequency,
                  float duration = 2,
                  int sample_rate = 44100,
                  int num_channels = 2)
{
  // Make new source and reserve memory for audio data
  Source result;
  result.reserve_channels_mem( (int) (duration * sample_rate) );

  // Init floats for linear interpolation
  float value, value1, value2, coef1, coef2;
  float index = 0;
  float index_increment = TABLE_SIZE * (frequency / sample_rate);

  for (int s = 0; s < (duration * sample_rate); ++s){
    coef2 = fmod(index, 1);
    coef1 = 1 - coef2;
    value1 = coef1 * table[floor(index)];
    value2 = coef2 * table[(int) (floor(index) + 1) % TABLE_SIZE];

    value = value1 + value2;

    for (int channel = 0; channel < result.num_channels; ++channel){
      result.append(channel, value);
    }

    index = fmod(index + index_increment, TABLE_SIZE);
  }

  return result;
}


/*
 * PHASOR
 */
vector<float> gen_phasor_table(){
  vector<float> result_vector;

  float increment = 1 / TABLE_SIZE;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result_vector[i] = i * increment;
  }

  return result_vector;
}

Source phasor(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> phasor_table = gen_phasor_table();
  return gen_source(phasor_table, frequency, duration, sample_rate, num_channels);
}


/*
 * SAWTOOTH
 */
vector<float> gen_sawtooth_table(){
  vector<float> result_vector;

  float increment = 2.0 / TABLE_SIZE;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result_vector.push_back( (increment * i) - 1 );
  }

  return result_vector;
}

Source sawtooth(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> sawtooth_table = gen_sawtooth_table();
  return gen_source(sawtooth_table, frequency, duration, sample_rate, num_channels);
}

/*
 * SINEWAVE
 */
vector<float> gen_sine_table(){
  vector<float> result_vector;

  float increment = (2 * M_PI) / TABLE_SIZE;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result_vector.push_back( sin(i * increment) );
  }

  return result_vector;
}

Source sinewave(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> sine_table = gen_sine_table();
  return gen_source(sine_table, frequency, duration, sample_rate, num_channels);
}


/*
 * TRIANGLE
 */
vector<float> gen_triangle_table(){
  vector<float> result_vector;

  float increment = 2 / (TABLE_SIZE * 0.5);
  float value = 0;
  for (int i = 0; i < TABLE_SIZE; ++i){
    if ( i < (TABLE_SIZE * 0.5) ){
      value += increment;
    } else {
      value -= increment;
    }
    result_vector.push_back(value - 1);
  }

  return result_vector;
}

Source triangle(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> triangle_table = gen_triangle_table();
  return gen_source(triangle_table, frequency, duration, sample_rate, num_channels);
}


/*
 * SQUARE
 */
vector<float> gen_square_table(){
  vector<float> result_vector;

  for (int i = 0; i < TABLE_SIZE; ++i){
    if (i < (TABLE_SIZE * 0.5) ){
      result_vector.push_back(1);
    } else {
      result_vector.push_back(-1);
    }
  }

  return result_vector;
}

Source square(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> square_table = gen_square_table();


  return gen_source(square_table, frequency, duration, sample_rate, num_channels);
}
