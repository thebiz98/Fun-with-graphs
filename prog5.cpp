#include<bits/stdc++.h>
#include<fstream>

using namespace std;

#define pb push_back
#define mp make_pair
#define INF 1000000

void swaps(pair<int, int> &a, pair<int, int> &b)
{
	pair<int, int> tmp;
	tmp=a;
	a=b;
	b=tmp;
}

class heap {
	vector<pair <int, int>> h;
	public:
		heap(vector<pair <int, int>> x)
		{
			h=x;
		}
		int left(int i)
		{
			return 2*i+1;
		}
		int right(int i)
		{
			return 2*i+2;
		}
		int parent(int i)
		{
			return i/2;
		}
		int heapSize()
		{
			return h.size();
		}
		int inHeap(int x)
		{
			int i;
			for(i=0;i<h.size();i++)
			{
				if(h[i].first==x)
					return 1;
			}
			return 0;
		}
		int findIndex(int x)
		{
			int i;
			for(i=0;i<h.size();i++)
			{
				if(h[i].first==x)
					return i;
			}
			return -1;
		}
		void minHeapify(int i);
		void buildMinHeap();
		pair<int, int> heapExtractMin();
		void heapDecreaseKey(int i, int key);
		friend class graph;
};


class graph {
	int n,cost;
	int *p;
	int *index;
	list<pair<int, int>> *adj;
	vector<pair <int, int>> vertices;
	vector<pair<int, pair<int, int>>> edges;
	pair <set <int>, vector<pair<int, pair<int, int>>>> ans;
	public:
		graph(int ne, int max)
		{
			n=ne;
			p=new int[ne];
			index=new int[max];
			adj=new list<pair<int, int>> [ne];
			cost=0;
		}
		void gen_vertices(int *v);
		void addEdge(int a, int b, int w);
		void MST_Prim();
		void printGraph();
		void printMST();
};

void heap::minHeapify(int i)
{
	int l=left(i);
	int r=right(i);
	int min;
	if(l<h.size()&&h[l].second<h[i].second)
		min=l;
	else
		min=i;
	if(r<h.size()&&h[r].second<h[min].second)
		min=r;
	if(min!=i)
	{
		swaps(h[i],h[min]);
		minHeapify(min);
	}
}

void heap::buildMinHeap()
{
	int i;
	for(i=h.size()/2;i>=0;i++)
		minHeapify(i);
}

pair<int, int> heap::heapExtractMin()
{
	pair<int, int> ans=mp(-1,-1);
	if(h.size()<1)
		return ans;
	ans=h[0];
	h[0]=h[h.size()-1];
	h.erase(h.end()-1);
	minHeapify(0);
	return ans;
}

void heap::heapDecreaseKey(int i, int key)
{
	if(key>h[i].second)
		return;
	h[i].second=key;
	while(i>0&&h[parent(i)].second>h[i].second)
	{
		swaps(h[parent(i)],h[i]);
		i=parent(i);
	}
}

void graph::gen_vertices(int *v)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		p[i]=0;
		vertices.pb(mp(v[i],INF));
		index[v[i]-1]=i;
	}
}

void graph::addEdge(int a, int b, int w)
{
	edges.pb(mp(w,mp(a,b)));
	adj[index[a-1]].pb(mp(b,w));
	adj[index[b-1]].pb(mp(a,w));
}

void graph::MST_Prim()
{
	vertices[0].second=0;
	int i,w;
	pair<int, int> temp;
	list<pair<int, int>>::iterator itr;
	pair<int, int> v;
	heap ni=heap(vertices);
	while(ni.heapSize()!=0)
	{
		temp=ni.heapExtractMin();
		ans.first.insert(temp.first);
		if(p[index[temp.first-1]]!=0)
		{
			ans.second.pb(mp(temp.second,mp(p[index[temp.first-1]],temp.first)));
			cost+=temp.second;
		}
		for(itr=adj[index[temp.first-1]].begin();itr!=adj[index[temp.first-1]].end();itr++)
		{
			v=*itr;
			if(ni.inHeap(v.first)&&v.second<vertices[index[v.first-1]].second)
			{
				p[index[v.first-1]]=temp.first;
				vertices[index[v.first-1]].second=v.second;
				w=ni.findIndex(v.first);
				if(w>=0)
					ni.heapDecreaseKey(w,v.second);
			}
		}
	}
}

void graph::printGraph()
{
	int i;
	cout<<"Vertices are: ";
	for(i=0;i<vertices.size();i++)
		cout<<"index= "<<index[vertices[i].first-1]<<" vertex= "<<vertices[i].first<<" key= "<<vertices[i].second<<endl;
	cout<<endl;
	cout<<"Edges are:\n";
	for(i=0;i<edges.size();i++)
		cout<<edges[i].second.first<<" "<<edges[i].second.second<<" "<<edges[i].first<<endl;
}

void graph::printMST()
{
	ofstream fout;
	fout.open("mst_prim");
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
	fout<<ans.second.size()<<endl;
	cout<<"The edges are:\n";
	for(i=0;i<ans.second.size();i++)
	{
		fout<<ans.second[i].second.first<<" "<<ans.second[i].second.second<<" "<<ans.second[i].first<<endl;
		cout<<ans.second[i].second.first<<" "<<ans.second[i].second.second<<" "<<ans.second[i].first<<endl;
	}
	fout<<cost<<endl;
	cout<<"The weight for this spanning tree is: "<<cost<<endl;
	fout.close();
}

int main(int argc, char*argv[])
{
	ifstream fin;
	fin.open(argv[argc-1]);
	int n,en,i,a,b,w,max;
	fin>>n;
	int *v=new int[n];
	for(i=0;i<n;i++)
	{
		fin>>v[i];
		if(max<v[i])
			max=v[i];
	}
	fin>>en;
	graph sets=graph(n,max);
	sets.gen_vertices(v);
	for(i=0;i<en;i++)
	{
		fin>>a>>b>>w;
		sets.addEdge(a,b,w);
	}
	cout<<"The graph obtained is:\n";
	sets.printGraph();
	sets.MST_Prim();
	cout<<"The minimum spanning tree is:\n";
	sets.printMST();
	fin.close();
	return 0;
}
