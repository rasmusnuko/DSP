#include "player.h"

int main(int argc, char **argv){
  Player player;

  player.p_source = sine_test();

  player.initialize();
  player.open();
}
