#include "player.h"

#include <cmath>

// STATIC
int Player::p_sDefaultDeviceNumber = -1;

/*
 * Constructor
 */
Player::Player():
  p_frequency(0.0),
  stream(0),
  left_phase(0),
  right_phase(0),
  p_global_index(0){ }


/*
 * Tries to initalize a new output via default device
 */ 
void Player::initialize(){

  // Initializing PortAudio
  PaError err = Pa_Initialize();

  // Print if error occurs
  if (err != paNoError){ printf("Error initializing audio interface.\n"); }


  // Getting default audio device
  p_sDefaultDeviceNumber = Pa_GetDefaultOutputDevice();

  // Device info pointer
  const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(p_sDefaultDeviceNumber);

  printf( "Initializing audio interface to: [ " );

  if( p_sDefaultDeviceNumber == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultOutputDevice )
  {
      const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
  }

  printf( " ]\n" );
}


/*
 * Terminates output device
 */
void Player::terminate(){
  Pa_Terminate();
}


/*
 * Open stream
 */
void Player::open(){
  PaStreamParameters output_params;
  PaError err;
  
  output_params.device = Pa_GetDefaultOutputDevice();
  if(output_params.device == paNoDevice){
    fprintf(stderr, "Error in Plauer::open() while getting default output device.");
    terminate();
  }

  output_params.channelCount = 2;
  output_params.sampleFormat = paFloat32;
  output_params.suggestedLatency = Pa_GetDeviceInfo(output_params.device)->defaultLowOutputLatency;
  output_params.hostApiSpecificStreamInfo = NULL;


  printf("Player opening stream...\n");
  err = Pa_OpenStream(&stream,
                      NULL,
                      &output_params,
                      SAMPLE_RATE,
                      FRAMES_PER_BUFFER,
                      paNoFlag,
                      &Player::paCallback,
                      this);
  

  if(err != paNoError){
    terminate();
    return;
  }

  err = Pa_StartStream(stream);

  if(err != paNoError){
    return;
  }
}


/*
 * PortAudio user callback function
 */
int Player::paUserCallback(const void* input_buf, void* output_buf,
                           unsigned long frames_per_buffer,
                           const PaStreamCallbackTimeInfo* time_info,
                           PaStreamCallbackFlags status_flags)
{
  // Current mem positions of output buffer
  float *out = (float*) output_buf;

  // Avoid unused variable warnings
  (void) time_info; 
  (void) status_flags;
  (void) input_buf;

  // Create signal
  for (int j = 0; j < TABLE_SIZE; ++j){
    *out++ = p_source.channels[0][p_global_index];   // left
    *out++ = p_source.channels[1][p_global_index];   // right

    ++p_global_index;
  }

  return paContinue;
}



// TEST
int main(int argc, char** argv){
  Player player;
  
  player.p_source = sine_test();

  player.initialize();
  player.open();
}
