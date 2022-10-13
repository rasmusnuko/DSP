#include "../wavetable.cpp"

void sinewave_test(){
  Source sine = ::sinewave(220, 2);
  string filepath = "output/sinewave_wavetable_test.wav";
  ::render_wav(sine, filepath);
}

void sawtooth_test(){
  Source sawtooth = ::sawtooth(220, 2);
  string filepath = "output/sawtooth_wavetable_test.wav";
  ::render_wav(sawtooth, filepath);
}

void triangle_test(){
  Source triangle = ::triangle(220, 2);
  string filepath = "output/triangle_wavetable_test.wav";
  ::render_wav(triangle, filepath);
}

void square_test(){
  Source square = ::square(220, 2);
  string filepath = "output/square_wavetable_test.wav";
  ::render_wav(square, filepath);
}

int main(){
  sinewave_test();
  sawtooth_test();
  triangle_test();
  square_test();
  
  return 0;
}
