#include<bits/stdc++.h>
using namespace std;

vector<vector<double>> population;
void initPopulation(int popSize);
double random(double Min, double Max);
double fittest=-100000000;
double secondFit=-100000000;
double father[100];
double mother[100];
double inputs[100];
void coitus(int popSize, int weights);



void initPopulation(int popSize, int weights){
	for(int i=0; i<popSize; i++){
		population.push_back(vector<double>());
		for(int j=0; j<weights; j++){
			population[i].push_back(random(-4, 4));
		}
	}
	for(int i=0; i<popSize; i++){
		for(int j=0; j<weights; j++){
			cout<<population[i][j]<<" ";
		}
		cout<<endl;
	}
}

void coitus(int popSize, int weights){


	//crossover

	int point=weights/2+rand()%2;
    int tieBreaker=rand()%2;
    double tampChild[weights];
	//Slow approach
/*    for(int i=0; i<weights; i++){
		if(i<point)tampChild[i]=father[i];
		else tampChild[i]=mother[i];

	}
*/
	//Fast approach
    if(tieBreaker==1){
		for(int i=0; i<point; i++){

			tampChild[i]=father[i];
		}
		for(int i=point; i<weights; i++){
			tampChild[i]=mother[i];
		}

    }
    else{
		for(int i=0; i<point; i++){
			tampChild[i]=mother[i];
		}
		for(int i=point; i<weights; i++){
			tampChild[i]=father[i];
		}

    }

	//mutation
	for(int i=0; i<popSize; i++){
		point=rand()%weights;
		population.push_back(vector<double>());
		for(int j=0; j<weights; j++){
			if(j==point){

				population[i].push_back(tampChild[j]+random(-1, 1));
			}
			else population[i].push_back(tampChild[j]);
		}
	}


}

void fitness(int popSize, int weights){
	double tampPop[popSize];
	for(int i=0; i<popSize; i++){
		double currentValue=0;
		for(int j=0; j<weights; j++){
			currentValue+=(population[i][j]*inputs[j]);
		}
		if(currentValue>fittest){
			fittest=currentValue;
			for(int j=0; j<weights; j++){
				father[j]=population[i][j];
			}

		}
		else if(currentValue>secondFit){
			secondFit=currentValue;
			for(int j=0; j<weights; j++){
				mother[j]=population[i][j];
			}

		}
	}
	population.clear();



}


double random(double Min, double Max){
    return ((double(rand()) / double(RAND_MAX)) * (Max - Min)) + Min;
}



int main(){
	srand(time(0));
	int popSize, weights, genNum;
	cout<<"Enter the population size and the number of weights: "<<endl;
	cin>>popSize>>weights;
    cout<<"Enter "<<weights<<" 'X' inputs: \n";
    for(int i=0; i<weights; i++){
		cin>>inputs[i];
    }
    cout<<"Number of generations: \n";
    cin>>genNum;
    cout<<"---------------------------------------------------------\n\n";
/*
	Default set of inputs:
	// result=x1*w1+x2*w2+x3*w3+x4*w4+x5*w5+x6*w6;

	popSize=10;
	weights=6;
	genNum=100

	//x set inputs;

	inputs[0]=-4;
	inputs[1]=-2;
	inputs[2]=3.5;
	inputs[3]=5;
	inputs[4]=-11;
	inputs[5]=-4.7;

	//program will find the best set of w for each generation: ;

*/
	cout<<"The initial population::: \n\n";
	initPopulation(popSize, weights);
	fitness(popSize, weights);
	cout<<"\n\nBest of initial population\n\n--------\nFather: "<<fittest<<"\n---------\n";
	for(int i=0; i<weights; i++){
		cout<<father[i]<<" ";
	}
	cout<<"\n--------\nMother: "<<secondFit<<"\n---------\n";
	for(int i=0; i<weights; i++){
		cout<<mother[i]<<" ";
	}
	int generation=1;
	while(generation<=genNum){
		fitness(popSize, weights);
		coitus(popSize, weights);
		cout<<"\n\n\nGeneration: "<<generation<<"\n\n--------\nFather: "<<fittest<<"\n---------\n";
        for(int i=0; i<weights; i++){
			cout<<father[i]<<" ";
        }

		cout<<"\n--------\nMother: "<<secondFit<<"\n---------\n";
		for(int i=0; i<weights; i++){
			cout<<mother[i]<<" ";
        }
        generation++;

	}
	cout<<"\n\n\n";
	cout<<"After "<<generation-1<<" generations the best value of 'Y' is: "<<fittest<<"\n\n";


}

