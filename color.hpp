#ifndef COLOR_HPP
#define COLOR_HPP

#include "math.hpp"
struct Color {
    float r, g, b,a;
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f,float a = 1.0f) : r(r), g(g), b(b),a(a) {}

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b,a + other.a);
    }
     Color operator-(const Color& other) const {
        return Color(r - other.r, g - other.g, b - other.b,a - other.a);
    }
     Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar,a * scalar);
    }
     Color operator/(float scalar) const {
        return Color(r / scalar, g / scalar, b / scalar,a / scalar);
    }
     Color operator-() const {
        return Color(-r, -g, -b,-a);
    }
     bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
     bool operator!=(const Color& other) const {
        return !(*this == other);
    }
    friend Color operator*(float s,const Color& c){
        return  c*s;
    }

    Color clamp(){
        return Color(
            std::max(0.0f,std::min(1.0f,r)),
            std::max(0.0f,std::min(1.0f,g)),
            std::max(0.0f,std::min(1.0f,b)),
            std::max(0.0f,std::min(1.0f,a))
        );
    }
    unsigned char toByte(float v){
        return static_cast<unsigned char>(v*255.0f);
    }
    unsigned int toRGBA(){
        unsigned char R=toByte(clamp().r);
        unsigned char G=toByte(clamp().g);
        unsigned char B=toByte(clamp().b);
        unsigned char A=toByte(clamp().a);
        return (R<<24)|(G<<16)|(B<<8)|A;
    }
    
};


#endif