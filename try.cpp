//#include <stdio.h>
//#include <stdlib.h>
//
//#include <k4a/k4a.h>
//#include <k4abt.h>
//#include <opencv2\opencv.hpp>
//#include <k4arecord\types.h>
//#include <k4arecord\record.h>
//
////定义的报错显示程序
//#define VERIFY(result, error)                                                                            \
//    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
//    {                                                                                                    \
//        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
//        exit(1);                                                                                         \
//    }                                                                                                    \
//
//int main()
//{
//	uint32_t device_count = k4a_device_get_installed_count();
//	k4a_capture_t sensor_capture;//捕获用变量
//	k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;//一个常量表示全关
//
//	printf("Found %d connected devices:\n", device_count);
//	k4a_device_t device[4];
//	//k4a_device_t device = NULL;//需改成数组
//	k4a_record_t record = NULL;
//
//	for (uint8_t deviceIndex = 0; deviceIndex < device_count; deviceIndex++)
//	{
//		//一个个打开设备
//		if (K4A_RESULT_SUCCEEDED != k4a_device_open(deviceIndex, &device[deviceIndex]))
//		{
//			printf("%d: Failed to open device\n", deviceIndex);
//			continue;
//		}
//		// Start camera. Make sure color camera is enabled.
//	
//		deviceConfig.camera_fps = K4A_FRAMES_PER_SECOND_30;
//		deviceConfig.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG; // <==== For Color image
//		deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_720P;
//		deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED; // <==== For Depth image 
//		bool sync_in, sync_out;
//		VERIFY(k4a_device_get_sync_jack(device[deviceIndex], &sync_in, &sync_out), "get sync jack failed");
//		printf("%d", sync_in);
//		printf("%d\n", sync_out);
//
//		VERIFY(k4a_record_create("c:\\temp\\b.mkv", device[0], deviceConfig, &record), "create record failed!");
//		VERIFY(k4a_record_write_header(record), "write record header failed!");
//		if (sync_in == true)
//		{
//			deviceConfig.wired_sync_mode = K4A_WIRED_SYNC_MODE_SUBORDINATE;
//		}
//		else if (sync_out == true)
//		{
//			deviceConfig.wired_sync_mode = K4A_WIRED_SYNC_MODE_MASTER;
//		}
//		else
//		{
//			deviceConfig.wired_sync_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
//		}
//
//		VERIFY(k4a_device_start_cameras(device[deviceIndex], &deviceConfig), "Start K4A cameras failed!");//启动
//		//校准设备
//		k4a_calibration_t sensor_calibration;
//		VERIFY(k4a_device_get_calibration(device[deviceIndex], deviceConfig.depth_mode, deviceConfig.color_resolution, &sensor_calibration),
//			"Get depth camera calibration failed!")
//	}
//
//	/*k4abt_tracker_t tracker = NULL;
//	VERIFY(k4abt_tracker_create(&sensor_calibration, &tracker), "Body tracker initialization failed!");*/
//
//	int frame_count = 0;
//	
//	
//	do
//	{
//		frame_count++;
//		for (uint8_t deviceIndex = 0; deviceIndex < device_count; deviceIndex++)
//		{
//
//			k4a_wait_result_t get_capture_result = k4a_device_get_capture(device[deviceIndex], &sensor_capture, K4A_WAIT_INFINITE);
//			printf("%d", deviceIndex);
//			//传递K4A_WAIT_INFINITE值将无限期地阻塞，直到数据可用，设备断开连接或发生其他错误。
//			if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
//			{
//
//				k4a_image_t img;
//				
//				img = k4a_capture_get_color_image(sensor_capture);//从捕获中获取图像
//				k4a_record_write_capture(record, sensor_capture);
//
//				k4a_capture_release(sensor_capture);
//				if (img != NULL)
//				{
//					printf(" | Depth16 res:%4dx%4d stride:%5d time:%lld\n",
//						k4a_image_get_height_pixels(img),
//						k4a_image_get_width_pixels(img),
//						k4a_image_get_stride_bytes(img),
//						k4a_image_get_system_timestamp_nsec(img));
//
//
//
//					uint8_t* buffer = k4a_image_get_buffer(img);
//
//					// convert the raw buffer to cv::Mat
//					int rows = k4a_image_get_height_pixels(img);
//					int cols = k4a_image_get_width_pixels(img);
//					cv::Mat colorMat(rows, cols, CV_8UC4, (void*)buffer, cv::Mat::AUTO_STEP);
//					/*cv::imshow("dd", colorMat);*/
//				/*	cv::imwrite(".\\a\\alpha" + \
//						std::to_string(frame_count) + \
//						std::to_string(deviceIndex) + ".png", colorMat);
//					cv::waitKey(0);*/
//					//k4a_image_t image;
//
//					/*k4a_result_t a = k4a_image_create(K4A_IMAGE_FORMAT_COLOR_NV12, k4a_image_get_height_pixels(img),
//						k4a_image_get_width_pixels(img),0,&img);*/
//
//						/*uint8_t* a = k4a_image_get_buffer(img);*/
//
//						//k4a_image_create_from_buffer(k4a_image_get_format（img）, k4a_image_get_height_pixels(img), k4a_image_get_width_pixels(img), )
//
//						// Release the image
//					k4a_image_release(img);//
//				}
//
//
//
//				//	k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(tracker, sensor_capture, K4A_WAIT_INFINITE);
//				//	
//				//	k4a_capture_release(sensor_capture); // Remember to release the sensor capture once you finish using it
//				//	if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
//				//	{
//				//		// It should never hit timeout when K4A_WAIT_INFINITE is set.
//				//		printf("Error! Add capture to tracker process queue timeout!\n");
//				//		break;
//				//	}
//				//	else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
//				//	{
//				//		printf("Error! Add capture to tracker process queue failed!\n");
//				//		break;
//				//	}
//
//				//	k4abt_frame_t body_frame = NULL;
//				//	k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);
//				//	if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
//				//	{
//				//		// Successfully popped the body tracking result. Start your processing
//
//				//		size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
//				//		printf("%zu bodies are detected!\n", num_bodies);
//
//				//		k4abt_frame_release(body_frame); // Remember to release the body frame once you finish using it
//				//	}
//				//	else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
//				//	{
//				//		//  It should never hit timeout when K4A_WAIT_INFINITE is set.
//				//		printf("Error! Pop body frame result timeout!\n");
//				//		break;
//				//	}
//				//	else
//				//	{
//				//		printf("Pop body frame result failed!\n");
//				//		break;
//				//	}
//				//}
//				//else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)//捕获超时
//				//{
//				//	// It should never hit time out when K4A_WAIT_INFINITE is set.
//				//	printf("Error! Get depth frame time out!\n");
//				//	break;
//				//}
//				//else
//				//{
//				//	printf("Get depth capture returned error: %d\n", get_capture_result);
//				//	break;
//			}
//
//		}
//	} while (frame_count < 100);
//
//	printf("Finished body tracking processing!\n");
//
//	/*4abt_tracker_shutdown(tracker);
//	k4abt_tracker_destroy(tracker);*/
//	k4a_record_close(record);//关闭录像句柄
//	for (uint8_t deviceIndex = 0; deviceIndex < device_count; deviceIndex++)
//	{
//		k4a_device_stop_cameras(device[deviceIndex]);//停止流
//		k4a_device_close(device[deviceIndex]);
//	}
//
//
//
//
//	/*getchar();*/
//	return 0;
//
//}
//
////#include <stdio.h>
////#include <stdlib.h>
////
////#include <k4a/k4a.h>
////#include <k4abt.h>
////#include <opencv2\opencv.hpp>
////#include <k4arecord\types.h>
////#include <k4arecord\record.h>
////
////#define VERIFY(result, error)                                                                            \
////    if(result != K4A_RESULT_SUCCEEDED)                                                                   \
////    {                                                                                                    \
////        printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
////        exit(1);                                                                                         \
////    }                                                                                                    \
////
////int main()
////{
////	
////	k4a_device_t device = NULL;//打开一个设备
////	VERIFY(k4a_device_open(0, &device), "Open K4A Device failed!");
////
////	// Start camera. Make sure depth camera is enabled.
////	k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;//一个常量表示全关
////	deviceConfig.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
////	deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_720P;
////	deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
////	deviceConfig.camera_fps = K4A_FRAMES_PER_SECOND_30;
////	VERIFY(k4a_device_start_cameras(device, &deviceConfig), "Start K4A cameras failed!");//启动
////
////	k4a_calibration_t sensor_calibration;
////	VERIFY(k4a_device_get_calibration(device, deviceConfig.depth_mode, deviceConfig.color_resolution, &sensor_calibration),
////		"Get depth camera calibration failed!")
////
////		/*k4abt_tracker_t tracker = NULL;
////		VERIFY(k4abt_tracker_create(&sensor_calibration, &tracker), "Body tracker initialization failed!");*/
////
////	int frame_count = 0;
////	//k4a_record_t record = NULL;
////	//VERIFY(k4a_record_create("c:\\temp\\b.mkv", device, deviceConfig, &record), "create record failed!");
////	//VERIFY(k4a_record_write_header(record),"write record header failed!");
////	do
////	{
////		k4a_capture_t sensor_capture;
////		k4a_wait_result_t get_capture_result = k4a_device_get_capture(device, &sensor_capture, K4A_WAIT_INFINITE);
////		//传递K4A_WAIT_INFINITE值将无限期地阻塞，直到数据可用，设备断开连接或发生其他错误。
////		if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
////		{
////			frame_count++;
////			k4a_image_t img;
////			img = k4a_capture_get_color_image(sensor_capture);//从捕获中获取图像
////			k4a_capture_release(sensor_capture);
////			if (img != NULL)
////			{
////				printf(" | Depth16 res:%4dx%4d stride:%5d\n",
////					k4a_image_get_height_pixels(img),
////					k4a_image_get_width_pixels(img),
////					k4a_image_get_stride_bytes(img));
////
////
////				uint8_t* buffer = k4a_image_get_buffer(img);
////
////				// convert the raw buffer to cv::Mat
////				int rows = k4a_image_get_height_pixels(img);
////				int cols = k4a_image_get_width_pixels(img);
////				/*VERIFY(k4a_record_write_capture(record, sensor_capture),"write record failed");*/
////
////				//保存图像
////				cv::Mat colorMat(rows, cols, CV_8UC4, (void*)buffer, cv::Mat::AUTO_STEP);
////				/*cv::imshow("dd", colorMat);*/
////				cv::imwrite(".\\a\\alpha"+ std::to_string(frame_count)+".png", colorMat);
////				cv::waitKey(0);
////
////
////
////
////				k4a_image_release(img);//
////				k4a_capture_release(sensor_capture);
////			}
////
////
////
////			//	k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(tracker, sensor_capture, K4A_WAIT_INFINITE);
////			//	
////			//	k4a_capture_release(sensor_capture); // Remember to release the sensor capture once you finish using it
////			//	if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
////			//	{
////			//		// It should never hit timeout when K4A_WAIT_INFINITE is set.
////			//		printf("Error! Add capture to tracker process queue timeout!\n");
////			//		break;
////			//	}
////			//	else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
////			//	{
////			//		printf("Error! Add capture to tracker process queue failed!\n");
////			//		break;
////			//	}
////
////			//	k4abt_frame_t body_frame = NULL;
////			//	k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);
////			//	if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
////			//	{
////			//		// Successfully popped the body tracking result. Start your processing
////
////			//		size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
////			//		printf("%zu bodies are detected!\n", num_bodies);
////
////			//		k4abt_frame_release(body_frame); // Remember to release the body frame once you finish using it
////			//	}
////			//	else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
////			//	{
////			//		//  It should never hit timeout when K4A_WAIT_INFINITE is set.
////			//		printf("Error! Pop body frame result timeout!\n");
////			//		break;
////			//	}
////			//	else
////			//	{
////			//		printf("Pop body frame result failed!\n");
////			//		break;
////			//	}
////			//}
////			//else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)//捕获超时
////			//{
////			//	// It should never hit time out when K4A_WAIT_INFINITE is set.
////			//	printf("Error! Get depth frame time out!\n");
////			//	break;
////			//}
////			//else
////			//{
////			//	printf("Get depth capture returned error: %d\n", get_capture_result);
////
////			//	break;
////		}
////
////	} while (frame_count < 10);
////
////	printf("Finished body tracking processing!\n");
////
////	/*4abt_tracker_shutdown(tracker);
////	k4abt_tracker_destroy(tracker);*/
////	//k4a_record_close(record);//关闭录像句柄
////	k4a_device_stop_cameras(device);//停止流
////	k4a_device_close(device);
////	getchar();
////	return 0;
////	
////}