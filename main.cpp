#include<iostream>
#include<string>
#include<stdlib.h>
#include <stdio.h>
#include<math.h>

//Uzay Dalyan
//150170041


using namespace std;


class Neuron{
	
	protected:
		
		double z;
		double a;
	
	public:
		
		Neuron(){z = 0; a = 0;};
		Neuron* nextn;
		virtual void activate() = 0;
		double getz(){return z;};
		double geta(){return a;};
		void setz(double zsetter){z = zsetter;};
		void seta(double asetter){a= asetter;};
};

class SigmoidNeuron : public Neuron{
	
	public:
		
		void activate();
};

void SigmoidNeuron::activate(){
	
	seta(1/(1 + exp(-this->z)));
}

class ReluNeuron : public Neuron{
	
	public:
		
		void activate();
};

void ReluNeuron::activate(){
	
	seta(fmax(0, this->z));
}

class LReluNeuron : public Neuron{
	
	public:
		
		void activate();
};

void LReluNeuron::activate(){
	
	seta(fmax(this->z, (0.1 * this->z)));
}

class Layer{// constructorın sonuna matris yapıştırıcam
	
	private:
		
		Neuron* neuronshead;
		int population;
		
	public:
		
		~Layer();
		Layer(double* iunputarray, int neuron_number, int typen); // first layer constructor
		Layer(int numbern, int typen, int popbefore, Layer* layer_before); // other layers constructor
		Layer* nextl;
		int getpop(){return population;};
};

Layer::Layer(double* inputarray, int neuron_number , int typen){ // first layer constructor
	
	Neuron* traverse;
	population = neuron_number;
	
	switch(typen){
		
		case 0:
			
			neuronshead = new SigmoidNeuron();
			neuronshead->setz(*inputarray);
			neuronshead->seta(*inputarray);
			traverse = neuronshead;
			
			for (int i = 1; i < neuron_number; i++){
				
				traverse->nextn = new SigmoidNeuron();
				traverse->nextn->setz(*(inputarray+i));
				traverse->nextn->seta(*(inputarray+i));
				traverse = traverse->nextn;
			}
			
			cout << "Layer 0:" << endl;
			traverse = this->neuronshead;
			while(traverse){
				
				cout << traverse->geta() << endl;
				traverse = traverse->nextn;
			}
			
			break;
		
		case 1:
			
			neuronshead = new LReluNeuron();
			neuronshead->setz(*inputarray);
			neuronshead->seta(*inputarray);
			traverse = neuronshead;
			
			for (int i = 1; i < neuron_number; i++){
				
				traverse->nextn = new ReluNeuron();
				traverse->nextn->setz(*(inputarray+i));
				traverse->nextn->seta(*(inputarray+i));
				traverse = traverse->nextn;
			}
			
			cout << "Layer 0:" << endl;
			traverse = this->neuronshead;
			while(traverse){
				
				cout << traverse->geta() << endl;
				traverse = traverse->nextn;
			}
			
			break;	
			
		case 2:
			
			neuronshead = new ReluNeuron();
			neuronshead->setz(*inputarray);
			neuronshead->seta(*inputarray);
			traverse = neuronshead;
			
			for (int i = 1; i < neuron_number; i++){
				
				traverse->nextn = new LReluNeuron();
				traverse->nextn->setz(*(inputarray+i));
				traverse->nextn->seta(*(inputarray+i));
				traverse = traverse->nextn;
			}
			
			cout << "Layer 0:" << endl;
			traverse = this->neuronshead;
			while(traverse){
				
				cout << traverse->geta() << endl;
				traverse = traverse->nextn;
			}
			
			break;	
	}
}

Layer::Layer(int numbern, int typen, int popbefore, Layer* layer_before){ // other layers constructor
	
	Neuron* traversen;
	traversen = layer_before->neuronshead;
	this->population = numbern;
	double sum;
	
	double w[numbern][popbefore];
	double b[numbern][1];
	double x[popbefore][1];
	double result[numbern][1];
	
	for(int i = 0; i < numbern; i++){
		
		for(int k = 0; k < popbefore; k++){
			
			w[i][k] = 0.1;
		}
	}
	
	for(int j = 0; j < numbern; j++){
		
			b[j][1] = 0.1;
	}
	
	for(int i = 0; i < popbefore; i++){
		
		x[i][1] = traversen->geta();
		traversen = traversen->nextn;	
	}
	
	for(int i = 0; i < numbern; i++){
		
		sum = 0;
		for(int k = 0; k < popbefore; k++){
			
			sum = sum + w[i][k] * x[k][1];
		}
		
		result[i][1] = sum;
		result[i][1] = result[i][1] + b[i][1];
	}
	
	switch(typen){  
		
		case 0:
			
			neuronshead = new SigmoidNeuron();
			neuronshead->setz(result[0][1]);
			neuronshead->activate();
			cout << neuronshead->geta() << endl;
			traversen = neuronshead;

			
			for (int i = 1; i < numbern; i++){
				
				traversen->nextn = new SigmoidNeuron();
				traversen->nextn->setz(result[i][1]);
				traversen->nextn->activate();
				cout << traversen->nextn->geta() << endl;
				traversen = traversen->nextn;
			}
			
			break;	
			
		case 1:
			
			neuronshead = new LReluNeuron();
			neuronshead->setz(result[0][1]);
			neuronshead->activate();
			cout << neuronshead->geta() << endl;
			traversen = neuronshead;

			
			for (int i = 1; i < numbern; i++){
				
				traversen->nextn = new LReluNeuron();
				traversen->nextn->setz(result[i][1]);
				traversen->nextn->activate();
				cout << traversen->nextn->geta() << endl;
				traversen = traversen->nextn;	
			
		
			}
			
			break;
			
		case 2:
			
			neuronshead = new ReluNeuron();
			neuronshead->setz(result[0][1]);
			neuronshead->activate();
			cout << neuronshead->geta() << endl;
			traversen = neuronshead;

			
			for (int i = 1; i < numbern; i++){
				
				traversen->nextn = new ReluNeuron();
				traversen->nextn->setz(result[i][1]);
				traversen->nextn->activate();
				cout << traversen->nextn->geta() << endl;
				traversen = traversen->nextn;	
			}
			
			break;	
	
	}
}

Layer::~Layer(){
	
	Neuron* dest;
	Neuron*destback;
	dest = this->neuronshead;
	destback = dest;
	
	while(dest){
		
		dest = dest->nextn;
		delete destback;
		Neuron *destback = dest;
	}
	
	delete dest;
	
}

class Network{
	
	private:
		
		Layer* layers_head;
	
	public:
		
		~Network();
		Network(int layern, int* neuron_n, int* neuron_t, double* input_a);	
};

Network::Network(int layern, int* neuron_n, int* neuron_t, double* input_a){
	
	layers_head = new Layer(input_a, *neuron_n, *neuron_t);
	
	Layer* traversel;
	traversel = layers_head;
	layers_head->nextl = NULL;
	for(int k = 1; k < layern; k++){
		
		cout << "Layer " << k << ":" << endl;
		traversel->nextl = new Layer(*(neuron_n+k), *(neuron_t+k), traversel->getpop(), traversel);
		traversel = traversel->nextl;
		traversel->nextl = NULL;
		
	}
	
}

Network::~Network(){
		
	Layer* ldest;
	Layer* ldestback;
	ldest = this->layers_head;
	ldestback = ldest;
	
	while(ldest){
		
		ldest = ldest->nextl;
		delete ldestback;
		Layer *ldestback = ldest;
	}
	
	delete ldest;
}

int main(int argc, char* argv[]){
	
	FILE* fptr;
	
	try{
		
		fptr = fopen(argv[1], "r");
		
		int counter = 0;
		int number_test;
		int input_number;
		double anything;
		
		fscanf(fptr, "%d", &number_test);
		fscanf(fptr, "%d", &input_number);
		
		while(!feof(fptr)){
			
			fscanf(fptr, "%lf", &anything);
			counter++;
		}
		
		if(2*number_test + input_number - 1 != counter){
			
			throw "Input shape does not match!";
		}
	
	}
	
	catch(const char* error){
		
		fclose(fptr);
		cerr << error;
		exit(1);
	}
	
	fclose(fptr);
	
	fptr = fopen(argv[1], "r");
	
	int layer_number;
	
	fscanf(fptr, "%d", &layer_number);

	int *neuron_number;
	int *neuron_types;
	double *inputs;
	
	neuron_number = new int[layer_number];
	neuron_types = new int[layer_number];
	inputs = new double[layer_number];
	
	for(int l = 0; l < layer_number; l++){
	
		fscanf(fptr,"%d", (neuron_number+l));

	}
	
	for(int l = 0; l < layer_number; l++){
		
		fscanf(fptr,"%d", (neuron_types+l));
		
		try{
			
			if(*(neuron_types+l) != 0 & *(neuron_types+l) != 1 & *(neuron_types+l) != 2){
				
				throw "Unidentified activation function!";
			}
		}
			
		catch(const char* error2)	{
			
			fclose(fptr);
			cerr << error2;
			delete[] neuron_number;
			delete[] neuron_types;
			delete[] inputs;
			exit(1);
		}
	}
	
	for(int l = 0; l < layer_number; l++){
		
		fscanf(fptr,"%lf", (inputs + l));
	}
	
	Network system(layer_number, neuron_number, neuron_types, inputs);
	
	delete[] neuron_number;
	delete[] neuron_types;
	delete[] inputs;
	
	return 0;
}









































