#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include"object.h"
#include<memory>
#include<vector>

using std::shared_ptr;
using std::make_shared;

class object_list : public object{
public:
	std::vector<shared_ptr<object>> objects;//list of objects
public:
	object_list(){}
	object_list(shared_ptr<object> obj){
		objects.push_back(obj);
	}

	void clear(void){ objects.clear(); }
	void add(shared_ptr<object> obj){objects.push_back(obj);}

	virtual bool hit(const ray& r , double t_min , double t_max , hit_record& record) const override;
};

bool object_list :: hit (const ray& r , double t_min , double t_max , hit_record& record) const{

	/*
		How it works? -- 
		For each ray check if the ray hits ANY object in the object_list(in particular if any ray hits any sphere in world) , then 
			set hit_anything to high
			update closest object to the pixel

		'record' is hit_record of ray and closest object to that pixel	
	*/
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	
	for(const auto &obj : objects){

		//if ray r hits any obj , closer than previous closest obj , store information in temp_rec
		if(obj->hit(r , t_min , closest_so_far , temp_rec)){
			hit_anything = true;
			closest_so_far = temp_rec.t;// update closest_so_far if ray hits next object at a distance closer than closest_so_far
			record = temp_rec; // also update record with the hit_record of new obj (which is closer)
		}
	}

	return hit_anything;
}

#endif