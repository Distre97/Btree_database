#include "table.h"
#include "ulity.h"

char r_count=0;

/*******************************************
/func:查找功能（未完成）

/param:查找类型
bigt表示大于等于，smallt表示小于等于，
betwn表示小于某值，大于某值

/param:查找的属性名

/param:查找的值

/param:查找返回的行数据
********************************************/
void table::Search(string type,string atri,long long value,vector<vector<long long>> v)
{
	ifstream index;
	//先判断有没索引文件
	if(table::Exist_index(atri)==1)
	{
		index.open(atri);
		if(index.is_open())
		{
			//有索引文件且能被打开，则使用索引搜索
			table::Search_by_Index(type,atri,value,v);
		}
		else
			Error("opening index file");
	}
	else
	{
		//没有的话先建立再查询
		table::Index(1,atri);
		index.open(atri);
		if(index.is_open())
		{
			table::Search_by_Index(type,atri,value,v);
		}
		else
			Error("opening index file");
	}
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
void table::Search_by_Index(string type,string atri,long long value,
	vector<vector<long long>> v){
	cout<<"search by index\n";
}
/*******************************************
/func:判断是否存在名为atri的索引文件

/param:索引文件名
********************************************/
int table::Exist_index(string atri)
{
	ifstream file;
	file.open(atri);
	if(file.is_open())
		return 1;
	else
		return 0;
}
/*******************************************
/func:添加一行数据

/param:属性名组

/param:对应值组
********************************************/
int table::Append(string* atri,int* value)
{
	cout<<"Append"<<endl;
}
/*******************************************
/func:生成索引文件（未完成）

/param：索引类型，
0表示属性名索引，1表示单个属性的值索引

/param:索引文件名
********************************************/
void table::Index(int type,string atri)
{
	cout<<"create index!"<<endl;
}
/*******************************************
/func:读取文件并存入容器，初始化表

/param：返回的属性名容器

/param:返回的数据容器
********************************************/
void table::Read_data_and_atri(vector<string> atri,vector<vector<long long>> _data)
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
					// cout<<a<<" ";
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

/return:文件大小,long型
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
/func:读取文件的数据行数

/return:数据行数
********************************************/
int table::get_data_colum()
{
	int f_s = get_file_length(table::get_file_name());
	int a_l = table::_get_atri_l();
	int d_c = (f_s-a_l)/800;
	// printf("%d %d %d\n", f_s,a_l,d_c);
	return d_c;
}
