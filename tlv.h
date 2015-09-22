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

struct svg
{
    double width,height;
    std::vector<std::string> data;
    svg()
    {
        width=height=1e3;
    }
    svg(double x)
    {
        width=height=x;
    }
    svg(double w,double h)
    {
        width=w,height=h;
    }
    bool write(std::string fout_name)
    {
        FILE *fout=fopen(fout_name.c_str(),"w");
        if(fout)
        {
            const std::string header="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""+std::to_string(width)+"\" height=\""+std::to_string(height)+"\">";
            fprintf(fout,"%s\n",header.c_str());
            for(std::string str: data) fprintf(fout,"    %s\n",str.c_str());
            fprintf(fout,"</svg>\n");
            fclose(fout);
            return true;
        }
        else return false;
    }
    void prepend(svg *img)
    {
        data.insert(data.begin(),img->data.begin(),img->data.end());
    }
    void append(svg *img)
    {
        data.insert(data.end(),img->data.begin(),img->data.end());
    }
    void import(svg *img)
    {
        data=img->data;
    }
    void clear()
    {
        data.clear();
    }
};

template<typename ...Args> bool tlv(svg *img,std::string str,Args... args)
{
    const std::vector<double> arg={args...};
    if(arg.size()==(size_t)count(str.begin(),str.end(),'$'))
    {
        std::string svd="<"+str+"/>";
        for(double i: arg) svd.replace(svd.find("$"),1,std::string("\""+std::to_string(i)+"\""));
        img->data.push_back(svd);
        return true;
    }
    else
    {
        printf("tlv: %lu != %lu learn how to count\n",arg.size(),(size_t)std::count(str.begin(),str.end(),'$'));
        return false;
    }
}

template<typename ...Args> bool tlv_text(svg *img,std::string txt,std::string str,Args... args)
{
    const std::vector<double> arg={args...};
    if(arg.size()==(size_t)count(str.begin(),str.end(),'$'))
    {
        std::string svd="<text "+str+">";
        for(double i: arg) svd.replace(svd.find("$"),1,std::string("\""+std::to_string(i)+"\""));
        svd+=txt+"</text>";
        img->data.push_back(svd);
        return true;
    }
    else
    {
        printf("tlv: %lu != %lu learn how to count\n",arg.size(),(size_t)std::count(str.begin(),str.end(),'$'));
        return false;
    }
}

#define drw(img,str,...)\
tlv(img,#str,##__VA_ARGS__)
#define txt(img,txt,str,...)\
tlv_text(img,txt,#str,##__VA_ARGS__)
#endif
#endif
