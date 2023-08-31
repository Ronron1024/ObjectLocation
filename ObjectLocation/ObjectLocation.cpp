// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

using namespace std;

int main()
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());

	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("depthshot.pcd", *cloud) == -1)
	{
		PCL_ERROR("Could not open file.");
		return 1;
	}

	std::cout << *cloud << std::endl;

	return 0;
}
