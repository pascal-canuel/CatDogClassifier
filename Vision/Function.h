#pragma once
#include <Eigen/Dense>
#include "Activation.h"
#include "Loss.h"

class Function
{
public:
	static Eigen::VectorXf ActivationFunction(Activation activation, Eigen::VectorXf  src);
	static Eigen::VectorXf ErrorFunction(Loss loss, Eigen::VectorXf  src);
private:
	// activation
	static Eigen::VectorXf Sigmoid(Eigen::VectorXf  src);

	// loss
	static Eigen::VectorXf MeanSquaredError(Eigen::VectorXf  src);
};

