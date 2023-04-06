#include <iostream>
using namespace std;

typedef struct plate{
    int label;
    int macarons;
    struct plate *next;
}P;

P *head=NULL, *new_plate, *current_plate, *mark, *target_plate=NULL, *candidate;
P *remove_front, *remove_middle, *remove_last;

//for exceptional condition
int clockwise(int,int);
int check_step(int,int);
void find_max();
void tar(int);

int main()
{
    //make new plates
    for(int label=1;label<=10;label++){
        new_plate=(P*)malloc(sizeof(P));
        new_plate->label=label;
        cin>>new_plate->macarons;
        //link the new plate
        if(label!=1)    current_plate->next=new_plate;
        current_plate=new_plate;
        if(label==1)    head=new_plate;
        if(label==10)   new_plate->next=head;//circular linked list
    }
    int current_macarons,a,b;
    int check=0;
    for(int time=1;time<=100;time++){
        //find current plate
        if(time!=1){
            int new_current_label=(target_plate->label)%10+1;
            mark=head;
            for(int f=0;f<9;f++){
                if(mark->label!=new_current_label)  mark=mark->next;
                else f=9;
            }
            current_plate=mark;
            head=current_plate;
        }
        else current_plate=head;
        current_macarons=current_plate->macarons;
        //remove the plates
        remove_front=current_plate->next;
        remove_middle=remove_front->next;
        remove_last=remove_middle->next;
        current_plate->next=remove_last->next;
        //select target plate
        mark=current_plate->next;
        candidate=NULL;
        tar(current_macarons);
        /*
        do{
            if(mark->macarons<current_macarons){
                if(candidate!=NULL){
                    if  (mark->macarons>candidate->macarons)  candidate=mark;
                    else if(mark->macarons==candidate->macarons){
                        check=check_step(mark->label,candidate->label);//1:mark,2:candidate
                        if(check==1)    candidate=mark;
                    }
                }
                else    candidate=mark;
            }
            mark=mark->next;
        }while(mark!=head);
        //if the current plate has fewest macarons
        if(candidate==NULL) find_max();
            */
        //select finished
        //target_plate=candidate;
        //eat macarons
        a=target_plate->label;
        b=target_plate->macarons;
        (a<=b)?target_plate->macarons-=a:target_plate->macarons+=(50-a);
        //put the plates back
        head=target_plate;
        remove_last->next=remove_middle;//reverse the original removed plates order
        remove_middle->next=remove_front;
        remove_front->next=target_plate->next;
        target_plate->next=remove_last;
    }
    mark=head;
    for(int j=0;j<10;j++){
        cout<<mark->label<<" / "<<mark->macarons<<endl;
        mark=mark->next;
    }
    return 0;
}

int check_step(int mark_label, int candidate_label){
    int step,step_front=0,step_back=0,run, clabel[2],cstep[2];
    P *counter1;
    clabel[0]=mark_label;
    clabel[1]=candidate_label;
    for(int r=0;r<2;r++){
        run=1;
        step=0;
        counter1=current_plate->next;
        while(run){
            step++;
            if(counter1->label==clabel[r]){
                step_front=step;
                step_back=7-step_front;
                run=0;
            }
            counter1=counter1->next;
        }
        cstep[r]=(step_front>step_back)?step_back:step_front;
    }
    if(cstep[0]<cstep[1]) return 1;//mark wins
    else if(cstep[0]==cstep[1]){
        run=clockwise(clabel[0],clabel[1]);
        return (run==1)?1:2;
    }
    else   return 2;
}

void find_max(){
    int Max=0,exc;
    for(int k=0;k<7;k++){
        mark=mark->next;
        if(mark->macarons==0){
            mark=mark->next;
            k++;
        }else if(mark->macarons>Max){
            candidate=mark;
            Max=mark->macarons;
        }else if(mark->macarons==Max){
            exc=clockwise(mark->label,candidate->label);
            if(exc==1)  candidate=mark;
        }
    }
}

int clockwise(int mark_label, int candidate_label){
    P *counter=current_plate;
    int run=0;
    while(!run){
        if(counter->label==mark_label)  run=1;//mark
        else if(counter->label==candidate_label) run=2;//candidate
        else counter=counter->next;
    }
    return (run==1)?1:2;
}

void tar(int curma){
    int t1=-1,t2=-1,s1=0,s2=0,m1=0,m2=0,ms1=0,ms2=0;
    int ans=0;
    P *plate1=current_plate->next,*plate2=current_plate->next->next->next->next;
    for(int i1=1;i1<=3;i1++){
        if(plate1->macarons<curma && plate1->macarons>t1){
            t1=plate1->macarons;
            s1=i1;
        }else if(plate1->macarons>=curma && plate1->macarons>=m1){
            m1=plate1->macarons;
            ms1=i1;
        }
        plate1=plate1->next;
    }

    for(int i2=3;i2>=1;i2--){
        if(plate2->macarons<curma && plate2->macarons>=t2){
            t2=plate2->macarons;
            s2=i2;
        }else if(plate2->macarons>=curma && plate2->macarons>m2){
            m2=plate2->macarons;
            ms2=4-i2;
        }
        plate2=plate2->next;
    }
    if(t1==-1 && t2==-1){
        if(m1>m2 ||(m1==m2 && (4-ms1)<ms2))   ans=ms1;
        else ans=3+ms2;
    }else if(t1>t2 || (t1==t2 && s1<=s2) )    ans=s1;
    else ans=7-s2;
    target_plate=current_plate;
    for(int a=1;a<=ans;a++){
        target_plate=target_plate->next;
    }
}
