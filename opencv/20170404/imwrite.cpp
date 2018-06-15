#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
	// Mat imread(const string& filename, int flags = 1);
	// flags > 0,返回3通道图像，如果磁盘上的图像文件是单通道的灰度图
	// 则会被强制转为3通道
	// flags = 0,返回单通道图像，如果磁盘上的图像文件是多通道图像，
	// 则会被强制转为单通道
	// flags < 0,不对图像进行通道转换

	// 返回单通道图像
	Mat im = imread("test.jpg", 0);
	if(im.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}

	Mat result;
	Canny(im, result, 50, 150);

	// bool imwrite(const string& filename, InputArray image,
	//				const vector<int>& params = vector<int>());
	// BMP格式是无损格式，但是一般不进行压缩，文件尺寸非常大；
	// JPEG格式的文件娇小，但是JPEG是有损压缩，会丢失一些信息。
	// PNG是无损压缩格式，推荐使用
	// 第三个参数params可以指定文件格式的一些细节信息。与文件格式有关
	// JPEG: 表示图像是质量，取值范围从0到100.数值越大表示图像质量越高
	// 当然文件也越大。默认值是95
	// PNG: 表示压缩级别。取值范围从0到9.数值越大表示文件越小，
	// 但是压缩花费的时间也越长。默认值是3
	// PPM,PGM或PBM：表示文件是以二进制还是纯文本方式存储，取值为0或1
	// 1:表示已二进制方式存储，默认值为1

	// 并不是所有的Mat对象都可以保存为图像文件，目前支持的格式只有8U类型
	// 的单通道和3通道(颜色顺序为BGR)矩阵；如果需要保存16U格式图像，只能
	// 使用PNG、JPEG2000和TIFF格式。如果希望将其他格式的矩阵保存为图像文件
	// 可以先用Mat::convertTo()函数或者cvtColor()函数将矩阵转为可以保存的格式

	bool bRet = imwrite("test-canny.png", result);
	if(bRet)
		cout << "save image success." << endl;
	else
		cout << "save image failed." << endl;

	system("pause");
	return 0;
}