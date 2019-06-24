#include <stdio.h>
double f(double y) { return(4.0 / (1.0 + y * y)); }
int main(int arg, char **argg)
{
	int numOfThr = argg[1][0] - 48;
	double w, x, sum, pi;
	int i;
	int n = 1000000000;
	w = 1.0 / n;
	sum = 0.0;
#pragma omp parallel for private(x) shared(w) \
            reduction(+:sum) num_threads(numOfThr)
	for (i = 0; i < n; i++)
	{
		x = w * (i - 0.5);
		sum = sum + f(x);
	}
	pi = w * sum;
	printf("pi = %f\n", pi);
}
