// playground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fab/fab.h"
#include <vector>
#include <map>
#include <string>
using namespace std;
struct stt
{
	int x, y, z;
};
int sss[2][4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
11, 12, 13, 14, 15, 16, 101, 102, 103, 104, 105, 106, 107, 108, 109,
1010, 1011, 1012, 1013, 1014, 1015, 1016 };
class MyClass
{
public:
	MyClass(){}
	~MyClass(){}
	virtual void func_test(){
		printf("mycl\n");
	}

private:

};
class MyClass2:public MyClass
{
	
	int ddd;
public:
	MyClass2(int g){
		char nnn[20] = { 0 };
		ddd = g;
	}
	MyClass2(MyClass2&){
		ddd = 0;
	}
	void func_test(){
		printf("mycl2\n");
	}
};

class testc
{
public:
	testc(){}
	virtual void func_test(){
		printf("mycl\n");
	}
	//string get_cname()
	//{
	//	return typeid(*this).name();
	//}
};
class t1estc0 :public testc
{
	int ggg;
public:
	t1estc0(int i){ ggg = i; }
	t1estc0(){}
	t1estc0(t1estc0&){}
	
};
struct testalias
{
	int jj;
	int& ij = jj;
};


//class testc1 :public testc0
//{
//public:
//	testc1(long j){}
//	testc1(testc1&){}
//};
/*#include <windows.h>
#include <tchar.h>  
#include <locale.h>*/  
#include <ShlObj.h>
#include <typeinfo>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#define eprintf(format, ...)   fprintf (stderr, format , __VA_ARGS__)
int _tmain(int argc, _TCHAR* argv[])
{
	vector<stt> vstt;
	stt st0{ 1, 2, 3 };
	stt st1{ 4, 5, 6 };
	stt st2{ 1, 2, 3 };
	vstt.push_back(st0);
	vstt.push_back(st1);
	vstt.push_back(st2);
	//int (*s)[4]= sss;
	int *p = (int*)sss;
	for (int ix = 0; ix < 32;ix++)
	{
		printf("%d\n", *p++);
	}
	MyClass* pm = new MyClass2(1);
	printf("name:::%s\n",typeid(*pm).name());
	
	testc* pcn = new t1estc0(1);
	//testc* pcn2 = new testc1(1L);
	printf("name:%s\n", typeid(*pcn).name());
	//printf("name:%s\n", typeid(*pcn2).name());

	eprintf("");
	//mms->func_test();
	delete pm;
	using namespace fab;
	MyClass2 mmg(1);
	Factory<MyClass> ft;
	ft.Register("MyClass2", [](int ss){return new MyClass2(ss); });
	ft.Register("MyClass3", [](MyClass2& ss){return new MyClass2(ss); });

	auto mc = ft.Create("MyClass3",mmg);
	mc->func_test();
	int iy = -1;
	int ddd = iy > 0 ? 1 : 2 + 3;
	map<string, stt> mptext;
	mptext["x"].x = 0;
	mptext["x"].y= 0;

	mptext["y"].y = 1;
	mptext["z"].z = 2;
	static int ssy;
	struct sss
	{
		void fun()
		{
			ssy = 1;
		}
	};
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 ret = trans*glm::vec4(1000.0f, 100.0f, 1.0f, 1.0f);
	printf("%f,%f,%f\n", ret.x, ret.y, ret.z);
	vector<int> vtest = { 1, 3, 4, 5 };
	for (auto& iv:vtest)
	{
		iv = iv + 2;
	}
	testalias mya;
	mya.jj = 1111;
	printf("ij=%d\n", mya.ij);
	int tst_int;
	printf("%s\n",typeid(tst_int).name());
	char* tst_str = "gfsdgd";
	printf("%s\n", typeid(tst_str).name());
	//testc cn;
	//printf("name:%s\n", cn.get_cname());
	//testc0 cn0;
	//printf("name:%s\n", cn0.get_cname());
 //   testc1 cn1;
	//printf("name:%s\n", cn1.get_cname());



	OPENFILENAME ofn = { sizeof(OPENFILENAME) };
	return 0;
}

