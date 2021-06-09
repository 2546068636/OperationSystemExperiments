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
	cout<<"��ѡ���㷨"<<endl;
	cout<<"1:ѡ�������������㷨"<<endl;
	cout<<"2:ѡ��ѭ����ת�����㷨"<<endl;
	cout<<"���������֣�"<<endl;

}
void read()
{
	cout<<"��������̵���Ŀ��";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		cout<<"�������"<<i+1<<"�����̵���Ϣ"<<endl;
		cout<<"������ý��̵ı�ʶ��:";
		pcb pcb1;
		cin>>pcb1.name;
		cout<<"�����������Ҫ������ʱ��:";
		cin>>pcb1.needtime;
		pcb1.prio = 50 - pcb1.needtime;
		pcb1.state = "W";
		pcb1.cputime = 0;
		pcb1.round = 2;
		q.push(pcb1);
		qr.push(pcb1);
		cout<<endl;
	}
	cout<<"ִ��ǰ��������״̬"<<endl;
	print_1(q);
	cout<<"******************************��ʼִ��******************************"<<endl;
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
			cout<<"��ǰ���еĽ�����(��\"R\"̬Ϊ)"<<endl;
			print_0(p);
			cout<<"��ǰ�������еĽ�����(��\"W\"̬Ϊ)"<<endl;
			print_1(q);
			cout<<"��ǰ���н����Ľ�����(��\"F\"̬Ϊ)"<<endl;
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
			cout<<"��ǰ���еĽ�����(��\"R\"̬Ϊ)"<<endl;
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
			cout<<"��ǰ�������еĽ�����(��\"W\"̬Ϊ)"<<endl;
			print_2(qr);
			cout<<"��ǰ���н����Ľ�����(��\"F\"̬Ϊ)"<<endl;
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
		cout<<"��������������"<<endl;
		return 0;
	}
	cout<<"******************************ִ�н���******************************"<<endl;
	print_2(qq);
	return 0;
}
