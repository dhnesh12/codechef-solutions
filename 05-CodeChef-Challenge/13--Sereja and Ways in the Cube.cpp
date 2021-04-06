#include <bits/stdc++.h>
    using namespace std;
     
     
    typedef long int ll;
     
    int main()
    {	
        ios_base::sync_with_stdio(0); cin.tie(0);
    	ll tc;cin>>tc;
     
    	while(tc--)
    	{
    		ll n;cin>>n;
    		ll a[n+1][n+1][n+1];
     
    		for(ll k=0;k<n;k++)
    			for(ll j=0;j<n;j++)
    				for(ll i=0;i<n;i++)
    					cin>>a[k+1][j+1][i+1];
     
            
            if(n<5 )
            {
                cout<<"1\n1 1 1\n";continue;
            }
            
            ll n1=1,n2=1,n3=1;
            int vis[n+2][n+2] = {0};
            int vis2[n+2][n+2] = {0};
            
            vector<ll>seq1[2],seq2[2],seqq2[2],seq3[2],ans[3];
            
            
            for(n2=1;n2<n;n2++)
            {
                seq1[0].push_back(n1);
                seq1[1].push_back(n2);
                
                ll nn = seq1[0].size()-1;
                if(nn>0){
                vis[seq1[0][nn-1]][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]+1][seq1[1][nn-1]]=1;
                
                vis[seq1[0][nn-1]][seq1[1][nn-1]+1]=1;
                vis[seq1[0][nn-1]-1][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]][seq1[1][nn-1]-1]=1;
                }
            }
            
            
            for(n1=1;n1<n;n1++)
            {
                seq1[0].push_back(n1);
                seq1[1].push_back(n2);
                
                
                ll nn = seq1[0].size()-1;
                if(nn>0){
                vis[seq1[0][nn-1]][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]+1][seq1[1][nn-1]]=1;
                
                vis[seq1[0][nn-1]][seq1[1][nn-1]+1]=1;
                vis[seq1[0][nn-1]-1][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]][seq1[1][nn-1]-1]=1;
                }
            }
            
            for(;n2>1;n2--)
            {
                seq1[0].push_back(n1);
                seq1[1].push_back(n2);
                
                
                ll nn = seq1[0].size()-1;
               if(nn>0){
                vis[seq1[0][nn-1]][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]+1][seq1[1][nn-1]]=1;
                
                vis[seq1[0][nn-1]][seq1[1][nn-1]+1]=1;
                vis[seq1[0][nn-1]-1][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]][seq1[1][nn-1]-1]=1;
                }
            }
            
            ll cnt=n-2,f=3;
            ll tmp1=-1,tmp2=0;
            
            while(true)
            {
                seq1[0].push_back(n1);
                seq1[1].push_back(n2);
                
                ll nn = seq1[0].size()-1;
                if(nn>0){
                vis[seq1[0][nn-1]][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]+1][seq1[1][nn-1]]=1;
                
                vis[seq1[0][nn-1]][seq1[1][nn-1]+1]=1;
                vis[seq1[0][nn-1]-1][seq1[1][nn-1]]=1;
                vis[seq1[0][nn-1]][seq1[1][nn-1]-1]=1;
                }
                n1+=tmp1;n2+=tmp2;
                
                if(vis[n1][n2])
                {
                    n1-=tmp1;n2-=tmp2;
                    f+=1;f= f%4;
                    if(f==0)
                    {
                        tmp1 = 0;tmp2 = 1;
                    }
                    else if(f==1)
                    {   
                        tmp1 = 1;tmp2 = 0;
                    }
                    else if(f==2)
                    {
                        tmp1 = 0;tmp2 = -1;
                    }
                    else
                    {
                        tmp1 = -1;tmp2 = 0;
                    }
                
                
                n1+=tmp1;n2+=tmp2;
                
                if(vis[n1][n2])
                { 
                    break;
                }
                    
                }
            }
            
        
            for(ll i=0;i<seq1[0].size();i++)
            {
                vis2[seq1[0][i]][seq1[1][i]] = 1;
            }
            
            seq2[0].push_back(2);
            seq2[1].push_back(1);
            vis2[2][1]=1;
            
            n1=2,n2=2;
            
            while(true)
            {
                seq2[0].push_back(n1);
                seq2[1].push_back(n2);
                vis2[n1][n2]=1;
                
                ll fff=1;
                
                if(vis2[n1-1][n2]==0)
                n1-=1,fff=0;
                else if(vis2[n1][n2-1]==0)
                n2-=1,fff=0;
                else if(vis2[n1][n2+1]==0)
                n2+=1,fff=0;
                else if(vis2[n1+1][n2]==0)
                n1+=1,fff=0;             
                
                if(fff)
                break;
            }
           
           ll x = seq1[0][seq1[0].size()-1],y=seq1[1][seq1[1].size()-1];
           seqq2[0].push_back(x);
           seqq2[1].push_back(y);
           
           for(ll i=seq2[0].size()-(1 + n%2);i>=0;i--)
           {
               if( abs(seq2[0][i]-x)  + abs(seq2[1][i]-y) < 2)
               {
                   seqq2[0].clear();
                   seqq2[1].clear();
                   seqq2[0].push_back(x);
                   seqq2[1].push_back(x);
                   
               }
                seqq2[0].push_back(seq2[0][i]);
                seqq2[1].push_back(seq2[1][i]);
           }
           
           
           
           seq3[0].push_back(2);
           seq3[1].push_back(1);
           seq3[0].push_back(1);
           seq3[1].push_back(1);
            
            
            for(ll i=1;i<=n;i++)
            {
                if(i%3==1)
                {
                    for(ll j=0;j<seq1[0].size();j++)
                    ans[0].push_back(i),ans[1].push_back(seq1[0][j]),ans[2].push_back(seq1[1][j]);
                    
                }
                else if(i%3==2)
                {
                    for(ll j=0;j<seqq2[0].size();j++)
                    ans[0].push_back(i),ans[1].push_back(seqq2[0][j]),ans[2].push_back(seqq2[1][j]);
                    
                }
                else
                {
                    for(ll j=0;j<seq3[0].size();j++)
                    ans[0].push_back(i),ans[1].push_back(seq3[0][j]),ans[2].push_back(seq3[1][j]);
                    
                    
                }
            }
            
            
            cout<<ans[0].size()<<"\n";
            
            for(ll i=0;i<ans[0].size();i++)
            {
                cout<<ans[0][i]<<" "<<ans[1][i]<<" "<<ans[2][i]<<" \n";
            }
            
    	}
     
    	
     
    	return 0;
    }  