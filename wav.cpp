/*
 * THIS IS IMPLEMENTED IN ORDER TO RENDER WAV FILES.
 * SEE FUNCTION export_wav() FOR PARAMETERS.
 */
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#include "source.h"

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
const int subchunk1_size = 16;
const int audio_format = 1;

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
 * with specified filename, sample rate and bit rate
 */
int render_wav(Source source, string filename)
{
    // Open new wav file
    ofstream wav;
    wav.open(filename, ios::binary);

    int byte_rate = source.sample_rate * source.num_channels * (subchunk1_size / 8);
    int block_allign = source.num_channels * (subchunk1_size / 8);

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
        write_as_bytes(wav, source.num_channels, 2);
        write_as_bytes(wav, source.sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_allign, 2);
        write_as_bytes(wav, source.bit_depth, 2);
        
        // Data sub-chunk
        wav << subchunk2_id;
        wav << subchunk2_size;

        // Save memory location before writing data
        int start_data = wav.tellp();

        // Write data
        int write_size = 2; // bytes
        int increment = write_size * 8;
        // Iterate through channel
        for (int i = 0; i < source.channels[0].size() ; ++i){
            // Alternate between channels
            for (int c = 0; c < source.num_channels; ++c){
                write_as_bytes(wav, source.channels[c][i], write_size);
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
    
    } else {return -1;} // if wav didn't open and/or didn't associate with this stream object.

    return 0;
}

/*
 * Load a wav into a Source object
 */
Source load_wav(string filename, int num_channels, int sample_rate, int bit_depth){
  Source source;
  source.num_channels = num_channels;
  source.sample_rate = sample_rate;
  source.bit_depth = bit_depth;

  return source;
}

/*
 * Generate test audio data and write to wav file
 */
int main(){
    Source sine = sine_test();
    string filename = "sine.wav";
    render_wav(sine, filename);
    printf("Created %s\n", filename.c_str());
    return 0;
}
