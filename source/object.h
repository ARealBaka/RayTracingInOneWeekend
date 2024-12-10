#ifndef OBJ_H
#define OBJ_H
//����������һ��material��ܹؼ���ʹ��std::shared_ptr<material>mat;���ᱨ��
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

