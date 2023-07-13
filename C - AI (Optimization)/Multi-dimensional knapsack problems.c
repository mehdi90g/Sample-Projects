/* C codes for models MKP2 and MKP3 (multi-dimensional knapsack problems) of my Master thesis (Page 16) */
/* Master thesis available online at http://repository.bilkent.edu.tr/bitstream/handle/11693/32170/Thesis.pdf */

#include <stdlib.h>	/* for printf and NULL */
#include <stdio.h>	/* for srand, rand */ 
#include <time.h>
#include "gurobi_c.h"

int T[5] = { 5, 10, 15, 20, 25 };
int V0[2] = { 5, 10 };

enum N { N = 100 }; //number of products // const int N = 100; (without gurobi)
enum M { M = 10 }; //number of customer types // const int M = 10; (without gurobi)

double ran1;
double ran2;
double ran3;
double ran4;

double prm; //variable to store maximum price

double pr[N];   //Selling Price
double V[M][N]; 
double Vper[M][N];
double S[5][N];

double q0[5][M][N];
double q1[5][M][N];
double L0[2][5][M][N];
double L1[2][5][M][N];

double t0[5][M][N];
double t1[5][M][N];
double total_time[5];




int main(int argc, char *argv[])
{

	srand(99999999999999); //initializing random generator with an integer valued seed.
	srand(time(NULL));

	FILE*fp;
	fp = fopen("D:\OutputData.txt", "w");  // fopen with "w", generates an empty file for the purpose of writing.
	if (!fp)
	{
		printf("can not open file");
		exit(1);
	}

	////// random for V[i][j] //////

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			ran1 = rand() % 10001;  //generating a random number from zero to 10,000
			ran2 = (ran1 / 10000);  //transforming the random number to be between 0 and 1 with 4 decimal points. 
			V[i][j] = ran2;

		}
	}


	////// random for S[k][j] //////

	for (int j = 0; j < N; j++) {
		for (int k = 0; k < 5; k++) {
			ran1 = rand() % 10001;
			ran2 = (ran1 / 10000);
			S[k][j] = ran2;
		}
	}



	////// random for pr[j] //////

	for (int j = 0; j < N; j++) {
		ran3 = rand() % (20001) + 10000;  //random number between 10,000 to 20,000
		ran4 = (ran3 / 10000);   //transforming the random number to be between 1 and 2 with 4 decimal points.
		pr[j] = ran4;
	}



	for (int e = 0; e <= 4; e++) {



		////////////////////////////// knapsack 1 (MKP 2 - continuous relaxation) ///////////////////////////////////////

		for (int i = 0; i < M; i++)
		{
			for (int p = 0; p < N; p++)
			{


				////// random for Vper[i][j] //////

				for (int j = 0; j < N; j++) {
					for (int i = 0; i < M; i++) {
						Vper[i][j] = V[i][j];

					}
				}

				Vper[i][p] = 0;

				GRBenv   *env = NULL;
				GRBmodel *model = NULL;
				int       error = 0;
				double    sol[N];
				int       ind[N];
				double    val[N];
				double    obj[N];
				char      vtype[N];
				int       optimstatus;
				double    objval;
				double    time0;

				/* Create environment */

				error = GRBloadenv(&env, NULL);
				if (error) goto QUIT;

				/* Create an empty model */

				error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
				if (error) goto QUIT;


				/* Add variables */

				for (int j = 0; j < N; j++)

				{
					error = GRBaddvar(model, 0, NULL, NULL, Vper[i][j],
						0.0, 1.0, GRB_CONTINUOUS, NULL);
					if (error) goto QUIT;
				}


				/* Change objective sense to maximization */

				error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
				if (error) goto QUIT;

				/* Integrate new variables */

				error = GRBupdatemodel(model);
				if (error) goto QUIT;

				/* First constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[0][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT;

				/* 2nd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[1][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT;

				/* 3rd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[2][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT;

				/* 4th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[3][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT;

				/* 5th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[4][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT;

				/* Optimize model */

				error = GRBoptimize(model);
				if (error) goto QUIT;

				//Get Runtime

				error = GRBgetdblattr(model, "Runtime", &time0);
				if (error) goto QUIT;

				t0[e][i][p] = time0;

				//Get Obj. Value

				error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
				if (error) goto QUIT;

				q0[e][i][p] = objval;

			QUIT:

				/* Error reporting */

				if (error) {
					printf("ERROR: %s\n", GRBgeterrormsg(env));
					exit(1);
				}


				/* Free model */

				GRBfreemodel(model);

				/* Free environment */

				GRBfreeenv(env);



			} //end of for p

		} // end of for i



		  ////////////////////////////// knapsack 2 (MKP 3 - continuous relaxation) ///////////////////////////////////////



		for (int i = 0; i < M; i++)
		{
			for (int p = 0; p < N; p++)
			{


				////// random for Vper[i][j] //////

				for (int j = 0; j < N; j++) {
					for (int i = 0; i < M; i++) {
						Vper[i][j] = V[i][j];

					}
				}

				Vper[i][p] = 0;

				GRBenv   *env = NULL;
				GRBmodel *model = NULL;
				int       error = 0;
				double    sol[N];
				int       ind[N];
				double    val[N];
				double    obj[N];
				char      vtype[N];
				int       optimstatus;
				double    objval;
				double    time1;


				/* Create environment */

				error = GRBloadenv(&env, NULL);
				if (error) goto QUIT2;

				/* Create an empty model */

				error = GRBnewmodel(env, &model, "mip2", 0, NULL, NULL, NULL, NULL, NULL);
				if (error) goto QUIT2;


				/* Add variables */

				for (int j = 0; j < N; j++)

				{
					error = GRBaddvar(model, 0, NULL, NULL, Vper[i][j],
						0.0, 1.0, GRB_CONTINUOUS, NULL);
					if (error) goto QUIT2;
				}


				/* Change objective sense to maximization */

				error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
				if (error) goto QUIT2;

				/* Integrate new variables */

				error = GRBupdatemodel(model);
				if (error) goto QUIT2;

				/* First constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[0][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[0][p], NULL);
				if (error) goto QUIT2;

				/* 2nd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[1][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[1][p], NULL);
				if (error) goto QUIT2;

				/* 3rd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[2][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[2][p], NULL);
				if (error) goto QUIT2;

				/* 4th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[3][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[3][p], NULL);
				if (error) goto QUIT2;

				/* 5th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[4][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[4][p], NULL);
				if (error) goto QUIT2;

				/* Optimize model */

				error = GRBoptimize(model);
				if (error) goto QUIT2;

				//Get Runtime

				error = GRBgetdblattr(model, "Runtime", &time1);
				if (error) goto QUIT2;

				t1[e][i][p] = time1;


				//Get Obj. Value

				error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
				if (error) goto QUIT2;

				q1[e][i][p] = objval;

			QUIT2:

				/* Error reporting */

				if (error) {
					printf("ERROR: %s\n", GRBgeterrormsg(env));
					exit(1);
				}


				/* Free model */

				GRBfreemodel(model);

				/* Free environment */

				GRBfreeenv(env);


			} //end of for p

		} // end of for i


	} //End of for e (T[e])


	  // system("pause");



	

		for (int e = 0; e <= 4; e++) {

			total_time[e] = 0;

			for (int i = 0; i < M; i++)
			{
				for (int p = 0; p < N; p++)
				{
					total_time[e] = total_time[e] + t0[e][i][p] + t1[e][i][p];
				}
			}
		}

		fprintf(fp, "Times: \n");

		for (int e = 0; e <= 4; e++) {

			fprintf(fp, "%f \n", total_time[e]);
		}



	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {

			for (int i = 0; i < M; i++)
			{
				for (int p = 0; p < N; p++)
				{
					L0[r][e][i][p] = 1 / (V0[r] + q0[e][i][p]);

					L1[r][e][i][p] = 1 / (V0[r] + V[i][p] + q1[e][i][p]);
				}
			}
		}
	}



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
	fprintf(fp, "\n");

	for (int i = 0; i < 5; i++) {

		fprintf(fp, "[");
		for (int j = 0; j < N; j++) {
			fprintf(fp, "%f", S[i][j]);
			fprintf(fp, "\t");
		}
		fprintf(fp, "]");
		fprintf(fp, "\n");
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


			fprintf(fp, "For V0=%d and T=%d we have: \n\n", r + 1, e + 1);

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

		}

	}




////////////////////////////////////////////////////////////
///////////////////INTEGER SOLUTION/////////////////////////
///////////////////////////////////////////////////////////


	for (int e = 0; e <= 4; e++) {



		////////////////////////////// knapsack 1 (MKP 2 - Integer Solution) ///////////////////////////////////////

		for (int i = 0; i < M; i++)
		{
			for (int p = 0; p < N; p++)
			{


				////// random for Vper[i][j] //////

				for (int j = 0; j < N; j++) {
					for (int i = 0; i < M; i++) {
						Vper[i][j] = V[i][j];

					}
				}

				Vper[i][p] = 0;

				GRBenv   *env = NULL;
				GRBmodel *model = NULL;
				int       error = 0;
				double    sol[N];
				int       ind[N];
				double    val[N];
				double    obj[N];
				char      vtype[N];
				int       optimstatus;
				double    objval;
				double    time0;

				/* Create environment */

				error = GRBloadenv(&env, NULL);
				if (error) goto QUIT3;

				/* Create an empty model */

				error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
				if (error) goto QUIT3;


				/* Add variables */

				for (int j = 0; j < N; j++)

				{
					error = GRBaddvar(model, 0, NULL, NULL, Vper[i][j],
						0.0, 1.0, GRB_INTEGER, NULL);
					if (error) goto QUIT3;
				}


				/* Change objective sense to maximization */

				error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
				if (error) goto QUIT3;

				/* Integrate new variables */

				error = GRBupdatemodel(model);
				if (error) goto QUIT3;

				/* First constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[0][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT3;

				/* 2nd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[1][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT3;

				/* 3rd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[2][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT3;

				/* 4th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[3][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT3;

				/* 5th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[4][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e], NULL);
				if (error) goto QUIT3;

				/* Optimize model */

				error = GRBoptimize(model);
				if (error) goto QUIT3;

				//Get Runtime

				error = GRBgetdblattr(model, "Runtime", &time0);
				if (error) goto QUIT3;

				t0[e][i][p] = time0;

				//Get Obj. Value

				error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
				if (error) goto QUIT3;

				q0[e][i][p] = objval;

			QUIT3:

				/* Error reporting */

				if (error) {
					printf("ERROR: %s\n", GRBgeterrormsg(env));
					exit(1);
				}


				/* Free model */

				GRBfreemodel(model);

				/* Free environment */

				GRBfreeenv(env);



			} //end of for p

		} // end of for i



		  ////////////////////////////// knapsack 2 (MKP 3 - Integer Solution) ///////////////////////////////////////



		for (int i = 0; i < M; i++)
		{
			for (int p = 0; p < N; p++)
			{


				////// random for Vper[i][j] //////

				for (int j = 0; j < N; j++) {
					for (int i = 0; i < M; i++) {
						Vper[i][j] = V[i][j];

					}
				}

				Vper[i][p] = 0;

				GRBenv   *env = NULL;
				GRBmodel *model = NULL;
				int       error = 0;
				double    sol[N];
				int       ind[N];
				double    val[N];
				double    obj[N];
				char      vtype[N];
				int       optimstatus;
				double    objval;
				double    time1;


				/* Create environment */

				error = GRBloadenv(&env, NULL);
				if (error) goto QUIT4;

				/* Create an empty model */

				error = GRBnewmodel(env, &model, "mip2", 0, NULL, NULL, NULL, NULL, NULL);
				if (error) goto QUIT4;


				/* Add variables */

				for (int j = 0; j < N; j++)

				{
					error = GRBaddvar(model, 0, NULL, NULL, Vper[i][j],
						0.0, 1.0, GRB_INTEGER, NULL);
					if (error) goto QUIT4;
				}


				/* Change objective sense to maximization */

				error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
				if (error) goto QUIT4;

				/* Integrate new variables */

				error = GRBupdatemodel(model);
				if (error) goto QUIT4;

				/* First constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[0][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[0][p], NULL);
				if (error) goto QUIT4;

				/* 2nd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[1][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[1][p], NULL);
				if (error) goto QUIT4;

				/* 3rd constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[2][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[2][p], NULL);
				if (error) goto QUIT4;

				/* 4th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[3][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[3][p], NULL);
				if (error) goto QUIT4;

				/* 5th constraint */

				for (int j = 0; j < N; j++)
				{
					ind[j] = j;
					val[j] = S[4][j];
				}

				error = GRBaddconstr(model, N, ind, val, GRB_LESS_EQUAL, T[e] - S[4][p], NULL);
				if (error) goto QUIT4;

				/* Optimize model */

				error = GRBoptimize(model);
				if (error) goto QUIT4;

				//Get Runtime

				error = GRBgetdblattr(model, "Runtime", &time1);
				if (error) goto QUIT4;

				t1[e][i][p] = time1;


				//Get Obj. Value

				error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
				if (error) goto QUIT4;

				q1[e][i][p] = objval;

			QUIT4:

				/* Error reporting */

				if (error) {
					printf("ERROR: %s\n", GRBgeterrormsg(env));
					exit(1);
				}


				/* Free model */

				GRBfreemodel(model);

				/* Free environment */

				GRBfreeenv(env);


			} //end of for p

		} // end of for i


	} //End of for e (T[e])


	  // system("pause");





	for (int e = 0; e <= 4; e++) {

		total_time[e] = 0;

		for (int i = 0; i < M; i++)
		{
			for (int p = 0; p < N; p++)
			{
				total_time[e] = total_time[e] + t0[e][i][p] + t1[e][i][p];
			}
		}
	}

	fprintf(fp, "Times: \n");

	for (int e = 0; e <= 4; e++) {

		fprintf(fp, "%f \n", total_time[e]);
	}



	for (int r = 0; r <= 1; r++) {

		for (int e = 0; e <= 4; e++) {

			for (int i = 0; i < M; i++)
			{
				for (int p = 0; p < N; p++)
				{
					L0[r][e][i][p] = 1 / (V0[r] + q0[e][i][p]);

					L1[r][e][i][p] = 1 / (V0[r] + V[i][p] + q1[e][i][p]);
				}
			}
		}
	}



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
	fprintf(fp, "\n");

	for (int i = 0; i < 5; i++) {

		fprintf(fp, "[");
		for (int j = 0; j < N; j++) {
			fprintf(fp, "%f", S[i][j]);
			fprintf(fp, "\t");
		}
		fprintf(fp, "]");
		fprintf(fp, "\n");
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


			fprintf(fp, "For V0=%d and T=%d we have: \n\n", r + 1, e + 1);

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

		}

	}


	return 0;

}
