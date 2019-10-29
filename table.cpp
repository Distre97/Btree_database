#include "table.h"
#include "ulity.h"
char r_count=0;

/*******************************************
/func:查找功能

/param:查找类型
bigt表示大于等于，smallt表示小于等于，
betwn表示小于某值，大于某值

/param:查找的属性名

/param:查找的值

/param:查找返回的行数据
********************************************/
void table::Search(int type,string atri,long long value1,long long value2)
{
	ifstream index;
	string in_name;
	atri.copy((char*)&in_name,atri.size());
	in_name.append(".index");
	// BTree<long long> a();
	//先判断有没索引文件
	if(table::Exist_index(in_name)==true)
	{
		//有索引文件且能被打开，则使用索引搜索
		BTree<long long> a = Index_from_files(in_name);
		a.Search_(a.m_proot,type,value1,value2);
	}
	else
	{
		//没有的话先建立再查询	
		BTree<long long> a=table::Index(atri);
		index.open(in_name,ios::in);
		if(index.is_open())
		{
			a.Search_(a.m_proot,type,value1,value2);
		}
		else{
			Error("opening index file");
			return;
		}
	}
	Print();
	result.erase(result.begin(),result.end());
}
/*******************************************
/func:判断是否存在名为atri的索引文件

/param:索引文件名
********************************************/
bool table::Exist_index(string atri)
{
	ifstream file;
	file.open(atri);
	if(file.is_open())
		return true;
	else
		return false;
}
/*******************************************
/func:添加一行数据

/param:属性名组

/param:对应值组
********************************************/
bool table::Append(vector<string> atri,vector<long long> value)
{
	long long data;
	ofstream wr;
	{
		WSpinLock<char> locker( &r_count );
		wr.open(table::get_file_name(),ios::out);
		wr.seekp(0,ios::end);
		for(int i=0;i<100;i++){
			for(int j=0;j<atri.size();j++){
				if(_atri_in_file.at(i)!=atri.at(j))
				{
					data = INFINITY;
					wr.write((char*)&data,8);
				}
				else
				{
					wr.write((char*)&value.at(j),8);
					break;
				}
			}
		}
		wr.close();
	}	
	cout<<"Append!"<<endl;
}
/*******************************************
/func:生成值索引

/param:索引的属性名
********************************************/
BTree<long long> table::Index(string atri)
{
	int n;
	char* arr;	
	string in_name=atri+".index";	
	int col = table::get_data_colum();
	long long data;

	//获取目标属性在文件中的位置
	for(int i=0;i<100;i++)
	{
		if(this->_atri_in_file.at(i)==atri)
		{
			n=i;
			break;
		}
		Error("No attribute in data files!");
	}

	long pos=this->atri_l;//获取数据在文件中的开始位置
	Pair<long long> p;//保存数据用于插入的键值对
	
	//插入索引，并写入索引文件同时进行
	//保证读并发，此时由于还没创建索引文件
	//所以不用保证写并发
	RSpinLock<char> r1(&r_count);
	{
		BTree<long long> a(TREE_SIZE);
		ofstream index;//写入的索引文件流
		index.open(in_name,ios::out|ios::app);
		index.seekp(0,ios::end);
		ifstream r_data;//读原文件流
		r_data.open(this->file_name,ios::in);
		for(int j=0;j<col;j++)
		{
			pos += COLUM_SIZE*j;
			r_data.seekg(pos);
			r_data.read((char*)&data,8);
			p.item = data;
			p.num = j;
			a.Insert(p);
			arr = (char*)&data;
			index.write(arr,8);
			index.write((char*)&j,4);
		}
		r_data.close();
		index.close();
		return a;
	}

}
/*******************************************
/func:读取文件并存入容器，初始化表

/param：返回的属性名容器

/param:返回的数据容器
********************************************/
void table::Read_atri(vector<string> atri)
{
	
	int i,j=0;
	ifstream r_atri;
	char a;
	long long d;
	r_atri.open(this->file_name,ios::in);
	r_atri.seekg(0,ios::beg);
	long pos = r_atri.tellg();
	string s="";
	RSpinLock<char> r1(&r_count);
	{

		//读取属性名序列
		for(i=0;i<100;i++)
		{
			while(true)
			{
				r_atri.read(&a,1);
				if(a!='@')
				{
					s+=a;
				}
				else
					break;
			}

			atri.push_back(s);//读入内存
			table::atri_l = table::atri_l+1+s.size();
			s.erase(s.begin(),s.end());
		}
		r_atri.close();
	}
}
/*******************************************
/func:读取索引文件

/param：文件名

/return:索引的B+树
********************************************/
BTree<long long> Index_from_files(string file_name)
{
	BTree<long long> a(TREE_SIZE);
	Pair<long long> temp;
	ifstream ind;
	//读写互斥
	RSpinLock<char> r1(&r_count);
	{
		ind.open(file_name,ios::in);
		if(ind.is_open())
		{
			ind.seekg(0,ios::beg);
			for(int i=0;i<get_index_length(file_name);i++)
			{
				ind.read((char*)&temp.item,8);
				ind.read((char*)&temp.num,4);
				a.Insert(temp);
			}
		}
		ind.close();
	}
	return a;
}


string table::get_file_name()
{
	return this->file_name;
}
int table::_get_atri_l()
{
	return table::atri_l;
}
/*******************************************
/func:读取文件大小

/param：文件名

/return:文件大小,int型
********************************************/
int get_file_length(string file_name)
{
	long l,m;
	ifstream f(file_name,ios::in);
	l = f.tellg();
	f.seekg(0,ios::end);
	m = f.tellg();
	f.close();
	return (int)(m-l);
}
/*******************************************
/func:读取索引文件大小

/param：文件名

/return:文件大小,int型
********************************************/
int get_index_length(string name)
{
	int l = get_file_length(name);
	return (int)l/12;
}
/*******************************************
/func:读取文件的数据行数

/return:数据行数
********************************************/
int table::get_data_colum()
{
	int f_s = get_file_length(table::get_file_name());
	int a_l = table::_get_atri_l();
	int d_c = (f_s-a_l)/COLUM_SIZE;
	return d_c;
}
/*******************************************
/func:打印查找的数据
********************************************/
void Print(){
	long long data;
	// string s;
	Read_atri(this->_atri_in_file);
	//判断是否有符合查询标准的数据
	if(result.size()<=0){
		Error("no result!");
		return;//没有直接退出
	}
	else
	{//先打印属性名
		for(int i=0;i<100;i++)
			printf("%s\t", _atri_in_file.at(i));
	}
	//再打印数据，读互斥
	RSpinLock<char> r1(&r_count);
	{
		ifstream pr;
		pr.open(table::get_file_name(),ios::in);
		int pos = table::_get_atri_l();
		for(int i=0;i<result.size();i++)
	    {
	    	pr.seekg(pos+COLUM_SIZE*result.at(i),ios::beg);
	    	for(int j=0;j<100;j++){
	    		pr.read((char*)&data,8);
	    		printf("%lld\t", data);
	    	}
	    }
	    pr.close();
	}
}