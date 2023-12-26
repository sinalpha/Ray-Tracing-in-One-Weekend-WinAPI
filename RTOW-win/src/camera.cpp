#include "../include/camera.h"

void camera::render(HDC hdc, const hittable& world) {
	initialize();

	for (int j = 0; j < image_height; ++j) {
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int sample = 0; sample < samples_per_pixel; ++sample) {
				ray r{ get_ray(i, j) };
				pixel_color += ray_color( r, world);
			}
			write_color(hdc, i, j, pixel_color, samples_per_pixel);
		}
	}

}

void camera::initialize() {


	center = point3(0, 0, 0);

	double focal_length{ 1.0 };
	double viewport_height{ 2.0 };
	double viewport_width{ viewport_height * (static_cast<double>(image_width) / image_height) };

	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);
	
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;
	
	point3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}


//�� ������ ���忡 �ִ� ������Ʈ�� �����ϴ��� �˻��Ѵ�.
color camera::ray_color(const ray& r, const hittable& world) const {
	hit_record rec;
	//�����ϸ� rec�� ������ ����ǰ� then�� �����.
	if (world.hit(r, interval(0, infinity), rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	double a{ 0.5 * (unit_direction.y() + 1.0) };
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
	point3 pixel_center{ pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v) };
	//�ȼ� i,j�� ���ø� �ȼ��� ��ǥ���ϱ�(��ũ��)
	point3 pixel_sample{ pixel_center + pixel_sample_square() };

	point3 ray_origin{ center };
	point3 ray_direction{ pixel_sample - ray_origin };

	return ray(ray_origin, ray_direction);
}

//�̻��� �ȼ��� ����κ��� ����-�� ������ �ű�� �ٽ� �������� 0 ~ 1������ �� ���ϱ�
vec3 camera::pixel_sample_square() const {
	double px{ -0.5 + random_double() };
	double py{ -0.5 + random_double() };

	return (px * pixel_delta_u) + (py * pixel_delta_v);
}