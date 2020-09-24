#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<graphics.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

char login[20];
int round=0;

class property
{ int no,amount,status;
  char prop[25];
  char owner[20];
  public:
  property()
  {
	status=0;
  }
  void assignprop(char p[])
	{strcpy(prop,p);}
  void subno(int x)
	{no-=x;}
  int retstatus()
	{return status;}

  int retamount()
	{return amount;}

  char* retname()
	{return prop;}

  int retpos()
	{return no;}

  void updatestatus(int a)
	{status=a;}

  void assignowner(char a[])
	{strcpy(owner,a);}

  char* retowner()
	{return owner;}

  void bdisplay(int x,float y)
	{
		gotoxy(x,y++);
		puts(prop);
		gotoxy(x,y);
		cout<<"$"<<amount;
	}

  void display(int x,int y)
	{
		gotoxy(x,y++);
		cout<<"Name:";puts(prop);
		gotoxy(x,y++);
		cout<<"Amount:"<<amount;
		gotoxy(x,y++);

		if(status==0)
			{cout<<"Owned By: Nobody";}
		else
			{cout<<"Owned By: ";puts(owner);}
	}

  void mdisplay(int p=4,int q=4)
  {
   gotoxy(p,q++);
   cout<<"Name:"; puts(prop);
   gotoxy(p,q++);
   cout<<"Amount:"<<amount;
   gotoxy(p,q);
   cout<<"Position:"<<no;
  }

  void accept()
  {
	 property obj1;
	 ifstream hin("property.txt",ios::in|ios::binary);
	 status=0;
	 rectangle(170,200,440,350);
	 settextstyle(3,0,4);
	 outtextxy(180,150,"Create Property");
	 settextstyle(2,0,6);
	 gotoxy(24,15);
	 cout<<"Enter Name:";
	 gotoxy(24,19);
	 cout<<"Enter Position:";
	 gotoxy(23,20);cout<<"(7-10,12-15,";
	 gotoxy(23,21);cout<<" 17-20)";
	 gotoxy(24,17);cout<<"Enter Amount:";

	 gotoxy(36,15);
	 gets(prop);

	 gotoxy(37,17);
	 cin>>amount;

	 type:
	 setfillstyle(1,BLACK);
	 bar(300,290,439,349);
	 gotoxy(40,19);
	 cin>>no;
	 if(no==6||no==11||no==16||no>20||no<6)
		{
		 setcolor(RED);
		 outtextxy(160,365,"Please Enter a valid Position");
		 getch();setcolor(WHITE);
		 bar(155,360,500,400);
		 goto type;
		}
	while(hin.read((char*)&obj1,sizeof(obj1)))
		{
		 if(obj1.retpos()==no)
			{ setcolor(RED);
			  outtextxy(170,365,"This position is filled");
			  getch();setcolor(WHITE);
			  bar(155,360,500,400);
			  goto type;
			}
		}
  }
};


class player
{
  int cash,pos,type,rank;
  char user[20];char password[20];
  property props[20];
  public:
	player()
	{}
	player(int x)  //assign name,cash, pos
	{
		type=(x>0);
		cash=2500;
		switch(x)
		{
			case 1:strcpy(user,"comp1");pos=1;break;
			case 2:strcpy(user,"comp2");pos=1;break;
			case 3:strcpy(user,"comp3");pos=1;break;
			default:strcpy(user,login);pos=1;break;
		}
	}

	void assignname(char n[])
	{strcpy(user,n);}

	void assignpass(char ch[])
	{strcpy(password,ch);}

	void highdisplay(int y)
	{ gotoxy(25,y);puts(user);
	  gotoxy(40,y);cout<<cash;
	}

	void display()
	{cout<<"Name:"<<user<<"   cash:"<<cash;}

	void checkcash()
	{cout<<"Available cash = "<<cash;}

	void addpos(int q,int h)
	{pos+=h;
	 if(q==1)
	{
	 if(pos>=20)
		{::round++;}
	}
	 if(pos>20)
	  pos%=20;
	}

	void assigncash(int c)
	{cash=c;}

	int rettype()
	{
		return type;
	}
	int retcash()
	{
		return cash;
	}
	int retPos()
	{
		return pos;
	}
	char * retuser()
	{
		return user;
	}
	char * retpass()
	{
		return password;
	}
	void addcash(int x)
	{
		cash+=x;
	}
	void acceptname();
	void print();

};

  void player::acceptname()
{
	cout<<"Enter Name:";
	gets(user);
}

void buy(player &x)
{

	property obj;
	fstream fin("property.txt",ios::in|ios::out|ios::binary);

      if(strcmp(x.retuser(),login)==0)
       {
	while(fin.read((char*)&obj,sizeof(obj)))
	  {
	    if(obj.retpos()==x.retPos())
		{
		   if(obj.retstatus()==1)
			{
			 gotoxy(23,15);
			 cout<<"This property belongs";
			 gotoxy(21,18);
			 cout<<"to ";
			 puts(obj.retowner());
			 gotoxy(24,19);
			 getch();
			 goto end;
			}
		   else
		       {
			int j=fin.tellg();
			x.addcash(-obj.retamount());
			fin.seekp(j-sizeof(obj),ios::beg);
			obj.assignowner(x.retuser());
			obj.updatestatus(1);
			fin.write((char*)&obj,sizeof(obj));
			gotoxy(23,16);
			cout<<"Property Bought";
			getch();
			goto end;
		       }
			end:
			break;
		}
	    }
      }
     else
     {
	while(fin.read((char*)&obj,sizeof(obj)))
	  {
	    if(obj.retpos()==x.retPos())
	       {
		int l=fin.tellg();
		x.addcash(-obj.retamount());
		fin.seekp(l-sizeof(obj),ios::beg);
		obj.assignowner(x.retuser());
		obj.updatestatus(1);
		fin.write((char*)&obj,sizeof(obj));
	       }
	   }
     }
      fin.close();
}

int drawdice(int x1=20,int y1=20)
{
  srand(time(NULL));
  int nu=0,nuu;
  nuu=rand()%5+1;
  rectangle(x1,y1,x1+70,y1+70);
  for(int count=0;count<6;count++,nu++)
 {
	switch(nu)
       {
	       case 4:	     //1
			delay(250);
			pieslice(x1+35,y1+35,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
		       //	cleardevice();
			break;

	       case 1:      //2
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
			//cleardevice();
			break;

	       case 5:     //3
			delay(250);
			pieslice(x1+35,y1+35,0,360,2);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
			//cleardevice();
			break;

	       case 0:     //4
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
			//cleardevice();
			break;

	       case 2:     //5
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			pieslice(x1+35,y1+35,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
			//cleardevice();
			break;

		case 3:    //6
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			pieslice(x1+23,y1+35,0,360,2);
			pieslice(x1+47,y1+35,0,360,2);
			delay(700);
			setfillstyle(0,1);
			bar(x1+1,y1+1,x1+69,y1+69);
			//cleardevice();
			break;
       }

   }
	setcolor(GREEN);
	switch(nuu)
       {
	       case 4:	     //1
			delay(250);
			pieslice(x1+35,y1+35,0,360,2);
			nuu-=3;
			break;

	       case 1:      //2
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			nuu++;
			break;

	       case 5:     //3
			delay(250);
			pieslice(x1+35,y1+35,0,360,2);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			nuu-=2;
			break;

	       case 0:     //4
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			nuu+=4;
			break;

	       case 2:     //5
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			pieslice(x1+35,y1+35,0,360,2);
			nuu+=3;
			break;

		case 3:    //6
			delay(250);
			pieslice(x1+23,y1+23,0,360,2);
			pieslice(x1+47,y1+47,0,360,2);
			pieslice(x1+47,y1+23,0,360,2);
			pieslice(x1+23,y1+47,0,360,2);
			pieslice(x1+23,y1+35,0,360,2);
			pieslice(x1+47,y1+35,0,360,2);
			nuu+=3;
			break;
       }
	  setcolor(WHITE);
	  return nuu;
}

void instructions()
{
    settextstyle(2,0,9);
    outtextxy(220,30,"RULES");
    settextstyle(2,0,6);
    outtextxy(0,100,"The object of the game is to become the wealthiest player through");
    outtextxy(0,120,"buying, renting and selling of property.");
    outtextxy(0,150,"The user begins the game by rolling the dice and depending on the");
    outtextxy(0,170,"space your token reaches, you may be entitled to buy real estate");
    outtextxy(0,190,"or other properties, or be obliged to pay rent, pay taxes, go to");
    outtextxy(0,210,"jail or gamble at the casino.");
    outtextxy(0,240,"Whenever you land on an unowned property you may buy it from the");
    outtextxy(0,260,"Bank at its printed price.");
    outtextxy(0,290,"When you land on a property that is owned by another player, the");
    outtextxy(0,310,"owner collects rent from you in accordance to that particular");
    outtextxy(0,330,"property.");
    outtextxy(0,360,"The rules of the mini games will be displayed as the player lands");
    outtextxy(0,380,"on the respective spaces.");
    setcolor(WHITE+BLINK);
    outtextxy(220,430,"Press any key continue...");
    getch();
}

  void board(player User,player c1,player c2,player c3)
{

 cleardevice();

 setcolor(WHITE);

 if(User.retPos()<=9)
{
  switch(User.retPos())
  {
	       case 1:	pieslice(433,468,0,360,2);break;
	       case 2:  pieslice(354,468,0,360,2);break;
	       case 3:  pieslice(275,468,0,360,2);break;
	       case 4:  pieslice(196,468,0,360,2);break;
	       case 5:  pieslice(117,468,0,360,2);break;
	       case 6:  pieslice(38,468,0,360,2);break;
	       case 7:  pieslice(38,389,0,360,2);break;
	       case 8:  pieslice(38,310,0,360,2);break;
	       case 9:  pieslice(38,231,0,360,2);break;
  }
}
  else if(User.retPos()>9 && User.retPos()<=18)
   {
      switch(User.retPos()-9)
	{     case 1:   pieslice(38,152,0,360,2);break;
	      case 2:   pieslice(38,73,0,360,2);break;
	      case 3:   pieslice(117,73,0,360,2);break;
	      case 4:   pieslice(196,71,0,360,2);break;
	      case 5:   pieslice(275,71,0,360,2);break;
	      case 6:   pieslice(354,71,0,360,2);break;
	      case 7:   pieslice(433,71,0,360,2);break;
	      case 8:   pieslice(433,150,0,360,2);break;
	      case 9:   pieslice(433,229,0,360,2);break;
	}
   }
  else if(User.retPos()>18 && User.retPos()<=20)
  {
     switch(User.retPos()-18)
       {     case 1:   pieslice(433,308,0,360,2);break;
	     case 2:   pieslice(433,387,0,360,2);break;
       }

  }

 setcolor(CYAN);
 if(c2.retPos()<=9)
{
  switch(c2.retPos())
  {
	       case 1:	pieslice(424,468,0,360,2);break;
	       case 2:  pieslice(345,468,0,360,2);break;
	       case 3:  pieslice(264,468,0,360,2);break;
	       case 4:  pieslice(193,468,0,360,2);break;
	       case 5:  pieslice(108,468,0,360,2);break;
	       case 6:  pieslice(29,468,0,360,2);break;
	       case 7:  pieslice(29,389,0,360,2);break;
	       case 8:  pieslice(29,310,0,360,2);break;
	       case 9:  pieslice(29,231,0,360,2);break;
  }
}
  else if(c2.retPos()>9 && c2.retPos()<=18)
   {
      switch(c2.retPos()-9)
	{     case 1:   pieslice(29,152,0,360,2);break;
	      case 2:   pieslice(29,73,0,360,2);break;
	      case 3:   pieslice(108,73,0,360,2);break;
	      case 4:   pieslice(187,71,0,360,2);break;
	      case 5:   pieslice(264,71,0,360,2);break;
	      case 6:   pieslice(345,71,0,360,2);break;
	      case 7:   pieslice(424,71,0,360,2);break;
	      case 8:   pieslice(424,150,0,360,2);break;
	      case 9:   pieslice(424,229,0,360,2);break;
	}
   }
  else if(c2.retPos()>18 && c2.retPos()<=20)
  {
     switch(c2.retPos()-18)
       {     case 1:   pieslice(424,308,0,360,2);break;
	     case 2:   pieslice(424,387,0,360,2);break;
       }

  }


 setcolor(GREEN);
 if(c1.retPos()<=9)
{
  switch(c1.retPos())
  {
	       case 1:	pieslice(415,468,0,360,2);break;
	       case 2:  pieslice(336,468,0,360,2);break;
	       case 3:  pieslice(257,468,0,360,2);break;
	       case 4:  pieslice(178,468,0,360,2);break;
	       case 5:  pieslice(99,468,0,360,2);break;
	       case 6:  pieslice(20,468,0,360,2);break;
	       case 7:  pieslice(20,389,0,360,2);break;
	       case 8:  pieslice(20,310,0,360,2);break;
	       case 9:  pieslice(20,231,0,360,2);break;
  }
}
  else if(c1.retPos()>9 && c1.retPos()<=18)
   {
      switch(c1.retPos()-9)
	{     case 1:   pieslice(20,152,0,360,2);break;
	      case 2:   pieslice(20,73,0,360,2);break;
	      case 3:   pieslice(99,73,0,360,2);break;
	      case 4:   pieslice(178,71,0,360,2);break;
	      case 5:   pieslice(277,71,0,360,2);break;
	      case 6:   pieslice(336,71,0,360,2);break;
	      case 7:   pieslice(415,71,0,360,2);break;
	      case 8:   pieslice(415,150,0,360,2);break;
	      case 9:   pieslice(415,229,0,360,2);break;
	}
   }
  else if(c1.retPos()>18 && c1.retPos()<=20)
  {
     switch(c1.retPos()-18)
       {     case 1:   pieslice(415,308,0,360,2);break;
	     case 2:   pieslice(415,387,0,360,2);break;
       }

  }


 setcolor(RED);
 if(c3.retPos()<=9)
{
  switch(c3.retPos())
  {
	       case 1:	pieslice(406,468,0,360,2);break;
	       case 2:  pieslice(327,468,0,360,2);break;
	       case 3:  pieslice(248,468,0,360,2);break;
	       case 4:  pieslice(169,468,0,360,2);break;
	       case 5:  pieslice(90,468,0,360,2);break;
	       case 6:  pieslice(11,468,0,360,2);break;
	       case 7:  pieslice(11,389,0,360,2);break;
	       case 8:  pieslice(11,310,0,360,2);break;
	       case 9:  pieslice(11,231,0,360,2);break;
  }
}
  else if(c3.retPos()>9 && c3.retPos()<=18)
   {
      switch(c3.retPos()-9)
	{     case 1:   pieslice(11,152,0,360,2);break;
	      case 2:   pieslice(11,73,0,360,2);break;
	      case 3:   pieslice(90,73,0,360,2);break;
	      case 4:   pieslice(169,71,0,360,2);break;
	      case 5:   pieslice(248,71,0,360,2);break;
	      case 6:   pieslice(327,71,0,360,2);break;
	      case 7:   pieslice(421,71,0,360,2);break;
	      case 8:   pieslice(406,150,0,360,2);break;
	      case 9:   pieslice(406,229,0,360,2);break;
	}
   }
  else if(c3.retPos()>18 && c3.retPos()<=20)
  {
     switch(c3.retPos()-18)
       {     case 1:   pieslice(406,308,0,360,2);break;
	     case 2:   pieslice(406,387,0,360,2);break;
       }

  }

   setcolor(WHITE);
   rectangle(0,0,475,475);
   rectangle(80,80,396,396);

   for(int i=80;i<=396;i+=79) //bottom
   line(i,396,i,475);
   for(int k=396;k>=80;k-=79) //right
   line(396,k,475,k);
   for(int h=396;h>=80;h-=79) //left
   line(0,h,80,h);
   for(int u=80;u<=396;u+=79) //top
   line(u,0,u,80);

   settextstyle(0,0,0);
   outtextxy(23,8,"JAIL");
   setlinestyle(0,0,3);  //thickness=3
   rectangle(17,25,58,60);
   for(int y=28;y<60;y+=10)
   line(y,25,y,60);

   outtextxy(14,405,"CASINO");
   settextstyle(0,0,3);
   outtextxy(15,425,"$$");

   setlinestyle(0,0,3);
   settextstyle(0,0,0);
   outtextxy(416,10,"LAKE");
   outtextxy(404,19,"MONOPOLY");
   arc(445,70,60,120,27);
   arc(420,23,245,300,27);
   arc(445,77,60,120,27);
   arc(420,30,245,300,27);

   setfillstyle(1,15);
   settextstyle(0,0,3);
   outtextxy(405,412,"GO!");
   bar(417,448,450,450);
   setlinestyle(0,0,0);
   for(int a=453,s=445;s<=449;s++,a--)
   line(a,s,a+5,s);
   for(int q=453,w=453;w>=449;w--,q--)
   line(q,w,q+5,w);
   for(int p=417,pp=444,hh=455;p>411;p--,pp++,hh--)
   line(p,pp,p,hh);

   gotoxy(64,4);cout<<"Cash:";
   cout<<User.retcash();
   gotoxy(64,3);
   cout<<"Name:";
   puts(User.retuser());

   property obj;
   ifstream fin("property.txt",ios::in|ios::binary);

   settextstyle(0,0,1);
   outtextxy(330,415,"st1");
   outtextxy(330,425,"$100");

   outtextxy(250,415,"st2");
   outtextxy(250,425,"$200");

   outtextxy(170,415,"st3");
   outtextxy(170,425,"$300");

   outtextxy(90,415,"st4");
   outtextxy(90,425,"$400");

   while(fin.read((char*)&obj,sizeof(obj)))
	{ switch(obj.retpos()-6)
		{      case 1: obj.bdisplay(2,22);break;
		       case 2: obj.bdisplay(2,17);break;
		       case 3: obj.bdisplay(2,12);break;
		       case 4: obj.bdisplay(2,7);break;
		       case 6: obj.bdisplay(12,2);break;
		       case 7: obj.bdisplay(22,2);break;
		       case 8: obj.bdisplay(32,2);break;
		       case 9: obj.bdisplay(42,2);break;
		}
	  switch(obj.retpos()-16)
		{	case 1: obj.bdisplay(52,7);break;
			case 2: obj.bdisplay(52,12);break;
			case 3: obj.bdisplay(52,17);break;
			case 4: obj.bdisplay(52,22);break;
		}
	}

   fin.close();

}

void casino(player &o)
{
  gotoxy(17,9);
  cout<<"Roll a one or two and win $50,";
  gotoxy(17,10);
  cout<<"a three or four and lose $50,";
  gotoxy(17,11);
  cout<<"a six and win $75";
  getch();
  int d=drawdice(200,270);
  getch();
  if(d==1 || d==2)
	{
	 gotoxy(17,15);
	 cout<<"Congratulations! You win $50!";
	 o.addcash(50);
	 getch();
	}
  if(d==3 || d==4)
	{
	 gotoxy(17,15);
	 cout<<"Bad luck.You lose $50";
	 o.addcash(-50);
	 getch();
	}
  if(d==6)
	{
	 gotoxy(17,15);
	 cout<<"Congratulations!! You win $75!";
	 o.addcash(100);
	 getch();
	}
}

void jail(player &p)
{
  gotoxy(17,15);
  cout<<"Bad luck. You lose $70";
  p.addcash(-70);
  getch();
}

/*void river(player &p)
{
  gotoxy(13,21);
  cout<<"....";
  getch();
} */

void turn(int a,player &User,player &c1,player &c2,player &c3)
{
  int m=0;
  char ch[10];
  menu:
  int s=0;
  property obj;
  cleardevice();
  board(User,c1,c2,c3);

  if(a==4)
  {
   gotoxy(26,9);
   cout<<"Comp3 Turn";
   delay(2000);
   c3.addpos(0,drawdice(200,270));
   delay(2000);
   board(User,c1,c2,c3);

    if(c3.retPos()==6)
	{ int n=random(2);
	  if(n==0)
	  { gotoxy(24,10);cout<<"Comp3 lost $50";
	    delay(2000);c3.addcash(-50);
	    a++;goto menu;
	  }
	  else
	  { gotoxy(24,10);cout<<"Comp3 won $50";
	    delay(2000);c3.addcash(50);
	    a++;goto menu;
	  }
	}

  if(c3.retPos()==11)
	{
	  gotoxy(24,10);
	  cout<<"Comp3 lost $50";
	  delay(2000);
	  c3.addcash(-50);
	  a++;goto menu;
	}

   if(c3.retPos()!=1)
	  {
	   rectangle(165,130,325,225);
	   gotoxy(24,10);
	   cout<<"Current space:";
	   ifstream gin("property.txt",ios::in|ios::binary);

		while(gin.read((char*)&obj,sizeof(obj)))
			{
				if(c3.retPos()==obj.retpos())
					{
					 obj.display(24,11);
					 if(obj.retstatus()==1 && strcmp(obj.retowner(),c3.retuser())!=0)
						{
						 gotoxy(24,14);
						 cout<<"Rent Paid:"<<obj.retamount()*0.1;
						 c3.addcash(-obj.retamount()*0.1);
						 delay(2000);
						 s++;
						}
					  else if(obj.retstatus() && strcmp(obj.retowner(),c3.retuser())==0)
						{s++;}
					}
			}
	    gin.close();
	   }
	    if(s==0)
	   {
	    delay(2000);
	    buy(c3);
	    gotoxy(21,16);
	    cout<<"Comp3 bought property";
	    delay(2000);
	   }
	   a++;
	   goto menu;

  }

  if(a==3)
  {
   gotoxy(26,9);
   cout<<"Comp2 Turn";
   delay(2000);
   c2.addpos(0,drawdice(200,270));
   delay(2000);
   board(User,c1,c2,c3);

   if(c2.retPos()==6)
	{ int n=random(2);
	  if(n==0)
	  { gotoxy(24,10);cout<<"Comp2 lost $50";
	    delay(2000);c2.addcash(-50);
	    a++;goto menu;
	  }
	  else
	  { gotoxy(24,10);cout<<"Comp2 won $50";
	    delay(2000);c2.addcash(50);
	    a++;goto menu;
	  }
	}

  if(c2.retPos()==11)
	{
	  gotoxy(24,10);
	  cout<<"Comp2 lost $50";
	  delay(2000);
	  c2.addcash(-50);
	  a++;goto menu;
	}

   if(c2.retPos()!=1)
	  {
	   rectangle(165,130,325,225);
	   gotoxy(24,10);
	   cout<<"Current space:";
	   ifstream gin("property.txt",ios::in|ios::binary);

		while(gin.read((char*)&obj,sizeof(obj)))
			{
				if(c2.retPos()==obj.retpos())
					{
					 obj.display(24,11);
					 if(obj.retstatus()==1 && strcmp(obj.retowner(),c2.retuser())!=0)
						{
						 gotoxy(24,14);
						 cout<<"Rent Paid:"<<obj.retamount()*0.1;
						 c2.addcash(-obj.retamount()*0.1);
						 delay(2000);
						 s++;
						}
				   else if(obj.retstatus() && strcmp(obj.retowner(),c2.retuser())==0)
						{s++;}
					}
			}
	    gin.close();
	   }

	    if(s==0)
	   {
	    buy(c2);
	    delay(2000);
	    gotoxy(21,16);
	    cout<<"Comp2 bought property";
	    delay(2000);
	   }
	   a++;
	   goto menu;

  }

  if(a==2)
  {
   gotoxy(26,9);
   cout<<"Comp1 Turn";
   delay(2000);
   c1.addpos(0,drawdice(200,270));
   delay(2000);
   board(User,c1,c2,c3);

   if(c1.retPos()==6)
	{ int n=random(2);
	  if(n==0)
	  { gotoxy(24,10);cout<<"Comp1 lost $50";
	    delay(2000);c1.addcash(-50);
	    a++;goto menu;
	  }
	  else
	  { gotoxy(24,10);cout<<"Comp1 won $50";
	    delay(2000);c1.addcash(50);
	    a++;goto menu;
	  }
	}

  if(c1.retPos()==11)
	{
	  gotoxy(24,10);
	  cout<<"Comp1 lost $50";
	  delay(2000);c1.addcash(-50);
	  a++;goto menu;
	}

   if(c1.retPos()!=1)
	  {
	   rectangle(165,130,325,225);
	   gotoxy(24,10);
	   cout<<"Current space:";
	   ifstream gin("property.txt",ios::in|ios::binary);

		while(gin.read((char*)&obj,sizeof(obj)))
			{
				if(c1.retPos()==obj.retpos())
					{

					 obj.display(24,11);
					 if(obj.retstatus()==1 && strcmp(obj.retowner(),c1.retuser())!=0)
						{
						 gotoxy(24,14);
						 cout<<"Rent Paid:"<<obj.retamount()*0.1;
						 c1.addcash(-obj.retamount()*0.1);
						 delay(2000);
						 s++;
						}
					 if(obj.retstatus()&&strcmp(obj.retowner(),c1.retuser())==0)
						{s++;}
					}
			}
	    gin.close();
	   }
	   if(s==0)
	   {
	    buy(c1);
	    gotoxy(21,16);
	    delay(2000);
	    cout<<"Comp1 bought property";
	    delay(2000);
	   }


	   a++;
	   goto menu;

  }

  if(a==1)
  {

   if(User.retPos()==6 && m!=0)
	{casino(User);a++;goto menu;}
   if(User.retPos()==11 && m!=0)
	{jail(User);a++;goto menu;}
 //  if(User.retPos()==16 && m!=0)
   //	{river(User);a++;goto menu;}

   gotoxy(64,10);
   cout<<"1.View Properties";
   gotoxy(64,11);
   cout<<"2.Instructions";
   gotoxy(64,13);
   cout<<"4.Buy";
   gotoxy(64,12);
   cout<<"3.Roll Dice";
   if(m==1)
  {
    gotoxy(64,14);
    cout<<"5.Stay";
  }

   property obj;

   ifstream gin("property.txt",ios::in|ios::binary);
   if(User.retPos()!=1)
	{
		rectangle(165,130,325,225);
		gotoxy(24,10);
		cout<<"Current space:";

		while(gin.read((char*)&obj,sizeof(obj)))
			{
				if(User.retPos()==obj.retpos())
					{
					 obj.display(24,11);
					 if(obj.retstatus()==1 && strcmp(obj.retowner(),User.retuser())!=0 && m==1)
						{
						 gotoxy(24,14);
						 cout<<"Rent Paid:"<<obj.retamount()*0.1;
						 User.addcash(-obj.retamount()*0.1);
						}
					}
			}

	}

   int opt,M=0;
   gin.close();
   gotoxy(64,16);
   cout<<"Enter Choice:";
   cin>>opt;
   switch(opt)
   {
	     case 1:   int p=4,q=4;
		       cleardevice();
		       ifstream fin("property.txt",ios::in|ios::binary);
		       while(fin.read((char*)&obj,sizeof(obj)))
			{
			   if(strcmp(obj.retowner(),login)==0)
				{
				 obj.mdisplay(p,q);cout<<endl;M++;
				 p+=25;
				 if(p>=40)
				 {q+=5;
				  p=4;
				 }
				}
			}
		       fin.close();
		       if(M==0)
			{ gotoxy(10,10);
			  cout<<"You don't own any properties as of now.";
			}
		       getch();
		       goto menu;

	     case 2:   cleardevice();
		       instructions();
		       goto menu;

	     case 3:
		       if(m==1)
			{
			 gotoxy(17,17);
			 cout<<"You have already rolled";
			 getch();
			 goto noroll;
			}
		       else if(m==0)
		       {
			 User.addpos(1,drawdice(200,270));
			 delay(2000);
			 m++;
		       }
		       noroll:
		       goto menu;

	     case 4:   if(m==0)
		       {
			gotoxy(17,17);
			cout<<"You need to roll the dice first";
			getch();
			goto menu;
		       }
		       else
		       {
			buy(User);
			a++;
			m--;
			goto menu;
		       }

	      case 5:  if(m==0)
		       {
			gotoxy(17,17);
			cout<<"You need to roll the dice first";
			getch();
			goto menu;
		       }
		       a++;
		       goto menu;

	      case 6:  exit(0);

    }

  }
}

int high(player &x)
{
	fstream f("property.txt",ios::in|ios::binary);
	property p;
	int val=x.retcash();
	while(f.read((char*)&p,sizeof(p)))
	if(strcmp(p.retowner(),login))
		val+=p.retamount();
	f.close();
	return val;
}

void modihi(player x)
{
	fstream f("high.txt",ios::in|ios::binary),g("h.txt",ios::out|ios::binary);
	player p;
	f.read((char *)&p,sizeof(p));
	while(p.retcash()>=x.retcash())
{	g.write((char *)&p,sizeof(p));
	f.read((char *)&p,sizeof(p));
}
	g.write((char *)&x,sizeof(x));
	while(f.read((char *)&p,sizeof(p)))
	{
		g.write((char *)&p,sizeof(p));
	}
	f.close();g.close();
	remove("high.txt");
	rename("h.txt","high.txt");
}

void printhi()
{
	fstream f("high.txt",ios::in|ios::binary);
	player p; int i=0,n=8;
	settextstyle(3,0,1);
	outtextxy(250,10,"LEADER BOARD");
	while(i++<8&&f.read((char *)&p,sizeof(p)))
	{       gotoxy(23,n);
		cout<<i<<".";
		p.highdisplay(n);
		n++;
	}
	cout<<"\n\n";
	f.close();
}

void printhi(player x,player y,player z,player w)
{
	fstream f("high.txt",ios::out|ios::in|ios::binary);
	player p; int i=0,n=5;
	settextstyle(3,0,1);
	outtextxy(250,10,"LEADER BOARD");
	while(i++<8&&f.read((char *)&p,sizeof(p)))
	{       gotoxy(25,n);
		cout<<i<<".";
		p.display();cout<<endl;
		n++;
	}

	cout<<"\n\n";
	x.display();cout<<endl;
	y.display();cout<<endl;
	z.display();cout<<endl;
	w.display();  f.close();
}

void disprop()
{
	int c=7,d=8;
	property obj;
	ifstream fin("property.txt",ios::in|ios::binary);
	while(fin.read((char*)&obj,sizeof(obj)))
	      {     if(d<=20)
			{ obj.mdisplay(c,d);
			  d+=4;
			}

		   else
			{
			  c+=18;d=8;
			  obj.mdisplay(c,d);
			  d+=4;
			}
	      }
       fin.close();


}

 void modprop()
{


  int q,i,tag;char ch[20],cha[20];
  property obj;
  lab:
  tag=0;
  cleardevice();
  disprop();
  outtextxy(50,50,"1.Add Properties");
  outtextxy(230,50,"2.Remove Properties");
  outtextxy(450,50,"3.Edit Name");
  outtextxy(50,70,"4.Delete Data");
  outtextxy(230,70,"5.Reset Owners");
  outtextxy(450,70,"6.Exit");
  outtextxy(240,380,"Enter Choice:");
  rectangle(30,100,600,370);
  gotoxy(47,25);
  cin>>i;
  switch(i)
 {
  case 1:
	    cleardevice();
	    fstream fout("property.txt",ios::app|ios::binary);
	    fout.seekp(0,ios::end);
	    if(fout.tellp()/sizeof(obj)==16)
		{
		 rectangle(50,200,570,280);
		 outtextxy(65,210,"The maximum number of properties has been reached.");
		 outtextxy(65,230,"If you wish to add more properties, you may remove");
		 outtextxy(65,250,"a few properties from the list and continue.");
		 getch();
		}
	    else
		{
			{
			 obj.accept();
			 fout.write((char*)&obj,sizeof(obj));
			}
		}
	   fout.close();
	   goto lab;

   case 2:
	   cleardevice();
	   rectangle(30,100,600,370);
	   disprop();
	   outtextxy(120,380,"Enter Name to remove:");
	   gotoxy(42,25);
	   gets(ch);
	   ifstream gin("property.txt",ios::in|ios::binary);
	   ofstream gout("temp.txt",ios::app|ios::binary);

	   while(gin.read((char*)&obj,sizeof(obj)))
		{
		   if(strcmpi(obj.retname(),ch)!=0)
			{
			   gout.write((char*)&obj,sizeof(obj));
			}
		   else
			{tag++;}
		}

		if(tag==0)
		{
		 setcolor(RED);
		 outtextxy(165,420,"This Property doesn't exist");
		 getch();setcolor(WHITE);
		}

	   gin.close();gout.close();
	   remove("property.txt");
	   rename("temp.txt","property.txt");
	   goto lab;

   case 3:
		cleardevice();
		rectangle(30,100,600,360);
		disprop();
		outtextxy(100,365,"Enter Name to change:");
		gotoxy(40,24);
		gets(ch);
		fstream fin("property.txt",ios::out|ios::in|ios::binary);

		while(fin.read((char*)&obj,sizeof(obj)))
			{
			   if(strcmp(obj.retname(),ch)==0)
				{
				  q=fin.tellg();
				  fin.seekp(q-sizeof(obj),ios::beg);
				  outtextxy(157,380,"Enter new Name:");
				  gotoxy(40,25);
				  gets(cha);
				  obj.assignprop(cha);
				  fin.write((char*)&obj,sizeof(obj));
				  tag++;
				}
			}

		 if(tag==0)
		 {
		  setcolor(RED);
		  outtextxy(200,420,"This Property doesn't exist");
		  getch();setcolor(WHITE);
		 }

		fin.close();
		goto lab;

     case 4:	fstream del("property.txt",ios::in|ios::out|ios::binary);
		fstream del1("temp.txt",ios::in|ios::out|ios::binary);
		del.close();
		del1.close();
		remove("property.txt");
		rename("temp.txt","property.txt");
		goto lab;

     case 5:    int p;
		fstream own("property.txt",ios::in|ios::out|ios::binary);
		while(own.read((char*)&obj,sizeof(obj)))
			{
			  p=own.tellg();
			  own.seekp(p-sizeof(obj),ios::beg);
			  obj.assignowner("Nobody");
			  obj.updatestatus(-1);
			  own.write((char*)&obj,sizeof(obj));
			}
		 own.close();
		 goto lab;

       case 6:  break;

  }
 }


void main()
{
  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, "C://TC//BGI");     // TC TURBOC3
  int c,y,t=0,l;char p[20],p1[20],p2[20],r;
  player temp;

  main:

  cleardevice();
  line(190,50,190,80);
  line(200,90,410,90);
  line(200,40,410,40);
  line(420,51,420,80);
  arc(410,50,0,90,10);
  arc(200,50,90,180,10);
  arc(200,80,180,270,10);
  arc(410,80,270,360,10);

  settextstyle(1,0,5);
  outtextxy(200,40,"MONOPOLY");
  setcolor(WHITE);
  settextstyle(2,0,6);
  outtextxy(250,272,"1.Log in");
  outtextxy(250,292,"2.Sign in");
  outtextxy(250,312,"3.Exit");
  outtextxy(233,332,"Enter Choice:");
  gotoxy(46,22);
  cin>>c;

  if(c==2)
  {
   ifstream i("player.txt",ios::in|ios::binary);
    pass:
    cleardevice();

    line(190,50,190,80);
    line(200,90,410,90);
    line(200,40,410,40);
    line(420,51,420,80);
    arc(410,50,0,90,10);
    arc(200,50,90,180,10);
    arc(200,80,180,270,10);
    arc(410,80,270,360,10);
    settextstyle(1,0,5);
    outtextxy(200,40,"MONOPOLY");
    settextstyle(2,0,6);

    rectangle(170,200,440,350);
    settextstyle(3,0,4);
    outtextxy(190,150,"Create Account");
    settextstyle(2,0,6);
    gotoxy(24,15);
    cout<<"Enter Username:";
    gotoxy(24,17);cout<<"Enter Password:";gotoxy(24,18);cout<<"(Max 10 Char)";
    gotoxy(24,20);cout<<"Re enter Password:";
    gotoxy(40,15);
    gets(login);

    i.seekg(0,ios::beg);
    while(i.read((char*)&temp,sizeof(temp)))
	{   if(strcmpi(temp.retuser(),login)==0)
		{
		 setcolor(RED);
		 outtextxy(165,355,"This username already exists.");
		 setcolor(WHITE);getch();goto pass;
		}
	}

    i.close();
    gotoxy(40,17);
    for(t=0;t<=10;t++)
    {
      r=getch();
      if(r==13)
	{break;}
      cout<<"*";
      p[t]=r;
    }
    p[t]='\0';

    gotoxy(43,20);
    for(t=0;t<=10;t++)
    {
      r=getch();
      if(r==13)
	{break;}
      cout<<"*";
      p1[t]=r;
    }
     p1[t]='\0';
     t=0;

    if(strcmp(p,p1)!=0)
    {
      setcolor(RED);
      outtextxy(160,355,"Please enter the same Password");
      setcolor(WHITE);getch();goto pass;
    }

    ofstream f("player.txt",ios::app|ios::binary); // app/out
    temp.assignname(login);
    temp.assignpass(p);
    f.write((char*)&temp,sizeof(temp));
    f.close();
    cleardevice();

  }
  else if(c==1)
  {
    cleardevice();
    line(190,50,190,80);
    line(200,90,410,90);
    line(200,40,410,40);
    line(420,51,420,80);
    arc(410,50,0,90,10);
    arc(200,50,90,180,10);
    arc(200,80,180,270,10);
    arc(410,80,270,360,10);
    settextstyle(1,0,5);
    outtextxy(200,40,"MONOPOLY");
    settextstyle(2,0,6);

    settextstyle(3,0,4);
    outtextxy(265,150,"LOGIN");
    settextstyle(2,0,6);
    rectangle(170,200,440,300);
    gotoxy(24,15);
    cout<<"Enter Username:";
    gotoxy(24,17);
    cout<<"Enter Password:";
    gotoxy(40,15);gets(login);gotoxy(40,17);

    for(;t<10;t++)
    {
      r=getch();
      if(r==13)
	{break;}
      cout<<"*";
      p[t]=r;
    }
     p[t]='\0';
     t=0;

    ifstream g("player.txt",ios::in|ios::binary);
    while(g.read((char*)&temp,sizeof(temp)))
	{ if(strcmp(temp.retuser(),login)==0 && strcmp(temp.retpass(),p)==0)
		{
		 t++;
		}
	}
    g.close();
    if(t==0)
	{ setcolor(RED);
	  outtextxy(160,355,"Invalid Username or Password");
	  setcolor(WHITE);
	  getch();
	  goto main;
	}
    temp.assignpass(p2);
    temp.assignname(login);
  }
   else if(c==3)
	{ cleardevice();closegraph();exit(0); }
   else
   {
     setcolor(RED);
     outtextxy(160,355,"Invalid Input. Please enter again.");
     setcolor(WHITE);
     delay(1500);
     goto main;
   }

  player user(0),c1(1),c2(2),c3(3);
  user.assignpass(p);

  if(strcmpi(login,"Admin")==0)
  {
    loop:
    cleardevice();
    line(190,50,190,80);
    line(200,90,410,90);
    line(200,40,410,40);
    line(420,51,420,80);
    arc(410,50,0,90,10);
    arc(200,50,90,180,10);
    arc(200,80,180,270,10);
    arc(410,80,270,360,10);
    settextstyle(1,0,5);
    outtextxy(200,40,"MONOPOLY");
    settextstyle(2,0,6);

    outtextxy(450,110,"Signed in as:");
    outtextxy(485,130,"Admin");
    outtextxy(225,255,"1.View Properties");
    outtextxy(225,275,"2.Modify Properties");
    outtextxy(225,295,"3.Exit");
    outtextxy(225,315,"Enter Choice:");
    gotoxy(45,21);
    cin>>y;

    switch(y)
    {	case 1:    cleardevice();
		   rectangle(30,100,600,370);
		   disprop();
		   setcolor(RED);
		   outtextxy(190,375,"Press any key to continue");
		   setcolor(WHITE);
		   getch();
		   goto loop;

	case 2:    cleardevice();
		   modprop();

		   goto loop;

	case 3:    goto main;

	default:   setcolor(RED);
		   outtextxy(160,355,"Invalid Input. Please Enter Again");
		   setcolor(WHITE);getch();
		   goto loop;

    }
  }
  else
 {
    mainmenu:
    settextstyle(2,0,6);
    cleardevice();
    line(190,50,190,80);
    line(200,90,410,90);
    line(200,40,410,40);
    line(420,51,420,80);
    arc(410,50,0,90,10);
    arc(200,50,90,180,10);
    arc(200,80,180,270,10);
    arc(410,80,270,360,10);
    settextstyle(1,0,5);
    outtextxy(200,40,"MONOPOLY");
    settextstyle(2,0,6);

    outtextxy(450,123,"Signed in as:");
    gotoxy(61,10);
    cout<<user.retuser();
    outtextxy(225,255,"1. Begin Game");
    outtextxy(225,275,"2. Leader Board");
    outtextxy(225,295,"3. Exit");
    outtextxy(225,315,"Enter Choice:");
    gotoxy(45,21);

    cin>>l;

    switch(l)
  {
	  case 1:     cleardevice();
		      instructions();
		      cleardevice();
		      while(::round<1)
		     {
		      board(user,c1,c2,c3);
		      turn(1,user,c1,c2,c3);
		      ::round++;
		     }
		      delay(1000);
		      cleardevice();
		      settextstyle(1,0,4);
		      outtextxy(200,200,"GAME OVER...");
		      getch();
		      cleardevice();
		      user.assigncash(high(user));
		      c1.assigncash(high(c1));
		      c2.assigncash(high(c2));
		      c3.assigncash(high(c3));

		      ofstream fout("high.txt",ios::app|ios::binary);
		      fout.write((char*)&user,sizeof(user));
		      fout.close();
		      cout<<"H";
		      modihi(user);
		      printhi(user,c1,c2,c3);
		      getch();
		      cleardevice();
		      goto mainmenu;

	  case 2:     cleardevice();
		      printhi();getch();
		      goto mainmenu;

	  case 3:     goto main;

	  default:    setcolor(RED);
		      outtextxy(160,355,"Invalid Input. Please Enter Again");
		      setcolor(WHITE);getch();
		      goto mainmenu;
  }
 }
}


