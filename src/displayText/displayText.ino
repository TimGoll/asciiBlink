#include "asciiBlink.h"

void setup() {
  asciiBlink.begin(200);
  asciiBlink.enableDebug();
  asciiBlink.definePins(10,9,8,7,6,5,4,3);
  asciiBlink.setFrameTime(1500);
  asciiBlink.setPauseTime(75);
  asciiBlink.registerNewString("Hello World!");
  asciiBlink.registerNewDelay();
  asciiBlink.registerNewDelay();
}

void loop() {
  asciiBlink.update();
}
