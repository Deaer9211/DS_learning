#include <iostream>
using namespace std;

typedef struct monster{
    //struct monster *parent;
    struct monster *Left;
    struct monster *Right;
    int star;
}mon;

mon *RealWorld,*monst,*aban;
int num,L=0,R=0,mon_num=0,attack=0;
int CheckRealWorld();
void summon();
void compare();
void traversing(mon*);

int main()
{
    char cmd[12];
    int run=1;
    RealWorld=(mon*)malloc(sizeof(mon));
    RealWorld->Left=RealWorld->Right=NULL;
    while(run){
        cin>>cmd;
        if(cmd[0]=='T') run=0;
        else if(cmd[0]=='S')    summon();
        else{ //attack
            if(RealWorld->Left) attack+=RealWorld->Left->star;
            if(RealWorld->Right) attack+=RealWorld->Right->star;
        }
    }
    traversing(RealWorld->Left);
    traversing(RealWorld->Right);
    cout<<endl<<attack<<endl;
    return 0;
}

int CheckRealWorld(){
    if(L==0) return 0;
    else if(R==1) return 1;//full
    else    return 2;//one space remain
}

void compare(){
    int a=RealWorld->Left->star,b=RealWorld->Right->star,c=monst->star;
    if(c>a && c>b){
        if(a<=b){
            aban=RealWorld->Left;
            RealWorld->Left=monst;
        }else{
            aban=RealWorld->Right;
            RealWorld->Right=monst;
        }
    }else if(c>a){
        aban=RealWorld->Left;
        RealWorld->Left=monst;
    }else if(c>b){
        aban=RealWorld->Right;
        RealWorld->Right=monst;
    }
}

void summon(){
    scanf(" -> %d*",&num);
    int check=CheckRealWorld();
    monst=(mon*)malloc(sizeof(mon));
    monst->star=num;
    monst->Left=monst->Right=NULL;
    if(check==0){
        RealWorld->Left=monst;
        L=1;
        mon_num++;
    }else{
        if(num<=4){
            if(check==2){
                RealWorld->Right=monst;
                R=1;
            }else{
                compare();
                monst->Left=aban;
            }
        }else if(num==5 || num==6){
            if(check==2){
                aban=RealWorld->Left;
                RealWorld->Left=monst;
                monst->Left=aban;
            }else{
                compare();
                monst->Left=aban;
            }
        }else{
            RealWorld->star=num;
            monst=RealWorld;
            RealWorld=(mon*)malloc(sizeof(mon));
            RealWorld->Left=monst;
            RealWorld->Right=NULL;
            R=0;
        }
        mon_num++;
    }
}
void traversing(mon *tra){
    if(tra){
        (mon_num--!=1)?cout<<tra->star<<"* ":cout<<tra->star<<"*";;
        if(tra->Left)   traversing(tra->Left);
        if(tra->Right)  traversing(tra->Right);
    }
}
