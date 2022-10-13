#include "../wavetable.cpp"

string prefix = "output/wavetable/";

void sinewave_test(){
  Source sine = ::sinewave(220, 2);
  string filepath = prefix + "sinewave_wavetable_test.wav";
  ::render_wav(sine, filepath);
}

void sawtooth_test(){
  Source sawtooth = ::sawtooth(220, 2);
  string filepath = prefix + "sawtooth_wavetable_test.wav";
  ::render_wav(sawtooth, filepath);
}

void triangle_test(){
  Source triangle = ::triangle(220, 2);
  string filepath = prefix + "triangle_wavetable_test.wav";
  ::render_wav(triangle, filepath);
}

void square_test(){
  Source square = ::square(220, 2);
  string filepath = prefix + "square_wavetable_test.wav";
  ::render_wav(square, filepath);
}

int main(){
  sinewave_test();
  sawtooth_test();
  triangle_test();
  square_test();
  
  return 0;
}
