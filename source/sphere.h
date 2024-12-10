#ifndef SEPHERE_H
#define SEPHERE_H
#include"object.h"
class sphere:public object
{
public:
	sphere(){}
    sphere(point3 c, double r, std::shared_ptr<material>m) :radius(r), center(c), mat(m) {}
	bool intersect(const ray& r, double r_tmin, double r_tmax, intersection& rec)const override
	{
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;
        auto sqrtd = std::sqrt(discriminant);
        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= r_tmin || r_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= r_tmin || r_tmax <= root)
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        //设置法线方向始终指向与入射光线相反方向
		vec3 outward_normal = (rec.p - center) / radius;
        if (dot(r.direction(), outward_normal) > 0)
        {
            rec.normal = -outward_normal;
            rec.normal_face_outward = false;
        } 
        else
        {
            rec.normal = outward_normal;
            rec.normal_face_outward = true;
        } 
        rec.mat = mat;
        return true;
	}
private:
	double radius;
	point3 center;
    std::shared_ptr<material> mat;
};



#endif
