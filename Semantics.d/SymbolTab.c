/*************************************************************************
	> File Name: SymbolTab.c
	> Author: yusnows
	> Mail: YusnowsLiang@gmail.com
	> Created Time: Tue 08 May 2018 07:01:30 PM CST
    > Copyright@yusnows: All rights reserve!
 ************************************************************************/

#include<stdio.h>
#include "SymbolTab.h"
#include "./3rdparty/uthash.h"
#include <string.h>

int ClearArrayList(arr_t *a)
{
	if(a!=NULL)
		ClearArrayList(a->array);
	free(a);
	return 0;
}

void *AllocTab()
{
	void *ret;
	ret=NULL;
	return ret;
}


SbTab_t *AllocSbTab()
{
	SbTab_t *ret;
	ret=NULL;
	return ret;
}

SbTab_t *AllocSymbol(char *namev,SbType_t type)
{
	SbTab_t *ret;
	ret=(SbTab_t *)malloc(sizeof(SbTab_t));
	char*t;
    t=(char*)malloc(sizeof(char )*(strlen(namev)+1));
	strcpy(t,namev);
	ret->name=t;
	ret->SbType=type;
//	ret->depth=depth;
//	if(ret->SbType!=INT_T)
	ret->SubTab=NULL;
	ret->parent=NULL;
	return ret;
}

unsigned int GetSbTabSize(SbTab_t **tab)
{
	if(tab==NULL || *tab==NULL)
		return 0;
	unsigned int ret=0;
	ret=HASH_COUNT(*tab);
	return ret;
}

int InsertSymbol(SbTab_t **tab,SbTab_t *symbol)
{
	if(symbol==NULL)
		return 1;
	if(symbol->name==NULL)
		return 2;
	HASH_ADD_KEYPTR( hh, *tab, symbol->name, strlen(symbol->name), symbol );
	return 0;
}

SbTab_t *FindSymbol(SbTab_t **tab,const char *name, SbTab_t *result)
{
	if(tab==NULL || *tab==NULL)
		return NULL;
	result = NULL;
	HASH_FIND_STR(*tab,name,result);
	return result;
}

int DeleteSymbol(SbTab_t **tab,SbTab_t *symbol)
{
	if(*tab==NULL)
		return 0;
	HASH_DEL(*tab,symbol);
	if(symbol->SbType==STRUCT_T)
	{
		ClearSbTab((SbTab_t**)(&((symbol->SubTab))));
	}
	else if(symbol->SbType==FUNCDEF)
	{
		ClearFuncTab((FuncTab_t*)(symbol->SubTab));
	}
	else if(symbol->SbType==ARRAY)
	{
		ClearArrayList((arr_t*)(symbol->SubTab));
	}
	free(symbol);
	return 0;
}

int ClearSbTab(SbTab_t **tab)
{
	if(tab==NULL || *tab==NULL)
		return 0;
	SbTab_t *cur, *tmp;
	HASH_ITER(hh, *tab, cur, tmp) {
		DeleteSymbol(tab,cur);
//		free(cur);
	}
	return 0;
}

int PrintSymbolTab(SbTab_t **tab)
{
	SbTab_t *s;
	for(s=*tab;s!=NULL;s=s->hh.next)
	{
		printf("Symbol name is %s, ",s->name);
		switch(s->SbType)
		{
			case INT_T: printf("It is a int symbol\n");break;
			case FLOAT_T:  printf("It is a float symbol\n");break;
			case ARRAY: printf("It is a array\n");break;
			case FUNCDEF: printf("It is a Function\n");break;
			case STRUCT_T: printf("It is a Struct\n");break;
			default:break;
		}
	}
	return 0;
}

int ClearFuncTab(FuncTab_t *tab)
{
	ClearSbTab(&(tab->retType));
	ClearSbTab(&(tab->paraList));
	ClearSbTab(&(tab->FuncDef));
	return 0;
}

/*
//Strcut table operation
StTab_t *AllocStTab()
{
	StTab_t *ret=NULL;
	return ret;
}
StTab_t *AllocStItem(char *name,SbType_t type)
{
	StTab_t *ret;
	ret=(StTab_t*)malloc(sizeof(StTab_t));
	strcpy(ret->name,name);
	ret->SbType=type;
//	ret->depth=depth;
	return ret;
}
unsigned int GetStTabSize(StTab_t **tab)
{
	unsigned int ret;
	ret=HASH_COUNT(*tab);
	return ret;
}
int InsertStItem(StTab_t **tab, StTab_t *item)
{
	HASH_ADD_KEYPTR( hh, *tab, item->name, strlen(item->name), item );
	return 0;
}
StTab_t *FindStItem(StTab_t **tab, const char *name, StTab_t *result)
{
	HASH_FIND_STR(*tab,name,result);
	return result;
}
int DeleteStItem(StTab_t **tab, StTab_t *item)
{
	HASH_DEL(*tab,item);
	if(item->SbType==STRUCT_T)
	{
		ClearSymbolTab((SbTab_t*)&(item->SubTab));
	}
	else if(item->SbType==FUNCDEF)
	{

	}
	free(item);
	return 0;
}
int ClearStTab(StTab_t **tab)
{
	SbTab_t *cur, *tmp;
	HASH_ITER(hh, *tab, cur, tmp) {
		DeleteSymbol(*tab,cur);
//		free(cur);
	}
	return 0;
}
int PrintStTab(StTab_t **tab)
{

	StTab_t *s;
	for(s=*tab;s!=NULL;s=s->hh.next)
	{
		printf("Symbol name is %s, ",s->name);
		switch(s->SbType)
		{
			case BASIC: printf("It is a basic symbol\n");break;
			case ARRAY: printf("It is a array\n");break;
			case FUNCDEF: printf("It is a Function\n");break;
			case STRUCT_T: printf("It is a Struct\n");break;
			default:break;
		}
	}
	return 0;
}
*/