//txt转为pcd文件

#include<iostream>  
#include<fstream>  
#include <string>  
#include <vector>  
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>  

using namespace std;

typedef struct tagPOINT_3D
{
	double x;  //mm world coordinate x  
	double y;  //mm world coordinate y  
	double z;  //mm world coordinate z  
	double r;
}POINT_WORLD;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

int main()
{
	/////加载txt数据  
	PointT TxtToPcd;
	PointCloudT::Ptr TxtToPcd_Cloud;
	int number_Txt;
	FILE *fp_txt;
	tagPOINT_3D TxtPoint;
	vector<tagPOINT_3D> m_vTxtPoints;
	TxtToPcd_Cloud.reset(new PointCloudT);
	fp_txt = fopen("G:\\opencv_qt_halcon_pcl_vs2015\\test\\Halcontest\\QtHalcontest\\QtHalcontest\\QtHalcontest\\1.txt", "r");

	if (fp_txt)
	{
		while (fscanf(fp_txt, "%f %f %f", &TxtToPcd.x, &TxtToPcd.y, &TxtToPcd.z) != EOF)
		{
			TxtToPcd_Cloud->points.push_back(TxtToPcd);
		}
	}
	else
		cout << "txt数据加载失败！" << endl;
	number_Txt = m_vTxtPoints.size();
	pcl::PointCloud<pcl::PointXYZ> cloud;


	// Fill in the cloud data  
	cloud.width = number_Txt;
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width * cloud.height);


	for (size_t i = 0; i < cloud.points.size(); ++i)
	{
		cloud.points[i].x = m_vTxtPoints[i].x;
		cloud.points[i].y = m_vTxtPoints[i].y;
		cloud.points[i].z = m_vTxtPoints[i].z;
	}
	pcl::io::savePCDFileASCII("G:\\opencv_qt_halcon_pcl_vs2015\\test\\Halcontest\\QtHalcontest\\QtHalcontest\\QtHalcontest\\1.pcd", cloud);
	std::cerr << "Saved " << cloud.points.size() << " data points to txt2pcd.pcd." << std::endl;


	for (size_t i = 0; i < cloud.points.size(); ++i)
		std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;


	system("pause");
	return 0;
}

/*if (TxtToPcd_Cloud->is_dense)
pcl::copyPointCloud(*TxtToPcd_Cloud, *cloud_);
else
{
	PCL_WARN("Cloud is not dense! Non finite points will be removed\n");
	std::vector<int> vec;
	pcl::removeNaNFromPointCloud(*TxtToPcd_Cloud, *cloud_, vec);
}*/