#include <cmath>
#include <random>

LR_GD(objFunc, X, y, Xtest, ytest, passes, a, b, gamma, batchSize, dataset, gridNum, maxRunTime);
//can matrixXd be return type?
LR_GD(objFunc, X, y, Xtest, ytest, passes, a, b, gamma, batchSize, dataset, gridNum, maxRunTime){
	int d = size(X,1), n = size(X,2);
	iterNum = passes *2;
	lambda = objFunc.lambda;
	w = MatrixXd::Zero(d,1);
	initCost = objFunc.costprint(w,X,y,0);
	iniDistance = ((w.array() - objFunc.optSolution).array().square()).array().sum();
	initLoglikelihood = objFunc.loglikelihood(w,Xtest,ytest);
	//Matrix5d may not existed
	Matrix5d subOptimality(0,0,1,1,initLoglikelihood);
	//use boost library for timing later
	tstart = tic;

	for(int i=0;i<iterNum;i++){
		eta = a * pow(b+t,-gamma);
		default_random_engine generator;
		normal_distribution<double> distribution(0,sqrt(2*eta/n));
		w = w - eta * (objFunc.grad_noreg(w,X,y)+objFunc.lambda*w) +\
		distribution(generator);
		//print cost
		if (t%2==0){
			cost = objFunc.costprint(w,X,y,t/2);
			loglikelihood = objFunc.loglikelihood(w,Xtest,ytest);
			if(cost<=objFunc.optCost)
				fprintf('Oops, we attain the optimal solution ...\n');
			else{
				error = (cost-objFunc.optCost)/(initCost-objFunc.optCost);
				distance = ((w.array()-objFunc.optSolution).array().square()).array().sum() / initDistacne;
				MatrixXd ret(2,5);
				for(int i=0;i<5;i++)
					ret(0,i) = subOptimality(i);
				ret(1,0)=t/2;ret(1,1)=toc(start);ret(1,2)=error;ret(1,3)=distance;ret(1,4)=loglikelihood;
			}
		}
		now = toc(start);
		if (now > maxRunTime)
			break;//what matlab do here if break
	}
	return ret;
}