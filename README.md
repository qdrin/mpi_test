MPI testing program
# Prerequisites: OpenMPI installed on localhost and every host wich you need to run program on

# Build and prepair:
  e.g. Ubuntu: `g++ -g exponent.cpp -o exponent -I/usr/lib/x86_64-linux-gnu/openmpi/include -lmpi -lmpi_cxx`

# Run on localhost
  `runmpi ./exponent`
# Run on multiple hosts:

## Install openssh-server on all hosts
  `sudo apt install openssh-server`

## Create (if already doesn't exist) your ssh-key
  `ssh-keygen`

### copy the ssh key to every host with MPI running
  e.g. `ssh-copy-id ~/.ssh/id_rsa.pub username@host`
### copy ./exponent to every host to same locations

#### edit o create file like ./hosts, defining all the hosts with MPI

##### run with `runmpi --hostfile ./hosts ./exponent`