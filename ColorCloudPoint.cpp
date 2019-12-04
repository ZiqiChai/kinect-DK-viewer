//#include <k4a/k4a.hpp>
//#include <iostream>
//#include <vector>
//#include <array>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//#include <pcl/io/pcd_io.h>
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
//#include <pcl/visualization/pcl_visualizer.h>
//
//#include "Pixel.h"
//#include "DepthPixelColorizer.h"
//#include "StaticImageProperties.h"
//#include "k4a_grabber.h"
//
//using namespace std;
//using namespace cv;
//using namespace boost;
//using namespace pcl;
//
//typedef pcl::PointXYZRGBA PointType;
//
//int main(int argc, char **argv)
//{
//	const uint32_t deviceCount = k4a::device::get_installed_count();
//	if (deviceCount == 0)
//	{
//		cout << "No Azure Kinect DK devices detected!" << endl;
//	}
//
//	// PCL Visualizer
//	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
//		new pcl::visualization::PCLVisualizer("Point Cloud Viewer"));
//	viewer->setCameraPosition(0.0, 0.0, -2500.0, 1.0, -1.0, 1.0);
//
//	// Point Cloud
//	pcl::PointCloud<PointType>::ConstPtr cloud;
//
//	// Retrieved Point Cloud Callback Function
//	boost::mutex mutex;
//	boost::function<void(const pcl::PointCloud<PointType>::ConstPtr&)> function = 
//		[&cloud, &mutex](const pcl::PointCloud<PointType>::ConstPtr& ptr)
//	{
//		boost::mutex::scoped_lock lock(mutex);
//
//		// Point Cloud Processing
//		cloud = ptr->makeShared();
//
//	};
//
//	// KinectAzureDKGrabber
//	boost::shared_ptr<pcl::Grabber> grabber =
//		boost::make_shared<pcl::KinectAzureDKGrabber>(0, K4A_DEPTH_MODE_NFOV_UNBINNED,
//			K4A_IMAGE_FORMAT_COLOR_BGRA32, K4A_COLOR_RESOLUTION_720P);
//
//	// Register Callback Function
//	boost::signals2::connection connection = grabber->registerCallback(function);
//
//	// Start Grabber
//	grabber->start();
//
//	while (!viewer->wasStopped())
//	{
//		// Update Viewer
//		viewer->spinOnce();
//		boost::mutex::scoped_try_lock lock(mutex);
//		if (lock.owns_lock() && cloud)
//		{
//			// Update Point Cloud
//			if (!viewer->updatePointCloud(cloud, "cloud"))
//			{
//				viewer->addPointCloud(cloud, "cloud");
//			}
//		}
//	}
//
//	// Stop Grabber
//	grabber->stop();
//
//	// Disconnect Callback Function
//	if (connection.connected())
//	{
//		connection.disconnect();
//	}
//	return 0;
//}