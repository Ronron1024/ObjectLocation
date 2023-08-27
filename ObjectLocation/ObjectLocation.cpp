// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

std::tuple<int, int, int> RGB_Texture(rs2::video_frame texture, rs2::texture_coordinate Texture_XY)
{
	// Get Width and Height coordinates of texture
	int width = texture.get_width();  // Frame width in pixels
	int height = texture.get_height(); // Frame height in pixels

	// Normals to Texture Coordinates conversion
	int x_value = std::min(std::max(int(Texture_XY.u * width + .5f), 0), width - 1);
	int y_value = std::min(std::max(int(Texture_XY.v * height + .5f), 0), height - 1);

	int bytes = x_value * texture.get_bytes_per_pixel();   // Get # of bytes per pixel
	int strides = y_value * texture.get_stride_in_bytes(); // Get line width in bytes
	int Text_Index = (bytes + strides);

	const auto New_Texture = reinterpret_cast<const uint8_t*>(texture.get_data());

	// RGB components to save in tuple
	int NT1 = New_Texture[Text_Index];
	int NT2 = New_Texture[Text_Index + 1];
	int NT3 = New_Texture[Text_Index + 2];

	return std::tuple<int, int, int>(NT1, NT2, NT3);
}

int main()
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>());
	pcl::visualization::CloudViewer viewer("Viewer");

	rs2::pointcloud rs_cloud;

	rs2::pipeline pipeline;
	rs2::config config;

	config.enable_stream(RS2_STREAM_COLOR, 848, 480, RS2_FORMAT_BGR8, 30);
	config.enable_stream(RS2_STREAM_DEPTH, 848, 480, RS2_FORMAT_Z16, 30);

	pipeline.start(config);

	for (int i = 0; i < 30; i++)
		pipeline.wait_for_frames();

	while (!viewer.wasStopped())
	{
		rs2::frameset frames = pipeline.wait_for_frames();
		rs2::depth_frame depth = frames.get_depth_frame();
		rs2::video_frame RGB = frames.get_color_frame();

		rs_cloud.map_to(RGB);
		rs2::points points = rs_cloud.calculate(depth);

		rs2::video_stream_profile stream_profile = points.get_profile().as<rs2::video_stream_profile>();

		cloud->width = static_cast<uint32_t>(stream_profile.width());
		cloud->height = static_cast<uint32_t>(stream_profile.height());
		cloud->is_dense = false;
		cloud->points.resize(points.size());

		const rs2::texture_coordinate* texture_coordinate = points.get_texture_coordinates();
		const rs2::vertex* vertex = points.get_vertices();

		std::tuple <uint8_t, uint8_t, uint8_t> rgb_color;

		for (int i = 0; i < points.size(); i++)
		{
			cloud->points[i].x = vertex[i].x;
			cloud->points[i].y = vertex[i].y;
			cloud->points[i].z = vertex[i].z;

			rgb_color = RGB_Texture(RGB, texture_coordinate[i]);

			cloud->points[i].r = std::get<2>(rgb_color);
			cloud->points[i].g = std::get<1>(rgb_color);
			cloud->points[i].b = std::get<0>(rgb_color);
		}

		viewer.showCloud(cloud);
	}

	return 0;
}
