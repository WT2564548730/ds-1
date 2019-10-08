#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//选手链表定义
typedef struct PerNode{
    string name;
    int rank,score;
    int score1[5]={7,5,3,2,1};
    int score2[3]={5,3,2};
    struct PerNode *Next;
}*Person;

//项目链表定义
typedef struct PNode{
    int pnum,rank,score;
    string *Match,match;
    int *PreRank,preRank;
    
    struct PNode *Next;
    Person per;
}*Program;

//学校链表定义
typedef struct SNode{
    int n,m,w;
    string snum,school;
    Program Mgame;
    Program Fgame;
    struct SNode *Next;
    int grade;
}*Sport;

Sport SCreate();
Program PCreate(int x,int y);
void SInput(Sport Shead,Program Phead);
Program PInput(Program Phead,int x,int tag);
Person PerInput(int n,int preRank);
void Pprint(Sport School);
void Sprint(Sport School);
void Find(Sport Shead,Sport t);

//main函数
int main(){
    Sport School=new SNode;
    Program Game=new PNode;
    School=SCreate();                            //初始化
    Game=PCreate(School->m,School->w);            //初始化
    SInput(School,Game);                        //输入
    Pprint(School);                                //学校各项目成绩表
    Sprint(School);                                //所有学校排名表
    delete School;
    return 0;
}

//学校链表初始化
Sport SCreate(){
    Sport Shead=new SNode;
    cout<<"请输入学校数 男子项目数 女子项目数 : ";
    cin>>Shead->n>>Shead->m>>Shead->w;
    cout<<endl;
    return Shead;
}

//项目链表预处理
Program PCreate(int x,int y){
    Program Phead;
    Phead=new PNode;
    
    Phead->Match=new string[x+y+1];
    Phead->PreRank=new int[x+y+1];
    
    for(int i=0;i<x+y;i++){
        if(i==0){
            cout<<"请输入男子项目的信息"<<endl;
            cout<<"项目名称 取前几名"<<" : "<<endl;
        }
        
        if(i==x){
            cout<<endl;
            cout<<"请输入女子项目的信息"<<endl;
            cout<<"项目名称 取前几名"<<" : "<<endl;
        }
        cin>>Phead->Match[i+1]>>Phead->PreRank[i+1];
    }
    cout<<endl;
    
    return Phead;
}

//学校链表输入
void SInput(Sport Shead,Program Game){
    Sport end=Shead;
    Sport t;
    
    for(int i=0;i<Shead->n;i++){
        cout<<"*********************************************"<<endl;
        t=new SNode;
        cout<<"请输入学校 "<<i+1<<" 的信息"<<endl;
        cout<<"学校编码 学校名称 : ";
        cin>>t->snum>>t->school;
        cout<<t->snum<<" ; "<<t->school;
        cout<<endl<<endl;
        
        t->Mgame=PInput(Game,Shead->m,0);
        t->Fgame=PInput(Game,Shead->w,Shead->m);
        t->grade+=(t->Mgame->score+t->Fgame->score);
        if(end==Shead){
            end->Next=t;
            end=t;
        }
        else{
            if(t->grade<end->grade){
                end->Next=t;
                end=t;
            }
            else
                Find(Shead,t);
        }
    }
    end->Next=NULL;
    cout<<endl;
}

//项目链表输入
Program PInput(Program Game,int x,int tag){
    Program Phead,t,end;
    Phead=new PNode;
    
    end=Phead;
    int score=0;
    
    for(int i=0;i<x;i++){
        t=new PNode;
        if(tag==0)
            t->pnum=i+1;
        else
            t->pnum=tag+i+1;
        t->match=Game->Match[t->pnum];
        t->preRank=Game->PreRank[t->pnum];
        
        int n;
        cout<<"请输入项目 "<<t->pnum<<" 的参赛人数 : ";
        cin>>n;
        t->per=PerInput(n,t->preRank);
        score+=t->per->score;
        
        end->Next=t;
        end=t;
    }
    end->Next=NULL;
    Phead->score=score;
    return Phead;
}

//参赛选手链表输入
Person PerInput(int n,int preRank){
    Person head,end,t;
    head=new PerNode;
    end=head;
    int score=0,j=1;
    while(n--){
        t=new PerNode;
        cout<<"请输入选手 "<<j<<" 的姓名及排名 : ";
        cin>>t->name;
        cin>>t->rank;
        if(preRank==5){
            if(t->rank>5)    t->score=0;
            else
                t->score=t->score1[t->rank-1];
        }
        if(preRank==3){
            if(t->rank>3)    t->score=0;
            else
                t->score=t->score2[t->rank-1];
        }
        
        score+=t->score;
        end->Next=t;
        end=t;
        j++;
    }
    cout<<endl;
    head->score=score;
    end->Next=NULL;
    return head;
}

//各学校成绩单输出
void Pprint(Sport School){
    cout<<endl<<endl<<endl<<endl<<endl;
    Sport p=School->Next;
    while(p){
        cout<<"***************************************************************"<<endl;
        Program x=p->Mgame->Next;
        Program y=p->Fgame->Next;
        cout<<p->school<<"的成绩表"<<endl;
        cout<<"项目 姓名 排名 得分"<<endl<<endl;
        cout<<"男子项目"<<endl;
        while(x){
            cout<<x->match<<" : "<<endl;
            Person h=x->per->Next;
            while(h){
                cout<<h->name<<"  "<<h->rank<<"  "<<h->score<<endl;
                h=h->Next;
            }
            x=x->Next;
        }
        cout<<endl;
        cout<<"女子项目"<<endl;
        while(y){
            cout<<y->match<<" : "<<endl;
            Person h=y->per->Next;
            while(h){
                cout<<h->name<<"  "<<h->rank<<"  "<<h->score<<endl;
                h=h->Next;
            }
            y=y->Next;
        }
        cout<<endl;
        p=p->Next;
    }
}

//学校排名链表输出
void Sprint(Sport School){
    cout<<"***************************************************************"<<endl;
    Sport p=School->Next;
    int i=1;
    cout<<"团体总分报表"<<endl;
    while(p){
        cout<<"第 "<<i++<<" 名  "<<p->snum<<"  "<<p->school<<"  "<<p->Mgame->score<<"  "<<p->Fgame->score<<"  "<<p->grade<<endl;
        p=p->Next;
    }
}

//查找排序
void Find(Sport Shead,Sport t){
    Sport head=Shead;
    Sport q=head,p=head->Next;
    
    while(t->grade<p->grade){
        q=q->Next;
        p=p->Next;
    }
    
    t->Next=p;
    q->Next=t;
    head=head->Next;
}

/*
 3 2 2
 m100m 3
 m200m 5
 f100m 3
 f200m 5
 001 内师大
 2
 aaa 2
 bbb 2
 2
 ccc 2
 ddd 2
 2
 eee 2
 fff 2
 2
 ggg 2
 hhh 2
 002 内工大
 2
 iii 3
 jjj 3
 2
 kkk 3
 lll 3
 2
 mmm 3
 nnn 3
 2
 ooo 3
 ppp 3
 003 内科大
 2
 qqq 1
 rrr 1
 2
 sss 1
 ttt 1
 2
 uuu 1
 vvv 1
 2
 www 1
 xxx 1
 */

