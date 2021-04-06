#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int T,Delivery,Coupon;
int total_A=0,total_B=0,with_coupon,without_coupon;
cin>>T;
while(T--)
{
	for(int i=0;i<10;i++){}
int A[3],B[3];
cin>>Delivery>>Coupon;
for(int i=0;i<3;i++)
{
cin>>A[i];
}
for(int i=0;i<10;i++){}
for(int j=0;j<3;j++)
{
cin>>B[j];
}
for(int i=0;i<10;i++){}
total_A=A[0]+A[1]+A[2];
total_B=B[0]+B[1]+B[2];
if(total_A >=150 && total_B >= 150)
{
with_coupon=total_A+total_B+Coupon;
without_coupon=total_A+total_B+2*(Delivery);
}
else if(total_A >=150 || total_B >= 150)
{
with_coupon=total_A+total_B+Coupon+Delivery;
without_coupon=total_A+total_B+2*(Delivery);
}
else
{
with_coupon=total_A+total_B+Coupon+2*(Delivery);
without_coupon=total_A+total_B+2*(Delivery);

    }
    if(with_coupon<without_coupon)
        {
            cout<<"YES\n";
        }
        else
        {
            cout<<"NO\n";
        }  
}
	return 0;
}
