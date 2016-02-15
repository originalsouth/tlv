/* By BC van Zuiden -- Leiden, February 2016 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
/* https://github.com/originalsouth/tlv */

//Include the tlv header
#include "tlv.h"

int main()
{
    //Create svg object
    tlv::svg img;
    //Draw a black rectangle
    tlv_drw(&img,rect x1="%g" y1="%g" width="%g" height="%g" fill="%s",0.0,0.0,img.width,img.height,"black");
    //Create some animation function
    auto anim=[&]()
    {
        tlv_drw(&img,animate attributeName="r" dur="2s" values="50;250;50" repeatCount="indefinite");
    };
    //Animate on circle
    tlv_for(&img,"circle",anim,cx="500" cy="500" r="50" fill="pink");
    //Draw a blue line
    tlv_drw(&img,line x1="500" y1="500" x2="600" y2="600" stroke-width="20" stroke="blue");
    //Draw a green circle
    tlv_drw(&img,circle cx="500" cy="500" r="100" fill="green");
    //Write some text
    tlv_yfo(&img,"text","TLV",x="470" y="505" fill="orange" font-size="36");
    //Write svg object to file "output.svg"
    img.write("output.svg");
    //Exit with a smiley face now open the svg with a text editor (preferably neovim) and compare :)
    return EXIT_SUCCESS;
}
