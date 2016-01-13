// TLV some version
// An extremely lightweight svg header only library written in C++11
// By Benny van Zuiden, MSc
// Leiden, NL 2015
// Feel free to use for any of your projects while retaining this banner
// Compiled binaries that aren't free and open source, should produce this banner in the about or version information
// You are free to fork and redistribute while retaining this banner somewhere "based on this banner or something"
// AS USUAL: THIS SOFTWARE IS EXTREMELY BAD FOR YOU AND CAN ONLY BE USED AT YOUR OWN RISK
// THIS SOFTWARE WILL DESTROY EVERYTHING YOU OWN INCLUDING YOUR BODY
// DONT USE THIS SOFTWARE
// IF YOU DO IT IS AT YOUR OWN RISK
//
// TLV is and always will be a work in progress, pull requests, input, suggestions are very welcome

//Include the tlv header
#include "tlv.h"

int main()
{
    //Create svg object
    tlv::svg img;
    //Draw a black rectangle
    tlv_drw(&img,rect x1="%g" y1="%g" width="%g" height="%g" fill="%s",0.0,0.0,img.width,img.height,"black");
    //Draw a blue line
    tlv_drw(&img,line x1="500" y1="500" x2="600" y2="600" stroke-width="20" stroke="blue");
    //Draw a green circle
    tlv_drw(&img,circle cx="500" cy="500" r="100" fill="green");
    //Write some text
    tlv_txt(&img,"TLV",x="470" y="505" fill="orange" font-size="36");
    //Write svg object to file "output.svg"
    img.write("output.svg");
    //Write svg object to compressed file "output.svgz" (only for linux)
    img.zwrite("output.svg");
    //Exit with a smiley face
    return EXIT_SUCCESS;
}
