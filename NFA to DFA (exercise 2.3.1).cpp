#include<bits/stdc++.h>
using namespace std;

#define n 4

string start_state,end_state;
string a[20][3];
string ch[50];
string r[50][2];

string sorting(string s)
{
    char temp;
    for(int i=0; i<s.length(); i++)
    {
        for(int j=i+1; j<s.length(); j++)
        {
            if(s[i]>s[j])
            {
                temp=s[j];
                s[j]=s[i];
                s[i]=temp;
            }
        }
    }
    return s;
}

string generate_powerset(int counter, int l)
{
    string res;
    for(int j = 0; j < l; j++)
    {
        if(counter & (1 << j))
        {
            res+=a[j][0];
            if(a[j][0]==end_state)
                res+='*';       ///accepting state
        }
    }
    if(res==start_state)
        res+='$';     ///$ for start state
    res=sorting(res);
    return res;
}

string cardinality(string s)
{
    string str;
    int i=0,j=0,temp;
    int l=s.length();
    s=sorting(s);
    if(s[i]!='0')
        str+=s[i];
    for(i=1; s[i]; i++)
    {
        if(s[i]!=s[i-1] && s[i]!='0')
        {
            str+=s[i];
        }
    }
    return str;
}

void generate_nfa(string s,int c)
{
    for(int i = 0; i < s.length(); i++)
    {
        string t;
        t+=s[i];
        for(int j = 0; j < n; j++)
        {
            if(t==a[j][0])
            {
                r[c][0]+=a[j][1];
                r[c][1]+=a[j][2];
            }
        }

    }
    r[c][0]=cardinality(r[c][0]);
    r[c][1]=cardinality(r[c][1]);
}

string de_set(string r)
{
    string t;
    int c=0;
    for(int i = 0; i<r.length(); i++)
    {
        if(r[i] != '{' && r[i] != '}' && r[i] != ',')
        {
            t+=r[i];
            c++;
        }
    }
    return t;
}

string re_set(string s)
{
    string t;
    int c=0;
    while(c<s.length())
    {
        if(c==0 && s[c]=='*')
        {
            t=t+'*'+'{';
            c++;
        }
        if(c==0 && s[c]=='$')
        {
            t=t+'$'+'{';
            c++;
        }
        else if(c==0)
            t=t+'{';
        t+=s[c];
        if(c<s.length()-1)
            t+=',';
        c++;
    }
    t+='}';
        t+="\t\t";
    return t;
}

int main()
{
    ifstream in;
    ofstream out;
    int i, j, l;
    int c=0;

    cout << "Enter Starting state (\"p\" for 2.3.1): " ;
    cin >> start_state ;
    cout << "Enter ending state (\"q\" for 2.3.1): ";
    cin >> end_state;
    //cout<<"How many state: ";
    //cin>>n;
    in.open("input table.txt");
    if(!in.is_open())
        cout<<"File open error"<<endl;

    for(i = 0; i < n; i++)
    {
        in >> a[i][0] >> a[i][1] >> a[i][2];
        a[i][1]=de_set(a[i][1]);
        a[i][2]=de_set(a[i][2]);
    }
    in.close();

    for(i = 0; i < pow(2,n); i++)
    {
        ch[i] = generate_powerset(i,n);
        generate_nfa(ch[i],i);
    }

    cout<<"                     |         0         |        1        |"<<endl;
    cout<<"---------------------|-------------------|-----------------|"<<endl;
    for(i = 1; i < pow(2,n); i++)
    {
        if(r[i][0]== "0" || r[i][1] == "0")
            continue;
        else
        {
            cout<<re_set(ch[i])<<"\t|  "<<re_set(r[i][0])<<"\t|  "<<re_set(r[i][1])<<endl;
        }
    }
    return 0;
}







