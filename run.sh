num_proc=1
if [ $1 ]
then
  num_proc=$1
fi
# mpirun -np $num_proc ~/command/learning/cpp/mpi/exponent 400 5
mpirun -v --hostfile hosts ~/command/learning/cpp/mpi/exponent 400 5
