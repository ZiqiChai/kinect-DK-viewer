////#include <k4a/k4a.hpp>
//#include <thread>
//#include <iostream>
//#include <windows.h>
//#include <vector>
//#include <array>
//#include <stdlib.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>
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
//thread* tids;
//thread* tids_s;
//thread tid_ss;
//k4a::device* dev;
//bool esc = false, show[2] = { false,false },h = true;
//
//void save(cv::Mat & colorFrame, int i)
//{
//	int flag = -1;
//	int frame_count = 0;
//	//cv:VideoWriter colorwriter;
//	//colorwriter.open(".\\VideoTest" + std::to_string(i) + ".avi", CAP_OPENCV_MJPEG, 15.0, colorFrame.size());
//
//	while (1)
//	{
//
//		if (show[i])
//		{
//			if (KEY_DOWN('S') && flag == -1)
//			{
//				frame_count++;
//				imwrite(".\\photos" + std::to_string(i) + "\\alpha" + std::to_string(frame_count) + ".jpg", colorFrame);
//				printf("You can take another picture1!\n");
//				flag = 0;
//			}
//			if (!KEY_DOWN('S'))
//			{
//				flag = -1;
//			}
//
//		}
//
//		if (esc)
//		{
//			break;
//		}
//	}
//}
//
//void cap(k4a::device& dev_d, cv::Mat& colorFrame, int i)  //普通的函数，用来执行线程
//{
//	//k4a::image depthImage;
//	k4a::image colorImage;
//	//k4a::image irImage;
//
//	//cv::Mat depthFrame;
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
//
//	cv:VideoWriter colorwriter;
//	while (1)
//	{
//		if (dev_d.get_capture(&capture, std::chrono::milliseconds(0)))
//		{			
//			//depthImage = capture.get_depth_image();
//			colorImage = capture.get_color_image();
//			//irImage = capture.get_ir_image();
//
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = colorImage.get_buffer();
//			//depthImage = capture.get_depth_image(); 
//			colorImage = capture.get_color_image();
//			//irImage = capture.get_ir_image();
//
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//			colorTextureBuffer = colorImage.get_buffer();
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			colorFrame = cv::Mat(1, colorImage.get_height_pixels() * colorImage.get_width_pixels(), CV_8UC1, colorTextureBuffer);
//			colorFrame = imdecode(colorFrame, IMREAD_COLOR);
//			/*cvtColor(colorFrame, colorFrame, COLOR_BGRA2BGR);*/
//			show[i] = true;
//			tids_s[i] = thread(save, ref(colorFrame), i);//保证第一时间开启显示窗
//			break;
//		}
//	}
//	colorwriter.open(".\\output-" + std::to_string(i) + ".mkv", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, colorFrame.size(), true);
//	if (!colorwriter.isOpened())
//	{
//		cout << "初始化VideoWriter失败！" << endl;
//	}
//
//
//	while (1)
//	{ 
//		if (dev_d.get_capture(&capture, std::chrono::milliseconds(0)))
//		{
//			//depthImage = capture.get_depth_image();
//			colorImage = capture.get_color_image();
//			//irImage = capture.get_ir_image();
//
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = colorImage.get_buffer();
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			show[i] = false;
//			colorFrame = cv::Mat(1,colorImage.get_height_pixels()* colorImage.get_width_pixels(), CV_8UC1, colorTextureBuffer);
//			colorFrame = imdecode(colorFrame ,IMREAD_COLOR);
//			if (colorFrame.data == NULL)
//			{
//				cout << "erro" << endl;
//			}
//			show[i] = true;
//			/*cvtColor(colorFrame, colorFrame,COLOR_BGRA2BGR);*/
//			colorwriter << colorFrame;
//
//			//colorFrame = cv::imdecode(colorTextureBuffer,cv::IMREAD_UNCHANGED);
//			//irFrame = cv::Mat(irImage.get_height_pixels(), irImage.get_width_pixels(), CV_8UC4, irTextureBuffer.data());
//			//imshow("Kinect depth map", depthFrame);
//			//imshow("Kinect ir frame", irFrame);
//
//			imshow("Kinect color frame" + std::to_string(i), colorFrame);
//			waitKey(1);
//
//		}
//		if (esc)
//		{
//			dev_d.close();
//			break;
//		}
//	}
//}
//
//
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
//		config.camera_fps = K4A_FRAMES_PER_SECOND_30;
//		config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//		config.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
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
//		dev[deviceindex].set_color_control(K4A_COLOR_CONTROL_BRIGHTNESS, K4A_COLOR_CONTROL_MODE_MANUAL, 150);//手动设置曝光
//		cout << "finished opening k4a device!" << endl;
//	}
//	return devicecount;
//
//}
//
//void keyboards()
//{
//	while (1)
//	{
//		if (KEY_DOWN('Q'))
//		{
//			esc = true;
//			break;
//		}
//		else
//		{
//			esc = false;
//		}
//		//Sleep(3);
//	}
//
//}
//
//int main()
//{
//	//主函数所用变量
//
//	cv::Mat* colorframe;
//
//
//	uint32_t num = init_start();//初始化,启动相机
//	tids = new thread[num];
//	tids_s = new thread[num];
//	colorframe = new cv::Mat[num];
//	tid_ss = thread(keyboards);
//	for (int i = 0; i < num; ++i)
//	{
//		tids[i] = thread(cap, ref(dev[i]), ref(colorframe[i]),i);
//		
//	}
//	for (int i = 0; i < num; ++i)
//	{
//		cout << "thread' id is " << tids[i].get_id() << endl;
//		cout << "threads' id is " << tids_s[i].get_id() << endl;
//	}
//
//
//	//保证子线程停止
//	tids[0].join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
//	tids[1].join();
//	tids_s[0].join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
//	tids_s[1].join();
//	tid_ss.join();
//	//or use detach
//	//th1.detach();
//	//th2.detach();
//
//	return 0;
//}
//
//
