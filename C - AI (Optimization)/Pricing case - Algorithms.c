/* C codes for algorithms of Proposition 8 (Pricing case) of my Master thesis (Page 35) */
/* Master thesis available online at http://repository.bilkent.edu.tr/bitstream/handle/11693/32170/Thesis.pdf */

#include <iostream>
#include <stdio.h>	
#include <conio.h>
#include <math.h>
#include <string.h>
#include <cstring>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

const int N = 100; // Number of products j
const int M = 10; // Number of customers i
const int Pl = 8; // Number of price levels
const int Mu = 2; // Value of Mu


int T[5] = { 5, 10, 25, 50, 100 };
int V0[2] = { 20, 40 };

double Pr[N][Pl];

float start_time;
float end_time;


double ran1;
double ran2;
double ran3;
double ran4;

double max1;
double prm[N]; //max price in all k=1..Pl for each j=1..N
double pmax; //max price in all j
double inc[N];


double ratio[2][N][M];
int ratio1[1][N][M];

double u[M][N];
double V[M][N];   //max Vijk in k
double VK[M][N][Pl];   //Vijk
double VKper[M][N][Pl];
double VKm;   //max Vijk when Xipr=0
double Vper[M][N];
double L0[2][5][M][N][Pl];
double L1[2][5][M][N][Pl];
double S[N];
double Totrev[M][N];
double Totcap[M][N];




float second() {
	return ((float)clock() / (float)CLK_TCK);
}



void main() {

	srand(99999999999999);
	srand(time(NULL));
	FILE*fp;

	fp = fopen("D:\OutputData4.txt", "w");
	if (!fp)
	{
		printf("can not open file");
		exit(1);
	}


	////// random for u[i][j] between 1 and 3 //////

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			ran1 = rand() % (20001) + 10000;
			ran2 = (ran1 / 10000);
			u[i][j] = ran2;

		}
	}


	////// random for prm[j] between 1.01 and 3 with two decimal points //////

	for (int j = 0; j < N; j++) {
		
			ran1 = rand() % (200) + 101;
			ran2 = (ran1 / 100);
			prm[j] = ran2;
	}


	////// Price increments for each j //////
	for (int j = 0; j < N; j++) {
		inc[j] = (prm[j] - 1) / (Pl - 1);
	}


	////// pr[j][k] //////
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < Pl; k++) {
			Pr[j][k] = 1 + (k * inc[j]);

		}
	}



	////// maximum price: pmax //////
	pmax = 0;
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < Pl; k++) {
			if (Pr[j][k] > pmax) { pmax = Pr[j][k]; }
		}
	}

	//////  S[j] = 1  //////

	for (int j = 0; j < N; j++) {

		S[j] = 1;

	}


	//////  V[i][j] = Max VK[i][j][k] for k  //////

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			V[i][j] = exp((u[i][j] - 1)/ Mu) ;

		}
	}

	

	////// VK[i][j][k]  //////
	for (int k = 0; k < Pl; k++) {
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < M; i++) {
				VK[i][j][k] = exp((u[i][j] - Pr[j][k]) / Mu);

			}
		}
	}


	start_time = second();


	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {




			////// Vper[i][j] //////

			for (int j = 0; j < N; j++) {
				for (int i = 0; i < M; i++) {
					Vper[i][j] = V[i][j];

				}
			}


			////////////////////////////// knapsack 1///////////////////////////////////////

			
			for (int i = 0; i < M; i++)
			{

				for (int p = 0; p < N; p++)
				{


					//////knapsack 1 for k=0/////
					for (int j = 0; j < N; j++)
					{

						Vper[i][p] = VK[i][p][1];
						ratio[0][i][j] = j;
						ratio[1][i][j] = Vper[i][j] / S[j];
					}



					for (int k = 0; k < N; k++)
					{
						for (int j = k + 1; j < N; j++)
						{
							if (ratio[1][i][k] < ratio[1][i][j]) {
								swap(ratio[0][i][k], ratio[0][i][j]);
								swap(ratio[1][i][k], ratio[1][i][j]);
							}

						}
					}



					for (int j = 0; j < N; j++) { ratio1[0][i][j] = ratio[0][i][j]; }


					Totrev[i][p] = 0;
					Totcap[i][p] = 0;
					int j = 0;

					while (Totcap[i][p] + S[ratio1[0][i][j]] <= T[e])
					{

						Totrev[i][p] = Totrev[i][p] + Vper[i][ratio1[0][i][j]];
						Totcap[i][p] = Totcap[i][p] + S[ratio1[0][i][j]];
						j++;
					}


					////////////
					for (int j = 0; j < N; j++) {
						for (int f = 0; f < M; f++) {
							Vper[f][j] = V[f][j];

						}
					}
					/////////////

						L0[r][e][i][p][0] = 1 / (V0[r] + Totrev[i][p]);




						//////knapsack 1 for k=1,..,9/////
						for (int j = 0; j < N; j++)
						{
							ratio[0][i][j] = j;
							ratio[1][i][j] = Vper[i][j] / S[j];
						}



						for (int k = 0; k < N; k++)
						{
							for (int j = k + 1; j < N; j++)
							{
								if (ratio[1][i][k] < ratio[1][i][j]) {
									swap(ratio[0][i][k], ratio[0][i][j]);
									swap(ratio[1][i][k], ratio[1][i][j]);
								}

							}
						}



						for (int j = 0; j < N; j++) { ratio1[0][i][j] = ratio[0][i][j]; }


						Totrev[i][p] = 0;
						Totcap[i][p] = 0;
						int t = 0;

						while (Totcap[i][p] + S[ratio1[0][i][t]] <= T[e])
						{

							Totrev[i][p] = Totrev[i][p] + Vper[i][ratio1[0][i][t]];
							Totcap[i][p] = Totcap[i][p] + S[ratio1[0][i][t]];
							t++;
						}


						////////////
						for (int j = 0; j < N; j++) {
							for (int f = 0; f < M; f++) {
								Vper[f][j] = V[f][j];

							}
						}
						/////////////



						for (int k = 1; k < Pl; k++) {

							L0[r][e][i][p][k] = 1 / (V0[r] + Totrev[i][p]);

						}




				} //end of index p

			} //End of the main for i





			  ////////////////////////////// knapsack 2///////////////////////////////////////




			  ////// random for Vper[i][j] //////

			for (int j = 0; j < N; j++) {
				for (int i = 0; i < M; i++) {
					Vper[i][j] = V[i][j];

				}
			}


			for (int i = 0; i < M; i++)
			{

				for (int p = 0; p < N; p++)
				{

					for (int j = 0; j < N; j++)
					{

						Vper[i][p] = 0;
						ratio[0][i][j] = j;
						ratio[1][i][j] = Vper[i][j] / S[j];
					}



					for (int k = 0; k < N; k++)
					{
						for (int j = k + 1; j < N; j++)
						{
							if (ratio[1][i][k] < ratio[1][i][j]) {
								swap(ratio[0][i][k], ratio[0][i][j]);
								swap(ratio[1][i][k], ratio[1][i][j]);
							}

						}
					}



					for (int j = 0; j < N; j++) { ratio1[0][i][j] = ratio[0][i][j]; }


					Totrev[i][p] = 0;
					Totcap[i][p] = 0;
					int j = 0;

					while (Totcap[i][p] + S[ratio1[0][i][j]] <= (T[e] - S[p]))
					{

						Totrev[i][p] = Totrev[i][p] + Vper[i][ratio1[0][i][j]];
						Totcap[i][p] = Totcap[i][p] + S[ratio1[0][i][j]];
						j++;
					}


					////////////
					for (int j = 0; j < N; j++) {
						for (int f = 0; f < M; f++) {
							Vper[f][j] = V[f][j];

						}
					}
					/////////////



					for (int k = 0; k < Pl; k++)

					{

						L1[r][e][i][p][k] = 1 / (V0[r] + VK[i][j][k] + Totrev[i][p]);

					}





				} //end of index p

			} //End of the main for 


		} // End of for e (T)

	}   // End of for r (V0)




	end_time = second();


	printf("%f", end_time - start_time);

	fprintf(fp, "Total time = %f", end_time - start_time);


	fprintf(fp, "\n\n");
	

	fprintf(fp, "This is maximum of pr[j][k]");
	fprintf(fp, "\n");
	fprintf(fp, "%.20f", pmax);


	fprintf(fp, "\n\n\n");

	fprintf(fp, "c =");
	fprintf(fp, "\n");

	fprintf(fp, "[");
	fprintf(fp, "\n");

		for (int j = 0; j < N; j++) {

			fprintf(fp, "[");
			for (int k = 0; k < Pl; k++)
			{
				fprintf(fp, "%.20f ", Pr[j][k]);
			}
			fprintf(fp, "]");
		}
		fprintf(fp, "\n];");
		


	fprintf(fp, "\n\n\n");

	fprintf(fp, "v =");
	fprintf(fp, "\n");

	fprintf(fp, "[");
	fprintf(fp, "\n");

	for (int i = 0; i < M; i++) {

		fprintf(fp, "[");
		for (int j = 0; j < N; j++) {

			fprintf(fp, "[");
			for (int k = 0; k < Pl; k++)
			{
				fprintf(fp, "%.20f ", VK[i][j][k]);
			}
			fprintf(fp, "]");
		}
		fprintf(fp, "]");
		fprintf(fp, "\n");
	}

	fprintf(fp, "];");



	fprintf(fp, "\n\n\n");



	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {


			fprintf(fp, "For V0=%d and T=%d we have: \n\n", r + 1, e + 1);

			fprintf(fp, "L0 =");
			fprintf(fp, "\n");

			fprintf(fp, "[");
			fprintf(fp, "\n");

			for (int i = 0; i < M; i++) {

				fprintf(fp, "[");
				for (int j = 0; j < N; j++) {

					fprintf(fp, "[");
					for (int k = 0; k < Pl; k++)
					{
						fprintf(fp, "%.20f ", L0[r][e][i][j][k]);
					}
					fprintf(fp, "]");
				}
				fprintf(fp, "]");
				fprintf(fp, "\n");
			}

			fprintf(fp, "];");


			fprintf(fp, "\n\n\n");

			fprintf(fp, "L1 =");
			fprintf(fp, "\n");

			fprintf(fp, "[");
			fprintf(fp, "\n");

			for (int i = 0; i < M; i++) {

				fprintf(fp, "[");
				for (int j = 0; j < N; j++) {

					fprintf(fp, "[");
					for (int k = 0; k < Pl; k++) {

						fprintf(fp, "%.20f ", L1[r][e][i][j][k]);
					} 
					fprintf(fp, "]");
			    }
				fprintf(fp, "]");
				fprintf(fp, "\n");
			}

			fprintf(fp, "];");
			fprintf(fp, "\n\n\n");

			fprintf(fp, "END!");


		}

	}


	_getch();
	return;

}


