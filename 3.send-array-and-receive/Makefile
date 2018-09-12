default: clean complie run

clean: 
	clear

complie: 
	mpicc -o 3.send-array-and-receive 3.send-array-and-receive.c

run:
	mpirun -np 2 -hostfile /etc/cluster-hosts.txt 3.send-array-and-receive


all: run
