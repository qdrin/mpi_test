// Игрушка для "пощупать" Openmpi - расчет экспоненты по ряду Тейлора
// e^x=∑((x^n)/n!)

#define OMPI_IMPORTS

#include <iostream>
#include <chrono>
#include <boost/lexical_cast.hpp>
#include "mpi.h"

using namespace std;

double fact(int n) {
  if(n == 0)
    return 1;
  else
    return n*fact(n-1);
}

double exp(double x, int n) {
  double res = 1;
  for(int i=0; i < n; i++) {
    res *= x;
  }
  return res;
}

int main(int argc, char* argv[]) {
  if(argc < 3) {
    cout << "Need 2 integer arguments to run\n";
    return 1;
  }
  auto t0 = std::chrono::steady_clock::now();
  int rc;
  double startwtime = 0.0;
  double endwtime;
  int i;
  int myid;
  int numprocs;
  long double fractsum=0, result, sum;
  int x = boost::lexical_cast<int>(argv[2]);
  int n = boost::lexical_cast<int>(argv[1]);
  if (rc = MPI_Init(&argc, &argv)) {
    cout << "MPI run error" << rc << ", stopped\n";
    MPI_Abort(MPI_COMM_WORLD, rc);
  }

  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  if(myid == 0) {
    startwtime = MPI_Wtime();
    cout << "Started. x=" << x << ", n=" << n << ", rc=" << rc << ", numprocs: " << numprocs
        << ", startwtime: " << startwtime << endl;
  }

  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  for (i = myid; i <= n; i += numprocs) {
    // cout << "myid=" << myid << endl;
    fractsum += exp(x, i) / fact(i);
  }

  MPI_Reduce(&fractsum, &result, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if(myid == 0) {
    endwtime = MPI_Wtime();
    cout << "result: " << result << ", endwtime: " << endwtime << endl;
    cout << "time elapsed: " << (endwtime - startwtime)*1000 << " msec\n";
  }
  MPI_Finalize();
  if(myid == 0) {
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> lat = t1 - t0;
    cout << "time elapsed(local): " << lat.count() << endl;
  }
  return 0;
}