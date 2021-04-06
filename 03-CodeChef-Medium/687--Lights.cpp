#include <bits/stdc++.h>
using namespace std; 
#define ll long long 	
const int MOD = (int)1e9+7;
const int INF = (int)1e9;

int n; 
double L,R;
const double epsilon = 1e-9;
double x[50000],y[50000],z[50000];

bool overlaps(pair<double,double> a, pair<double,double> b){
	//cout<<"SUBTRACTION"<<(b.first-a.second)<<endl;
	if( (b.first-a.second)<=epsilon) return true;
	return false;
}
bool inside(pair<double,double> range, double l, double r){
	if(range.first-l<=epsilon && r-range.second<=epsilon) return true;
	return false;
}
bool valid(double h){
	vector<pair<double,double>> ranges;
	for(int i=0;i<n;i++){
		if(h<y[i]){
			double l1 = tan(z[i]*M_PI/180.0)*(y[i]-h);
			ranges.push_back({x[i]-l1,x[i]+l1});
			//cout<<ranges.back().first<<" "<<ranges.back().second<<endl;
		}
	}
	//cout<<"__________"<<endl;
	sort(ranges.begin(),ranges.end());
	vector<pair<double,double>> mergedRanges;
	if(ranges.size()!=0) mergedRanges.push_back(ranges[0]);
	for(int i=1;i<ranges.size();i++){
		if(overlaps(mergedRanges.back(),ranges[i])){
			mergedRanges.back().second = max(ranges[i].second,mergedRanges.back().second);
		}
		else mergedRanges.push_back(ranges[i]);
	}
	for(int i=0;i<mergedRanges.size();i++){
		//cout<<mergedRanges[i].first<<" "<<mergedRanges[i].second<<endl;
		if(inside(mergedRanges[i],L,R)) return true;
	}
	return false;
}
int main(){
	cin>>n>>L>>R;
	for(int i=0;i<n;i++){
		cin>>x[i]>>y[i]>>z[i];
	}
	double H1 = 0.0, H2 = 1000.0;
	double ans = INT_MIN;
	for(int i=0;i<=30;i++){
		double M = (H2+H1)/2.0;
		if(valid(M)){
			ans = max(ans,M);
			H1 = M+epsilon;
		}
		else H2 = M-epsilon;
	}
	cout<<setprecision(12)<<ans<<endl;
	return 0;
}
