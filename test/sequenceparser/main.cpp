
#include "bracket.cpp"

#include<iostream>
#include <memory>
#include<vector>
#include<string>

auto Parsebracket(std::string stringsequence){
	auto NextOpenbracket=1;
	auto cPosition=1;
	std::vector<uint> Startedbrakets;
	brackets Foundbrackets; 
		
	for(char& c : stringsequence) {
    	
		//OpenbracketMet 
		if (c=='(') {
			//std::cout<<"in ("<<'\n';
			Foundbrackets.open(cPosition);
			Startedbrakets.push_back(NextOpenbracket);
			NextOpenbracket++;
		}
		else if (c==')') {// ClosebracketMet();
			//std::cout<<"in )"<<'\n';
			Foundbrackets.close(cPosition,Startedbrakets.back());
			Startedbrakets.pop_back();
		}
		
		std::cout<<cPosition <<" : " << c <<'\n';
		cPosition++;
	}

	//Found brackets cout
	std::cout<<Foundbrackets.size() <<" blocks found :" << '\n';
	for(int i=1;i<=Foundbrackets.size();i++){
		Foundbrackets[i]->setdata(stringsequence);
		
		Foundbrackets[i]->value();
	}
	//std::cout<<"test : " << Foundbrackets[1]->startPosition()<<'\n';
	//std::cout<<" extracted data : " << Foundbrackets[1]->extractData(Foundbrackets[2])<<'\n';
	
	return 1;
}

int main(){
	auto Parsed=Parsebracket("(moi(nice())fatigu)(last)");
	return 1;
}

