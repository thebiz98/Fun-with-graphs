#include<bits/stdc++.h>
#include<fstream>

using namespace std;

#define pb push_back
#define mp make_pair

class graph {
	int *p,*r;
	int n,cost;
	vector<int> vertices;
	vector<pair<int, pair<int, int>>> edges;
	pair <set<int>, vector<pair<int, pair<int, int>>>> ans;
	public:
		graph(int ne)
		{
			n=ne;
			p=new int[ne];
			r=new int[ne];
			cost=0;
		}
		void makeSet()
		{
			int i;
			for(i=0;i<n;i++)
			{
				p[i]=i+1;
				vertices.pb(i+1);
				r[i]=0;
			}
		}
		void addEdge(int a, int b, int w);
		void Union(int a, int b);
		int findSet(int x);
		void printGraph();
		void Kruskal_MST();
		void printMST();
		~graph()
		{
			vertices.clear();
			edges.clear();
			ans.second.clear();
		}
};

void graph::Union(int a, int b)
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

int graph::findSet(int x)
{
	if(p[x-1]!=x)
		p[x-1]=findSet(p[x-1]);
	return p[x-1];
}

void graph::addEdge(int a, int b, int w)
{
	edges.pb(mp(w,mp(a,b)));
}

bool order(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
	return (a.first<b.first);
}

void graph::Kruskal_MST()
{
	sort(edges.begin(),edges.end(),order);
	int i;
	int x,y;
	for(i=0;i<edges.size();i++)
	{
		x=findSet(edges[i].second.first);
		y=findSet(edges[i].second.second);
		if(x!=y)
		{
			cost+=edges[i].first;
			Union(x,y);
			ans.first.insert(edges[i].second.first);
			ans.first.insert(edges[i].second.second);
			ans.second.pb(edges[i]);
		}
	}
}

void graph::printGraph()
{
	int i;
	cout<<"Vertices are: ";
	for(i=0;i<vertices.size();i++)
		cout<<vertices[i]<<" ";
	cout<<endl;
	cout<<"Edges are:\n";
	for(i=0;i<edges.size();i++)
		cout<<edges[i].second.first<<" "<<edges[i].second.second<<" "<<edges[i].first<<endl;
}

void graph::printMST()
{
	ofstream fout;
	fout.open("mst_kruskal",ios::app);
	int i;
	set<int>::iterator itr;
	cout<<"The vertices in the MST are: ";
	fout<<ans.first.size()<<endl;
	for(itr=ans.first.begin();itr!=ans.first.end();itr++)
	{
		fout<<*itr<<" ";
		cout<<*itr<<" ";
	}
	fout<<endl;
	cout<<endl;
	cout<<"The edges are:\n";
	fout<<ans.second.size()<<endl;
	for(i=0;i<ans.second.size();i++)
	{
		fout<<ans.second[i].second.first<<" "<<ans.second[i].second.second<<" "<<ans.second[i].first<<endl;
		cout<<ans.second[i].second.first<<" "<<ans.second[i].second.second<<" "<<ans.second[i].first<<endl;
	}
	cout<<"The weight of the minimum spanning tree is: "<<cost<<endl;
	fout<<cost<<endl;
	fout.close();
}

int main(int argc, char *argv[])
{
	ifstream fin;
	fin.open(argv[argc-1]);
	int n,en,i,a,b,w,tmp,max=0;
	fin>>n;
	for(i=0;i<n;i++)
	{
		fin>>tmp;
		if(tmp>max)
			max=tmp;
	}
	fin>>en;
	graph sets=graph(max);
	sets.makeSet();
	for(i=0;i<en;i++)
	{
		fin>>a>>b>>w;
		sets.addEdge(a,b,w);
	}
	cout<<"The graph obtained is:\n";
	sets.printGraph();
	sets.Kruskal_MST();
	cout<<"The minimum spanning tree is:\n";
	sets.printMST();
	fin.close();
	return 0;
}
