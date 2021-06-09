#include <bits/stdc++.h>
using namespace std;
const int N = 32767;
int number[N];
struct node
{
	int num;//编号
	int adr,size,next;
};
list <node> l;
list <node> l2;
int n,m;
class my_greater1
{
    public:
    bool operator () (const node s1, const node s2)
    {
        if (s1.size == s2.size)
            return s1.adr < s2.adr;
        else
            return s1.size < s2.size;
    }
};
class my_greater2
{
    public:
    bool operator () (const node s1, const node s2)
    {
        return s1.adr < s2.adr;
    }
};
void start_0()
{
	node p;
	p.adr = 0;
	p.size = N;
	p.num = 0;
	number[0] = 1;
	p.next = p.adr + p.size;
	l.push_back(p);
	cout<<"*************程序已申请一整块空闲区，其首址为0，大小为32767*******"<<endl;
	cout<<"******************请选择算法****************************************"<<endl;
	cout<<"******************First Fit Algorithm请输入1************************"<<endl;
	cout<<"******************Best  Fit Algorithm请输入2************************"<<endl;
}
void start_1()
{
	cout<<"请选择:1.分配内存，2.回收内存，3.退出"<<endl;
}
void start_2()
{
	cout<<"输入申请的分区大小"<<endl;
}
void print_free()
{
	cout<<endl<<"空闲区队列情况为："<<endl;
	list<node>::iterator it;
	for (it = l.begin();it != l.end(); ++it)
	{
		node p = *it;
		cout<<"编号"<<"\t"<<"首地址"<<"\t\t"<<"终止地址"<<"\t"<<"大小"<<"\t"<<endl;
		cout<<p.num<<"\t"<<p.adr<<"\t\t"<<p.next<<"\t\t"<<p.size<<"\t"<<endl;
	}
}
void print_use()
{
	cout<<endl<<"使用区队列情况为："<<endl;
	list<node>::iterator it;
	for (it = l2.begin();it != l2.end(); ++it)
	{
		node p = *it;
		cout<<"编号"<<"\t"<<"首地址"<<"\t\t"<<"终止地址"<<"\t"<<"大小"<<"\t"<<endl;
		cout<<p.num<<"\t"<<p.adr<<"\t\t"<<p.next<<"\t\t"<<p.size<<"\t"<<endl;
	}
}
int main(int argc, char const *argv[])
{
	start_0();
	cin>>m;
	while(1)
	{
		start_1();
		cin>>n;
		if (n == 1)
		{
			bool flag = false;
			int start_sq;
			cout<<"请输入申请区的大小："<<endl;
			node pp;
			cin>>pp.size;
			list<node>::iterator it;
			for (it = l.begin();it != l.end(); ++it)
			{
				node p = *it;
				if (p.size >= pp.size)
				{
					start_sq = p.adr;
					p.adr += pp.size;
					p.size = p.next - p.adr;

					pp.adr = start_sq;
					pp.next = pp.adr + pp.size;
					for (int i = 0; i < N; ++i)
					{
						//cout<<"asd"<<endl;
						if (number[i] == 0)
						{
							number[i] = 1;
							pp.num = i;
							break;
						}
					}
					l2.push_back(pp);
					l.emplace(it,p);
					l.erase(it);
					flag = true;
					break;
				}
			}
			if (flag) cout<<"申请成功！申请区起始地址为："<<start_sq<<endl;
			else cout<<"申请失败！"<<endl;

		}
		else if (n == 2)
		{
			if (l2.empty())
			{
				cout<<"暂无申请区可以释放！请先分配内存！"<<endl;
				continue;
			}
			else
			{
				cout<<"请输入释放区的首地址："<<endl;
				node pp;
				cin>>pp.adr;
				cout<<"请输入释放区的大小："<<endl;
				cin>>pp.size;
				pp.next = pp.adr + pp.size;
				list<node>::iterator it;
				bool flag = true;
				for (it = l2.begin();it != l2.end(); ++it)
				{
					node p = *it;
					if (p.size == pp.size && p.adr == pp.adr && p.next == pp.next)
					{
						flag = false;
						cout<<"释放成功！"<<endl;
						l.push_back(p);
						l2.erase(it);
						break;
					}
				}
				if (flag) cout<<"释放失败，请检查输入的首地址与大小！"<<endl;
			}

		}
		else break;
		list <node> lt;
		stack<node> s;
		l.sort(my_greater2());
		list<node>::iterator it;
		it = l.begin();
		node p = *it;
		s.push(p);
		it++;
		for (;it != l.end(); ++it)
		{
			node pp = *it;
			p = s.top();
			s.pop();
			if (p.next == pp.adr)
			{
				p.next = pp.next;
				p.size = p.next - p.adr;
				p.num = min(p.num,pp.num);
				number[max(p.num,pp.num)] = 0;
				s.push(p);
			}
			else
			{
				s.push(p);
				s.push(pp);
			}
		}
		while(!s.empty())
		{
			node pt = s.top();
			s.pop();
			lt.push_back(pt);
		}
		swap(l,lt);
		if (m == 1) l.sort(my_greater2());
		else l.sort(my_greater1());


		print_free();
		//print_use();
	}

	return 0;
}
