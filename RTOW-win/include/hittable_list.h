#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

//포함하고 있는 관계인데 왜 상속을 받지?
class hittable_list : public hittable{
public:
	std::vector<shared_ptr<hittable>> objects;

	hittable_list();
	hittable_list(shared_ptr<hittable>);

	void clear();

	void add(shared_ptr<hittable>);
	bool hit(const ray& r, double ray_tmin, double ray_tamx, hit_record& rec) const;
};

#endif