#include "Engine.h"

#include <iostream>
#include <vector>

Vec3 getIntersectionPoint(const Ray& ray, double t) {
    return ray.origin + ray.direction*t;
}

Vec3 getReflection(const Vec3& direction, const Vec3& normal) {
    return direction - 2.0 * dot(direction, normal) * normal;
}

bool isPointInShadow(const Vec3& point, const Vec3& lightOrigin, const std::vector<Sphere>& spheres, const Vec3& normal) {
    Vec3 lightDirection = normalize(lightOrigin - point);
    
    Ray shadowRay;
    shadowRay.origin = point + lightDirection * 1e-3;
    shadowRay.direction = lightDirection;
    
    for (const Sphere& sphere : spheres) {
        double t = sphere.intersect(shadowRay);
        if (t > 0.0) {
            return true;
        }
    }
    
    return false;
}

Vec3 getRayColor(const Ray& ray, const std::vector<Sphere>& spheres, const Light& light) {
    Vec3 rayColor = { 1.0, 1.0, 1.0 };
    
    double closestT = std::numeric_limits<double>::max();
    int closestSphereIndex = -1;
    for (int i = 0; i < spheres.size(); ++i) {
        double t = spheres[i].intersect(ray);
        if (t < closestT && t > 0.0) {
            closestT = t;
            closestSphereIndex = i;
        }
    }
    
    if (closestSphereIndex != -1) {
        Sphere closestSphere = spheres[closestSphereIndex];
        
        Vec3 intersectionPoint = getIntersectionPoint(ray, closestT);
        Vec3 normal = closestSphere.getNormal(intersectionPoint);
        Vec3 viewDirection = normalize(ray.origin - intersectionPoint);
        
        Vec3 lightShadowPosition = { -light.origin.x, light.origin.y, -light.origin.z };
        
        Vec3 ambientColor = { 0.1, 0.1, 0.1 };
        
        if (!closestSphere.material.diffuse) {
            rayColor = closestSphere.material.albedo;
            if (isPointInShadow(intersectionPoint, lightShadowPosition, spheres, normal)) {
                rayColor = closestSphere.material.albedo * 0.3 + ambientColor;
            }
            return rayColor;
        }
        
        Vec3 lightDirection = normalize(light.origin - intersectionPoint);
        double diffuse = std::max(dot(normal, lightDirection), 0.0);
        Vec3 diffuseColor = diffuse * closestSphere.material.albedo * light.intensity;
        
        Vec3 reflectionDirection = normalize(getReflection(-lightDirection, normal));
        double specular = std::pow(std::max(dot(viewDirection, reflectionDirection), 0.0), 32);
        Vec3 specularColor = specular * light.intensity;
        
        rayColor = diffuseColor + specularColor + ambientColor;
    }
    
    return rayColor;
}

void renderScene(Framebuffer& framebuffer, Camera& camera, const Light& light, const std::vector<Sphere>& spheres) {
    for (int y = 0; y < framebuffer.getHeight(); ++y) {
        for (int x = 0; x < framebuffer.getWidth(); ++x) {
            Vec3 pixelColor = { 0.0, 0.0, 0.0 };
            for (int s = 0; s < camera.sampleSize; ++s) {
                double xOffset = (camera.sampleSize) ? randomDouble() : 0.0;
                double yOffset = (camera.sampleSize) ? randomDouble() : 0.0;
                
                double u = (static_cast<double>(x) + xOffset) / (framebuffer.getWidth() - 1) * 2.0 - 1.0;
                double v = 1.0 - ((static_cast<double>(y) + yOffset) / (framebuffer.getHeight() - 1)) * 2.0;
                
                Ray ray;
                ray.origin = camera.position;
                ray.direction = camera.lookAt(u, v, framebuffer.getAspectRatio());
                
                pixelColor = pixelColor + getRayColor(ray, spheres, light);
            }
            
            pixelColor = clamp(pixelColor / camera.sampleSize, 0.0, 1.0);
            
            framebuffer.setPixel(x, y, pixelColor);
        }
    }
}

int main() {
    Framebuffer framebuffer(200, 16.0 / 9.0);
    
    Light light;
    light.origin = { 0.0, 1.0, 0.0 };
    light.intensity = { 1.0, 1.0, 1.0 };
    
    std::vector<Sphere> spheres {
        { { 0.0, 0.0, 0.0 }, 1.0, { { 1.0, 0.0, 0.0 }, true } },
        { { 0.0, -10001.0, 0.0 }, 10000.0, { { 1.0, 1.0, 1.0 }, false } }
    };
    
    Camera camera;
    camera.position = { 0.0, 0.5, 3.0 };
    camera.targetPosition = { spheres[0].origin };
    camera.sampleSize = 4;
    
    double angle = 0.0;
    double rotationRadius = 3.0;
    
    while (true) {
        light.origin.x = sin(angle) * rotationRadius;
        light.origin.z = cos(angle) * rotationRadius;
        angle += 0.05;
        
        renderScene(framebuffer, camera, light, spheres);
        framebuffer.present();
        framebuffer.clear();
        framebuffer.clearConsole();
    }
    
    return 0;
}