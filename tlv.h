/* By BC van Zuiden -- Leiden, February 2016 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
/* https://github.com/originalsouth/tlv */

#ifndef __TLV__
#define __TLV__

#if __cplusplus < 201103L
#error "C++11 not detetected: tlv requires C++11 to work (update your compiler)."
#else

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

namespace tlv
{
    struct svg
    {
        double width,height;
        std::string header;
        std::vector<std::string> data;
        svg();
        svg(double x);
        svg(double w,double h);
        bool write(std::string fout_name);
        void prepend(svg *img);
        void append(svg *img);
        void import(svg *img);
        void clear();
    };
    template<typename ...Args> bool tlv_drw(svg *img,std::string str,Args... args);
    template<typename ...Args> bool tlv_hdr(svg *img,std::string str,Args... args);
    template<typename ...Args> bool tlv_yfo(svg *img,std::string marker,std::string content,std::string str,Args... args);
    template<typename ...Args> bool tlv_obj(svg *img,std::string marker,svg *object,std::string str,Args... args);
    template<typename ...Args,typename lambda> bool tlv_for(svg *img,std::string marker,lambda x,std::string str,Args... args);
    svg::svg()
    {
        width=height=1e3;
        tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
    }
    svg::svg(double x)
    {
        width=height=x;
        tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
    }
    svg::svg(double w,double h)
    {
        width=w,height=h;
        tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
    }
    bool svg::write(std::string fout_name)
    {
        FILE *fout=fopen(fout_name.c_str(),"w");
        if(fout)
        {
            fprintf(fout,"%s\n",header.c_str());
            for(std::string str: data) fprintf(fout,"%s\n",str.c_str());
            fprintf(fout,"</svg>\n");
            fclose(fout);
            return true;
        }
        else return false;
    }
    void svg::prepend(svg *img)
    {
        data.insert(data.begin(),img->data.begin(),img->data.end());
    }
    void svg::append(svg *img)
    {
        data.insert(data.end(),img->data.begin(),img->data.end());
    }
    void svg::import(svg *img)
    {
        data=img->data;
    }
    void svg::clear()
    {
        data.clear();
    }
    template<typename ...Args> bool tlv_drw(svg *img,std::string str,Args... args)
    {
        const std::string svd="<"+str+"/>";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        else
        {
            snprintf(buffer,size,svd.c_str(),args...);
            img->data.push_back(std::string(buffer));
            delete[] buffer;
            return true;
        }
    }
    template<typename ...Args> bool tlv_hdr(svg *img,std::string str,Args... args)
    {
        const std::string svd="<svg xmlns=\"http://www.w3.org/2000/svg\" "+str+">";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        else
        {
            snprintf(buffer,size,svd.c_str(),args...);
            img->header=std::string(buffer);
            delete[] buffer;
            return true;
        }
    }
    template<typename ...Args> bool tlv_yfo(svg *img,std::string marker,std::string content,std::string str,Args... args)
    {
        const std::string svd="<"+marker+" "+str+">";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        else
        {
            snprintf(buffer,size,svd.c_str(),args...);
            img->data.push_back(std::string(buffer)+content+std::string("</")+marker+std::string(">"));
            delete[] buffer;
            return true;
        }
    }
    template<typename ...Args> bool tlv_obj(svg *img,std::string marker,svg *object,std::string str,Args... args)
    {
        const std::string svd="<"+marker+" "+str+">";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        else
        {
            snprintf(buffer,size,svd.c_str(),args...);
            img->data.push_back(std::string(buffer));
            img->append(object);
            img->data.push_back(std::string("</")+marker+std::string(">"));
            delete[] buffer;
            return true;
        }
    }
    template<typename ...Args,typename lambda> bool tlv_for(svg *img,std::string marker,lambda x,std::string str,Args... args)
    {
        const std::string svd="<"+marker+" "+str+">";
        const size_t size=1+snprintf(nullptr,0,svd.c_str(),args...);
        char *buffer=new(std::nothrow) char[size];
        if(buffer==nullptr) return false;
        else
        {
            snprintf(buffer,size,svd.c_str(),args...);
            img->data.push_back(std::string(buffer));
            x();
            img->data.push_back(std::string("</")+marker+std::string(">"));
            delete[] buffer;
            return true;
        }
    }
}
#define tlv_drw(img,str,...) tlv::tlv_drw(img,#str,##__VA_ARGS__)
#define tlv_hdr(img,str,...) tlv::tlv_hdr(img,#str,##__VA_ARGS__)
#define tlv_yfo(img,mrk,txt,str,...) tlv::tlv_yfo(img,mrk,txt,#str,##__VA_ARGS__)
#define tlv_obj(img,mrk,object,str,...) tlv::tlv_for(img,mrk,object,#str,##__VA_ARGS__)
#define tlv_for(img,mrk,lambda,str,...) tlv::tlv_for(img,mrk,lambda,#str,##__VA_ARGS__)
#endif
#endif
