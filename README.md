# asciiBlink

`asciiBlink` is a small and lightweight library for easy display of binary Ascii characters. While developing, its main focus was set to eliminate blocking through delays. Therefore you need to add the line `asciiBlink.update();` to your main loop.

## Functions
`void asciiBlink.begin([memsize]);`:<br>
Initializes the library. Must be called before anything else from this specific library. Otherwise strange things will happen. `memsize` is not needed and is set to `200` per default. If your program does weird things, you are probably out of memory.

`void asciiBlink.definePins(p0, p1, p2, p3, p4, p5, p6, p7);`:<br>
This function defines the pins to display the characters on. No need to setting up the pins manually. MSB first. Overwrites the old pins if called again.

`void asciiBlink.setFrameTime(time);`:<br>
Can be called at any time. It sets the time per character. Default value is `1000ms`.

`bool asciiBlink.registerNewString(string);`:<br>
Can be called at any time. It adds new strings to the list. Be careful to not overflow the size of you characterbuffer. Returns false if memory overflows.

`bool asciiBlink.registerNewDelay();`:<br>
Registers a delay like any other char. Returns false if memory overflows.

`void asciiBlink.update();`:<br>
Must be called in your main loop to process the LED value.

## Example:

```cpp
#include <asciiBlink.h>

void setup() {
    asciiBlink.begin(200); //max amount of frames
    asciiBlink.definePins(0,1,2,3,4,5,6,7); //LED Pins (MSB left)
    asciiBlink.setFrameTime(1000); //time per frame
    asciiBlink.registerNewString("Hello World!");
}

void loop() {
    asciiBlink.update();
}
```
