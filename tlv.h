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
            const string header="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""+to_string(width)+"\" height=\""+to_string(height)+"\">";
            fprintf(fout,"%s\n",header.c_str());
            for(string str: data) fprintf(fout,"    %s\n",str.c_str());
            fprintf(fout,"</svg>\n");
            fclose(fout);
            return true;
        }
        else return false;
    }
};

template<typename ...Args> bool tlv(svg *img,string str,Args... args)
{
    const vector<double> arg={args...};
    if(arg.size()==(size_t)count(str.begin(),str.end(),'$'))
    {
        string svd="<"+str+"/>";
        for(double i: arg) svd.replace(svd.find("$"),1,string("\""+to_string(i)+"\""));
        img->data.push_back(svd);
        return true;
    }
    else
    {
        printf("tlv: %lu != %lu learn how to count\n",arg.size(),(size_t)count(str.begin(),str.end(),'$'));
        return false;
    }
}

#define drw(img,str,...)\
tlv(img,#str,##__VA_ARGS__)
#endif
#endif
