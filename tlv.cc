// TLV some version
// An extremely lightweight svg header only library written in C++11
// By Benny van Zuiden, MSc
// Insituut Lorentz for theoretical physics
// Leiden, NL 2015
// Feel free to use for any of your projects while retaining this banner
// Compiled binaries that aren't free and open source, should produce this banner in the about or version information
// You are free to fork and redistribute while retaining this banner somewhere "based on this banner or something"
// AS USUAL: THIS SOFTWARE IS EXTREMELY BAD FOR YOU AND CAN ONLY BE USED AT YOUR OWN RISK
// THIS SOFTWARE WILL DESTROY EVERYTHING YOU OWN INCLUDING YOUR BODY
// DONT USE THIS SOFTWARE
// IF YOU DO IT IS AT YOUR OWN RISK
//
// TLV is a work in progress, pull requests, input, suggestions are very welcome

#include "tlv.h"

int main()
{
    svg img;
    rect(&img,0.0,0.0,1000.0,1000.0,"black");
    line(&img,500.0,500.0,600.0,600.0,20.0,"blue");
    circle(&img,500.0,500.0,100.0,"green");
    img.write("output.svg");
    return EXIT_SUCCESS;
}
