/**
 * @file      main.cpp
 * @brief     Stream compaction test program
 * @authors   Kai Ninomiya
 * @date      2015
 * @copyright University of Pennsylvania
 */

#include <cstdio>
#include <character_recognition/mlp.h>
#include <character_recognition/common.h>
#include "testing_helpers.hpp"
#include <iostream>
#include <fstream>
#include <string.h> 
using namespace std;

void createInputXor(float *input) {
	input[0] = 0.0;
	input[1] = 0.0;
	input[2] = 0.0;
	input[3] = 1.0;
	input[4] = 1.0;
	input[5] = 0.0;
	input[6] = 1.0;
	input[7] = 1.0;
}

void createOutputXor(float *output) {
	output[0] = 1.0;
	output[1] = 0.0;
	output[2] = 0.0;
	output[3] = 1.0;
	output[4] = 0.0;
	output[5] = 1.0;
	output[6] = 1.0;
	output[7] = 0.0;
}

void xor2x2NN(int INPUT_SIZE, int HIDDENLAYER_SIZE, int OUTPUT_SIZE, int FEATURE_SIZE,float totalError, int epochs) {
	float *input = new float[INPUT_SIZE*FEATURE_SIZE];
	float *hidden = new float[INPUT_SIZE*HIDDENLAYER_SIZE];
	float *output = new float[INPUT_SIZE*OUTPUT_SIZE];
	float *weightsIH = new float[HIDDENLAYER_SIZE*FEATURE_SIZE];
	float *weightsHO = new float[HIDDENLAYER_SIZE*OUTPUT_SIZE];
	float *outputNN = new float[INPUT_SIZE*OUTPUT_SIZE];
	int *predict = new int[INPUT_SIZE];
	int *actualOutput = new int[INPUT_SIZE];
	float *finalLoss = new float;
	
	createInputXor(input);
	createOutputXor(output);
	srand(10);
	genArrayA(FEATURE_SIZE*HIDDENLAYER_SIZE, weightsIH, 0);
	genArrayB(HIDDENLAYER_SIZE*OUTPUT_SIZE, weightsHO, 1);

	//zeroArray(FEATURE_SIZE*HIDDENLAYER_SIZE, weightsIH);
	//zeroArray(HIDDENLAYER_SIZE*OUTPUT_SIZE, weightsHO);

	printf("Weights A array: \n");
	printArray(HIDDENLAYER_SIZE*FEATURE_SIZE, weightsIH, true);
	printf("Weights B array: \n");
	printArray(HIDDENLAYER_SIZE*OUTPUT_SIZE, weightsHO, true);

	actualOutput[0] = 0;
	actualOutput[1] = 1;
	actualOutput[2] = 1;
	actualOutput[3] = 0;

	CharacterRecognition::createAndTrainNN(INPUT_SIZE, HIDDENLAYER_SIZE, OUTPUT_SIZE, FEATURE_SIZE, input, hidden, outputNN, weightsIH, weightsHO, output,predict,totalError,epochs,finalLoss);

	printf("Statistics for Neural Network Training\n\n");
	printf("Number of Epochs: %d\n\n", epochs);
	printf("Minimum permissible Error: %0.2f\n\n", totalError);
	printf("Error in the last epoch: %0.3f\n\n", *finalLoss);
	printf("SoftMax probabilities Values:\n");
	printArray(INPUT_SIZE*OUTPUT_SIZE, outputNN, true);
	printf("\n True Values are:\n");
	printIntArray(INPUT_SIZE, actualOutput, true);
	printf("\n Predicted values are:\n");
	printIntArray(INPUT_SIZE, predict, true);

	//for (int i = 0; i < INPUT_SIZE; i++) {
	//
//	}
	//printf()

	/*
	printf("After NN and Training \n");
	printf("Input Array: \n");
	printArray(INPUT_SIZE*FEATURE_SIZE, input, true);
	printf("hidden Layer Array: \n");
	printArray(INPUT_SIZE*HIDDENLAYER_SIZE, hidden, true);
	printf("Output Array: \n");
	printArray(INPUT_SIZE*OUTPUT_SIZE, outputNN, true);
	printf("Actual Output Array: \n");
	printArray(INPUT_SIZE*OUTPUT_SIZE, output, true);
	printf("Weights A array: \n");
	printArray(HIDDENLAYER_SIZE*FEATURE_SIZE, weightsIH, true);
	printf("Weights B array: \n");
	printArray(HIDDENLAYER_SIZE*OUTPUT_SIZE, weightsHO, true);

	ofstream outputFile;
	outputFile.open("lossXorTraining.csv");
	outputFile << "Output Values after the Softmax Function" << endl;
	for (int i = 0; i < INPUT_SIZE*OUTPUT_SIZE; i++)
		outputFile << outputNN[i] << endl;

	outputFile << "Output Values for the hidden layer" << endl;
	for (int i = 0; i < INPUT_SIZE*HIDDENLAYER_SIZE; i++)
		outputFile << hidden[i] << endl;

	outputFile << "Values for Weights A" << endl;
	for (int i = 0; i < HIDDENLAYER_SIZE*FEATURE_SIZE; i++)
		outputFile << weightsIH[i] << endl;

	outputFile << "Values for Weights B" << endl;
	for (int i = 0; i < HIDDENLAYER_SIZE*OUTPUT_SIZE; i++)
		outputFile << weightsHO[i] << endl;

	outputFile.close();
	*/
}

void characterRecognition(int INPUT_SIZE,int HIDDENLAYER_SIZE,int OUTPUT_SIZE,int FEATURE_SIZE,float totalError, int epochs) {
	float *input = new float[INPUT_SIZE*FEATURE_SIZE];
	float *hidden = new float[INPUT_SIZE*HIDDENLAYER_SIZE];
	float *output = new float[INPUT_SIZE*OUTPUT_SIZE];
	float *weightsIH = new float[HIDDENLAYER_SIZE*FEATURE_SIZE];
	float *weightsHO = new float[HIDDENLAYER_SIZE*OUTPUT_SIZE];
	float *outputNN = new float[INPUT_SIZE*OUTPUT_SIZE];
	int *predict = new int[INPUT_SIZE*OUTPUT_SIZE];
	int *actualOutput = new int[INPUT_SIZE];
	float *finalLoss = new float;

	for (int i = 1; i <= INPUT_SIZE; i++) {
		string line;
		string filename;
		string temp;
		if (i < 10)
			filename = "C:\\Users\\somanshu\\Desktop\\Project2-Number-Algorithms\\Project2-Character-Recognition\\data-set\\0" + std::to_string(i) + "info.txt";
		else
			filename = "C:\\Users\\somanshu\\Desktop\\Project2-Number-Algorithms\\Project2-Character-Recognition\\data-set\\" + std::to_string(i) + "info.txt";
		ifstream myfile(filename);
		if (myfile.is_open())
		{
			int count = 0;
			while (getline(myfile, line))
			{
				if (count == 2) {
					std::size_t foundFirst = 1;
					std::size_t foundLast = 1;
					int counter = 0;
					while (foundLast < line.length()) {
						foundLast = line.find(" ", foundFirst);
						temp = line.substr(foundFirst, foundLast - foundFirst);
						float val = (float)std::stoi(temp);
						//float val2 = (float)val;
						input[(i - 1)*FEATURE_SIZE + counter] = val / 255;
						counter++;
						foundFirst = foundLast + 1;
					}
				}

				count++;
			}
			myfile.close();
		}
	}


	genArrayA(FEATURE_SIZE*HIDDENLAYER_SIZE, weightsIH, 0);
	genArrayB(HIDDENLAYER_SIZE*OUTPUT_SIZE, weightsHO, 1);

	zeroArray(INPUT_SIZE*OUTPUT_SIZE, output);
	for (int i = 0; i < OUTPUT_SIZE; i++)
		output[i*INPUT_SIZE + i] = 1.0;
	for (int i = 0; i < INPUT_SIZE; i++) {
		actualOutput[i] = i;
	}
	CharacterRecognition::createAndTrainNN(INPUT_SIZE, HIDDENLAYER_SIZE, OUTPUT_SIZE, FEATURE_SIZE, input, hidden, outputNN, weightsIH, weightsHO, output, predict,totalError,epochs,finalLoss);
	
	printf("Statistics for Neural Network Training\n\n");
	printf("Number of Epochs: %d\n\n", epochs);
	printf("Minimum permissible Error: %0.2f\n\n", totalError);
	printf("Error in the last epoch: %0.3f\n\n", *finalLoss);
	printf("SoftMax probabilities Values:\n");
	printArray(INPUT_SIZE*OUTPUT_SIZE, outputNN, true);
	printf("\n True Values are:\n");
	printIntArray(INPUT_SIZE, actualOutput, true);
	printf("\n Predicted values are:\n");
	printIntArray(INPUT_SIZE, predict, true);


	/*
	ofstream outputFile;
	outputFile.open("softMax_prob_characterRecognition.txt");
	outputFile << "Output Values after the Softmax Function" << endl;
	for (int i = 0; i < INPUT_SIZE*OUTPUT_SIZE; i++)
		outputFile << outputNN[i] << endl;
	outputFile.close();
	outputFile.open("hidden_layer_characterRecognition.txt");
	outputFile << "Output Values for the hidden layer" << endl;
	for (int i = 0; i < INPUT_SIZE*HIDDENLAYER_SIZE; i++)
		outputFile << hidden[i] << endl;
	outputFile.close();
	outputFile.open("weightsA_characterRecognition.txt");
	for (int i = 0; i < HIDDENLAYER_SIZE*FEATURE_SIZE; i++)
		outputFile << weightsIH[i] << endl;
	outputFile.close();
	outputFile.open("weightsB_characterRecognition.txt");
	for (int i = 0; i < HIDDENLAYER_SIZE*OUTPUT_SIZE; i++)
		outputFile << weightsHO[i] << endl;

	outputFile.close();
	*/
}
int main(int argc, char* argv[]) {
	
	printf("\n");
	printf("****************\n");
	printf("** CREATING THE NEURAL NETWORK **\n");
	printf("****************\n");

	/*
	const int INPUT_SIZE = 4; // Input size
	const int HIDDENLAYER_SIZE = 4; // Output size
	const int OUTPUT_SIZE = 2; // Output size
	const int FEATURE_SIZE = 2; // Feature Size
	float totalError = 0.1;
	int epochs = 3000;
	xor2x2NN(INPUT_SIZE,HIDDENLAYER_SIZE,OUTPUT_SIZE,FEATURE_SIZE,totalError,epochs);
	
	*/
	
	const int INPUT_SIZE = 52; // Input size
	const int HIDDENLAYER_SIZE = 10; // Output size
	const int OUTPUT_SIZE = 52; // Output size
	const int FEATURE_SIZE = 10201; // Feature Size
	float totalError = 0.1;
	int epochs = 3000;

	characterRecognition(INPUT_SIZE, HIDDENLAYER_SIZE, OUTPUT_SIZE, FEATURE_SIZE,totalError,epochs);
	
}
