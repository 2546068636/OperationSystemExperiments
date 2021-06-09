#include <bits/stdc++.h>
using namespace std;
const int N = 32767;
int number[N];
struct node
{
	int num;//���
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
	cout<<"*************����������һ���������������ַΪ0����СΪ32767*******"<<endl;
	cout<<"******************��ѡ���㷨****************************************"<<endl;
	cout<<"******************First Fit Algorithm������1************************"<<endl;
	cout<<"******************Best  Fit Algorithm������2************************"<<endl;
}
void start_1()
{
	cout<<"��ѡ��:1.�����ڴ棬2.�����ڴ棬3.�˳�"<<endl;
}
void start_2()
{
	cout<<"��������ķ�����С"<<endl;
}
void print_free()
{
	cout<<endl<<"�������������Ϊ��"<<endl;
	list<node>::iterator it;
	for (it = l.begin();it != l.end(); ++it)
	{
		node p = *it;
		cout<<"���"<<"\t"<<"�׵�ַ"<<"\t\t"<<"��ֹ��ַ"<<"\t"<<"��С"<<"\t"<<endl;
		cout<<p.num<<"\t"<<p.adr<<"\t\t"<<p.next<<"\t\t"<<p.size<<"\t"<<endl;
	}
}
void print_use()
{
	cout<<endl<<"ʹ�����������Ϊ��"<<endl;
	list<node>::iterator it;
	for (it = l2.begin();it != l2.end(); ++it)
	{
		node p = *it;
		cout<<"���"<<"\t"<<"�׵�ַ"<<"\t\t"<<"��ֹ��ַ"<<"\t"<<"��С"<<"\t"<<endl;
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
			cout<<"�������������Ĵ�С��"<<endl;
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
			if (flag) cout<<"����ɹ�����������ʼ��ַΪ��"<<start_sq<<endl;
			else cout<<"����ʧ�ܣ�"<<endl;

		}
		else if (n == 2)
		{
			if (l2.empty())
			{
				cout<<"���������������ͷţ����ȷ����ڴ棡"<<endl;
				continue;
			}
			else
			{
				cout<<"�������ͷ������׵�ַ��"<<endl;
				node pp;
				cin>>pp.adr;
				cout<<"�������ͷ����Ĵ�С��"<<endl;
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
						cout<<"�ͷųɹ���"<<endl;
						l.push_back(p);
						l2.erase(it);
						break;
					}
				}
				if (flag) cout<<"�ͷ�ʧ�ܣ�����������׵�ַ���С��"<<endl;
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
