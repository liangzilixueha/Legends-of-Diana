#include <cstdio>
#include <windows.h> 

using namespace std;

const HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

struct Button
{
	int x,y,lenx,leny,color1,color0;
	char * s;
	bool nowpoint;
	Button () ;
	void Print(bool a=1,int Nowcolor=7);
	bool SetButton (int x,int y,int lenx,int leny,int color1,int color0,const char s[],int Nowcolor=7);
	bool Check(int Nowcolor=7);
	void Delete(); 
};

Button::Button () 
{
	x=y=0;
	lenx=4;
	leny=1;
	color1=7;
	color0=0x70;
	nowpoint=0;
	s=new char [4];
	* s=* (s+2)='n';
	* (s+1)='o';
	* (s+3)='e';	
}

void Button::Print(bool a,int Nowcolor)
{
	if(a) SetConsoleTextAttribute(handle,this->color1);
	else SetConsoleTextAttribute(handle,this->color0);
	for(int i=0;i<this->leny;++i)
	{
		COORD pos = {this->x,this->y+i};
    	SetConsoleCursorPosition(handle,pos); 
		for(int j=0;j<this->lenx;++j)
		{
			printf("%c",*(this->s+i*lenx+j));
		}
	}
	SetConsoleTextAttribute(handle,Nowcolor);
}

bool Button::SetButton (int x,int y,int lenx,int leny,int color1,int color0,const char s[],int Nowcolor)
{
	this->x=x;
	this->y=y;
	this->lenx=lenx;
	this->leny=leny;
	this->color1=color1;
	this->color0=color0;
	delete [] this->s;
	int lens=strlen(s);
	this->s=new char [lens];
	for(int i=0;i<=lens;++i)
		* (this->s+i)=s[i];
	this->Print(1,Nowcolor);
	if(lens!=lenx*leny) return 0;
	else return 1;
}

bool Button::Check(int Nowcolor)
{
	POINT APOINT;
    GetCursorPos(&APOINT);
    ScreenToClient(GetForegroundWindow(),&APOINT);
    APOINT.y=APOINT.y/16;
	APOINT.x=APOINT.x/8;
	if(APOINT.x>=this->x&&APOINT.x<=this->x+this->lenx-1&&APOINT.y>=this->y&&APOINT.y<=this->y+this->leny-1)
	{
		if(this->nowpoint)
		{
			this->Print(0,Nowcolor);
			this->nowpoint=0;
		}
		if((GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1:0) return 1;
	}
	else
	{
		if(!this->nowpoint)
		{
			this->Print(1,Nowcolor);
			this->nowpoint=1;
		}
	}
	return 0;
}

void Button::Delete()
{
	for(int i=0;i<this->leny;++i)
	{
		COORD pos = {this->x,this->y+i};
    	SetConsoleCursorPosition(handle,pos); 
		for(int j=0;j<this->lenx;++j)
		{
			printf(" ");
		}
	}
	delete [] this->s;	
}

int main ()
{
	Button a;
	a.SetButton(1,10,4,1,7,0x70,"abcd");
	while(1)
	{
		if(a.Check())break;
	}
	a.Delete();
	return 0;	
}