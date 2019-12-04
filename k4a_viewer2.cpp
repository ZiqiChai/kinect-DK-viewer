////#include <k4a/k4a.hpp>
//#include <thread>
//#include <iostream>
//#include <windows.h>
//#include <vector>
//#include <array>
//#include <stdlib.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include "pixel.h"
//#include "depthpixelcolorizer.h"
//#include "staticimageproperties.h"
//
//using namespace cv;
//using namespace std;
//
//#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//#define verify(result, error)                                                                            \
//    if(result != k4a_result_succeeded)                                                                   \
//    {                                                                                                    \
//        printf("%s \n - (file: %s, function: %s, line: %d)\n", error, __file__, __function__, __line__); \
//        exit(1);                                                                                         \
//    }  
//
//k4a::device* dev;
//thread *tids;
//cv::Mat * colorframe;
//
//void cap(k4a::device &dev_d, int i)  //普通的函数，用来执行线程
//{
//	int flag = -1;
//	int frame_count = 0;
//	dev_d.set_color_control(K4A_COLOR_CONTROL_BRIGHTNESS, K4A_COLOR_CONTROL_MODE_MANUAL,90);
//	cout << "Finished start K4A device's capture!" << endl;
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
//	//查看capture地址
//	cout << "capture adress" << &capture << endl;
//
//	while (1)
//	{
//		if (dev_d.get_capture(&capture, std::chrono::milliseconds(0)))
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
//			imshow("Kinect color frame" + std::to_string(i), colorFrame);
//			//imshow("Kinect ir frame", irFrame);
//
//			if (KEY_DOWN('S') && flag == -1)
//			{
//				frame_count++;
//				imwrite(".\\photos" + std::to_string(i) + "\\alpha" + std::to_string(frame_count) + ".png", colorFrame);
//				printf("You can take another picture1!\n");
//				flag = 0;
//			}
//			if (!KEY_DOWN('S'))
//			{
//				flag = -1;
//			}
//		}
//		if (waitKey(30) == 27 || KEY_DOWN('Q'))
//		{
//			dev_d.close();
//			break;
//		}
//	}
//}
////
//
//uint32_t init_start()
//{
//	const uint32_t devicecount = k4a::device::get_installed_count();
//	if (devicecount == 0)
//	{
//		cout << "no azure kinect dk devices detected!" << endl;
//	}
//
//	dev = new k4a::device[devicecount];
//
//	for (uint8_t deviceindex = 0; deviceindex < devicecount; deviceindex++)
//	{
//		dev[deviceindex] = k4a::device::open(deviceindex);
//		//实验赋值
//		//k4a::device& dd = dev[deviceindex];
//		//cout << "dd is" << dd << "while d is" << dev[deviceindex] << endl;
//		k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//		config.camera_fps = K4A_FRAMES_PER_SECOND_15;
//		config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//		config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
//		config.color_resolution = K4A_COLOR_RESOLUTION_720P;
//		config.synchronized_images_only = true;
//
//		if (dev[deviceindex].is_sync_in_connected())
//		{
//			cout << "subordinate device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//		}
//		else if (dev[deviceindex].is_sync_out_connected())
//		{
//			cout << "master device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//		}
//		else
//		{
//			cout << "standalone device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//		}
//
//		cout << "started opening k4a device..." << endl;
//		dev[deviceindex].start_cameras(&config);
//		cout << "finished opening k4a device!" << endl;
//	}
//	return devicecount;
//
//}
//
//int main()
//{
//
//
//	//thread th1(t1);  //实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
//	////sleep(3000);
//	//thread th2(t2);
//
//	uint32_t num = init_start();//初始化,启动相机
//	tids = new thread[num];
//	colorframe = new cv::Mat[num];
//	for (int i = 0; i < num; ++i)
//	{
//		tids[i] = thread(cap, ref(dev[i]), i);
//	}
//	for (int i = 0; i < num; ++i)
//	{
//		cout << "thread' id is " << tids[i].get_id() << endl;
//	}
//	cout << dev[0] <<endl;
//	cout << dev[1] <<endl;
//
//
//	tids[0].join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
//	tids[1].join();
//
//	//or use detach
//	//th1.detach();
//	//th2.detach();
//
//	return 0;
//}
//
//
