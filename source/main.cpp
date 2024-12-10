#include "global.h"

#include "scene.h"
#include "object.h"
#include "objectlist.h"
#include "material.h"
#include "sphere.h"

int main(int argc,char* argv[])
{
	Scene scene;
	scene.aspect_ratio = 16.0/9.0;
	scene.img_width = 1200;
	scene.samples_per_pixel = 500;
	scene.max_depth = 50;
	scene.viewport_distance = 10;
	scene.fov = 20;
	scene.lookfrom = point3(13, 2, 3);
	scene.lookat = point3(0, 0, 0);
	scene.vup = vec3(0, 1, 0);
	scene.depth_field_angle = 0.6;

	objectlist objects;
    auto ground_material = make_shared<diffuse>(color(0.5, 0.5, 0.5));
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<diffuse>(albedo);
                    objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    objects.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<diffuse>(color(0.4, 0.2, 0.1));
    objects.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    objects.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	scene.render(objects,argv[1]);
	return 0;
}