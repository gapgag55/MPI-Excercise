default: clean complie run

clean: 
	clear

complie: 
	mpicc -o 4.master-slave 4.master-slave.c

run:
	mpirun -np 9 -hostfile /etc/cluster-hosts.txt 4.master-slave


all: run
