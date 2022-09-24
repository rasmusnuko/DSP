/*
 * THIS IS IMPLEMENTED IN ORDER TO RENDER WAV FILES.
 * SEE FUNCTION export_wav() FOR PARAMETERS.
 */

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

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
int render_wav(std::vector<std::vector<double> > channels,
               string filename,
               int num_channels = 2,
               int sample_rate = 44100,
               int bit_rate = 16)
{
    // Open new wav file
    ofstream wav;
    wav.open(filename, ios::binary);

    int byte_rate = sample_rate * num_channels * (subchunk1_size / 8);
    int block_allign = num_channels * (subchunk1_size / 8);

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
        write_as_bytes(wav, bit_rate, 2);
        
        // Data sub-chunk
        wav << subchunk2_id;
        wav << subchunk2_size;

        // Save memory location before writing data
        int start_data = wav.tellp();

        // Write data
        int write_size = 2; // bytes
        int increment = write_size * 8;
        // Iterate through channel
        for (int i = 0; i < channels[0].size() ; ++i){
            // Alternate between channels
            for (int c = 0; c < channels.size(); ++c){
                write_as_bytes(wav, channels[c][i], write_size);
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
 * Generate test audio data of a sine wave
 */
std::vector<std::vector<double> > sine_test(double frequency = 220,
                                            int duration = 2,
                                            int sample_rate = 44100)
{
    // Sine wave
    int max_amplitude = 32760;
    std::vector<double> channel0;
    std::vector<double> channel1;
    channel0.reserve(duration * sample_rate);
    channel1.reserve(duration * sample_rate);
    for(int i = 0; i < sample_rate * duration; i++){
        // Respect max amplitude
        double amplitude = ((double)i / sample_rate) * max_amplitude;
        // value = sine[i]
        double value = sin((2 * 3.14159 * i * frequency) / sample_rate);
        channel0.push_back(amplitude * value / 2);
        channel1.push_back((max_amplitude - amplitude) * value);
    }

    // Channels 2d matrix
    std::vector<std::vector<double> > channels;
    channels.push_back(channel0);
    channels.push_back(channel1);

    return channels;
}

/*
 * Generate test audio data and write to wav file
 */
int main(){
    std::vector<std::vector<double> > test_channels = sine_test();
    render_wav(test_channels, "test.wav");
    return 0;
}
