/*
 * THIS IS IMPLEMENTED IN ORDER TO RENDER AND OPEN WAV FILES.
 * SEE FUNCTIONS render_wav() and load_wav() FOR PARAMETERS.
 */
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "source.cpp"

using namespace std;

/*
 * See http://soundfile.sapp.org/doc/WaveFormat/
 */
// Riff chunk
const string chunk_id = "RIFF";
const string chunk_size = "----";
const string format = "WAVE";

// part of FMT sub-chunk
const string subchunk1_id = "fmt ";
const int subchunk1_size = 16;        // size_of float
const int audio_format = 1;           // PCM

// Data sub-chunk
const string subchunk2_id = "data";
const string subchunk2_size = "----";

/*
 * Writes data to files as bytes, used to write ints to file in wav header.
 */
void write_as_bytes(ofstream &file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}

/*
 * Generate new wav file from audio data in channels,
 * with specified filepath, sample rate and bit rate
 */
int render_wav(Source source, string filepath){
  int num_channels = source.num_channels;
  int sample_rate  = source.sample_rate;
  int bit_depth    = source.bit_depth;

  // Open new wav file
  ofstream wav;
  wav.open(filepath, ios::binary);

  int byte_rate = (sample_rate * num_channels * bit_depth) / 8;
  int block_align = num_channels * (bit_depth / 8);

  // Write wav header to file
  if (wav.is_open()) {
    // Riff chunk
    wav << chunk_id;
    wav << chunk_size;
    wav << format;

    // FMT sub-chunk
    wav << subchunk1_id;
    write_as_bytes(wav, subchunk1_size, 4);
    write_as_bytes(wav, audio_format, 2);
    write_as_bytes(wav, num_channels, 2);
    write_as_bytes(wav, sample_rate, 4);
    write_as_bytes(wav, byte_rate, 4);
    write_as_bytes(wav, block_align, 2);
    write_as_bytes(wav, bit_depth, 2);
    
    // Data sub-chunk
    wav << subchunk2_id;
    wav << subchunk2_size;

    // Save memory location before writing data
    int start_data = wav.tellp();

    //// Write data
    int max_amplitude = pow(2, bit_depth-1) - 1;  // "volume"

    int amount_samples = source.channels[0].size();
    for (int s = 0; s < amount_samples; ++s) {
      for (int c = 0; c < num_channels; ++c) {
        write_as_bytes(wav, (int)(source.channels[c][s] * max_amplitude), 2);
      }
    }

    // Save memory location after writing data
    int end_data = wav.tellp();

    // Go back in file and fill out subchunk2_size placeholder
    wav.seekp(start_data - 4);
    write_as_bytes(wav, end_data - start_data, 4);

    // Go to 4 bytes after the beginning of the file. Fill out chunk_size placeholder
    wav.seekp(4, ios::beg);
    write_as_bytes(wav, end_data - 8, 4);

    wav.close();
  
  } else {return -1;} // if wav didn't open and/or didn't associate with this stream object.

  printf("Created %s\n", filepath.c_str());
  return 0;
}


/*
 * Load a wav into a Source object
 */
Source load_wav(string filepath){
  // Open target file
  FILE *wav = fopen(filepath.c_str(), "r");

  Source result;

  // Load num_channels, sample_rate and bit_depth 
  fseek(wav, 22, SEEK_SET);
  fread(&result.num_channels, sizeof(short), 1, wav);
  fseek(wav, 24, SEEK_SET);
  fread(&result.sample_rate, sizeof(int), 1, wav);
  fseek(wav, 34, SEEK_SET);
  fread(&result.bit_depth, sizeof(short), 1, wav);

  // Size of data chunk
  int subchunk2_size;
  fseek(wav, 40, SEEK_SET);
  fread(&subchunk2_size, sizeof(int), 1, wav);

  // Calculate number of samples, samples per channel, and reserve memory for samples
  int num_samples = subchunk2_size / (result.bit_depth / 8);
  int num_samples_per_channel = num_samples / result.num_channels;
  result.reserve_channels_mem(num_samples_per_channel);

  printf("Reading %s\n", filepath.c_str());
  printf("%s num_channels: %i\n", filepath.c_str(), result.num_channels);
  printf("%s sample_rate: %i\n", filepath.c_str(), result.sample_rate);
  printf("%s bit_depth: %i\n", filepath.c_str(), result.bit_depth);
  printf("%s duration (seconds): %d\n", filepath.c_str(), num_samples_per_channel / result.sample_rate);

  // Set file pointer to start of data block
  fseek(wav, 44, SEEK_SET);
  // Values used for int -> float conversion
  int int_value;
  float float_value;
  float max_amplitude = pow(2, result.bit_depth-1) - 1;
  size_t read_size  = result.bit_depth / 8;   // bytes
  // Read all samples into result.channels float vector
  for (int s = 0; s < num_samples; ++s){
    fread(&int_value, (result.bit_depth / 8), 1, wav);
    float_value = int_value / max_amplitude;
    result.append( (s % result.num_channels), float_value);
    if (s < 200){
      printf("%.4f\t", result.channels[0][s]);
    }
  }

  return result;
}
