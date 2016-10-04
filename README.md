# Arduino ANSI

Collection of ANSI codes to use on c++ streams

environment: **Arduino**

![ANSI terminal example]("https://github.com/neu-rah/AnsiStream/blob/master/ansi.jpg")


## Example

```c++
#include <AnsiStream.h>

using namespace ANSI;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial<<home()<<defaultBackground()<<defaultForeground();
  Serial<<"ansi test "<<boldOn()<<"www.r-site.net"<<boldOff()<<endl;
  Serial<<xy(1,2)<<"Time:";
}

void loop() {
  Serial<<xy(7,2)<<setForegroundColor(RED)<<millis()/1000<<endl;
  delay(100);
}
```

the result can be seen on a linux system using the **screen** command.

    screen /dev/ttyUSB0 115200

to quit the screen use **CTRL+A** + **\**

_**note:** you will not be abble to use the arduino port while the screen utility is active._

## API

The following entities can be used on streaming:

### Commands

**home()** move cursor to home position.

**xy(x,y)** set cursor position.

**up(n)** move cursor up n lines, default to 1.

**down(n)** move cursor down n lines, defaults to 1.

**forward(n)** move cursor forward n characters, defaults to 1.

**backward(n)** move cursor back n characters, defaults to 1.

**eraseLine** deletes current line.

**eraseScreen()** clear the screen.

**setBackgroundColor(c)** set background color to be used.

**setForegroundColor(c)** set foreground color to be used.

**fill(x1,y1,x2,y2,c)** firl rectangular area with character c.

### Attributes

Set attributes to be used

**boldOn()** start bold text.

**boldOff()** end bold text.

**italicsOn()** start italic text.

**italicsOff()** end italic text.

**underlineOn()** start undelined text.

**underlineOff()** end underlined text.

**strikethroughOn()** start strikedout text.

**strikethroughOff()** end strikedout text.

**inverseOn()** start inverse text.

**inverseOff()** end inverse text.

**reset()** reset all attributes.

**defaultBackground()** use default background.

**defaultForeground()** use default foreground.

### Colors

Colors can be numeric values (see ansi color codes online).

however some color codes are defined by this library as a comodity:

BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
