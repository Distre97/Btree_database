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
void table::Search(string type,string atri,long long* value,vector<vector<long long > > v)
{
	ifstream index;
	string in_name=atri+".index";
	BTree<long long> a;
	//先判断有没索引文件
	if(table::Exist_index(in_name)==true)
	{
		index.open(in_name,ios::in);
		if(index.is_open())
		{
			//有索引文件且能被打开，则使用索引搜索
			table::Search_by_Index(type,atri,value,v,a);
		}
		else
			Error("opening index file");
	}
	else
	{
		//没有的话先建立再查询	
		a=table::Index(atri);
		index.open(in_name,ios::in);
		if(index.is_open())
		{
			table::Search_by_Index(type,atri,value,v,a);
		}
		else
			Error("opening index file");
	}
	a.Destory();
}
/*******************************************
/func:通过索引查找对应数据（未完成）

/param:查找类型
bigt表示大于等于，smallt表示小于等于，
betwn表示小于某值，大于某值

/param:查找的属性名

/param:查找的值

/param:查找返回的行数据
********************************************/
void table::Search_by_Index(string type,string atri,long long* value,
	vector<vector<long long>> v,BTree<long long > a){
	long long min;
	int i,j;

	switch(type){
		case BIGERTHEN:
			break;
		case SMALLTHEN:
			break;
		case BETWEEN:
			break;
		default:
			Error("search type");
			break;
	}
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
/func:添加一行数据()

/param:属性名组

/param:对应值组
********************************************/
bool table::Append(string* atri,int* value)
{
	cout<<"Append"<<endl;
}
/*******************************************
/func:生成文件名索引（未完成）

/param:索引名
********************************************/
BTree<char> table::Index_atri(string atri)
{
	BTree<char> c(TREE_SIZE);

	return c;
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
		r_data.open(this->file_name.ios::in);
		for(int j=0;j<col;j++)
		{
			pos += COLUM_SIZE*j;
			r_data.seekg(pos);
			r_data.read(&data,8);
			p.item = data;
			p.num = j;
			a.Insert(p);
			arr = (char*)&data;
			index.write(arr,8);
			index.write((char*)&j,4);
		}
		r_data.close();
		index.close();
		a.Destory();
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
	vector<long long> data;
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
		//读取每一行，读入内存
		// int d_c = table::get_data_colum();
		// // printf("%d\n", d_c);
		// while(j<d_c)
		// {
		// 	data.clear();
		// 	for(i=0;i<100;i++)
		// 	{
		// 		r_atri.read((char*)&d,8);
		// 		data.push_back(d);
		// 		printf("%lld ", d);

		// 		// cout<<data.at(i)<<" ";
		// 	}
		// 	_data.push_back(data);

		// 	j++;
		// }
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
	BTree<long long> a;
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
/func:读取索引大小

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
	int d_c = (f_s-a_l)/800;
	return d_c;
}
