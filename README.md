# asciiBlink

`asciiBlink` is a small and lightweight library for easy display of binary Ascii characters. While developing, its main focus was set to eliminate blocking through delays. Therefore you need to add the line `asciiBlink.update();` to your main loop.

## Installation
Download and import the zip-File from this repository.

## Functions
`void asciiBlink.begin([memsize]);`:<br>
Initializes the library. Must be called before anything else from this specific library. Otherwise strange things will happen. `memsize` is not needed and is set to `200` per default. If your program does weird things, you are probably out of memory.

`void asciiBlink.enableDebug();`:<br>
Enables serial output of the LED states. Can cause problems with LEDs if the pins interfere with the serial pins (0, 1).

`void asciiBlink.definePins(p0, p1, p2, p3, p4, p5, p6, p7);`:<br>
This function defines the pins to display the characters on. No need to setting up the pins manually. MSB first. Overwrites the old pins if called again.

`void asciiBlink.setFrameTime(time);`:<br>
Can be called at any time. It sets the time per character. Default value is `1000ms`.

`void asciiBlink.setPauseTime(time);`:<br>
Can be called at any time. It sets the delay between two characters. Default value is `50ms`.

`bool asciiBlink.registerNewString(string);`:<br>
Can be called at any time. It adds new strings to the list. Be careful to not overflow the size of you characterbuffer. Returns false if memory overflows.

`bool asciiBlink.registerNewDelay();`:<br>
Registers a delay like any other char. Returns false if memory overflows.

`bool asciiBlink.registerNewOnDelay();`:<br>
Registers a delay like any other char. All eight LEDs are turned on. Returns false if memory overflows.

`bool asciiBlink.test();`:<br>
Registers eight chars which are displayed after one another. Useful to test the connected LEDs.

`void asciiBlink.update();`:<br>
Must be called in your main loop to process the LED value.

## Example:

```cpp
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
```
