/*
 * main.cpp
 *
 *  Created on: 13 janv. 2015
 *      Author: jfellus
 */




#include <stdlib.h>
#include <stdio.h>
#include "common/utils.h"
#include "common/gossip.h"
#include "common/math.h"

int N = get_config("N", 100);

double TIME_PROCESS = get_config("TIME_PROCESS", 1);
double TIME_MESSAGE = get_config("TIME_MESSAGE", 1);
double TIME_RECEIVE = get_config("TIME_RECEIVE", 1);
double T_MAX = get_config("T_MAX", 1000*(TIME_PROCESS+TIME_MESSAGE+TIME_RECEIVE));

double t = 0;


int cur_id = 0;
class Node;
Node* node;
class Node {
public:
	int id;
	double oktime;

	double total_process;
	double total_msg;
	double total_idle;

public:
	Node() {
		id = cur_id++;
		oktime = 0;
		total_process = total_msg = total_idle = 0;
	}
	~Node() {}

	void process() {
		double t_process = rand_exp(1.0/TIME_PROCESS);
		double t_msg1 = rand_exp(1.0/TIME_PROCESS);
		double t_msg2 = rand_exp(1.0/TIME_PROCESS);
		double t_rcv1 = rand_exp(1.0/TIME_RECEIVE);
		double t_rcv2 = rand_exp(1.0/TIME_RECEIVE);


		oktime = t+t_process;

		Node* r = &node[gossip_choose_receiver(id)];
		if(r->oktime < oktime +t_msg1) r->oktime = oktime+t_msg1;
		r->oktime += t_rcv1;

		double oktime2 = r->oktime + t_msg2 + t_rcv2;

		total_process += t_process;
		r->total_msg += t_msg1;
		r->total_msg += t_rcv1;
		r->total_msg += t_msg2;
		total_msg += t_rcv2;
		total_idle += (oktime2 - oktime);

		oktime = oktime2;
	}
};



void stat() {
	double total_process = 0;
	double total_msg = 0;
	double total_idle = 0;
	for(int i=0; i<N; i++) {
		total_process += node[i].total_process;
		total_msg += node[i].total_msg;
		total_idle += node[i].total_idle;
	}
	double sum = (total_process + total_msg + total_idle)/100;
	total_process /= sum;
	total_msg /= sum;
	total_idle /= sum;

//	fappend("times.txt", fmt("%lf %lf %lf %lf\n", t, total_process, total_msg, total_idle));
	fappend("times.txt", fmt("%d %lf %lf %lf %lf\n", N, TIME_PROCESS, total_process, total_msg, total_idle));
}


int main(int argc, char **argv) {
	if(argc>=2) N = (int)TODOUBLE(argv[1]);
	if(argc>=3) TIME_PROCESS = TODOUBLE(argv[2]);
	T_MAX = 1000*(TIME_PROCESS+TIME_MESSAGE+TIME_RECEIVE);
	if(N>=400) T_MAX/=5;
	if(N>=4000) T_MAX/=6;
	if(N>=40000) T_MAX/=10;


	node = new Node[N];
	while(t<T_MAX) {
		double mint = T_MAX;
		int n = 0;
		for(int i=0; i<N; i++) {
			if(node[i].oktime < mint) {
				mint = node[i].oktime;
				n = i;
			}
		}
		t = mint;
		DBGV(t);
		node[n].process();

//		static int b = 0;
//		int c = (((int)t/100)*100);
//		if((t-c) < 1 && b!=c) stat();
//		b = c;
	}
	stat();
}
