#ifndef OBJLIST_H
#define OBJLIST_H
#include"object.h"
#include<vector>
class objectlist :public object
{
public:
	objectlist(){}
	objectlist(std::shared_ptr<object> obj) { add(obj); }

	std::vector<std::shared_ptr<object> >objects;

	void add(std::shared_ptr<object> p){ objects.push_back(p); }
	void clear() { objects.clear(); }

	bool intersect(const ray&r,double r_tmin,double r_tmax,intersection& rec)const override
	{
		double tmax = r_tmax;
		intersection temp;
		bool hitted = false;
		for (const auto& it : objects)
		{
			if (it->intersect(r, r_tmin, tmax, temp))
			{
				tmax = temp.t;
				hitted = true;
				rec = temp;
			}
		}
		return hitted;
	}
};

#endif // !OBJLIST_H


