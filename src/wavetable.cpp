/*
 * Sine generator from phasor
 */

#define TABLE_SIZE 256

#include <cmath>
#include "source.cpp"

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
  float index_increment = hz * TABLE_SIZE / sample_rate;

  for (int s = 0; s < (duration * sample_rate); ++s){
    for (int channel = 0; channel < result.num_channels; ++channel){
      if (fmod(value, 1) != 0){
        // Interpolate values if value is floating point value
        coef2 = fmod(index, 1);
        coef1 = 1 - coef2;
        value1 = coef1 * table[floor(index)];
        value2 = coef2 * table[(floor(index) + 1) % TABLE_SIZE];

        value = (value1 + value2) * 0.5;
      } else {
        value = table[index];
      }

      result.append(channel, value);
      index += index_increment;
    }
  }

  return result;
}


/*
 * PHASOR
 */
vector<float> gen_phasor_table(){
  result_vector = vector<float>(0, TABLE_SIZE);

  float value = 0;
  float increment = 1 / TABLE_SIZE;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result.table[i] = i * increment;
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
  result_vector = vector<float>(0, TABLE_SIZE);

  float value = 0;
  float increment = 2 / TABLE_SIZE;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result.table[i] = value - 1; // -1 to 1, instead of 0 to 2.
    value += increment;
  }

  return result_vector;
}

Source sawtooth(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> sawtooth_table = gen_sawtooth_table();
  return gen_source(sawtooth_table, frequency, duration, sample_rate, num_channels);
}

/*
 * SINE
 */
vector<float> gen_sine_table(){
  result_vector = vector<float>(0, TABLE_SIZE);

  float increment = (2 * M_PI) / TABLE_SIZE;
  float value = 0;
  for (int i = 0; i < TABLE_SIZE; ++i){
    result_vector.push_back(sin(2 * M_PI * value);
    value += increment;
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
vector<float> triangle_table(){
  result_vector = vector<float>(0, TABLE_SIZE);

  float increment = 1 / (TABLE_SIZE * 0.5);
  float value = 0;
  for int i = 0; i < TABLE_SIZE; ++i){
    result_vector.push_back(value);

    // Update value
    if i < (TABLE_SIZE * 0.5){
      value += increment;
    } else {
      value -= increment;
    }
  }

  return result_vector;
}

Source triangle(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> triangle_table = gen_sine_table();
  return gen_source(triangle_table, frequency, duration, sample_rate, num_channels);
}


/*
 * SQUARE
 */
vector<float> square_table(){
  vector<float> positive = vector<float>(1,  (int) (TABLE_SIZE / 2));
  vector<float> negative = vector<float>(-1, (int) (TABLE_SIZE / 2));

  vector<float> result_vector;
  result_vector.insert(result_vector.end(), positive, negative);

  return result_vector;
}

Source square(float frequency, float duration, int sample_rate = 44100, int num_channels = 2){
  vector<float> square_table = gen_square_table();
  return gen_source(square_table, frequency, duration, sample_rate, num_channels);
}
