#include<bits/stdc++.h>
#include<fstream>

using namespace std;

#define pb push_back
#define mp make_pair
#define edge vector<pair<pair<int, int>, int>>

class ds {
	int *p,*r;
	int n,max=0;
	edge edges;
	public:
		ds(int ne)
		{
			n=ne;
			p=new int[ne];
			r=new int[ne];
		}
		void makeSet()
		{
			int i;
			for(i=0;i<n;i++)
			{
				p[i]=i+1;
				r[i]=0;
			}
		}
		void Union(int a, int b);
		int findSet(int x);
		void addEdge(int a, int b, int w)
		{
			edges.pb(mp(mp(a,b),w));
		}
		void connectComp(int x, int y);
		void getForest(set <int> tmp[]);
		void printForest(set <int> tmp[], char *fname);
		void writeMaximal(set <int> tmp[], char *fname);
		void printEdges(int v, char *fname);
};

void ds::Union(int a, int b)
{
	int x=findSet(a);
	int y=findSet(b);
	int j;
	if(x==y)
		return;
	if(r[x-1]>r[y-1])
		p[y-1]=x;
	else
		p[x-1]=y;
	if(r[x-1]==r[y-1])
		r[y-1]=r[y-1]+1;
}

int ds::findSet(int x)
{
	if(p[x-1]!=x)
		p[x-1]=findSet(p[x-1]);
	return p[x-1];
}

void ds::connectComp(int x, int y)
{
	if(findSet(x)!=findSet(y))
		Union(x,y);
}

void ds::getForest(set <int> tmp[])
{
	int i;
	for(i=0;i<n;i++)
		tmp[findSet(i+1)].insert(i+1);
}

void ds::printForest(set <int> tmp[], char *fname)
{
	ofstream fout;
	int i,count=1;
	max=0;
	set <int>::iterator itr;
	for(i=0;i<=n;i++)
	{
		if(tmp[max].size()<tmp[i].size())
			max=i;
		if(tmp[i].begin()!=tmp[i].end())
		{
			fout.open(fname,ios::app);
			cout<<"Set number: "<<count<<endl;
			count++;
			fout<<tmp[i].size()<<endl;
			for(itr=tmp[i].begin();itr!=tmp[i].end();itr++)
			{
				fout<<*itr<<" ";
				cout<<*itr<<" ";
			}
			fout<<endl;
			cout<<"\nThe corresponding edges are:\n";
			fout.close();
			printEdges(i,fname);
		}
	}
}

void ds::writeMaximal(set <int> tmp[], char *fname)
{
	ofstream fout;
	fout.open(fname,ios::app);
	set<int>::iterator itr;
	cout<<"Maximal Set Size: "<<tmp[max].size()<<endl;
	fout<<tmp[max].size()<<endl;
	cout<<"The vertices: ";
	for(itr=tmp[max].begin();itr!=tmp[max].end();itr++)
	{
		fout<<*itr<<" ";
		cout<<*itr<<" ";
	}
	fout<<endl;
	cout<<endl;
	cout<<"The edges are:\n";
	fout.close();
	printEdges(max,fname);
}

void ds::printEdges(int v, char *fname)
{
	ofstream fout;
	fout.open(fname,ios::app);
	int i,count=0;
	for(i=0;i<edges.size();i++)
	{	
		if(findSet(edges[i].first.first)==v&&findSet(edges[i].first.second)==v)
		{
			count++;
			cout<<edges[i].first.first<<" "<<edges[i].first.second<<" "<<edges[i].second<<endl;
		}
	}
	fout<<count<<endl;
	for(i=0;i<edges.size();i++)
	{
		if(findSet(edges[i].first.first)==v&&findSet(edges[i].first.second)==v)
			fout<<edges[i].first.first<<" "<<edges[i].first.second<<" "<<edges[i].second<<endl;
	}
	fout.close();
}

int main(int argc, char*argv[])
{
	ifstream fin;
	fin.open(argv[argc-1]);
	int n,en,i,a,b,j,w;
	char out1[]="allconnected";
	char out2[]="maxconnected";
	fin>>n;
	fin>>en;
	ds sets=ds(n);
	sets.makeSet();
	for(i=0;i<en;i++)
	{
		fin>>a>>b>>w;
		sets.addEdge(a,b,w);
		sets.connectComp(a,b);
	}
	cout<<"The disjoint set forest obtained is:\n";
	cout<<"n= "<<n<<endl;
	set <int> forest[n+1];
	sets.getForest(forest);
	sets.printForest(forest, out1);
	sets.writeMaximal(forest, out2);
	fin.close();
	return 0;
}
