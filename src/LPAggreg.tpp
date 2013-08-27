template<>
void LPAggreg< vector<double> >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
	double ** sumValues = new double*[n];
	double ** entValues = new double*[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double[n];
		entValues[i] = new double[n];
		qualities.push_back(vector<Quality*>());
		for (int j=0; j<n; j++){
			qualities[i].push_back(new Quality(0,0));//WRITE*2
			eval.incrQCounter(2);
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		sumValues[0][j] = this->values[j];//WRITE
		entValues[0][j] = entropyReduction<double>(sumValues[0][j], 0);//WRITE
		eval.incrQCounter(2);
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {//WRITE*4
			sumValues[i][j] = sumValues[i - 1][j] + sumValues[0][i + j];
			entValues[i][j] = entValues[i - 1][j] + entValues[0][i + j];
			qualities[i][j]->setGain(entropyReduction(sumValues[i][j], entValues[i][j]));
			qualities[i][j]->setLoss(divergence(i + 1, sumValues[i][j], entValues[i][j]));
			eval.incrQCounter(4);
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n-1][0]->getGain(), qualities[n-1][0]->getLoss());//WRITE
		eval.incrQCounter();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {//WRITE*2
				qualities[i][j]->setGain(qualities[i][j]->getGain()/maxQuality->getGain());
				qualities[i][j]->setLoss(qualities[i][j]->getLoss()/maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

template<>
void LPAggreg< vector< vector<double> > >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
	int m = this->values[0].size();
	double *** sumValues = new double**[n];
	double *** entValues = new double**[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double*[n];
		entValues[i] = new double*[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new double[m];
			entValues[i][j] = new double[m];
			qualities[i].push_back(new Quality(0,0));
			eval.incrQCounter(2);
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k =0; k< m; k++){
			sumValues[0][j][k] = this->values[j][k];
			entValues[0][j][k] = entropyReduction<double>(sumValues[0][j][k], 0);
			eval.incrQCounter(2);
		}
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k =0; k< m; k++){
			sumValues[i][j][k] = sumValues[i - 1][j][k] + sumValues[0][i + j][k];
			entValues[i][j][k] = entValues[i - 1][j][k] + entValues[0][i + j][k];
			qualities[i][j]->addToGain(entropyReduction(sumValues[i][j][k], entValues[i][j][k]));
			qualities[i][j]->addToLoss(divergence(i + 1, sumValues[i][j][k], entValues[i][j][k]));
			eval.incrQCounter(4);
			}
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n-1][0]->getGain(), qualities[n-1][0]->getLoss());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				qualities[i][j]->setGain(qualities[i][j]->getGain()/maxQuality->getGain());
				qualities[i][j]->setLoss(qualities[i][j]->getLoss()/maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j=0; j < n; j++){
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

template<>
void LPAggreg< vector <vector< vector<double> > > >::computeQualitiesSpe(bool normalization) {
	//Init and allocation
	int n = this->getSize();
	int m = this->values[0].size();
	int l = this->values[0][0].size();
	double **** sumValues = new double***[n];
	double **** entValues = new double***[n];
	for (int i = 0; i < n; i++) {
		sumValues[i] = new double**[n];
		entValues[i] = new double**[n];
		qualities.push_back(vector<Quality*>());
		for (int j = 0; j<n; j++){
			sumValues[i][j] = new double*[m];
			entValues[i][j] = new double*[m];
			qualities[i].push_back(new Quality(0,0));
			eval.incrQCounter(2);
			for (int k = 0; k<m; k++){
				sumValues[i][j][k] = new double[l];
				entValues[i][j][k] = new double[l];
			}
		}
	}
	//Microscopic level
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < m; k++){
			for (int o = 0; o < l; o++){
				sumValues[0][j][k][o] = this->values[j][k][o];
				entValues[0][j][k][o] = entropyReduction<double>(sumValues[0][j][k][o], 0);
				eval.incrQCounter(2);
			}
		}
	}
	//Other levels
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			for (int k =0; k< m; k++){
				for (int o = 0; o < l; o++){
					sumValues[i][j][k][o] = sumValues[i - 1][j][k][o] + sumValues[0][i + j][k][o];
					entValues[i][j][k][o] = entValues[i - 1][j][k][o] + entValues[0][i + j][k][o];
					qualities[i][j]->addToGain(entropyReduction(sumValues[i][j][k][o], entValues[i][j][k][o]));
					qualities[i][j]->addToLoss(divergence(i + 1, sumValues[i][j][k][o], entValues[i][j][k][o]));
					eval.incrQCounter(4);
				}
			}
		}
	}
	if (normalization) {
		Quality * maxQuality = new Quality(qualities[n-1][0]->getGain(), qualities[n-1][0]->getLoss());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				qualities[i][j]->setGain(qualities[i][j]->getGain()/maxQuality->getGain());
				qualities[i][j]->setLoss(qualities[i][j]->getLoss()/maxQuality->getLoss());
				eval.incrQCounter(2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j=0; j < n; j++){
			for (int k=0; k<m; k++){
				delete[] sumValues[i][j][k];
				delete[] entValues[i][j][k];
			}
			delete[] sumValues[i][j];
			delete[] entValues[i][j];
		}
		delete[] sumValues[i];
		delete[] entValues[i];
	}
	delete[] sumValues;
	delete[] entValues;
}

template<typename Value>
LPAggreg<Value>::LPAggreg(){
}


template<typename Value>
LPAggreg<Value>::LPAggreg(Value values){
	this->values=values;
}

template<typename Value>
LPAggreg<Value>::~LPAggreg() {
	deleteQualities();
	deleteBestPartitions();
	deleteParameters();
	deleteQualityList();
}

template<typename Value>
void LPAggreg<Value>::setValues(const Value& values) {
	this->values=values;
}

template<typename Value>
unsigned int LPAggreg<Value>::getSize() {
	return this->values.size();
}



