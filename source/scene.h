#ifndef SCENE_H
#define SCENE_H
#include"objectlist.h"
#include"material.h"
//需要指定的参数有：img_width  aspect_ratio   viewport_distance  fov samples_per_pixel  max_depth  
//lookfrom  lookat  vup
class Scene
{
public:

	int img_width, img_height;
	double viewport_width, viewport_height;
	double fov;
	double viewport_distance;
	double aspect_ratio;
	//camera_from camera_at这两个参数主要用来指明相机看向哪个方向,lookat并不表示viewport的位置（由viewport_distance表示）
	point3 lookfrom;
	point3 lookat;
	vec3 vup; //镜头竖直方向

	//depth of field
	double depth_field_angle = 0;

	int samples_per_pixel;

	int max_depth;

	ray get_ray(int i, int j)
	{
		double random_U = random_double(-0.5, 0.5), random_V = random_double(-0.5, 0.5);
		point3 pixelpos = pixel00_loc + delta_v * (i + random_U) + delta_u * (j + random_V);
		point3 camera = (depth_field_angle >= 0) ? depth_field_sample() : lookfrom;
		vec3 dir = unit_vector(pixelpos - camera);
		return ray(camera, dir);
	}
	point3 depth_field_sample()
	{
		vec3 random = random_in_unit_disk();
		return lookfrom + random[0] * depth_field_u + random[1] * depth_field_v;
	}
	void render(const objectlist& objects,const char *fname)
	{
		initialize();
		std::ofstream file;
		file.open(fname);
		file << "P3\n" << img_width << ' ' << img_height << "\n" << "255\n";

		for (int i = 0; i < img_height; i++)
		{
			for (int j = 0; j < img_width; j++)
			{
				color pixel_color(0, 0, 0);
				//发出多条光线主要是为了反走样，不过由于漫反射是通过随机取反射方向，多次采样也有助于提高渲染稳定性
				for (int times = 0; times < samples_per_pixel; times++)
				{
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, objects);
				}
				pixel_color /= samples_per_pixel;
				write_color(file, pixel_color);
			}
		}
	}
	
private:

	point3 center;
	point3 viewport_upper_left;
	point3 pixel00_loc;

	vec3 delta_u, delta_v;

	vec3 depth_field_u, depth_field_v;
	double depth_field_radius;

	vec3 u, v, w;   // Camera frame basis vectors

	//当需要提前设置的参数都设置好后，调用render成员函数，render会调用initialize初始化其他的参数
	void initialize()
	{
		img_height = int(img_width / aspect_ratio);
		img_height = (img_height < 1) ? 1 : img_height; //小细节，避免img_height小于一个像素
		viewport_height = 2 * viewport_distance * std::tan(degrees_to_radians(fov / 2));
		viewport_width = viewport_height * img_width / img_height;

		//Camera frame basis vectors
		center = lookfrom;
		w = unit_vector(lookfrom - lookat);
		v = unit_vector(vup);
		u = unit_vector(cross(v, w));

		delta_u = viewport_width / img_width * u;
		delta_v = viewport_height / img_height * (-v);
		
		viewport_upper_left = center -w* viewport_distance - u * viewport_width / 2 + v * viewport_height/2;
		pixel00_loc = viewport_upper_left + 0.5 * delta_u + 0.5 * delta_v;

		depth_field_radius = std::tan(degrees_to_radians(depth_field_angle / 2)) * viewport_distance;
		depth_field_u = depth_field_radius * u;
		depth_field_v = depth_field_radius * v;

	}
	
	color ray_color(const ray& r, int depth, const objectlist& objects) const
	{
		if (depth <= 0)
			return color(0, 0, 0);
		intersection rec;
		if (objects.intersect(r, 0.001, infinity, rec))
		{
			color attenuation;
			ray scattered;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return ray_color(scattered, depth - 1, objects) * attenuation;
			else
				return color(0, 0, 0);
		}
		//若没有发生碰撞，则根据光线方向向量差分得到一个颜色的返回值
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
	
	

};


#endif
