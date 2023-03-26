#include "../include/Ray.hpp"

Ray::Ray(const Point3& origin, const Vec3& direction): orig(origin), dir(direction) {}

bool Ray::operator==(const Ray& ray) const 
{
    return (((orig.getX() == ray.origin().getX()) &
     (orig.getY() == ray.origin().getY()) &
     (orig.getZ() == ray.origin().getZ())) & (dir == ray.direction())) ;
}