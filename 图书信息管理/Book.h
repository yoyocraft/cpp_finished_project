#pragma once
#ifndef BOOK_H
#define BOOK_H

#include<iostream>
#include<string>
using namespace std;
class Book
{
private:
	int index;
	string mBookId;			//书号
	string mBookName;		//书名
	string mBookAuthor;		//作者
	string mBookPub;		//出版社
	string mBookPubDate;	//出版日期
	int mRemainAmount;		//库存

public:
	void SetIndex(int i) {		//设置下标
		index = i;
	}                       
	void SetInfo(string, string, string, string, string, int);//修改函数
	void SetBookId() {			//修改书号
		cin >> mBookId; 
	}                      
	void SetBookName() {		//修改书名
		cin >> mBookName; 
	}                  
	void SetBookAuthor() {		//修改作者
		cin >> mBookAuthor; 
	}              
	void SetBookPub() {			//修改出版社
		cin >> mBookPub;
	}                   
	void SetBookPubDate() {		//修改出版日期
		cin >> mBookPubDate; 
	}           
	void SetBookAmount() {		//修改数量
		cin >> mRemainAmount;
	}            
	void SetBookAmount1() { 
		mRemainAmount++; 
	}
	void SetBookAmount2() { 
		mRemainAmount--; 
	}
	void Show();

	string GetBookId() {		//获取书号
		return mBookId;
	}                   
	string GetBookName() {		//获取书名
		return mBookName; 
	}				 
	string GetBookAuthor() {	//获取作者
		return mBookAuthor; 
	}			 
	string GetBookPub() {		//获取出版社 
		return mBookPub; 
	}				 
	string GetBookPubDate() {	//获取出版日期
		return mBookPubDate;
	}         
	int GetBookAmount() {		//获取数量
		return mRemainAmount; 
	}           
};
#endif // !BOOK_H