default: clean complie run

clean: 
	clear

complie: 
	mpicc -o 2.send-and-receive 2.send-and-receive.c

run:
	mpirun -np 2 -hostfile /etc/cluster-hosts.txt 2.send-and-receive


all: run
