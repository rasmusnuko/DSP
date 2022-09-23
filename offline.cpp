/*
 * BASED ON https://www.youtube.com/watch?v=rHqkeLxAsTc
 */

#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

//// See http://soundfile.sapp.org/doc/WaveFormat/
// Riff chunk
const string chunk_id = "RIFF";
const string chunk_size = "----";
const string format = "WAVE";

// FMT sub-chunk
const string subchunk1_id = "fmt ";
const int subchunk1_size = 16;
const int audio_format = 1;
const int num_channels = 2;
const int sample_rate = 44100;
const int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
const int block_allign = num_channels * (subchunk1_size / 8);
const int bits_per_sample = 16;

// Data sub-chunk
const string subchunk2_id = "data";
const string subchunk2_size = "----";

// Init for synthesis
const int duration = 2;
const int max_amplitude = 32760;
const double frequency = 220;


// Writes data to files as bytes, used to write ints to file in wav header.
void write_as_bytes(ofstream &file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}


int main() {
    // Open new wav file
    ofstream wav;
    wav.open("test.wav", ios::binary);

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
        write_as_bytes(wav, block_allign, 2);
        write_as_bytes(wav, bits_per_sample, 2);
        
        // Data sub-chunk
        wav << subchunk2_id;
        wav << subchunk2_size;

        // Save current location
        int start_audio = wav.tellp();


        // Sine wave
        for(int i = 0; i < sample_rate * duration; i++){
            // Respect max amplitude
            double amplitude = ((double)i / sample_rate) * max_amplitude;
            // value = sine[i]
            double value = sin((2 * 3.14159 * i * frequency) / sample_rate);
            // channel1 increases
            double channel1 = amplitude * value / 2;
            // channel2 decreases
            double channel2 = (max_amplitude - amplitude) * value;

            // Write sine to file
            write_as_bytes(wav, channel1, 2);
            write_as_bytes(wav, channel2, 2);
        }

        // Save current location
        int end_audio = wav.tellp();

        // Go back in file and overwrite "subchunk2_size" with actual sub-chunk size
        wav.seekp(start_audio - 4);
        write_as_bytes(wav, end_audio - start_audio, 4);

        // 4 bytes after the start of the file and overwrite "chunk_size"
        wav.seekp(4, ios::beg);
        write_as_bytes(wav, end_audio - 8, 4);
        
    }

    return 0;
}
