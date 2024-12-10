#ifndef OBJ_H
#define OBJ_H
//在这里声明一个material类很关键，使得std::shared_ptr<material>mat;不会报错
class material;

class intersection
{
public:
	point3 p;
	vec3 normal;
	bool normal_face_outward;
	double t;
	std::shared_ptr<material>mat;
}; 

class object
{
public:
	material* mat;
	virtual ~object() = default;

	virtual bool intersect(const ray& r, double r_tmin, double r_tmax, intersection& rec) const = 0;

};

#endif // !OBJ_H

