#ifndef COLOR3_H
#define COLOR3_H
#include "vec3.h"
#include<fstream>
#include<iostream>

using color = vec3;
inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);
	return 0;
}
void write_color(std::ofstream& file, color pixel_color)
{
	double ir = linear_to_gamma(pixel_color.x());
	double ig = linear_to_gamma(pixel_color.y());
	double ib = linear_to_gamma(pixel_color.z());
	int ir_int = int(255.999 * ir);
	int ig_int = int(255.999 * ig);
	int ib_int = int(255.999 * ib);
	file << ir_int << " " << ig_int << " " << ib_int << "\n";
}
#endif