// ObjectLocation.cpp : Defines the entry point for the application.
//

#include "ObjectLocation.h"

using namespace std;

int main()
{
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
