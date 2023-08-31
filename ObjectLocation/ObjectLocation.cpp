// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

int main()
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());

	rs2::pointcloud rs_cloud;

	rs2::pipeline pipeline;

	pipeline.start();

	for (int i = 0; i < 30; i++)
		pipeline.wait_for_frames();

	rs2::frameset frames = pipeline.wait_for_frames();
	rs2::depth_frame depth = frames.get_depth_frame();

	rs2::points points = rs_cloud.calculate(depth);

	cloud->resize(points.size());
	cloud->is_dense = false;

	const rs2::vertex* vertex = points.get_vertices();

	int i = 0;
	for (auto& point : *cloud)
	{
		point.x = vertex[i].x;
		point.y = vertex[i].y;
		point.z = vertex[i].z;

		point.r = 0;
		point.g = 0;
		point.b = 255;

		i++;
	}

	pcl::io::savePCDFileASCII("depthshot.pcd", *cloud);

	return 0;
}
