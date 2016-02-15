# tlv
An extremely lightweight svg header only library written in C++11
```
/* By BC van Zuiden -- Leiden, February 2016 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
/* https://github.com/originalsouth/tlv */
```
### About
tlv aims to create a lightweight svg header only library, that makes creating svg's fast and easy. 
Currently tlv doesn't protect you from shooting yourself in your foot as it just a nice way of writing text to svg file.
tlv is and always will be a work in progress, pull requests, input, suggestions are very welcome.
Enjoy!

Feel free to reuse and contribute, pull requests are very welcome!
This code is (and forever will be) a work in progress.

### Todo
* Add more documentation
* Add functionality and improvements
* Keep lightweight!

### Usage
Include tlv.h in your project, nothing much you need to do.
You can see a working example in tlv.cc
You can find more information svg's [here](https://www.w3.org/Graphics/SVG/IG/resources/svgprimer.html) and [here](https://commons.wikimedia.org/wiki/SVG_examples).

### Building
To build the example file (tlv.cc) run something like:
```
make
```
This will create an example binary from tlv.cc which can be run as follows
```
./tlv
```
To clean run:
```
make clean
```
