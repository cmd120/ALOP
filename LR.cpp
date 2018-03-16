//Bayesian Logistic Regression, y_i \in {0, 1}
//data type not determined yet

// #include <Eigen/Dense>
#include "Eigen/Dense"
using namespace Eigen;
using namespace std;
class LR
{
private:
	lambda = 0;
	L = 0;
	mu = 0;
	optSolution;
	optConst;
	sigfunc(w, X, y);

public:
	LR();//如果lambda等都有初值0，应该有默认构造函数
	LR(lambda, L, mu);
	costfunc(w, X, y);
	loglikelihood(w, X, y);
	grad_noreg(~, w, X, y);//what ~ means in matlab?ignore the first argument?
	hypothesis(~, w, X);
	costprint(w, X, y, stage);
	predictfunc(w, X);
	score(w, X, y);
	~LR();
	
};

LR::LR(lambda,L,mu){
	 this->lambda = lambda;
	 this->L = L;
	 this->mu = mu;
}

inline LR::sigfunc(x, W, y){
	return (1 + (-X.adjoint()*w).array().exp().array()).cwiseInverse();
}

LR::costfunc(w, X, y){
	sigmoid = sigfunc(w, X, y);
	loss = -(y.cwiseProduct(sigmoid.array().log())\
			+(1-y.array()).cwiseProduct((1-sigmoid).array().log())).array().mean();
	regularizer = lambda/2 * (w.array().square()).array().sum();
	return loss + regularizer;
}

LR::loglikelihood(w, X, y){
	sigmoid = sigfunc(w, X, y);
	loglikelihood = (y.cwiseProduct(sigmoid.array().log())+\
		(1-y).cwiseProduct((1-sigmoid).array().log())).array().mean();
	return loglikelihood;
}

LR::grad_noreg(~, w, X, y){
	int d = size(X,1),n = size(X,2);
	tmpExp = (-(X.adjoint() * w)).array().exp();
	gradient = X * (1+tmpExp.array()-y).cwiseInverse() / n;
	return gradient;
}

LR::hypothesis(~, w, X){
	return (1+(-X.adjoint()*w).array().exp().array()).cwiseInverse();
}

LR::costprint(w, X, y, stage){
	cost = costfunc(w, X, y);
	grad_square = (grad_noreg(w,X,y)+lambda*w).norm();
	% fprintf('epoch: %4d, cost: %.25f, grad: %.25f\n', stage, cost, grad_square);
    % fprintf('epoch: %4d, cost: %.25f\n', stage, cost);  // resize the cost
	return cost;
}

LR::predictfunc(w,X){
	int n = size(X,2);
	y = hypothesis(w, X);
	labels = MatriXxd::Ones(n,1);
	for(int i =0;i<n;i++){
		if (labels(i,1) < 0.5) labels(i,1) = 0;
	}
}

LR::score(w, X, y){
	int n = size(X,2),sum=0;
	double score=0;
	labels = predictfunc(w,X);
	for (int i =0;i<n;i++){
		if (labels[i]==y[i]) sum+=1;
	}
	return sum/n;
}
