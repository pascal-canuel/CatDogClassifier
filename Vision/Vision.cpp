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

int main()
{
	//DataLoader dl;
	//auto test = dl.LoadData("../dataset/test");
	//std::vector<cv::Mat> testImages = std::get<0>(test);
	//std::vector<int> testLabels = std::get<1>(test);

	std::vector<cv::Mat> vecImages;
	MNIST::ReadImages("../MNIST/t10k-images.idx3-ubyte", vecImages);
	std::vector<int> vecLabels(10000);
	MNIST::ReadLabels("../MNIST/t10k-labels.idx1-ubyte", vecLabels);

	std::vector<cv::Mat> vecImagesTrain;
	MNIST::ReadImages("../MNIST/train-images.idx3-ubyte", vecImagesTrain);
	std::vector<int> vecLabelsTrain(60000);
	MNIST::ReadLabels("../MNIST/train-labels.idx1-ubyte", vecLabelsTrain);

	Network model({
		new Layers::Input(784),
		new Layers::Dense(30, sigmoid),
		new Layers::Dense(10, sigmoid)
		});

	model.Compile(stochastic_gradient_descent, mean_squared_error);
	model.Summary();
	model.Fit({ vecImages, vecLabels }, { vecImages, vecLabels });
	model.Hyperparameter(1, 10, 1.0);

	model.Train();
	//model.SaveWeights("MNIST_Model.dat");

	//model.LoadWeights("MNIST_Model.dat");

	for (int i = 0; i < vecImagesTrain.size(); i++)
	{
		cv::Mat resized;
		resize(vecImages[i], resized, cv::Size(100, 100));
		int prediction = model.Predict(vecImages[i]);
		std::cout << prediction << std::endl;
		imshow("Prediction", resized);
		waitKey(0);
	}
	
	waitKey(0);
	return 0;
}