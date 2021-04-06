#include<bits/stdc++.h>
#define CAPACITY 20
using namespace std;
int stack1[CAPACITY];
int top=-1;
void push(int x){
    if(top==CAPACITY-1){
        cout<<""<<endl;
    }
    else{
        top++;
        stack1[top]=x;
    }
}
int pop()
{
    if(top==-1){
        cout<<""<<endl;
    }
    else{
        int y=stack1[top];
        top--;
        return y;
    }
}
int main()
{
    int T;
    cin>>T;
    while(T>0){
        int N,temp,temp1;
        cin>>N;
        int A[N];
        for(int i=0;i<N;i++){
            cin>>A[i];
            push(A[i]);
        }
        if(N==1){
            cout<<A[0]<<endl;
        }
        else if(N==2){
            cout<<A[0]<<" "<<A[1]<<endl;
        }
        else{
            sort(A,A+N);
        for(int i=0;i<=top;i++){
            if(stack1[i]==A[N-1]){
                temp=i;
            }
            else if(stack1[i]==A[0]){
                temp1=i;
            }
        }
        if(temp<temp1){
            cout<<stack1[temp]<<" "<<stack1[temp1]<<endl;
        }
        else if(temp1<temp){
            cout<<stack1[temp1]<<" "<<stack1[temp]<<endl;
        }
    }
        for(int i=top;i>=0;i--){
            int z=pop();
        }
        T--;
    }
    return 0;
}

