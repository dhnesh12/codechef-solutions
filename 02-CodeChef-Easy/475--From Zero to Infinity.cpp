#include<bits/stdc++.h>

bool isvowel(char c){
	if((c=='a') || (c=='e') || (c=='i') || (c=='o') || (c=='u'))	return true;
	return false;
}

bool Isalice(std::string str){
	if(str.length()==2){
		if(isvowel(str[0]) || isvowel(str[1]))	return true;
		else	return false;
	}
	if(!isvowel(str[0]) && !isvowel(str[1]))	return false;
	for(int i=2;i<str.length();i++)
		if(!isvowel(str[i]))
			if((!isvowel(str[i-1])) || (!isvowel(str[i-2])))	return false;
	return true;
}

int main(){
	int t,l;
	std::cin >> t;
	while(t--){
		std::cin >> l;
		std::string s[l];
		for(int i=0;i<l;i++)	std::cin >> s[i];
		double randomArray[26],nalice=0,nbob=0;
		double aliceCnt[26]={0},aliceFrequency[26]={0};
		double bobCnt[26]={0},bobFrequency[26]={0};
		double alice=0,bob=0;
		for(int i=0;i<l;i++){
			std::memset(randomArray,0,sizeof(randomArray));
			for(int j=0;j<s[i].length();j++)	randomArray[int(s[i][j])-97]++;
			if(Isalice(s[i])){
				//std::cout << "Alice" << std::endl;
				nalice++;
				for(int j=0;j<26;j++){
					if(randomArray[j]!=0){
						aliceCnt[j]++;
						aliceFrequency[j] += randomArray[j];
					}
				}
			}else{
				//std::cout << "Bob" << std::endl;
				nbob++;
				for(int j=0;j<26;j++){
					if(randomArray[j]!=0){
						bobCnt[j]++;
						bobFrequency[j] += randomArray[j];
					}
				}
			}
		}
		// std::cout << "Index:" << "	" << "Alice:" << std::endl;
		// for(int j=0;j<26;j++)	std::cout << j << "	" << aliceCnt[j] << "	" << aliceFrequency[j] << "	" << std::endl;
		// std::cout << std::endl;
		// std::cout << "Index:" << "	" << "Bob:" << std::endl;
		// for(int j=0;j<26;j++)	std::cout << j << "	" << bobCnt[j] << "	" << bobFrequency[j] << "	" << std::endl;
		// std::cout << std::endl;
		// std::cout << "<------------------------------------------------------->" << std::endl;
		if(nalice>0)	alice=1.000000;
		if(nbob>0)	bob=1.000000;
		for(int j=0;j<26;j++)
			if(aliceCnt[j]!=0){
				alice *= (aliceCnt[j]/std::pow(aliceFrequency[j],nalice));
			}
		//std::cout << std::endl;
		for(int j=0;j<26;j++)
			if(bobCnt[j]!=0){
				bob *= (bobCnt[j]/std::pow(bobFrequency[j],nbob));
			}
		if((nbob == 0) || (alice/bob) > (10000000.0))
		std::cout << "Infinity" << std::endl;
		else
		std::cout << std::fixed << std::setprecision(7) << alice/bob << std::endl;
	for(int j=0;j<l;j++) s[j].clear();
	}
	return 0;
}