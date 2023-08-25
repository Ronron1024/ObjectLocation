// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

using namespace std;

int main()
{
	pcl::PointCloud<pcl::PointXYZ> cloud;

	cloud.width = 5;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.resize(cloud.width * cloud.height);

	for (auto& point : cloud)
	{
		point.x = 1024 * rand() / (RAND_MAX + 1.0f);
		point.y = 1024 * rand() / (RAND_MAX + 1.0f);
		point.z = 1024 * rand() / (RAND_MAX + 1.0f);
	}

	for (const auto& point : cloud)
	{
		std::cerr << "\t" << point.x << "\t\t" << point.y << "\t\t" << point.z << std::endl;
	}

	rs2::pipeline p;
	p.start();

	while (true)
	{
		rs2::frameset frames = p.wait_for_frames();
		rs2::depth_frame depth = frames.get_depth_frame();

		int width = depth.get_width();
		int height = depth.get_height();

		float dist_to_center = depth.get_distance(width / 2, height / 2);

		std::cout << "Facing object " << dist_to_center << " meters away.\r";
	}

	return 0;
}
