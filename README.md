# dndice
An extremely simple MIT-licensced RPG Dice rolling applet in the unix style using the C++11 uniform_int_distribution.

Less than 100 lines including the license.

## Example Usage
 - Roll a 134 sided die: `./roll d134`
 - Roll four 6 sided dice: `./roll 4d6`
 - Roll thirteen 12 sided dice, then add 19 to the total: `./roll 13d12+19`
 
## Compiling
 - Linux/OSX: `g++ -std=c++11 dndice.cpp -o roll`
 - Visual Studio Compiler (2013 and above): `cl dndice.cpp /Feroll.exe`

Binaries for Linux and Windows are available on the [releases page](http://github.com/fsmv/dndice/releases).
