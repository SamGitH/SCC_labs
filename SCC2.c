#include <stdio.h>
#include "mpi.h" 
#include <math.h> 
#include <time.h> 

#define Iterations 10000000 //количество итераций

double power(double x, double n) {
	if (n == 0) return 1;
	if (n < 0) return power(1.0 / x, -n);
	return x * power(x, n - 1);
}

int main() {

	int ProcNum, ProcRank, i;
	double x, MyPi = 0;
	double Sum = 0;
	double TotalTime;
	clock_t StartClock, EndClock; // объявляем стартовую и конечную переменную таймера и инициализируем стартовую переменную
	StartClock = clock();
	MPI_Init(NULL, NULL); // инициализируем MPI
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum); // записываем количество процессов с переменную ProcNum
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); // записываем номер процесса в переменную ProcRank

	for (i = ProcRank; i < Iterations; i += ProcNum)
	{
		x = power(-1, ProcRank) * 4 / (2 * i + 1);
		Sum += x;
	}

	MPI_Reduce(&Sum, &MyPi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); // пердварительные суммы Sum в переменную MyPi

	MPI_Finalize(); // завершаем работу MPI
}
