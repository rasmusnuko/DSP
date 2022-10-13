#include "../waveform.cpp"

string prefix = "output/waveform/";

void sine_test(){
  Source sine = ::sine(220, 2);
  string filepath = prefix + "sinewave_waveform_test.wav";
  ::render_wav(sine, filepath);
}

void sawtooth_test(){
  Source sawtooth = ::sawtooth(220, 2);
  string filepath = prefix + "sawtooth_waveform_test.wav";
  ::render_wav(sawtooth, filepath);
}

int main(){
  sine_test();
  sawtooth_test();
  
  return 0;
}
