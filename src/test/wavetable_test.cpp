#include "../wavetable.cpp"

void sine_test(){
  Source sine = ::sinewave(220, 2);
  string filepath = "output/sine_wavetable_test.wav";
  ::render_wav(sine, filepath);
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
  sine_test();
  triangle_test();
  square_test();
  
  return 0;
}
