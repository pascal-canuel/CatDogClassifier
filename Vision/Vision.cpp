/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset

Dataset: https://www.kaggle.com/c/dogs-vs-cats/data
Eigen: http://eigen.tuxfamily.org/index.php?title=Main_Page
*/

#include "AllIncludes.h"

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

	Mat testCat = imread("../dataset/test/cat/10000.jpg");
	Mat testDog = imread("../dataset/test/dog/10000.jpg");
	resize(testCat, testCat, size);
	resize(testDog, testDog, size);
	imshow("test/cat", testCat);
	imshow("test/dog", testDog);
}

int main()
{
	TestDependencies();

	waitKey(0);
	return 0;
}