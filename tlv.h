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
#include <cmath>
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
    template<typename ...Args> bool tlv_hdr(svg *img,std::string str,Args... args);
    template<typename ...Args> bool tlv_drw(svg *img,std::string str,Args... args);
    template<typename ...Args> bool tlv_opn(svg *img,std::string str,Args... args);
    bool tlv_cls(svg *img,std::string str);
    template<typename ...Args> bool tlv_yfo(svg *img,std::string marker,std::string content,std::string str,Args... args);
    template<typename ...Args> bool tlv_obj(svg *img,std::string marker,svg *object,std::string str,Args... args);
    template<typename ...Args,typename lambda> bool tlv_for(svg *img,std::string marker,lambda x,std::string str,Args... args);
    std::string rgb(unsigned char r,unsigned char g,unsigned char b);
    std::string hsv(double h,double s,double v);
}

tlv::svg::svg()
{
    width=height=1e3;
    tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
}

tlv::svg::svg(double x)
{
    width=height=x;
    tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
}

tlv::svg::svg(double w,double h)
{
    width=w,height=h;
    tlv_hdr(this,"width=\"%g\" height=\"%g\"",width,height);
}

bool tlv::svg::write(std::string fout_name)
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

void tlv::svg::prepend(svg *img)
{
    data.insert(data.begin(),img->data.begin(),img->data.end());
}

void tlv::svg::append(svg *img)
{
    data.insert(data.end(),img->data.begin(),img->data.end());
}

void tlv::svg::import(svg *img)
{
    data=img->data;
}

void tlv::svg::clear()
{
    data.clear();
}

template<typename ...Args> bool tlv::tlv_hdr(svg *img,std::string str,Args... args)
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

template<typename ...Args> bool tlv::tlv_drw(svg *img,std::string str,Args... args)
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

template<typename ...Args> bool tlv::tlv_opn(svg *img,std::string str,Args... args)
{
    const std::string svd="<"+str+">";
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

bool tlv::tlv_cls(svg *img,std::string str)
{
    const std::string svd="</"+str+">";
    img->data.push_back(svd);
    return true;
}

template<typename ...Args> bool tlv::tlv_yfo(svg *img,std::string marker,std::string content,std::string str,Args... args)
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

template<typename ...Args> bool tlv::tlv_obj(svg *img,std::string marker,svg *object,std::string str,Args... args)
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

template<typename ...Args,typename lambda> bool tlv::tlv_for(svg *img,std::string marker,lambda x,std::string str,Args... args)
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

std::string tlv::rgb(unsigned char r,unsigned char g,unsigned char b)
{
    char cstr[3];
    std::string retval=std::string("#");
    snprintf(cstr,3,"%02X",r);
    retval+=std::string(cstr);
    snprintf(cstr,3,"%02X",g);
    retval+=std::string(cstr);
    snprintf(cstr,3,"%02X",b);
    retval+=std::string(cstr);
    return retval;
}

std::string tlv::hsv(double h,double s,double v)
{
    h/=60.0,v*=256.0;
    if(v>255.0) v=255.0;
    const double f=h-std::floor(h),p=v*(1.0-s),q=v*(1.0-s*f),t=v*(1.0-(1.0-f)*s);
    switch((int)h)
    {
        case 0: return tlv::rgb(v,t,p);
        case 1: return tlv::rgb(q,v,p);
        case 2: return tlv::rgb(p,v,t);
        case 3: return tlv::rgb(p,q,v);
        case 4: return tlv::rgb(t,p,v);
        case 5: return tlv::rgb(v,p,q);
        default: return tlv::rgb(0,0,0);
    }
}

#define tlv_hdr(img,str,...) tlv::tlv_hdr(img,#str,##__VA_ARGS__)
#define tlv_drw(img,str,...) tlv::tlv_drw(img,#str,##__VA_ARGS__)
#define tlv_opn(img,str,...) tlv::tlv_opn(img,#str,##__VA_ARGS__)
#define tlv_cls(img,str,...) tlv::tlv_cls(img,#str,##__VA_ARGS__)
#define tlv_yfo(img,mrk,txt,str,...) tlv::tlv_yfo(img,mrk,txt,#str,##__VA_ARGS__)
#define tlv_obj(img,mrk,object,str,...) tlv::tlv_obj(img,mrk,object,#str,##__VA_ARGS__)
#define tlv_for(img,mrk,lambda,str,...) tlv::tlv_for(img,mrk,lambda,#str,##__VA_ARGS__)

#endif
#endif
