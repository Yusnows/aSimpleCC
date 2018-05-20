/*************************************************************************
	> File Name: SymbolTab.h
	> Author: yusnows
	> Mail: YusnowsLiang@gmail.com
	> Created Time: Tue 08 May 2018 07:01:06 PM CST
    > Copyright@yusnows: All rights reserve!
 ************************************************************************/

#ifndef _SYMBOLTAB_H
#define _SYMBOLTAB_H
#include "./3rdparty/uthash.h"

/*
* use to distinguish if it is strcut, function, int, float.
*/


typedef enum SymbolType_t
{
	INT_T=0,
	FLOAT_T=1,
	ARRAY=2,
	STRUCT_T=3,
	FUNCDEF=4, //函数定义
	FUNCCALL=5, //函数调用
	SUBTAB=6,
}SbType_t;


typedef struct array_t
{
	int size;
	SbType_t type; //only be BASIC or ARRAY
	struct array_t *array;
}arr_t;

int ClearArrayList(arr_t *a);

typedef struct SymbolTab_t
{
	char *name;
	SbType_t SbType;

	//父亲符号表
	struct SymbolTab_t *parent;
	//Array, Struct, Function
	void *SubTab;
	//变量作用域, 0 表示变量为全局变量
	//int depth;
	UT_hash_handle hh;
}SbTab_t;
/*
typedef struct StructTable_t
{
	char *name;
	SbType_t SbType;
	void *SubTab;
	//变量作用域, 0 表示变量为全局变量
	int depth;
	UT_hash_handle hh;
}StTab_t;
*/
typedef struct FunctionTable_t
{
	char *name;
	int hasDef;
	SbTab_t *parent;
	SbTab_t *retType;
	SbTab_t *paraList;
	SbTab_t *FuncDef;
}FuncTab_t;

//common operation
void *AllocTab();

//Symbol table operation
SbTab_t *AllocSbTab();
SbTab_t *AllocSymbol(char *name,SbType_t type);
unsigned int GetSbTabSize(SbTab_t **tab);
int InsertSymbol(SbTab_t **tab,SbTab_t *symbol);
SbTab_t *FindSymbol(SbTab_t **tab,const char *name, SbTab_t *result);
int DeleteSymbol(SbTab_t **tab,SbTab_t *symbol);
int ClearSbTab(SbTab_t **tab);
int PrintSbTab(SbTab_t **tab);
/*
//Strcut table operation
StTab_t *AllocStTab();
StTab_t *AllocStItem(char *name,SbType_t type,int depth);
unsigned int GetStTabSize(StTab_t **tab);
int InsertStItem(StTab_t **tab, StTab_t *item);
StTab_t *FindStItem(StTab_t **tab, const char *name, StTab_t *result);
int DeleteStItem(StTab_t **tab, StTab_t *item);
int ClearStTab(StTab_t **tab);
int PrintStTab(StTab_t **tab);
*/

//Function table operation
int ClearFuncTab(FuncTab_t *tab);
#endif