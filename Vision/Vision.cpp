/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset
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

	/*
	Before refactoring:
		68-69 secs backprop test images
		13-14 secs evaluation test images
	*/

	std::vector<Mat> vecImages;
	vecImages.reserve(10000);
	MNIST::ReadImages("../MNIST/t10k-images.idx3-ubyte", vecImages);
	std::vector<int> vecLabels(10000);
	MNIST::ReadLabels("../MNIST/t10k-labels.idx1-ubyte", vecLabels);

	std::vector<Mat> vecImagesTrain;
	vecImagesTrain.reserve(60000);
	MNIST::ReadImages("../MNIST/train-images.idx3-ubyte", vecImagesTrain);
	std::vector<int> vecLabelsTrain(60000);
	MNIST::ReadLabels("../MNIST/train-labels.idx1-ubyte", vecLabelsTrain);

	Network model({
		new Layers::Input(784),
		new Layers::Dense(30, sigmoid),
		new Layers::Dense(10, sigmoid)
		});

	model.Compile(stochastic_gradient_descent, cross_entropy);
	model.Summary();
	model.Fit({ vecImagesTrain, vecLabelsTrain }, { vecImages, vecLabels });
	model.Hyperparameter(60, 10, 0.01);

	//model.Train();

	//model.SaveWeights("MNIST_Model.dat");
	model.LoadWeights("MNIST_Model.dat");

	for (int i = 0; i < vecImages.size(); i++)
	{
		int prediction = model.Predict(vecImages[i]);
		Guess::Print(vecLabels[i], prediction, vecImages[i]);
		waitKey(0);
	}
	
	waitKey(0);
	return 0;
}