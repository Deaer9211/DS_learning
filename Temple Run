#include <iostream>
#include <stdlib.h>

using namespace std;
char movement[100][7];
int i=0,total_c[3]={0},get[3]={0},tre_num=0,get_num=0;//tre_num:treasure number, get_num:get number
int miss=0,total=0,total_get=0;

int final_count(int f){
    if(f==3)    return 500;
    else if(f==4)   return 300;
    else if(f==5)   return 150;
    else    return 50;
}

void count_get(int t){
    if(miss==0) get[get_num++]=t;//1:gold,2:silver
    else    miss--;
    if(get_num==3){
        total_get+=final_count(get[0]+get[1]+get[2]);
        get_num=0;
    }
}

void count_total(int treasure){
    total_c[tre_num++]=treasure;//1:golden,2:silver
    if(tre_num==3){
        total+=final_count(total_c[0]+total_c[1]+total_c[2]);
        tre_num=0;
    }
    count_get(treasure);
}

int backtotemple(int term){
    if(movement[term][0]==84)//T=84
        return (movement[term][1]==76)?1:2;//L=76
    else    return 3;
}

void treasure_find(){
    for(int j=0;j<i-1;j++){
        if(movement[j][0]==71)    count_total(1);//G=71,GOLDEN
        else if(movement[j][0]==83)    count_total(2);//S=83,SILVER
        else if(movement[j][0]==77)    miss=4;//M=77,MISS
        else continue;
    }
}

void route(){
    string direction[100];
    int mark=0;
    for(int j=0;j<i-1;j++){
        if(backtotemple(j)==1)  direction[mark++]="TR";
        else if(backtotemple(j)==2)    direction[mark++]="TL";
        else continue;
    }
    for(int k=mark-1;k>=0;k--){
        cout<<direction[k];
        if(k!=0)    cout<<"->";
    }
}

int main()
{
    while(!cin.eof())
        cin>>movement[i++];
    route();
    treasure_find();
    cout<<endl<<total_get<<endl<<total<<endl;
    return 0;
}
