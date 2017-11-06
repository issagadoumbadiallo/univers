#include <iostream>
#include <fstream>
#include <sstream>
#include "adouna/globalConst.h"
#include <algorithm>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cassert>

class Maille{
	private:
		int lasti,lastj;
		int iMax,jMax;
		std::vector<double> MailleContainer;
	public: 

		Maille(int iMax, int jMax):iMax(iMax),jMax(jMax){ lasti=0;lastj=0;MailleContainer.reserve(iMax*jMax);}
	
		~Maille(){
			std::cout<<"Destroying Maille"<<'\n';
			//std::cout<<"before"<<MailleContainer.size()<<'\n';
			//MailleContainer.erase(MailleContainer.begin(),MailleContainer.end());
			//std::cout<<"after"<<MailleContainer.size()<<'\n';
		}
		
		void clear(){MailleContainer.clear();}
		int size()const{return MailleContainer.size(); }
		int GetLasti() const {return lasti;}
		int GetLastj() const {return lastj;}
		
		double value(int i,int j) const {return MailleContainer[i+iMax*j];}

		void MailleGridPoint( int i, int j,double value) {
			MailleContainer[i+iMax*j]=value;
			if (i>lasti) lasti=i;
			if (j>lastj) lastj=j;
		}

};

void BuildTwoBlocks(int x,int y, Maille &blocs){
	
	blocs.clear();
	
	int i=0;
	
	auto Add=[&blocs, &x, &y,&i](int iValue,int jValue){
		
		if (iValue>=0 && jValue>=0) {
			std::cout<<"Blocs "<<i<<","<<x<<","<<y<<","<<iValue<<","<<jValue<<'\n'; 
			blocs.MailleGridPoint(i,0,x);
			blocs.MailleGridPoint(i,1,y);
			blocs.MailleGridPoint(i,2,iValue);
			blocs.MailleGridPoint(i,3,jValue);
			++i;
		}
	};
	
	Add(x-1,y);
	Add(x-1,y+1);
	Add(x,y+1);
	Add(x+1,y+1);
	Add(x+1,y);
	Add(x+1,y-1);
	Add(x,y-1);
	Add(x-1,y-1);	
	
}

void BuildBlocs(int i, int j,int nbBoxes, Maille &blocs){
	assert(nbBoxes >=2 || nbBoxes <= 3);
	
	;

	if  (nbBoxes==2) return BuildTwoBlocks(i,j,blocs);
	
	/* To be complete
	if  (nbBoxes=3) {
		Maille ThreeBBlocks(8,3);
		for(int i; i<=TwoBlocks.GetLasti();++i){
			for(int j; j<=TwoBlocks.GetLastj();++j){
				
			}
		}
		return ThreeBBlocks;
	}
	*/
}

class Grid{
	private:
		int lasti,lastj;
		int iMax=10000,jMax=10000;
		std::vector<double> GridPoint;
		std::vector<int> DataState;//1 yes filled with data ; 0 never touched
	public: 

		Grid(int iMax,int jMax){
			   lasti=iMax;lastj=jMax;
			   GridPoint.reserve(iMax*jMax);
			   DataState.reserve(iMax*jMax);
			  }
	
		~Grid(){
			std::cout<<"Destroying Grid"<<'\n';
		}
	
		Grid(std::string FileName){
			
			lasti=0;lastj=0;
			
			GridPoint.reserve(iMax*jMax);
			DataState.reserve(iMax*jMax);

			std::ifstream InPutFile;
			InPutFile.open(FileName, std::ifstream::in);

		    assert(InPutFile.is_open()==true && 
				   "Impossible d'acceder au fichier Input");

			std::string LineString;
			int i=0;
			int j=0;
			while (getline ( InPutFile, LineString) ) {   
				//;
				//if (i==2) goto next;
				std::stringstream LineStringElement;
				LineStringElement.str(LineString);

				std::string item;
				//std::cout<<"in"<<"\n";
				//std::cout<<LineString<<"\n";

				while(getline(LineStringElement, item,';')){
					if (item.size()>1) {

						std::string orbits(item);
						std::string::size_type sz;
						SetGridPoint(i,j,std::stod (orbits,&sz));	
						SetToFull(i,j);//Mark as Nodata in the field
						//std::cout<<i<<","<<j<<"\n";
						++j;
					}
				}

				if( j-1>lastj) lastj=j-1;	
				lasti=i;

				j=0;

				++i;
				}
				
			//next:
			//std::cout<<lasti<<"," << lastj <<"\n";

			InPutFile.close();

		}

		int GetLasti() const {return lasti;}
		int GetLastj() const {return lastj;}
		
		double value(int i,int j) const {return GridPoint[i+iMax*j];}

		void SetGridPoint( int i, int j,double value) {
			//if (i==1000 && j==1000) std::cout<<value<<"\n";
			GridPoint[i+iMax*j]=value;
		}
		
	   void SetToFull( int i, int j) {
			DataState[i+iMax*j]=1;
		    assert(DataState[0+iMax*1]!=1);
		}
		
		int ContainData( int i, int j)  const {
			//std::cout<<"set to "<<'\n' ; //<<DataState[i+iMax*j]<<","<<i<<","<<j<<'\n' ;
			//if ( DataState[i+iMax*j] == 1 ) return 0;  else return 1;
			return ( DataState[i+iMax*j] == 1 ) ? 1:0;
		}

		void Save(std::string FileName){//,bool SaveOnlyTheBest=false){
			//create a file and leave in open mode or better to right in ostream and

			std::ofstream OuPutFile(FileName);

			std::string LineString;
			
			for(int i=0; i<=lasti;++i){	
				
				LineString="";//initialisation
				for(int j=0; j<=lastj;++j){
					
					if (this->ContainData(i,j)==1){
						int value=this->value(i,j);//cast to int
						LineString=LineString +std::to_string(value) + ";";
					}
				}
				//write line
				OuPutFile<<LineString<<'\n';
			}
			
			OuPutFile.close();
			
			std::cout<<"data have been wrote "<<'\n';

		}
	
		void BestValueFromListOfPositionInGrid(Maille & Blocs,Maille & BestPoints){
			
			//std::cout<<Blocs.value(0,0)<<","<<Blocs.value(0,1)<<","<<Blocs.value(0,2)<<","<<Blocs.value(0,3)<<'\n';
			
			auto SetBestPoints=[&BestPoints](int row,int i, int j,double value){
					BestPoints.MailleGridPoint(row,0,i);//i
					BestPoints.MailleGridPoint(row,1,j);//j
					BestPoints.MailleGridPoint(row,2,value);
			};
			
			for(int i=0; i<=Blocs.GetLasti();++i){				
				for(int j=1; j<=Blocs.GetLastj();j=j+2){
					//if(i==3) goto next;
					int x=Blocs.value(i,j-1),y=Blocs.value(i,j);
					
					double value=this->value(x,y);
					///*
					std::cout<<"Point value =: "<<value<<'\n';
					std::cout<<"nuplet: "<<i<<","<<j<<","<<x<<","<<y<<'\n';
					//*/
					if (this->ContainData(x,y)==0){//If one point does not have value, stop for this bloc (row)
					    //std::cout<<"one empty point"<<'\n';//one empty point
						SetBestPoints(i,-1,-1,0);//no best for this block 
						goto NextNupletBlock;
					}
					std::cout<<"over"<<'\n';
					
					std::cout<<value<<'\n';
					if (j==1) {//at start
						SetBestPoints(i,x,y,value);
					}
					else {
						if (value>BestPoints.value(i,2)) {
							SetBestPoints(i,x,y,value);
						}
					}
					
				}
				NextNupletBlock:
				std::cout<<"";
				//std::cout<<"next nuplet"<<'\n';
			}
			/*
			//next:
			//i,j,value
			std::cout<<"BestiPosition,BestjPosition,BestvaluePosition (-1,*,* no best possible cause of empty point"<<'\n';
			std::cout<<BestPoints.value(0,0)<<","<<BestPoints.value(0,1)<<","<<BestPoints.value(0,2)<<'\n';
			std::cout<<BestPoints.value(1,0)<<","<<BestPoints.value(1,1)<<","<<BestPoints.value(1,2)<<'\n';
			std::cout<<BestPoints.value(2,0)<<","<<BestPoints.value(2,1)<<","<<BestPoints.value(2,2)<<'\n';
			std::cout<<"Going out of BestPoints"<<'\n';
			*/
		}
	
		void Aggregatevalue(const Maille &BestPoints) {
			int x, y;
			for(int i=0; i<=BestPoints.GetLasti();++i){	
				x=BestPoints.value(i,0);
				if (x!=-1){
					//Update the point Score by *
					y=BestPoints.value(i,1);
					
					GridPoint[x+iMax*y]=GridPoint[x+iMax*y]+1;
					std::cout<<"Aggregate value "<<GridPoint[x+iMax*y]<<" at "<<x<<","<<y<<'\n';
					
					SetToFull(x,y);//the data have been updated
				}
				if (i==1000) goto next;
			}
			next:
			std::cout<<"Aggregate out "<<'\n';	
			
		}

};

void ComputeBest(Grid & DataGrid, Grid * ptr_Score,int nbBoxes){
/*
	std::cout<<ptr_Score->GetLasti()<<'\n';
	std::cout<<DataGrid.GetLasti()<<'\n';
*/
	Maille Blocs(8,4);
	Maille BestPoints(8,3);
	
	for(int i=0; i<=DataGrid.GetLasti();++i){
		for(int j=0; j<=DataGrid.GetLastj();++j){
			//std::cout<<"in again"<<'\n';
			// si le point est vide ? aucun traitement
			if (DataGrid.ContainData(i,j)==1){
				
				std::cout<<"New Point " <<i<<","<<j<<"\n";//std::cout<<"check " <<DataGrid.value(i,j)<<'\n';
				//trouver les blocks nbBoxes autour de i,jMailleContainer
				//Find the best per  bloc
				BuildBlocs(i,j,2,Blocs) ;
				
				DataGrid.BestValueFromListOfPositionInGrid(Blocs,BestPoints);
			
				//std::cout<<"am out"<<'\n';
				//incrementer la valeur ds Score
				ptr_Score->Aggregatevalue(BestPoints);
				//std::cout<<"am outof agg"<<'\n'; 
				//std::cout<<"am out"<<j<<'\n';
				std::cout<<"Aggregate end "<<'\n';
	
			}	
			//std::cout<<"am out"<<'\n';
			//goto next;
			if (i==1000) goto next;
			//std::cout<<"am out"<<j<<'\n';
		}
		std::cout<<"over for"<<'\n';
	}
	// /*
	next:
	std::cout<<"over"<<'\n';
	// */
}



 int main() {

	globalobj::log<<"kljlk"<<"ljk";
	
	Grid File("/media/sf_cpproot/data/input/areva.csv");
	
	Grid Score(File.GetLasti(),File.GetLastj());

	ComputeBest(File,&Score,3);
	
	assert(Score.GetLasti()!=0);
	 
	Score.Save("/media/sf_cpproot/data/output/areva_score.csv");
	
	return 0;
}
