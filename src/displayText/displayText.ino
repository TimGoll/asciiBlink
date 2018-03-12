#include "asciiBlink.h"

void setup() {
  asciiBlink.begin(200);
  asciiBlink.definePins(0,1,2,3,4,5,6,7);
  asciiBlink.registerNewString("Hallo Welt!");
  asciiBlink.setFrameTime(1000);
}

void loop() {
  asciiBlink.update();
}
