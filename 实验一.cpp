#include <bits/stdc++.h>
using namespace std;
int n,m;
struct pcb
{
	string name;
	int prio,round,cputime,needtime;
	string state;
	bool operator < (const pcb & a) const
	{
		return prio < a.prio;
	}
};
priority_queue<pcb> q;
queue<pcb> qq;
queue<pcb> qr;
void print_0(pcb p)
{
	cout<<"name \t cputime \t needtime \t priority \t state"<<endl;
	cout<<p.name<<" \t "<<p.cputime<<" \t\t "<<p.needtime<<" \t\t "<<p.prio<<" \t\t "<<p.state<<endl;
}
void print_1(priority_queue<pcb> q1)
{
	while(!q1.empty())
	{
		pcb p = q1.top();
		q1.pop();
		if (p.state == "F" || p.state == "R") continue;
		print_0(p);
	}
}
void print_2(queue<pcb> q1)
{
	while(!q1.empty())
	{
		pcb p = q1.front();
		q1.pop();
		print_0(p);
	}
}
void menu()
{
	cout<<"请选择算法"<<endl;
	cout<<"1:选择优先数调度算法"<<endl;
	cout<<"2:选择循环轮转调度算法"<<endl;
	cout<<"请输入数字："<<endl;

}
void read()
{
	cout<<"请输入进程的数目：";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		cout<<"请输入第"<<i+1<<"个进程的信息"<<endl;
		cout<<"请输入该进程的标识符:";
		pcb pcb1;
		cin>>pcb1.name;
		cout<<"请输入进程需要的运行时间:";
		cin>>pcb1.needtime;
		pcb1.prio = 50 - pcb1.needtime;
		pcb1.state = "W";
		pcb1.cputime = 0;
		pcb1.round = 2;
		q.push(pcb1);
		qr.push(pcb1);
		cout<<endl;
	}
	cout<<"执行前就绪队列状态"<<endl;
	print_1(q);
	cout<<"******************************开始执行******************************"<<endl;
}
int main(int argc, char const *argv[])
{
	menu();
	cin>>m;
	if (m == 1)
	{
		read();
		while(!q.empty())
		{
			pcb p = q.top();
			q.pop();
			p.prio--;
			p.cputime++;
			p.needtime--;
			p.state = "R";
			cout<<"当前运行的进程是(即\"R\"态为)"<<endl;
			print_0(p);
			cout<<"当前就绪队列的进程是(即\"W\"态为)"<<endl;
			print_1(q);
			cout<<"当前运行结束的进程是(即\"F\"态为)"<<endl;
			print_2(qq);
			cout<<endl;
			if (p.needtime == 0)
			{
				p.state = "F";
				qq.push(p);
			}
			if(p.state == "R")
			{
				p.state = "W";
				q.push(p);
			}
		}
	}
	else if (m==2)
	{
		read();
		while(!qr.empty())
		{
			pcb p = qr.front();
			qr.pop();
			pcb pp2;
			bool flag = false;
			if (p.needtime < 2) flag = true;
			cout<<"当前运行的进程是(即\"R\"态为)"<<endl;
			if (p.needtime < 2)
			{
				p.needtime = 0;
				p.cputime++;
				p.state = "R";
				if (!qr.empty())
				{
					pp2 = qr.front();
					qr.pop();
					pp2.needtime--;
					pp2.cputime++;
					pp2.state = "R";
					print_0(p);
					print_0(pp2);
				}
				else
				{
					print_0(p);
					flag = false;
				}
			}
			else
			{
				p.cputime += 2;
				p.needtime -= 2;
				p.state = "R";
				print_0(p);
			}
			cout<<"当前就绪队列的进程是(即\"W\"态为)"<<endl;
			print_2(qr);
			cout<<"当前运行结束的进程是(即\"F\"态为)"<<endl;
			print_2(qq);
			cout<<endl;
			if (p.needtime <= 0)
			{
				p.state = "F";
				qq.push(p);
			}
			if(p.state == "R")
			{
				p.state = "W";
				qr.push(p);
			}
			if (flag)
			{
				if (pp2.needtime <= 0)
				{
					pp2.state = "F";
					qq.push(pp2);
				}
				if(pp2.state == "R")
				{
					pp2.state = "W";
					qr.push(pp2);
				}
			}

		}
	}
	else
	{
		cout<<"输入有误请重试"<<endl;
		return 0;
	}
	cout<<"******************************执行结束******************************"<<endl;
	print_2(qq);
	return 0;
}
