#include <iostream>
#include <string>

//可以参考caffe，由用户为每个算法制定data source以及其他信息
using namespace std;

int main(int argc,char*argv[]){
	// for (int i=0;i<argc;i++){
	// 	cout << argv[i] << endl;
	// }
	string dataDir = "../Data/";//shoule turn into absolute address later
	dataDir += argv[1];//locate the dataset file
	//file io follows, read specific dataset
	//a dataset includes Xtrain(d, n), ytrain(n, 1), Xtest(d, n'), and ytest(n', 1)
	int d = size(X,1), n = size(X,2);
	lambda = 1/n;

	//compute L and U
	L = lambda + ((Xtrain.col(0).array().square()).array()+1)/4;
	mu = lambda;
	objFunc = LR(lambda,L,mu);

	passes = 10;
	//int batchSize = 1;
	int batchSize = 128;
	double factorSVRG,factorSAGA,factorSAG,factorSGD_a,factorSGD_b,\
			factorSGD_gamma,factorSIG,factorIAGA,factorIAG;
	if(batchSize==1){
		factorSVRG = 1e-1;  % step size = factor / L
	    factorSAGA = 1e-1;
	    factorSAG = 1e-1;
	    factorSGD_a = 1;
	    factorSGD_b = 0;
	    factorSGD_gamma = 0.51;
	    factorSIG = 1e-1;  % step size = factor / L
	    factorIAGA = 1e-1;
	    factorIAG = 1e-2;
	}
	else{    
		factorSVRG = 4;
	    factorSAGA = 4;
	    factorSAG = 1;
	    % factorSGD_a = 1e1;
	    factorSGD_b = 0;
	    factorSGD_gamma = 0;
	    factorSIG = 4;
	    factorIAG = 1;
	    factorIAGA = 4;
	}
	int factorGD= 10;
	int maxRunTime = 60;

	//find or load optimal solution
	string objFuncType = '_logistic_norm';
	string filename = strcat(dataDir,dataset,objFuncType,'xxx');//format not decided
	if (filename not exist){
		wOpt = LR_FindOptSolution(objFunc,Xtrain,ytrain,Xtest,ytest,passes*20,factorSVRG,batchSize);
		save file;
	}
	else{
		load file;
	}
	objFunc.optSolution = wOpt;
	objFunc.optCost = objFunc.costfunc(wOpt,Xtrain,ytrain);
	if(ESS_ON not exsits){
		result = LR_GD(objFunc, Xtrain, ytrain, Xtest, ytest, passes, factorGD, factorSGD_b, factorSGD_gamma, batchSize, dataset, gridNum, maxRunTime);
	}
	else{
		result_ = LR_GD_M(objFunc, Xtrain, ytrain, Xtest, ytest, passes, factorGD, factor_b, factor_gamma, batchSize, dataset, gridNum, maxRunTime);
	}
	return 0;
}
//load dataset
