#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<set>
using namespace std;
list<string> text_all;

class Path
{
public:
	vector<string> left;
	vector<string> right;
	string& operator[](string& index)
	{
		for (int i = 0; i < left.size(); i++)
			if (left[i] == index)
				return right[i];
	}
	string& operator()(string& index)
	{
		for (int i = 0; i < left.size(); i++)
			if (right[i] == index)
				return left[i];
	}
	void add(string& a, string& b)
	{
		left.push_back(a);
		right.push_back(b);
	}
};

class Linker
{
public:
	bool linkable = false;
	Linker(const string start, const string target);
	~Linker();
	void print()
	{
		for (auto i = way.begin(); i != way.end(); i++)
		{
			cout << *i << "->";
		}
		cout << endl;
	}
private:
	list<string> way;
	queue<string> que, que2;
	set<string> checked, checked2;
	Path path;
	string start;
	string target;
	bool check(const string& a, const string& b)
	{
		return (bool)(a[a.length() - 2] == b[0] && a[a.length() - 1] == b[1]);
	}

	void q_in(string& idiom, queue<string>& que, set<string>& checked0, Path& path, char flag = 'L')
	{
		if (flag == 'L')
			for (auto i = text_all.begin(); i != text_all.end(); i++)
			{
				if (checked0.count(*i) == 0 && check(idiom, *i))
				{
					que.push(*i);
					checked0.insert(*i);
					path.add(idiom, *i);
				}
			}
		else
			for (auto i = text_all.begin(); i != text_all.end(); i++)
				if (checked0.count(*i) == 0 && check(*i, idiom))
				{
					checked0.insert(*i);
					que.push(*i);
					path.add(*i, idiom);
				}
	}
	void run()
	{
		string tmp, tmp2;
		linkable = false;
		q_in(start, que, checked, path, 'L');
		q_in(target, que2, checked2, path, 'R');

		while (que.size() != 0 && que2.size() != 0)
		{
			if (que2.size() >= que.size())
			{
				tmp = que.front();
				que.pop();
				if (checked2.count(tmp))
				{
					linkable = true;
					tmp2 = tmp;
					break;
				}
				else
					q_in(tmp, que, checked, path, 'L');
			}
			else
			{
				tmp2 = que2.front();
				que2.pop();
				if (checked.count(tmp2))
				{
					linkable = true;
					tmp = tmp2;
					break;
				}
				else
					q_in(tmp2, que2, checked2, path, 'R');
			}
		}
		if (linkable == false)
			return;
		for (auto i = checked.begin(); i != checked.end(); i++)
		{
			if (check(tmp, *i) && check(*i, tmp2))
				way.push_back(*i);
		}

		while (start != tmp)
		{
			tmp = path(tmp);
			way.push_front(tmp);
		}
		way.push_back(tmp2);
		while (tmp2 != target)
		{
			tmp2 = path[tmp2];
			way.push_back(tmp2);
		}
	}
};
Linker::Linker(const string start, const string target)
{
	this->start = start;
	this->target = target;
	run();
}

int main()
{

	ifstream infile;
	infile.open("1.txt", ios::in);
	if (infile.is_open() == false)
	{
		cout << "打开文件失败";
		return 0;
	}
	char buf[1024] = { 0 };
	while (infile >> buf)
	{
		text_all.push_back(buf);
	}

	Linker("胸有成竹", "为所欲为").print();
}
