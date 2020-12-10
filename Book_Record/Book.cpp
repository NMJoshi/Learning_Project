//DEC-20
#include<fstream>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<iomanip>
#include<conio.h>
using namespace std;
class Book{
	private:
		int bookid;
		char title[20];
		float price;
	public:
	Book(){
		bookid=0;
		strcpy(title,"None");
		price=0;
	}
	void getdata();	
	void showdata();
	int storedata();
	void viewdata();
	void searchdata(char *);
	void deletedata(char *);
	void updatedata(char *);
};
void Book::getdata(){
	cout<<"Enter Bookid: ";
	cin>>bookid;
	cout<<"\nEnter Title: ";
	cin.ignore();
	cin.getline(title,19);
	cout<<"\nEnter Price: ";
	cin>>price;
}
void Book::showdata(){
	cout<<"\nBOOK_ID  "<<setw(12)<<"TITLE"<<setw(12)<<"PRICE\n";
	cout<<setw(7)<<bookid<<setw(12)<<title<<setw(12)<<price;
}
int Book::storedata(){
	if(bookid==0&&price==0){
		cout<<"Book Data Not Initialized";
		return 0;
	}
	else{
		ofstream fout;
		fout.open("Record.dat",ios::app|ios::binary);
		fout.write((char*)this,sizeof(*this));
		fout.close();
		return 1;
	}
}
void Book::viewdata(){
	ifstream fin;
	fin.open("Record.dat",ios::in|ios::binary);
	if (!fin){
		cout<<"\nFIle Not Found!";
	}
	else{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof()){
			showdata();
			fin.read((char*)this,sizeof(*this));
		}
		fin.close();
	}
}
void Book::searchdata(char *t){
	int flag=0;
	ifstream fin;
	fin.open("Record.dat",ios::in|ios::binary);
	if(!fin){
		cout<<"\nFile Not Found!";
	}
	else{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof()){
			if(!strcmp(t,title)){//strcmp return 0 if both are same
				showdata();
				flag++;
			}
			fin.read((char*)this,sizeof(*this));
		}
		if(flag==0){
			cout<<"Record Not Found!";
		}
		fin.close();
	}
}
void Book::deletedata(char *t){
	ifstream fin;
	ofstream fout;
	fin.open("Record.dat",ios::in|ios::binary);
	if(!fin){
		cout<<"File Not Found!";
	}
	else{
		fout.open("temp.dat",ios::out|ios::binary);
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof()){
			if(strcmp(title,t)){
				fout.write((char *)this,sizeof(*this));
			}
			fin.read((char*)this,sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("Record.dat");
		rename("temp.dat","Record.dat");//(old,new)
		cout<<"Record Deleted Successfully!";
	}
}
void Book::updatedata(char *t){
	fstream file;
	file.open("Record.dat",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0);
	file.read((char*)this,sizeof(*this));
	while(!file.eof()){
		if(!strcmp(t,title)){
			cout<<"Enter Update data:\n";
			getdata();
			file.seekp(file.tellp()-sizeof(*this));
			file.write((char*)this,sizeof(*this));
		}
		file.read((char*)this,sizeof(*this));
	}
	
}
int manu(){
	cout<<"\n Book Management";
	cout<<"\n1. Insert Book Record";
	cout<<"\n2. View All book Record";
	cout<<"\n3. Search book Record";
	cout<<"\n4. Delete book Record";
	cout<<"\n5. Update book Record";
	cout<<"\n6. Exit";
	int choice;
	cout<<"\n\nEnter Your Choice :";
	cin>>choice;
	return choice;
}
int main(){
	Book b;
	while(1){
		char str[20];
		system("cls");
		switch(manu()){
			case 1:{
				b.getdata();
				b.storedata();
				cout<<"\nData Inserted Successfully!";
				getch();
				break;
			}	
			case 2:{
				b.viewdata();
				getch();
				break;
			}
			case 3:{
				cout<<"\nEnter Title of book to search:";
				cin.ignore();
				cin.getline(str,19);
				b.searchdata(str);
				getch();
				break;
			}
			case 4: {
				cout<<"\nEnter Title of book to Delete:";
				cin.ignore();
				cin.getline(str,19);
				b.deletedata(str);
				getch();
				break;
			}
			case 5:{
				cout<<"\nEnter Title of book to Update:";
				cin.ignore();
				cin.getline(str,19);
				b.updatedata(str);
				cout<<"\nDATA UPDATED SUCCESSFULLY!";
				getch();
				break;
			}	
			case 6:{
				system("color 0C");
				cout<<"THANK YOU, FOR USING APPLICATION!";
				cout<<"\nPress Any Key to Exit";
				getch();
				exit(0);
				break;
			}
			default:{
				cout<<"\nInvalied Choice!";
				break;
			}
			getch();
		}
	}
	return 0;
}
