/* PROGRAM FOR SIMULATING SLOTTED ALOHA TECHNIQUE
  %
  % Author: Shivam Prasad (prasadshivam2296@gmail.com)
  % Date:   25th July 2017
  % Description: This program simulates the SLOTTED-ALOHA technique for sending packets.
  % Throughput: The maximum throughput is 1/e frames per frame-time (reached when G = 1),
  %               which is approximately 0.368 frames per frame-time, or 36.8%.
  %
  % Usage: Slotted ALOHA is used in low-data-rate tactical satellite communications networks by military forces,
  %        in subscriber-based satellite communications networks, mobile telephony call setup, set-top box communications and in the contactless RFID technologies.
  %
  %
  % Input: The program assumes that senders are spread randomly on a maze of size n X m.
  %        The nodes have a random range lying in between a min and max value.
  %        Only those senders will communicate whose range is greater than their distance. These Senders are printed.
  %        Now, for Slotted ALOHA, input
  %        -> Kmax(The max number of attempts by a sender to send a packet).
  %        -> Tp(Time-out peroid, the number of slots a sender has to wait after a collision).
  %        For the simulator, enter the number of time slots.
  %        Now, the simulator describes the activity at each time slot.
  %        Finally, the total number of packets and the number of successful packets transmitted are displayed.
*/
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

typedef pair<int,int> pii;

int main()
{

    int i,j,dist,x1,x2,y1,y2,r1,r2,nodes,n,m,mn,mx,x,y;
    cout<<"\nEnter the dimensions of the maze(nxm):";
    cin>>n>>m;
    int ADJ[n][m];

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            ADJ[i][j]=' ';        //Initial configuration of the maze.
        }
    }
    cout<<"\nEnter the min and max ranges of the nodes: ";
    cin>>mn>>mx;

    cout<<"\nEnter the number of senders: ";
    cin>>nodes;

    srand(time(NULL));
    int MATRIX[nodes][3];

    for(i=0;i<nodes;i++){                   //Randomly placing the ith sender in the maze.
        do{ x=rand()%n;
            y=rand()%m;
        }while(ADJ[x][y]!=' ');               //the position should be free.

        ADJ[x][y]='*';
        MATRIX[i][0]=x;                     //x-coordinate
        MATRIX[i][1]=y;                     //y-coordinate
        MATRIX[i][2]=rand()%(mx-mn)+mn;     //Random range.
    }

    cout<<"Placing the senders: \n";
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
          cout<<char(ADJ[i][j]);          //Display the maze after randomly placing the senders.
        }
       cout<<"\n";
    }

    set<int > S;
    set<pii >points;

    for(i=0;i<nodes;i++){
        x1=MATRIX[i][0];
        y1=MATRIX[i][1];
        r1=MATRIX[i][2];

        for(j=i+1;j<nodes;j++){
            x2=MATRIX[j][0];
            y2=MATRIX[j][1];
            r2=MATRIX[j][2];
                dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));

                if(dist<=r1 && dist<=r2){      //i and j can communicate, so adding them.
                    points.insert({x1,y1});
                    points.insert({x2,y2});
                    S.insert(i);
                    S.insert(j);
                }
        }
    }

    cout<<"\nThe updated maze: "<<endl;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(points.find({i,j})!=points.end()){
                cout<<'*';//Display the maze after randomly placing the senders.
            }
            else cout<<" ";
        }
        cout<<"\n";
    }

    cout<<endl<<"\nThe SENDERS who will participate are: ";
    for(set<int >::iterator itr=S.begin();itr!=S.end();itr++){
        cout<<(*itr)+1<<" ";          //Display the Senders.
    }
    cout<<endl;


    cout<<"\n#########Using SLotted ALOHA#########\n";
    int Tp,Kmax;
    cout<<"\nEnter Kmax: ";
    cin>>Kmax;
    cout<<"\nEnter Tp: ";
    cin>>Tp;

    //Simulation
        vector<int> NODES(S.begin(),S.end());
         n=NODES.size();

        vector<int> Kvals(nodes+1);
        vector<int> WaitTime(nodes+1);

        for(i=0;i<=nodes;i++){
            Kvals[i]=0;
            WaitTime[i]=0;
        }

        vector<int>TOSEND;

        int total=0,slots,eff=0;
        cout<<"\nEnter the number of time slots to be used: ";
        cin>>slots;
        cout<<endl;

        for(i=0;i<slots;i++){

        cout<<"SLOT="<<i+1<<endl;
                for(j=0;j<n;j++){
                          //slot has been changed, Reducing the waiting times
                    if(WaitTime[NODES[j]]>0)
                        WaitTime[NODES[j]]--;
                }

               TOSEND.clear();

                for(int k=0;k<n;k++){
                    if(WaitTime[NODES[k]]){
                       continue;
                    }

                    int node=NODES[k];
                   if(rand()%2){
                        TOSEND.pb(node);
                    }
                }


                int sz=TOSEND.size();
                total+=sz;

                if(sz>1){
                    cout<<"Collision occured!!!"<<endl;

                    for(int m=0;m<sz;m++){ //increment the value of K for each node
                        Kvals[TOSEND[m]]++;

                        if(Kvals[TOSEND[m]]>Kmax){
                            cout<<"Aborting sender "<<TOSEND[m]+1<<"'s packet.\n";

                            Kvals[TOSEND[m]]=0;
                            WaitTime[TOSEND[m]]=0;

                        }
                        else{
                            cout<<"Sender " <<TOSEND[m]+1<<" Blocked";
                            WaitTime[TOSEND[m]]=((rand()%Kmax)+1);        //Random wait time.
                            cout<<". (waits for "<<WaitTime[TOSEND[m]]<<" time slots, K="<<Kvals[TOSEND[m]]<<")\n";
                            WaitTime[TOSEND[m]]++;
                        }
                    }
                }

                else if (sz==1){
                    cout<<"Sender "<<TOSEND[0]+1<<"'s packet successfully transmitted!\n";
                    eff++;
                    WaitTime[TOSEND[0]]=0;
                    Kvals[TOSEND[0]]=0;
                }
                cout<<endl;
        }
        cout<<"\nTotal number of packets="<<total;
        cout<<"\nTotal number of packets sent="<<eff<<endl;

}
