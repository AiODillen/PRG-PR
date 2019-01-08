#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Connection
{
  double weight;
  double deltaweight;
};
class Neuron;

typedef vector<Neuron> Layer;

class Neuron
{
public:
  Neuron(unsigned OutNum, unsigned myIndex);
  void setOutputVal(double val) {n_outputval = val;}
  double getOutputVal() {return n_outputval;}
  void feedforward(Layer &prevLayer);
  void calcOutputGradients(double targetVals);
  void calcHiddenGradients(Layer &nextLayer);
  void updateInputWeights(Layer &prevLayer);

private:
  static double transferfunction(double x);
  static double transferfunctionDerivative(double x);
  static double randomWeight() {return rand() / double(RAND_MAX);}
  double sumDOW(Layer &nextLayer);
  double n_outputval;
  vector<Connection> n_outputWeights;
  unsigned n_myIndex;
  double n_gradient;
  static double alpha;
  static double eta;
};

Neuron::Neuron(unsigned OutNum, unsigned myIndex)
{
  for (unsigned i=0; i < OutNum; ++i){
    n_outputWeights.push_back(Connection());
    n_outputWeights.back().weight = randomWeight();
  }
  n_myIndex = myIndex;
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer &prevLayer)
{
  for (unsigned n = 0; n < prevLayer.size(); ++n){
    Neuron &neuron = prevLayer[n];
    double oldDeltaWeight = neuron.n_outputWeights[n_myIndex].deltaweight;

    double newDeltaWeight=

          eta * neuron.getOutputVal() * n_gradient + alpha * oldDeltaWeight;
    neuron.n_outputWeights[n_myIndex].deltaweight = newDeltaWeight;
    neuron.n_outputWeights[n_myIndex].weight += newDeltaWeight;
  }
}
double Neuron::sumDOW(Layer &nextLayer)
{
  double sum = 0.0;

  for (unsigned n = 0; n < nextLayer.size(); ++n){
    sum += n_outputWeights[n].weight * nextLayer[n].n_gradient;
  }

  return sum;
}

void Neuron::calcHiddenGradients(Layer &nextLayer)
{
  double dow = sumDOW(nextLayer);
  n_gradient = dow * Neuron::transferfunctionDerivative(n_outputval);
}
void Neuron::calcOutputGradients(double targetVals)
{
  double delta = targetVals - n_outputval;
  n_gradient = delta * Neuron::transferfunctionDerivative(n_outputval);
}
double Neuron::transferfunction(double x)
{
  return 1/(1+exp(-x));
}

double Neuron::transferfunctionDerivative(double x)
{
  return exp(-x)*pow((1+exp(-x)), -2);
}
void Neuron::feedforward(Layer &prevLayer)
{
  double sum = 0.0;
  for (unsigned i = 0; i < prevLayer.size(); ++i){
    sum += prevLayer[i].getOutputVal() *
            prevLayer[i].n_outputWeights[n_myIndex].weight;
  }
  n_outputval = Neuron::transferfunction(sum);
}




class NNet
{
public:
    NNet(vector<unsigned> &topology);
    void feedforward(vector<double> &inputVals);
    void backprop(vector<double> &targetVals);
    void getresults(vector<double> &resultVals);
private:
    vector<Layer> nlayers;
    double error;
};

NNet::NNet(vector<unsigned> &topology)
{
  unsigned layerCount = topology.size();
  for (unsigned count = 0; count < layerCount; ++count){
    nlayers.push_back(Layer());
    unsigned numOutputs = count == topology.size() -1 ? 0 : topology[count + 1];
    for (unsigned neuronNum = 0; neuronNum <= topology[count]; ++neuronNum){
      nlayers.back().push_back(Neuron(numOutputs, neuronNum));
      cout << "Made a Neuron" << endl;
    }
    nlayers.back().back().setOutputVal(1.0);
  }

}

void NNet::getresults(vector<double> &resultVals)
{
  resultVals.clear();
  for (unsigned n = 0; n < nlayers.back().size() -1; ++n){
    resultVals.push_back(nlayers.back()[n].getOutputVal());
  }
}
void NNet::backprop(vector<double> &targetVals)
{
  Layer &outputLayer = nlayers.back();
  error = 0.0;
  for (unsigned i = 0; i < outputLayer.size(); ++i){
    double delta = targetVals[i] - outputLayer[i].getOutputVal();
    error += delta*delta;
  }
  error /= outputLayer.size()-1;
  error = sqrt(error);

  for (unsigned i = 0; i < outputLayer.size() -1; ++i){
    outputLayer[i].calcOutputGradients(targetVals[i]);
  }
  for (unsigned layerNum = nlayers.size() -2;layerNum > 0; --layerNum){
    Layer &hiddenLayer = nlayers[layerNum];
    Layer &nextLayer = nlayers[layerNum+1];

    for (unsigned j = 0; j < hiddenLayer.size(); ++j){
      hiddenLayer[j].calcHiddenGradients(nextLayer);
    }
  }

  for (unsigned layerNum = nlayers.size()-1; layerNum > 0; --layerNum){
    Layer &layer = nlayers[layerNum];
    Layer &prevLayer = nlayers[layerNum-1];

    for (unsigned n = 0; n < layer.size()-1 ; ++n){
      layer[n].updateInputWeights(prevLayer);
    }

  }
}
void NNet::feedforward(vector<double> &inputVals)
{
  if (inputVals.size() == nlayers[0].size()-1){
    cout << "all fine" << endl;
  }
  for (unsigned i = 0; i < inputVals.size(); ++i){
    nlayers[0][i].setOutputVal(inputVals[i]);
  }
  for (unsigned i = 1; i < nlayers.size(); ++i){
    Layer &prevLayer = nlayers[i-1];
    for (unsigned j = 0; j < nlayers[i].size(); ++j){
      nlayers[i][j].feedforward(prevLayer);
    }
  }
}

int main()
{
  vector<unsigned> topology;
  topology.push_back(5);
  topology.push_back(3);
  topology.push_back(3);
  topology.push_back(2);
  topology.push_back(1);
  NNet mynet(topology);

  vector<double> inputVals;
  mynet.feedforward(inputVals);

  vector<double> targetVals;
  mynet.backprop(targetVals);

  vector<double> resultVals;
  mynet.getresults(resultVals);
}
