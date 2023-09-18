# Branches

What are the purpose of each branches ?

## Main
Live stream camera depth canal, rendered using PCL CloudViewer.

You can read the CMakeLists.txt to understand how to link PCL and RealSens libraries.

## Depthshot
Save a depth screenshot in the file depthshot.pcd.

The file can latter be used to test algorithms.

## PCL
Base code to ensure that PCL is correctly installed.

## RealSense
Base code to ensure that RealSens is correctly installed.

## PlaneDetection
Detect a plane in the previously saved depthshot.pcd file.

# TODO
- Check if the plane detection algorithm is functionning with different images.
- Extract work object position (Euclidean Cluster Extraction)
- Convert work object position into rs003n frame of reference
- Integrate the program with the rs003n driver to send command to the robot

# Useful links
## PCL
[Main website](https://pointclouds.org/)

[GitHub repo](https://github.com/PointCloudLibrary/pcl)

[Documentation](https://pcl-tutorials.readthedocs.io/)

[CMake configuration](https://pcl.readthedocs.io/projects/tutorials/en/master/using_pcl_pcl_config.html)

[Plane detection](https://pcl.readthedocs.io/projects/tutorials/en/master/planar_segmentation.html#planar-segmentation)

[Cluster extraction](https://pcl.readthedocs.io/projects/tutorials/en/master/cluster_extraction.html#cluster-extraction)

## RealSense
[GitHub repo](https://github.com/IntelRealSense/librealsense)

[Documentation](https://dev.intelrealsense.com/docs)

[PCL Wrapper](https://dev.intelrealsense.com/docs/pcl-wrapper)