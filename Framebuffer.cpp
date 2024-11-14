#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, double aspectRatio)
    : m_width(width), m_height(width / 2 / aspectRatio), m_aspectRatio(aspectRatio) {
    initialize();
}

Framebuffer::~Framebuffer() {
    clear();
}

std::string Framebuffer::getAnsiString(const Vec3& color) {
    Vec3 scaledColor = {
        clamp(color.x * 255.0, 0.0, 255.0),
        clamp(color.y * 255.0, 0.0, 255.0),
        clamp(color.z * 255.0, 0.0, 255.0)
    };
    
    std::string result = "\033[48;2;" +
        std::to_string(static_cast<int>(scaledColor.x)) + ";" +
        std::to_string(static_cast<int>(scaledColor.y)) + ";" +
        std::to_string(static_cast<int>(scaledColor.z)) + "m";
    
    return result;
}

void Framebuffer::present() {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            Vec3 pixelColor = m_framebuffer[y * m_width + x];
            std::cout << getAnsiString(pixelColor) << ' ';
        }
        
        std::cout << "\033[0m\n";
    }
}

void Framebuffer::clearConsole() {
    std::cout << "\033[2J\033[1;1H";
}

void Framebuffer::setPixel(int x, int y, const Vec3& color) {
    m_framebuffer[y * m_width + x] = color;
}

void Framebuffer::clear() {
    m_framebuffer.clear();
}

int Framebuffer::getWidth() const {
    return m_width;
}

int Framebuffer::getHeight() const {
    return m_height;
}

double Framebuffer::getAspectRatio() const {
    return m_aspectRatio;
}

void Framebuffer::initialize() {
    int amountOfPixels = m_width*m_height;
    m_framebuffer.resize(amountOfPixels);
}