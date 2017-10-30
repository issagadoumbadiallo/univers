#include<iostream>
#include <memory>
#include<vector>
#include<string>

typedef unsigned int uint;

class bracket{
	
private:
	uint bracketIndex;
	uint OpenPosition;
	uint ClosePosition;
	std::string dataInsideTheBraket;
public:
	bracket(){
		static uint autobracketIndex=0;
		bracketIndex=++autobracketIndex;
		OpenPosition=0;//close position not set yet
		ClosePosition=0;//close position not set yet
		//std::cout<<"Index " << bracketIndex <<'\n';
	};
	
	void addOpen(uint position){OpenPosition=position;}
	void addClose(uint position){ClosePosition=position;}
	bool isOpen(){if (OpenPosition==0) return true;}
	bool isClosed(){if (ClosePosition==0) return true;}
	
	uint startPosition(){return OpenPosition;}
	uint endPosition(){return ClosePosition;}
	
	void value(){
		std::cout<<"     (" << bracketIndex 
							<< ", " << 	OpenPosition << ", " << ClosePosition << ") : "<< dataInsideTheBraket<<'\n';
		//return data;//
	}
	void setdata(std::string const&  stringsequence){
		dataInsideTheBraket=stringsequence.substr(OpenPosition,ClosePosition-OpenPosition-1);
	}
	auto extractData(std::shared_ptr<bracket> const dataToExtract){
		auto startOutside = this->OpenPosition;
		auto startInside  = dataToExtract->startPosition();
		auto endInside    = dataToExtract->endPosition();
		auto endOutside   = this->ClosePosition;

		return startOutside<=startInside && endInside<=endOutside ? 
			   this->dataInsideTheBraket.substr(startOutside-1,startInside-startOutside-1) 
			   + this->dataInsideTheBraket.substr(endInside-1,endOutside-endInside-1):"";
		
	}
	
	std::string data(){return dataInsideTheBraket;}
};

class brackets{
private:
	std::vector<std::shared_ptr<bracket>> bracketsPool;
public:

	brackets(){};
	
	void open(uint position){
			std::unique_ptr<bracket> prt_newbracket(new bracket);
			prt_newbracket->addOpen(position);
			bracketsPool.push_back(std::move(prt_newbracket));
		   //std::cout<<"bracket opened" <<'\n'; 
	}
	
	void close(uint position,uint BracketIndex){
		this->bracketsPool[BracketIndex-1]->addClose(position);
		//std::cout<<"Index closed " << BracketIndex <<'\n';
	}
	
	auto operator[](uint bracketIndex){
		return bracketsPool[bracketIndex-1];
	}
	
	auto size(){return bracketsPool.size();}
};
// this have to be put outside and a test have to be built
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
	for(uint i=1;i<=Foundbrackets.size();i++){
		Foundbrackets[i]->setdata(stringsequence);
		
		Foundbrackets[i]->value();
	}

	return 1;
}
