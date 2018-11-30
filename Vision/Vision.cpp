/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset

Dataset: https://www.kaggle.com/c/dogs-vs-cats/data
Eigen: http://eigen.tuxfamily.org/index.php?title=Main_Page
*/

#include "AllIncludes.h"
#include <opencv2/core/eigen.hpp>

using namespace cv;
using namespace Eigen;

void TestDependencies()
{
	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;
	
	Size size(200, 200);

	Mat trainCat = imread("../dataset/train/cat/0.jpg");
	Mat trainDog = imread("../dataset/train/dog/0.jpg");
	resize(trainCat, trainCat, size);
	resize(trainDog, trainDog, size);
	imshow("train/cat", trainCat);
	imshow("train/dog", trainDog);

	Mat testCat = imread("../dataset/test/cat/10000.jpg", 0);
	Mat testDog = imread("../dataset/test/dog/10000.jpg");
	resize(testCat, testCat, size);
	resize(testDog, testDog, size);
	imshow("test/cat", testCat);
	imshow("test/dog", testDog);
	
	MatrixXf X = MatrixXf(testCat.rows, testCat.cols);
	cv::cv2eigen(testCat, X);
}

int main()
{
	TestDependencies();

	DataLoader dl;
	auto test = dl.LoadData("../dataset/test");
	std::vector<cv::Mat> testImages = std::get<0>(test);
	std::vector<int> testLabels = std::get<1>(test);
	
	// genius https://stackoverflow.com/questions/14783329/opencv-cvmat-and-eigenmatrix
	Eigen::Map<Matrix<float, 64, 64>, RowMajor, Stride<3, 1>> red(testImages[0].ptr<float>());
	Eigen::Map<Matrix<float, 64, 64>, RowMajor, Stride<3, 1>> green(testImages[0].ptr<float>() + 1);
	Eigen::Map<Matrix<float, 64, 64>, RowMajor, Stride<3, 1>> blue(testImages[0].ptr<float>() + 2);

	// test of mapped data
	for (int i = 0; i < 25; i++)
	{
		std::cout << (float)testImages[0].at<Vec3f>(0, i)[0] << (float)testImages[0].at<Vec3f>(0, i)[1] << (float)testImages[0].at<Vec3f>(0, i)[2] << " vs " << red(0, i) << green(0, i) << blue(0, i) << std::endl;
	}

	for (int i = 0; i < 25; i++)
	{
		cv::imshow(dl.ClassNames[testLabels[i]], testImages[i]);
		waitKey(0);
	}

	auto train = dl.LoadData("../dataset/train");
	std::vector<cv::Mat> trainImages = std::get<0>(train);
	std::vector<int> trainLabels = std::get<1>(train);


	waitKey(0);
	return 0;
}