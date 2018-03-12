# asciiBlink

## Beispiel:

```cpp
#include <asciiBlink.h>

void setup() {
  asciiBlink.begin(200); //max amount of frames
  asciiBlink.definePins(0,1,2,3,4,5,6,7); //LED Pins (MSB left)
  asciiBlink.registerNewString("Hallo Welt!");
  asciiBlink.setFrameTime(1000); //time per frame
}

void loop() {
  asciiBlink.update();
}
```
