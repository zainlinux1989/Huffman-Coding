#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
using namespace std;

struct enKey
	{
		string str;
		int fc;
		enKey *l, *r;
	};

class minHeap
{
private:

	vector<enKey*>  h;

private:
	enKey * createNode(string Str,int freq)
	{
		enKey * key = new enKey;
		key->str = Str;
		key->fc = freq;
		key->l = NULL;
		key->r = NULL;
		return key;
	}
	 int parent(int i)
	{
		return (i / 2);
	}
	 int lchild(int i)
	{
		return (i * 2);
	}
	 int rchild(int i)
	{
		return (i * 2 )+ 1;
	}
	 void codeGenerate(string find,string &str, bool &flag,enKey*curr,int &x)
	 {
		 if((x==0)&&((curr->l==NULL)&&(curr->r==NULL)))
		 {
			 str.push_back('1');
		 }
		 else if((curr->l==NULL)&&(curr->r==NULL))
		 {
			 if(curr->str==find)
			 {
				 flag=true;
			 }
		 }
		 else
		 {
			 x++;
			 if(curr->l!=NULL)
			 {
				 str.push_back('0');
				 codeGenerate(find,str,flag,curr->l,x);
			 }
			 if(flag==true)
			 {
				 return;
			 }
			 str.erase((int)str.size()-1);
			 if(curr->r!=NULL)
			 {
				 str.push_back('1');
				 codeGenerate(find,str,flag,curr->r,x);
			 }
			 if(!flag)
			 {
				 str.erase((int)str.size()-1);
			 }
		 }
	 }

public:

	minHeap()
	{
		h.resize(1);
	}
	int Size()
	{
		return (h.size()-1);
	}
	enKey* getMin()
	{
		return h[1];
	}
	void insert(string Str,int freq)
	{
		enKey *key = createNode(Str, freq);
		h.push_back(key);

		int i = Size();

		while (i > 1 && ( (h[parent(i)]->fc) > (h[i]->fc) ))
		{
			swap(h[i], h[parent(i)]);
			i = parent(i);
		}

	}
	void insert(enKey *key)
	{
		h.push_back(key);

		int i = Size();

		while (i > 1 && ((h[parent(i)]->fc) > (h[i]->fc)))
		{
			swap(h[i], h[parent(i)]);
			i = parent(i);
		}
	}
	void s_sort()
	{
	  int i,j;
	  enKey* t;

	  for(i=1;i<Size()+1;i++)
	  {
	    for(j=i+1;j<Size()+1;j++)
	    {
	      if(h[j]->fc<h[i]->fc)
	      {
	        t=h[i];
	        h[i]=h[j];
	        h[j]=t;
	      }
	    }
	   }
	 }
	void minHeapify(int i)
	{
		int lc = lchild(i);
		int rc = rchild(i);
		int iMin = i;

		if (lc <= Size() && h[lc]->fc < h[iMin]->fc)
		{
			iMin = lc;
		}
		if (rc <= Size() && h[rc]->fc < h[iMin]->fc)
		{
			iMin = rc;
		}
		if (i != iMin)
		{
			swap(h[i], h[iMin]);
			minHeapify(iMin);
		}
	}
	void delMin()
	{
		if (Size() > 0)
		{
			swap(h[1],h[Size()]);
			h.pop_back();
			minHeapify(1);
		}
	}
	void print()
	{
		for(int i=1;i<Size()+1;i++)
		{
			cout<<h[i]->fc<<" ";
		}
		cout<<endl;
	}

	void codeGenerate(string find,string &str)
	{
		enKey*curr=getMin();
		bool flag=false;
		int x=0;
		codeGenerate(find,str,flag,curr,x);
	}
};

int binaryToDecimal(string str)
{
	int power=(int)str.length()-1;
	int y=0;
	int sum=0;
	for(int i=power;i>-1;i--)
	{
		if(i==0)
		{
			if(str[y]=='1')
			{
				sum=sum+pow(2,i);
			}
		}
		else
		{
			if(str[y]=='1')
			{
				sum=sum+pow(2,i);
			}
			y++;
		}
	}
	return  sum;
}
string dectoBin(int num)
{
	char arr[8]={'0','0','0','0','0','0','0','0'};
	int x=0;
	if(num!=0)
	{
		if(num==1)
		{
			arr[x]='1';
		}
		else
		{
		  while(num>1)
		  {
			if(num%2==1)
			{
				arr[x]='1';
			}
			x++;
			num=num/2;
		  }
		  arr[x]='1';
		}
	}
	string temp;
	for(int i=7;i>-1;i--)
	{
		temp.push_back(arr[i]);
	}
	return temp;
}
void putTreeRecursively(ofstream & output,enKey*curr,enKey*prev)
{
	if((curr->l==NULL)&&(curr->r==NULL))
	{
		if(prev->l==curr)
		{
			output<<4;
			output<<curr->str;
		}
		if(prev->r==curr)
		{
			output<<5;
			output<<curr->str;
		}
	}
	else
	{
		prev=curr;
		if(curr->l->l!=NULL)
		{
			output<<2;
		}
		putTreeRecursively(output,curr->l,prev);
		if(curr->r->r!=NULL)
		{
			output<<3;
		}
		putTreeRecursively(output,curr->r,prev);

	}


}
void putTreeinFile(ofstream &output,minHeap &obj)
{
	enKey* curr=obj.getMin();
	if((curr->l==NULL)&&(curr->r==NULL))
	{
		output<<7;
		output<<curr->str;

	}
	else
	{
		output<<1;
		enKey*prev=NULL;
		putTreeRecursively(output,curr,prev);
	}

}
void makecompressfile(minHeap &obj,string fileName,double &n)
{
	char x;
	string str;
	string temp;

	string outputFileName=fileName.substr(0,fileName.length()-2);
	ifstream input(fileName.c_str());
	ofstream output;

	if (input.is_open())
	{
		output.open((outputFileName+"cmp").c_str(), ios::out | ios::app | ios::binary );
		putTreeinFile(output,obj);

		output<<9<<endl;

		while (!(input.eof()))
		{
			input.get(x);
			if(!(input.eof()))
			{

				str.push_back(x);
				for (int i = 0; i < 7; i++)
				{
					input.get(x);
					str.push_back(x);
				}

				obj.codeGenerate(str,temp);
				output<<temp;
				n=n+(double)temp.size();

				str.clear();
				temp.clear();
			}

		}
		output.close();
	}
	else
		cout << "Could not open file";
	input.close();

}
void makeFreqTable(int freq_table[],double & N,string fileName)
{
	char x;
	string str;
	ifstream input(fileName.c_str());

	if (input.is_open())
	{
		while (!(input.eof()))
		{
			input.get(x);
			if(!(input.eof()))
			{

				str.push_back(x);
				N++;

				for (int i = 0; i < 7; i++)
				{
					input.get(x);
					str.push_back(x);
					N++;
				}
				freq_table[binaryToDecimal(str)]++;

				str.clear();
			}
		}
	}
	else
		cout << "Could not open file";
	input.close();
}

void compress(string fileName)
{
	minHeap h;
	int freq_table[256]={0};
	double N=0;
	double n=0;
	makeFreqTable(freq_table,N,fileName);

	for(int i=0;i<256;i++)
	{
		if(freq_table[i]!=0)
		{
			string temp;
			//cout<<i<<" ";
			temp=dectoBin(i);

			h.insert(temp,freq_table[i]);

		}
	}
	cout<<endl;
    h.s_sort();
    //h.print();

   while(h.Size()>1)
    {
    	enKey*ptr=new enKey;
    	ptr->str=" ";

    	enKey*temp1=h.getMin();
    	h.delMin();
    	enKey*temp2=h.getMin();
    	h.delMin();
    	ptr->fc= (temp1->fc) + (temp2->fc);

    	ptr->l=temp1;
    	ptr->r=temp2;

    	h.insert(ptr);
    	h.s_sort();
    }
   cout<<endl;
   makecompressfile(h,fileName,n);
   cout<<"Compression completely "<<endl;

   double r=0;
   r=(1 - n/N);
   r=r*100;

   cout<<"Compression ratio p = "<<r<<"%"<<endl<<endl;



}
void recursiveTreeMaking(ifstream & input,enKey* curr,char x)
{
	if(x=='4')
	{
		curr->l=new enKey;
		curr->l->l=NULL;
		curr->l->r=NULL;

		for(int i=0;i<8;i++)
		{
			input.get(x);
			curr->l->str.push_back(x);
		}
		return;
	}
	else if(x=='5')
	{
		curr->r=new enKey;
		curr->r->l=NULL;
		curr->r->r=NULL;

		for(int i=0;i<8;i++)
		{
			input.get(x);
			curr->r->str.push_back(x);
		}
		return;
	}

	else
	{
		if(x=='2')
		{
			curr->l=new enKey;
			curr->l->l=NULL;
			curr->l->r=NULL;

			curr=curr->l;
		}
		else if(x=='3')
		{
			curr->r=new enKey;
			curr->r->l=NULL;
			curr->r->r=NULL;

			curr=curr->r;
		}
		input.get(x);
		recursiveTreeMaking(input,curr,x);
		input.get(x);
		recursiveTreeMaking(input,curr,x);

	}


}
void makeTreefromFile(ifstream & input,minHeap & obj)
{
	char x;
	input.get(x);
	if(x=='7')
	{
		enKey* node=new enKey;
		for(int i=0;i<8;i++)
		{
			input.get(x);
			node->str.push_back(x);
		}
		node->l=NULL;
		node->r=NULL;
		obj.insert(node);

	}
	else
	{
		if(x=='1')
		{
			enKey* node=new enKey;
			node->l=NULL;
			node->r=NULL;
			obj.insert(node);
		}

		enKey* curr=obj.getMin();

		input.get(x);
		recursiveTreeMaking(input,curr,x);
		input.get(x);
		recursiveTreeMaking(input,curr,x);
	}

	input.get(x);
	input.get(x);

}
void decompress(string fileName)
{
	char x;
	minHeap obj;

	string fileN=fileName.substr(0,fileName.length()).c_str();
	string outputFileName=fileN.substr(0,fileN.length()-4);

	ifstream input(fileName.c_str());
	ofstream output;

	if(input.is_open())
	{
		makeTreefromFile(input,obj);

		output.open((outputFileName+"Z.8b").c_str(), ios::out | ios::app | ios::binary );

		enKey *root=obj.getMin();
		enKey* curr=root;

		if((root->l==NULL)&&(root->r==NULL))
		{
			input.get(x);
			while(!(input.eof()))
			{
				if(x=='1')
				{
					output<<curr->str;
				}
				input.get(x);
			}
		}
		else
		{
			input.get(x);
			while(!(input.eof()))
			{
				if(x=='0')
					curr=curr->l;
				else
					curr=curr->r;

				if((curr->l==NULL)&&(curr->r==NULL))
				{
					output<<curr->str;
					curr=root;
				}
				input.get(x);
			}
		}
		output.close();

		cout<<"Decompression completed"<<endl<<endl;
	}
	else
	{
		cout<<"Could not open that file ."<<endl;
	}

	input.close();



}
int main()
{
	string command;
	string fileName;
	cout<<">> ";
	getline(cin,command);
	cout<<endl;

	while ((command.length() >= 8)&&(command.substr(0,4)!="quit"))
	{
			if (command.substr(0, 8) == "compress")
			{
				fileName = command.substr(9, command.length() - 1);

				compress(fileName);
			}
			else if (command.substr(0, 10) == "decompress")
			{
				fileName = command.substr(11, command.length() - 1);

				decompress(fileName);
			}
		cout<<">> ";
		getline(cin,command);
		cout<<endl;
	}
	system("pause");
	return 0;

}


