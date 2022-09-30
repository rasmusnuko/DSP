#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <cmath>

#include "portaudio.h"
#include "source.h"

// Audio specifications
#define SAMPLE_RATE (44100.0)
#define FRAMES_PER_BUFFER (512)
#define TABLE_SIZE FRAMES_PER_BUFFER
#define TIME_STEP (1.0/SAMPLE_RATE)

#ifndef M_PI
#define M_PI (3.14159265)
#endif

class Player {
  public:
    Player();

    void initialize();
    void terminate();
    void open();

    Source p_source;

    int p_global_index;

    int paUserCallback(const void *input_buf, void *output_buf,
                       unsigned long frames_per_buf,
                       const PaStreamCallbackTimeInfo* time_info,
                       PaStreamCallbackFlags status_flags);

    // STATIC
    static int paCallback(const void *input_buf, void *output_buf,
                          unsigned long frames_per_buf,
                          PaStreamCallbackTimeInfo* time_info,
                          PaStreamCallbackFlags status_flags,
                          void *user_data)
    {
      return ((Player*)user_data)->paUserCallback(input_buf, output_buf,
                                                  frames_per_buf, time_info,
                                                  status_flags);
    }


  private:
    static int p_sDefaultDeviceNumber;

    float p_frequency;

    PaStream *stream;
    int left_phase;
    int right_phase;

    bool p_Playing;
};

#endif
