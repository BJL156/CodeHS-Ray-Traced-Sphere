#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Vec3.h"

#include <vector>
#include <iostream>

class Framebuffer {
public:
    Framebuffer(int width, double aspectRatio);
    ~Framebuffer();
    
    std::string getAnsiString(const Vec3& color);
    void present();
    void clearConsole();
    
    void setPixel(int x, int y, const Vec3& color);
    void clear();
    
    int getWidth() const;
    int getHeight() const;
    double getAspectRatio() const;
private:
    void initialize();
    
    int m_width;
    int m_height;
    double m_aspectRatio;
    std::vector<Vec3> m_framebuffer;
};

#endif