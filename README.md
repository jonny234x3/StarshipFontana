# Irwin the Treasure Hunter #
This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
Irwin is an energetic young explorer with only one thing on 
his mind, treasure. He searches high and low for any piece of
ancient hidden teasure to take for his collection. He was 
sent to retrieve the secret gems hidden in the skeleton desert.

He has found himself lost deep within the skeleton desert where
magically animated skeletons are trying to prevent him from 
stealing the jewels. He needs to retrieve the four gems to destroy
the skeleton magic. But be warned these tricky skeletons
posess the magic ability teleport in and out of the caverns.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

```bash
$ g++ -c src/*.cpp
$ g++ -o starship *.o -lSDL2 -lSDL2_image
```

which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$ ./starship`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## How To Play ##
Move the player with the arrow keys.
To throw knives at enemies use "W,A,S,D".
Killing enemies will add to you score but touching them will subtract 
from your score and you'll have to start again.

The objective is to collect all the gems without hitting any aliens
for the highest score.

## Issues ##
I think the SDL port has introduced some bounding box collision issues.

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).


The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
