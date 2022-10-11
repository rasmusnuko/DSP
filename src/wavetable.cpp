/*
 * Sine generator from phasor
 */

#define TABLE_SIZE 256

#include <cmath>
#include "source.cpp"

using namespace std;

class Wavetable{
  public:
    Wavetable(){
      this->table = vector<float>(0, TABLE_SIZE);
    }

    vector<float> get_table(){
      return this->table;
    }

    void gen_phasor_table(){
      result_vector = vector<float>(0, TABLE_SIZE);

      float value = 0;
      float increment = 1 / TABLE_SIZE;
      for (int i = 0; i < TABLE_SIZE; ++i){
        result.table[i] = i * increment;
      }

      this->table = result_vector;
    }


    Source wavetable_phasor(float hz = 220,
                            float duration = 2,
                            int sample_rate = 44100,
                            int num_channels = 2)
    {
      Source result;
      Wavetable phasor;
      phasor.gen_phasor_table();

      for (int c = 0; c < result.num_channels; ++c){
        result.channels[c].push_back(phasor.get_table());
        
      }

    
    }


    void gen_sawtooth_table(){
      result_vector = vector<float>(0, TABLE_SIZE);

      float value = 0;
      float increment = 2 / TABLE_SIZE;
      for (int i = 0; i < TABLE_SIZE; ++i){
        result.table[i] = value - 1; // -1 to 1, instead of 0 to 2.
        value += increment;
      }

      this->table = result_vector;
    }


    void gen_sine_table(){
      result_vector = vector<float>(0, TABLE_SIZE);

      float increment = (2 * M_PI) / TABLE_SIZE;
      float value = 0;
      for (int i = 0; i < TABLE_SIZE; ++i){
        result_vector.push_back(sin(2 * M_PI * value);
        value += increment;
      }

      this->table = result_vector;
    }

    void gen_triangle_table(){
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

      this->table = result_vector;
    }

  private:
    vector<float> table;
}

