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
/func:读取文件并存入容器(未完成)

/param：返回的属性名容器

/param:返回的数据容器
********************************************/
void table::Read_data_and_atri(vector<string> atri,vector<vector<long long>> data)
{
	RSpinLock<char> r1(&r_count);
	{
		ifstream r_atri;
		r_atri.open(this->file_name,ios::in);

		r_atri.close();
	}
}

string table::get_file_name()
{
	return this->file_name;
}


