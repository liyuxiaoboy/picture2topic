#include<iostream>
#include<fstream>

#include <ros/ros.h> 
#include <image_transport/image_transport.h> 
#include <opencv2/highgui/highgui.hpp> 
#include <cv_bridge/cv_bridge.h> 
using namespace std;

void LoadImages(const string &strFile, vector<string> &vstrImageFilenames,
                vector<double> &vTimestamps);

int main(int argc, char** argv) 
{  
    //input [the path of picture folder] /home/yxli/dataset/liio
    // Retrieve paths to images
    vector<string> vstrImageFilenames;
    vector<double> vTimestamps;
    string strFile = string("/home/yxli/dataset/liio")+"/rgb.txt";
    LoadImages(strFile, vstrImageFilenames, vTimestamps);
    int nImages = vstrImageFilenames.size();


    //init  node name image_publisher
    ros::init(argc, argv, "image_publisher"); 
    //handle
    ros::NodeHandle nh; 
    image_transport::ImageTransport it(nh); 
    //publish topic in topic camera/image cache 1
    image_transport::Publisher pub = it.advertise("usb_cam/image_raw", 10); 
    //image read
    //cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR); 
    //cv_bridge
    //sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg(); 
    //rate of publish
    ros::Rate loop_rate(30); 



    //while (nh.ok()) 
    for(int ni=0; nh.ok()&&ni<nImages; ni++)
    {
         cv::Mat image = cv::imread(string("/home/yxli/dataset/liio")+"/"+vstrImageFilenames[ni], CV_LOAD_IMAGE_COLOR);
         sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg(); 
         pub.publish(msg); 
         ros::spinOnce(); 
         loop_rate.sleep(); 
    } 
}



void LoadImages(const string &strFile, vector<string> &vstrImageFilenames, vector<double> &vTimestamps)
{
    ifstream f;
    f.open(strFile.c_str());

    // skip first three lines
    string s0;
    getline(f,s0);
    getline(f,s0);
    getline(f,s0);

    while(!f.eof())
    {
        string s;
        getline(f,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            double t;
            string sRGB;
            ss >> t;
            vTimestamps.push_back(t);
            ss >> sRGB;
            vstrImageFilenames.push_back(sRGB);
        }
    }
}
