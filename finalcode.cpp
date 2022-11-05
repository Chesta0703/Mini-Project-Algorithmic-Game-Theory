#include <bits/stdc++.h>
using namespace std;

ifstream fin;
ofstream fout;
int no_of_players,no_of_actions;
int len;
int **arr;
int *sds;
vector<vector<int>> wds,vwds;

int toNum(vector<int> &v){
    int sum=0;
    for(int i:v)
        sum=sum*no_of_actions+i;
    
    return sum;
}

vector<int> toStratProfile(int n){
    vector<int> v;
    for(int i=1;i<=no_of_players;i++){
        v.push_back(n%no_of_actions);
        n/=no_of_actions;
    }
    reverse(v.begin(),v.end());
    return v;
}

void displayStrategyProfile(vector<int> &prof){
    cout<<"(";
    for(int i=0;i<(prof.size()-1);i++)
        cout<<prof[i]+1<<",";
    cout<<prof[prof.size()-1]+1<<")\n";
}

vector<int> createIntersection(vector<int> &v1,vector<int> &v2){
    vector<int> temp;
    sort(v2.begin(),v2.end());
    for(int i:v1){
        if(binary_search(v2.begin(),v2.end(),i))
            temp.push_back(i);
    }
    return temp;
}

void createGame(int i,vector<int> &v){
    if(i==-1){
        int temp=toNum(v);
        cout<<"Enter payoffs for strategy profile (";
        for(int j=0;j<(v.size()-1);j++)
            cout<<v[j]+1<<",";
        cout<<v[v.size()-1]+1<<"): ";
        for(int j=0;j<no_of_players;j++){
            cin>>arr[temp][j];
            fout<<arr[temp][j]<<" "<<flush;
        }
        return;
    }

    for(int j=0;j<no_of_actions;j++){
        v[i]=j;
        createGame(i-1,v);
    }
}

void findStrats(int i,int skip_index,vector<int> &v){
    if(i==no_of_players){
        vector<int> temp;
        for(int j=0;j<no_of_actions;j++){
            v[skip_index]=j;
            temp.push_back(arr[toNum(v)][skip_index]);
        }
        int maxm=*max_element(temp.begin(),temp.end());
        vector<int> indices;
        for(int j=0;j<no_of_actions;j++){
            if(maxm==temp[j])
                indices.push_back(j);
        }
        
        temp.clear();
        if(sds[skip_index]!=-1){
            if((indices.size()==1)&&(sds[skip_index]==-2)){
                sds[skip_index]=indices[0];
            }
            else if(sds[skip_index]!=indices[0])
                sds[skip_index]=-1;
        }
        if(indices.size()<no_of_actions){
            wds[skip_index]=createIntersection(wds[skip_index],indices);
        }
        else
            wds[skip_index].clear();
        
        if(indices.size()<=no_of_actions){
            vwds[skip_index]=createIntersection(vwds[skip_index],indices);
        }
        return;
    }

    if(i==skip_index){
        v.push_back(-1);
        findStrats(i+1,skip_index,v);
        v.pop_back();
    }
    else{
        for(int j=0;j<no_of_actions;j++){
            v.push_back(j);
            findStrats(i+1,skip_index,v);
            v.pop_back();
        }
    }
}

void findCombinations(int i, vector<vector<int>> v_arr, vector<int> &v){
    if(i==no_of_players){
        displayStrategyProfile(v);
        return;
    }

    for(int j:v_arr[i]){
        v.push_back(j);
        findCombinations(i+1,v_arr,v);
        v.pop_back();
    }
}

void generate_from_gamut(){
    string str1="java -jar gamut.jar -g MajorityVoting -int_payoffs 1 ";
    string pl="-players "+to_string(no_of_players)+" ";
    string act="-actions "+to_string(no_of_actions);
    string str2=" -f temp.efg -output GambitOutput";
    string str=str1+pl+act+str2;

    system(&str[0]);
}

void generate_game(){
    fin.open("temp.efg");
    int n=0;
    string line;
    while (getline(fin,line))
        n++;
    cout<<n<<"\n";
    fout.open("game.efg");
    int i=1;
    fin.close();
    fin.open("temp.efg");
    while(getline(fin,line)){
        if(i==n){
            i++;
            continue;
        }
        else
            fout<<line<<endl;
        i++;
    }

    vector<int> v(no_of_players);
    createGame(no_of_players-1,v);
    v.clear();

}

void checkSDSE(){
    int c=0;
    for(int i=0;i<no_of_players;i++){
        if(sds[i]>=0)
            c++;
    }
    if(c==0){
        cout<<"There are no strongly dominant strategies.\n";
        cout<<"There is no strongly dominant strategy equilibrium.\n";
        return;
    }
    else if(c<no_of_players){
        for(int i=0;i<no_of_players;i++){
            if(sds[i]>=0){
                cout<<"Strategy "<<(sds[i]+1)<<" is a strongly dominant strategy for player "<<(i+1)<<".\n";
            }
        }
        cout<<"There is no strongly dominant strategy equilibrium.\n";
        return;
    }
    else{
        for(int i=0;i<no_of_players;i++){
            if(sds[i]>=0)
                cout<<"Strategy "<<(sds[i]+1)<<" is a strongly dominant strategy for player "<<(i+1)<<".\n";
        }
        cout<<"SDSE: ( ";
        for(int i=0;i<no_of_players;i++)
            cout<<(sds[i]+1)<<",";
        cout<<").\n";
    }
}

void checkWDSE(){
    bool ifWDS=true;
    bool ifWDSE=true;

    for(int i=0;i<no_of_players;i++){
        if(wds[i].size()==0){
            ifWDS=false;
            ifWDSE=false;
            break;
        }
    }

    if(ifWDS==false){
        cout<<"There are no weakly dominant strategies.\n";
        cout<<"There is no weakly dominant strategy equilibrium.\n";
        return;
    }

    for(int i=0;i<no_of_players;i++){
        if(wds[i].size()==0)
            continue;
        cout<<"For Player "<<(i+1)<<", the weakly dominant strategies are: ";
        for(int j:wds[i])
            cout<<j+1<<" ";
        cout<<"\n";
    }

    if(ifWDSE==false){
        cout<<"There is no weakly dominant strategy equilibrium.\n";
        return;
    }
    
    cout<<"The weakly dominant strategy equilibriums are:\n";

    vector<int> v;
    findCombinations(0,wds,v);
    v.clear();
}

void checkVWDSE(){
    bool ifVWDS=true;
    bool ifVWDSE=true;

    for(int i=0;i<no_of_players;i++){
        if(vwds[i].size()==0){
            ifVWDS=false;
            ifVWDSE=false;
            break;
        }
    }

    if(ifVWDS==false){
        cout<<"There are no very weakly dominant strategies.\n";
        cout<<"There is no very weakly dominant strategy equilibrium.\n";
        return;
    }

    for(int i=0;i<no_of_players;i++){
        if(vwds[i].size()==0)
            continue;
        cout<<"For Player "<<(i+1)<<", the very weakly dominant strategies are: ";
        for(int j:vwds[i])
            cout<<j+1<<" ";
        cout<<"\n";
    }

    if(ifVWDSE==false){
        cout<<"There is no very weakly dominant strategy equilibrium.\n";
        return;
    }
    
    cout<<"The very weakly dominant strategy equilibriums are:\n";

    vector<int> v;
    findCombinations(0,vwds,v);
    v.clear();
}

void findNE(){
    for(int i=0;i<len;i++){
        vector<int> v=toStratProfile(i);
        vector<int> prof=v;
        bool ifNE=true;
        for(int j=0;j<no_of_players;j++){
            int temp=arr[i][j];
            for(int k=0;k<no_of_actions;k++){
                v[j]=k;
                if(arr[toNum(v)][j]>temp){
                    ifNE=false;
                    break;
                }
            }
            v[j]=prof[j];
            if(ifNE==false)
                break;
        }
        if(ifNE==true){
            displayStrategyProfile(prof);
        }
    }
}

int main(){
    cout<<"Enter number of players: ";
    cin>>no_of_players;
    cout<<"Enter number of actions for each player: ";
    cin>>no_of_actions;

    len=pow(no_of_actions,no_of_players);

    arr=(int **)(malloc(len*sizeof(int *)));
    for(int i=0;i<len;i++)
        arr[i]=(int *)(malloc(no_of_players*sizeof(int)));
            

    generate_from_gamut();
    generate_game();

    sds=(int *)(malloc(no_of_players*sizeof(int)));
    for(int i=0;i<no_of_players;i++)
        sds[i]=-2;
    
    vector<int> temp;
    for(int i=0;i<no_of_actions;i++)
        temp.push_back(i);

    for(int i=0;i<no_of_players;i++){
        wds.push_back(temp);
        vwds.push_back(temp);
    }
    
    for(int i=0;i<no_of_players;i++){
        vector<int> v;
        findStrats(0,i,v);
        v.clear();
    }

    cout<<"\n";
    checkSDSE();
    cout<<"\n";
    checkWDSE();
    cout<<"\n";
    checkVWDSE();
    cout<<"\n";
    cout<<"The Nash Equlibriums are:\n";
    findNE();

    return 0;
}