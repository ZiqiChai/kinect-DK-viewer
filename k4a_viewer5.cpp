//#include <k4a/k4a.hpp>
//#include <thread>
//#include <iostream>
//#include <windows.h>
//#include <vector>
//#include <array>
//#include <stdlib.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>
//#include <k4arecord\types.h>
//#include <k4arecord\record.h>
//#include "pixel.h"
//#include "depthpixelcolorizer.h"
//#include "staticimageproperties.h"
//
//using namespace cv;
//using namespace std;
//
//#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
////����ı�����ʾ����
//#define VERIFY(result, error)                                                                            \
//    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
//    {                                                                                                    \
//        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
//        exit(1);                                                                                         \
//    }       
//
//thread* tids;
//thread* tids_s;
//thread tid_ss;
//k4a_device_t* dev;
//k4a_record_t* record = NULL;
//bool esc = false, show[2] = { false,false },h = true;
//
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
//void cap(k4a_device_t& dev_d, cv::Mat& colorFrame, k4a_record_t& record_d, int i)  //��ͨ�ĺ���������ִ���߳�
//{
//	//k4a::image depthImage;
//	k4a_image_t colorImage;
//	//k4a::image irImage;
//
//	//cv::Mat depthFrame;
//	//cv::Mat irFrame;
//
//	//std::vector<Pixel> depthTextureBuffer;
//	//std::vector<Pixel> irTextureBuffer;
//	uint8_t* colorTextureBuffer;
//
//	k4a_capture_t sensor_capture;//�����ñ���
//	//�鿴capture��ַ
//	//cout << "capture adress" << &sensor_capture << endl;
//
//
//	cv:VideoWriter colorwriter;
//	while (1)
//	{
//		if (k4a_device_get_capture(dev_d, &sensor_capture, K4A_WAIT_INFINITE) == K4A_WAIT_RESULT_SUCCEEDED)
//		{			
//			//depthImage = capture.get_depth_image();
//			colorImage = k4a_capture_get_color_image(sensor_capture);
//			k4a_capture_release(sensor_capture);
//			//irImage = capture.get_ir_image();
//
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = k4a_image_get_buffer(colorImage);
//
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			colorFrame = cv::Mat(1, k4a_image_get_height_pixels(colorImage) * k4a_image_get_width_pixels(colorImage), CV_8UC1, colorTextureBuffer);
//			colorFrame = imdecode(colorFrame, IMREAD_COLOR);
//			k4a_image_release(colorImage);
//			/*cvtColor(colorFrame, colorFrame, COLOR_BGRA2BGR);*/
//			show[i] = true;
//			tids_s[i] = thread(save, ref(colorFrame), i);//��֤��һʱ�俪����ʾ��,���ұ�����ʾ��ͼ��
//			break;
//		}
//	}
//	colorwriter.open(".\\output-" + std::to_string(i) + ".mkv", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, colorFrame.size(), true);
//	if (!colorwriter.isOpened())
//	{
//		cout << "��ʼ��VideoWriterʧ�ܣ�" << endl;
//	}
//
//
//	while (1)
//	{ 
//		if (k4a_device_get_capture(dev_d, &sensor_capture, K4A_WAIT_INFINITE) == K4A_WAIT_RESULT_SUCCEEDED)
//		{
//			//depthImage = capture.get_depth_image();
//			colorImage = k4a_capture_get_color_image(sensor_capture);//�Ӳ����л�ȡͼ��
//			if (colorImage != NULL)
//			{
//				printf(" | Depth16 res:%4dx%4d stride:%5d time:%lld\n",
//					k4a_image_get_height_pixels(colorImage),
//					k4a_image_get_width_pixels(colorImage),
//					k4a_image_get_stride_bytes(colorImage),
//					k4a_image_get_system_timestamp_nsec(colorImage));
//			}
//			k4a_record_write_capture(record_d, sensor_capture);
//			k4a_capture_release(sensor_capture);
//			//irImage = capture.get_ir_image();
//
//
//			//ColorizeDepthImage(depthImage, DepthPixelColorizer::ColorizeBlueToRed, GetDepthModeRange(config.depth_mode), &depthTextureBuffer);
//			//ColorizeDepthImage(irImage, DepthPixelColorizer::ColorizeGreyscale, GetIrLevels(K4A_DEPTH_MODE_PASSIVE_IR), &irTextureBuffer);
//
//			colorTextureBuffer = k4a_image_get_buffer(colorImage);
//
//			//depthFrame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_8UC4, depthTextureBuffer.data());
//			colorFrame = cv::Mat(1, k4a_image_get_height_pixels(colorImage) * k4a_image_get_width_pixels(colorImage), CV_8UC1, colorTextureBuffer);
//			colorFrame = imdecode(colorFrame, IMREAD_COLOR);
//			k4a_image_release(colorImage);
//			/*cvtColor(colorFrame, colorFrame, COLOR_BGRA2BGR);*/
//			if (colorFrame.data == NULL)
//			{
//				cout << "colorframe imdecode erro" << endl;
//			}
//			show[i] = true;
//			/*cvtColor(colorFrame, colorFrame,COLOR_BGRA2BGR);*/
//			colorwriter << colorFrame;
//			
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
//			k4a_record_close(record_d);//�ر�¼����
//			k4a_device_stop_cameras(dev_d);//ֹͣ��
//			k4a_device_close(dev_d);
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
//	record = new k4a_record_t[devicecount];
//	dev = new k4a_device_t[devicecount];
//
//	char str[5];
//
//	for (uint8_t deviceindex = 0; deviceindex < devicecount; deviceindex++)
//	{
//		if (K4A_RESULT_SUCCEEDED != k4a_device_open(deviceindex, &dev[deviceindex]))
//		{
//			printf("%d: Failed to open device\n", deviceindex);
//			continue;
//		}
//
//		//ʵ�鸳ֵ
//		//k4a::device& dd = dev[deviceindex];
//		//cout << "dd is" << dd << "while d is" << dev[deviceindex] << endl;
//		k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//		config.camera_fps = K4A_FRAMES_PER_SECOND_30;
//		config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//		config.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
//		config.color_resolution = K4A_COLOR_RESOLUTION_720P;
//		config.synchronized_images_only = true;
//		bool sync_in, sync_out;
//		VERIFY(k4a_device_get_sync_jack(dev[deviceindex], &sync_in, &sync_out), "get sync jack failed");
//		if (sync_in == true)
//		{
//			cout << "subordinate device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//		}
//		else if (sync_out == true)
//		{
//			cout << "master device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//		}
//		else
//		{
//			cout << "standalone device detected!" << endl;
//			config.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//		}
//		//�㶨�Զ�����
//		char name[20],tmp[20];
//		_itoa_s(deviceindex, tmp, 10);
//		strcpy(name, ".\\fulloutput-"); //ǰ���filename_
//		strcat(name, tmp); //�ļ����
//		strcat(name, ".mkv"); //�ļ���׺��
//		VERIFY(k4a_record_create(name, dev[deviceindex], config, &record[deviceindex]), "create record failed!");
//		VERIFY(k4a_record_write_header(record[deviceindex]), "write record header failed!");
//
//		cout << "started opening k4a device..." << endl;
//		VERIFY(k4a_device_start_cameras(dev[deviceindex], &config), "Start K4A cameras failed!");//����
//		//У׼�豸
//		k4a_calibration_t sensor_calibration;
//		VERIFY(k4a_device_get_calibration(dev[deviceindex], config.depth_mode, config.color_resolution, &sensor_calibration),
//			"Get depth camera calibration failed!")
//		VERIFY(k4a_device_set_color_control(dev[deviceindex], K4A_COLOR_CONTROL_BRIGHTNESS, K4A_COLOR_CONTROL_MODE_MANUAL, 150),"color brightness control failed");//�ֶ������ع�
//		cout << "finished opening k4a device!\n" << endl;
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
//	//���������ñ���
//
//	cv::Mat* colorframe = NULL;
//
//
//	uint32_t num = init_start();//��ʼ��,�������
//	tids = new thread[num];
//	tids_s = new thread[num];
//	colorframe = new cv::Mat[num];
//
//	
//	tid_ss = thread(keyboards);
//	for (int i = 0; i < num; ++i)
//	{
//		tids[i] = thread(cap, ref(dev[i]), ref(colorframe[i]), ref(record[i]), i);
//		
//	}
//	for (int i = 0; i < num; ++i)
//	{
//		cout << "thread' id is " << tids[i].get_id() << endl;
//		cout << "threads' id is " << tids_s[i].get_id() << endl;
//	}
//
//
//	//��֤���߳�ֹͣ
//	tids[0].join(); // ���뽫�߳�join����detach �ȴ����߳̽��������̲ſ����˳�
//	tids[1].join();
//	tids_s[0].join(); // ���뽫�߳�join����detach �ȴ����߳̽��������̲ſ����˳�
//	tids_s[1].join();
//	tid_ss.join();
//	//or use detach��֤���߳��ȶ�
//	//th1.detach();
//	//th2.detach();
//
//	return 0;
//}
//
//
