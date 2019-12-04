//#include <k4a/k4a.hpp>
//#include <thread>
//#include <iostream>
//#include <windows.h>
//#include <vector>
//#include <array>
//#include <stdlib.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include "Pixel.h"
//#include "DepthPixelColorizer.h"
//#include "StaticImageProperties.h"
//
//using namespace cv;
//using namespace std;
//
//#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//#define VERIFY(result, error)                                                                            \
//    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
//    {                                                                                                    \
//        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
//        exit(1);                                                                                         \
//    }  
//
//void t1()  //普通的函数，用来执行线程
//{
//	int flag = -1;
//	int frame_count = 0;
//	const uint32_t deviceCount = k4a::device::get_installed_count();
//	if (deviceCount == 0)
//	{
//		cout << "No Azure Kinect DK devices detected!" << endl;
//	}
//
//	k4a::device dev = k4a::device::open(1);
//
//	k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//	config.camera_fps = K4A_FRAMES_PER_SECOND_15;
//	config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//	config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
//	config.color_resolution = K4A_COLOR_RESOLUTION_720P;
//	config.synchronized_images_only = true;
//		
//	if (dev.is_sync_in_connected())
//	{
//		cout << "Subordinate device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//	}
//	else if (dev.is_sync_out_connected())
//	{
//		cout << "Master device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//	}
//	else
//	{
//		cout << "Standalone device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//	}
//
//	cout << "Started opening K4A device..." << endl;
//	dev.start_cameras(&config);
//	dev.set_color_control(K4A_COLOR_CONTROL_BRIGHTNESS, K4A_COLOR_CONTROL_MODE_MANUAL,90);
//	cout << "Finished opening K4A device!" << endl;
//
//	
//
//	//k4a::image depthImage;
//	k4a::image colorImage;
//	//k4a::image irImage;
//
//	//cv::Mat depthFrame;
//	cv::Mat colorFrame;
//	//cv::Mat irFrame;
//
//	//std::vector<Pixel> depthTextureBuffer;
//	//std::vector<Pixel> irTextureBuffer;
//	uint8_t* colorTextureBuffer;
//
//	k4a::capture capture;
//
//	while (1)
//	{
//		if (dev.get_capture(&capture, std::chrono::milliseconds(0)))
//		{
//			//depthImage = capture.get_depth_image();
//			colorImage = capture.get_color_image();
//			//irImage = capture.get_ir_image();
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = colorImage.get_buffer();
//
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			colorFrame = cv::Mat(colorImage.get_height_pixels(), colorImage.get_width_pixels(), CV_8UC4, colorTextureBuffer);
//			//irFrame = cv::Mat(irImage.get_height_pixels(), irImage.get_width_pixels(), CV_8UC4, irTextureBuffer.data());
//
//			//imshow("Kinect depth map", depthFrame);
//			imshow("Kinect color frame", colorFrame);
//			//imshow("Kinect ir frame", irFrame);
//
//			if (KEY_DOWN('S') && flag == -1)
//			{
//				frame_count++;
//				imwrite(".\\a\\alpha" + std::to_string(frame_count) + ".png", colorFrame);
//				printf("You can take another picture1!\n");
//				flag = 0;
//			}
//			if (!KEY_DOWN('S'))
//			{
//				flag = -1;
//			}
//		}
//		if (waitKey(30) == 27 || waitKey(30) == 'q')
//		{
//			dev.close();
//			break;
//		}
//	}
//	
//}
//
//void t2()
//{
//	int flag = -1;
//	int frame_count = 0;
//	const uint32_t deviceCount = k4a::device::get_installed_count();
//	if (deviceCount == 0)
//	{
//		cout << "No Azure Kinect DK devices detected!" << endl;
//	}
//
//	k4a::device dev = k4a::device::open(0);
//
//	k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//	config.camera_fps = K4A_FRAMES_PER_SECOND_15;
//	config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//	config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
//	config.color_resolution = K4A_COLOR_RESOLUTION_720P;
//	config.synchronized_images_only = true;
//
//	if (dev.is_sync_in_connected())
//	{
//		cout << "Subordinate device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//	}
//	else if (dev.is_sync_out_connected())
//	{
//		cout << "Master device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//	}
//	else
//	{
//		cout << "Standalone device detected!\n" << endl;
//		config.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//	}
//
//	cout << "Started opening K4A device..." << endl;
//	dev.start_cameras(&config);
//	dev.set_color_control(K4A_COLOR_CONTROL_BRIGHTNESS, K4A_COLOR_CONTROL_MODE_MANUAL, 90);
//	cout << "Finished opening K4A device!" << endl;
//
//	//k4a::image depthImage;
//	k4a::image colorImage;
//	//k4a::image irImage;
//
//	//cv::Mat depthFrame;
//	cv::Mat colorFrame;
//	//cv::Mat irFrame;
//
//	//std::vector<Pixel> depthTextureBuffer;
//	//std::vector<Pixel> irTextureBuffer;
//	uint8_t* colorTextureBuffer;
//
//	k4a::capture capture;
//
//	while (1)
//	{
//		if (dev.get_capture(&capture, std::chrono::milliseconds(0)))
//		{
//			//depthImage = capture.get_depth_image();
//			colorImage = capture.get_color_image();
//			//irImage = capture.get_ir_image();
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = colorImage.get_buffer();
//
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			colorFrame = cv::Mat(colorImage.get_height_pixels(), colorImage.get_width_pixels(), CV_8UC4, colorTextureBuffer);
//			//irFrame = cv::Mat(irImage.get_height_pixels(), irImage.get_width_pixels(), CV_8UC4, irTextureBuffer.data());
//
//			//imshow("Kinect depth map", depthFrame);
//			imshow("Kinect color frame0", colorFrame);
//			//imshow("Kinect ir frame", irFrame);
//
//			if (KEY_DOWN('S') && flag == -1)
//			{
//				frame_count++;
//				imwrite(".\\b\\beta" + std::to_string(frame_count) + ".png", colorFrame);
//				printf("You can take another picture2!\n");
//				flag = 0;
//			}
//			if (!KEY_DOWN('S'))
//			{
//				flag = -1;
//			}
//			//printf("%d", flag);
//		}
//		if (waitKey(30) == 27 || waitKey(30) == 'q')
//		{
//			dev.close();
//			break;
//		}
//	}
//	
//}
//
//void init_start()
//{
//	const uint32_t deviceCount = k4a::device::get_installed_count();
//	if (deviceCount == 0)
//	{
//		cout << "No Azure Kinect DK devices detected!" << endl;
//	}
//	k4a::device dev[4];
//	for (uint8_t deviceIndex = 0; deviceIndex < deviceCount; deviceIndex++)
//	{
//		dev[deviceIndex] = k4a::device::open(deviceIndex);
//
//		k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//		config.camera_fps = K4A_FRAMES_PER_SECOND_15;
//		config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//		config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
//		config.color_resolution = K4A_COLOR_RESOLUTION_720P;
//		config.synchronized_images_only = true;
//
//		if (dev[deviceIndex].is_sync_in_connected())
//		{
//			cout << "Subordinate device detected!\n" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//		}
//		else if (dev[deviceIndex].is_sync_out_connected())
//		{
//			cout << "Master device detected!\n" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//		}
//		else
//		{
//			cout << "Standalone device detected!\n" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//		}
//
//		cout << "Started opening K4A device..." << endl;
//		dev[deviceIndex].start_cameras(&config);
//		cout << "Finished opening K4A device!" << endl;
//	}
//	
//}
//
//int main()
//{
//	cv::Mat colorFrame1;
//	cv::Mat colorFrame2;
//
//	thread th1(t1);  //实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
//	//Sleep(3000);
//	thread th2(t2);
//
//	//init_start();//初始化,启动相机
//
//	th1.join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
//	th2.join();
//
//	//or use detach
//	//th1.detach();
//	//th2.detach();
//
//	return 0;
//}
