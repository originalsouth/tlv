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

#ifndef __TLV__
#define __TLV__

#if __cplusplus < 201103L
#error "C++11 not detetected: tlv requires C++11 to work (update your compiler)."
#else

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <zlib.h>

namespace tlv
{
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
                const char header[]="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%g\" height=\"%g\">\n";
                fprintf(fout,header,width,height);
                for(std::string str: data) fprintf(fout,"    %s\n",str.c_str());
                fprintf(fout,"</svg>\n");
                fclose(fout);
                return true;
            }
            else return false;
        }
        bool zwrite(std::string zout_name)
        {
            zout_name+="z";
            gzFile zout=gzopen(zout_name.c_str(),"w");
            if(zout)
            {
                const char header[]="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%g\" height=\"%g\">\n";
                gzprintf(zout,header,width,height);
                for(std::string str: data) gzprintf(zout,"    %s\n",str.c_str());
                gzprintf(zout,"</svg>\n");
                gzclose(zout);
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
        const std::string svd="<"+str+"/>";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        snprintf(buffer,size,svd.c_str(),args...);
        img->data.push_back(std::string(buffer));
        delete[] buffer;
        return true;
    }
    template<typename ...Args> bool tlv_text(svg *img,std::string txt,std::string str,Args... args)
    {
        const std::string svd="<text "+str+">";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        snprintf(buffer,size,svd.c_str(),args...);
        img->data.push_back(std::string(buffer)+txt+std::string("</text>"));
        delete[] buffer;
        return true;
    }
}
#define tlv_drw(img,str,...)\
tlv::tlv(img,#str,##__VA_ARGS__)
#define tlv_txt(img,txt,str,...)\
tlv::tlv_text(img,txt,#str,##__VA_ARGS__)
#endif
#endif
