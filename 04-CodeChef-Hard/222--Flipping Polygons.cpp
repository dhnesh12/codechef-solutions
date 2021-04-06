#include<bits/stdc++.h>
int n,q,type,l,r,p;  std::vector<int> a(1e5); struct Node{ int sign=1; long long deg=0; }seg[280000];
void lazy(int v) {
    seg[v<<1].deg += seg[v].deg*seg[v<<1].sign, seg[(v<<1)|1].deg += seg[v].deg*seg[(v<<1)|1].sign;
    seg[v<<1].sign *= seg[v].sign, seg[(v<<1)|1].sign *= seg[v].sign;
    seg[v].deg = 0; seg[v].sign=1;
}
void rotate(int v,int l,int r,int L,int R,int p) {
    if(l==L && r==R){ seg[v].deg += p*seg[v].sign; return; }   lazy(v); 
    if(L<=(r+l)/2) rotate(v<<1,l,(r+l)/2,L,std::min((r+l)/2,R),p);
    if(R>(r+l)/2)  rotate((v<<1)|1, (r+l)/2+1,r,std::max(L,(r+l)/2+1),R,p);
}
void reflect(int v,int l,int r,int L,int R) {
    if(l==L && r==R){ seg[v].sign *= -1;  return; } lazy(v);
    if(L<=(r+l)/2) reflect(v<<1,l,(r+l)/2,L,std::min((r+l)/2,R));
    if(R>(r+l)/2)  reflect((v<<1)|1, (r+l)/2+1,r,std::max(L,(r+l)/2+1),R);
}
std::pair<long long,int> query(int v,int l,int r,int L) {
    if(l==r && r==L) return {seg[v].deg, seg[v].sign}; lazy(v); 
    return L<=(r+l)/2?query(v<<1,l,(r+l)/2,L):query((v<<1)|1, (r+l)/2+1,r,L);
}
int main(){
    std::cin >> n >> q; for (int i=0; i<n; i++) std::cin >> a[i];
    while(q--) {
        std::cin >> type >> l >> r; --l; --r;
        if(type == 1) std::cin >> p, rotate(1,0,n-1,l,r,p);
        else if(type ==2) reflect(1,0,n-1,l,r);
        else {
            std::pair<long long,int> moved = query(1,0,n-1,l);
            r = moved.second==1?(r + moved.first)%a[l]:(-(r + moved.first)+!(a[l]%2))%a[l];
            std::cout << (r+a[l])%a[l]+1 << '\n';
        }
    } return 0;
}