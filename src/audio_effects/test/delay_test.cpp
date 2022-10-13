#include "../../wav.cpp"
#include "../delay.cpp"
#include "../add.cpp"

int main(){
  // Open test file into a Source
  string in_filepath = "guitar.wav";
  Source guitar = ::load_wav(in_filepath);

  // Generate delayed version of test file
  Source delayed_guitar = ::delay_ms(guitar, 300);  // 300ms delay

  // Sum the two together
  Source sum = ::add(guitar, delayed_guitar);

  // Render the sum
  string out_filepath = "output/delay_test.wav";
  ::render_wav(sum, out_filepath);

  return 0;
}
