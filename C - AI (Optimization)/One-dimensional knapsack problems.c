/* C codes for solution algorithms of KP2 and KP3 models (one-dimensional knapsack problems) of my Master thesis (Pages 13 and 14) */
/* Solution algorithm is proposed by Dantzig [33], and is also described in page 14 of my master thesis. */
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

const int N = 500; // Number of products j
const int M = 50; // Number of customers i


int T[5] = { 10, 25, 50, 100, 250 };
int V0[2] = { 10, 20 };


float start_time;
float end_time;


double ran1;
double ran2;
double ran3;
double ran4;

double max1;
double prm;


double ratio[2][N][M];
int ratio1[1][N][M];


double pr[N];   //Selling Price
double V[M][N];
double Vper[M][N];
double L0[2][5][M][N];
double L1[2][5][M][N];
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

	fp = fopen("D:\OutputData.txt", "w");
	if (!fp)
	{
		printf("can not open file");
		exit(1);
	}

	start_time = second();



	////// random for V[i][j] //////

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			ran1 = rand() % 10001;
			ran2 = (ran1 / 10000);
			V[i][j] = ran2;

		}
	}


	////// random for S[j] //////

	for (int j = 0; j < N; j++) {

		ran1 = rand() % 10001;
		ran2 = (ran1 / 10000);
		S[j] = ran2;

	}


	////// random for pr[j] //////

	for (int j = 0; j < N; j++) {
		ran3 = rand() % (20001) + 10000;
		ran4 = (ran3 / 10000);
		pr[j] = ran4;
	}




	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {




			////// random for Vper[i][j] //////

			for (int j = 0; j < N; j++) {
				for (int i = 0; i < M; i++) {
					Vper[i][j] = V[i][j];

				}
			}


			////////////////////////////// knapsack 1 (KP 2 - continuous relaxation - solution algorithm) ///////////////////////////////////////


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

					while (Totcap[i][p] + S[ratio1[0][i][j]] <= T[e])
					{

						Totrev[i][p] = Totrev[i][p] + Vper[i][ratio1[0][i][j]];
						Totcap[i][p] = Totcap[i][p] + S[ratio1[0][i][j]];
						j++;
					}


					////////////
					for (int j = 0; j < N; j++) {
						for (int i = 0; i < M; i++) {
							Vper[i][j] = V[i][j];

						}
					}
					/////////////

					L0[r][e][i][p] = 1 / (V0[r] + Totrev[i][p]);

				} //end of index p

			} //End of the main for i





			  ////////////////////////////// knapsack 2 (KP 3 - continuous relaxation - solution algorithm) ///////////////////////////////////////




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
						for (int i = 0; i < M; i++) {
							Vper[i][j] = V[i][j];

						}
					}
					/////////////

					L1[r][e][i][p] = 1 / (V0[r] + V[i][p] + Totrev[i][p]);


				} //end of index p

			} //End of the main for 


		} // End of for e (T)

	}   // End of for r (V0)




	end_time = second();


	printf("%f", end_time - start_time);




	prm = 0;
	for (int j = 0; j < N; j++) {
		if (pr[j] > prm) { prm = pr[j]; }
	}



	fprintf(fp, "\n\n");
	fprintf(fp, "This is maximum of pr[j]");
	fprintf(fp, "\n");
	fprintf(fp, "%f", prm);

	fprintf(fp, "\n\n\n");

	fprintf(fp, "s =");
	fprintf(fp, "\n");

	fprintf(fp, "[");
	for (int j = 0; j < N; j++) {
		fprintf(fp, "%f", S[j]);
		fprintf(fp, "\t");
	}
	fprintf(fp, "];");


	fprintf(fp, "\n\n\n");

	fprintf(fp, "c =");
	fprintf(fp, "\n");

	fprintf(fp, "[");
	for (int j = 0; j < N; j++) {
		fprintf(fp, "%f", pr[j]);
		fprintf(fp, "\t");
	}
	fprintf(fp, "];");





	fprintf(fp, "\n\n\n");

	fprintf(fp, "v =");
	fprintf(fp, "\n");

	fprintf(fp, "[");
	fprintf(fp, "\n");

	for (int i = 0; i < M; i++) {

		fprintf(fp, "[");
		for (int j = 0; j < N; j++) {
			fprintf(fp, "%f", V[i][j]);
			fprintf(fp, "\t");
		}
		fprintf(fp, "]");
		fprintf(fp, "\n");
	}

	fprintf(fp, "];");



	fprintf(fp, "\n\n\n");



	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {


			fprintf(fp, "For V0=%d and T=%d we have: \n\n",r+1,e+1);

			fprintf(fp, "L0 =");
			fprintf(fp, "\n");

			fprintf(fp, "[");
			fprintf(fp, "\n");

			for (int i = 0; i < M; i++) {

				fprintf(fp, "[");
				for (int j = 0; j < N; j++) {
					fprintf(fp, "%.10f", L0[r][e][i][j]);
					fprintf(fp, "\t");
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
					fprintf(fp, "%.10f", L1[r][e][i][j]);
					fprintf(fp, "\t");
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


