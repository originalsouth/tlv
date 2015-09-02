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

#ifndef __TLV__
#define __TLV__

#if __cplusplus < 201103L
#error "C++11 not detetected: tlv requires C++11 to work (update your compiler)."
#else

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define BEGIN "<"+string(__func__)+" "
#define STRF(a) string(string(#a)+"=\""+to_string(a)+"\" ")
#define STRA(a) string(string(#a)+"=\""+a+"\" ")
#define STRFD(a) string(string(dash(#a))+"=\""+to_string(a)+"\" ")
#define STRAD(a) string(string(dash(#a))+"=\""+a+"\" ")
#define END "/>"

string dash(string a)
{
    replace(a.begin(),a.end(),'_','-');
    return a;
}

struct svg
{
    double width,height;
    vector<string> data;
    svg()
    {
        width=height=1e3;
    }
    bool write(string fout_name)
    {
        FILE *fout=fopen(fout_name.c_str(),"w");
        if(fout)
        {
            const string header="<svg xmlns=\"http://www.w3.org/2000/svg\" "+STRF(width)+STRF(height)+">";
            fprintf(fout,"%s\n",header.c_str());
            for(string str: data) fprintf(fout,"    %s\n",str.c_str());
            fprintf(fout,"</svg>\n");
            fclose(fout);
            return true;
        }
        else return false;
    }
};

void line(svg *img,double x1,double y1,double x2,double y2,double stroke_width,string stroke)
{
    const string str=BEGIN+STRF(x1)+STRF(y1)+STRF(x2)+STRF(y2)+STRFD(stroke_width)+STRA(stroke)+END;
    img->data.push_back(str);
}

void rect(svg *img,double x,double y,double width,double height,string fill)
{
    const string str=BEGIN+STRF(x)+STRF(y)+STRF(width)+STRF(height)+STRA(fill)+END;
    img->data.push_back(str);
}

void circle(svg *img,double cx,double cy,double r,string fill)
{
    const string str=BEGIN+STRF(cx)+STRF(cy)+STRF(r)+STRA(fill)+END;
    img->data.push_back(str);
}
#endif
#endif
