// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

using namespace std;

int main()
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::visualization::CloudViewer viewer("Viewer");

	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("depthshot.pcd", *cloud) == -1)
	{
		PCL_ERROR("Could not open file.");
		return 1;
	}

	std::cout << *cloud << std::endl;

	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

	pcl::SACSegmentation<pcl::PointXYZRGB> seg;
	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setDistanceThreshold(0.01);
	seg.setInputCloud(cloud);

	seg.segment(*inliers, *coefficients);

	if (inliers->indices.size() == 0)
	{
		PCL_ERROR("Could not estimate a planar model.");
		return 1;
	}

	std::cout << "Model inliers: " << inliers->indices.size() << std::endl;

	std::cout << *coefficients << std::endl;

	std::uint8_t r = 0, g = 255, b = 0;
	std::uint32_t rgb = (std::uint32_t)r << 16 | (std::uint32_t) g << 8 | (std::uint32_t)b;
	for (const auto& idx : inliers->indices)
		cloud->points[idx].rgb = *reinterpret_cast<float*>(&rgb);

	viewer.showCloud(cloud);
	while (!viewer.wasStopped());

	return 0;
}
