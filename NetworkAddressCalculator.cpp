//-----		NETWORK ADDRESS CALCULATOR	------
//Author: Juan Sebastian Dueñas 		email: jsdueas@unal.edu.co

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include <math.h> 
#include <vector>
#include <algorithm>

using namespace std;


bitset<32>setAddress(int number){// makes a temp biset so it can be assign to an existing one
		bitset<32> temp (number);
		return temp;
}

	bitset <32> setMask (int n){// return the subnet mask 
		bitset<32> mask;
		for( int i=32-n; i< 32;i++){
			mask[i]=1;
		}
	
		return mask;
	}
	
 
	
	bitset <32> binaryForm(string IP){ 	// transform a IP address to its binary form
		string binIP ;					// IP address in binary form
		stringstream iss(IP);
		int octect[4] ;
		
		for (int i=0 ; i<4;i++){	
			iss >> octect[i];
			iss.ignore(1, '.');
			//cout<<octect[i]<<endl;
		}
		
		//octets in binary form
		bitset<8>binOct1(octect[0]);
		bitset<8>binOct2(octect[1]);
		bitset<8>binOct3(octect[2]);
		bitset<8>binOct4(octect[3]);
		
		// concatenate all the octects in one string
		binIP =    binOct1.to_string() + binOct2.to_string() 
				 + binOct3.to_string() + binOct4.to_string()  ; 
		bitset<32> stringToBitSet(binIP);
		
		return stringToBitSet;
	}
	
	string  numericForm (bitset <32> binIP){
		bitset<8> binOctect();						// octect in bin form
		stringstream iss( binIP.to_string() );		// 
		stringstream out("");
		char str[8];
	    
		for (int i=0; i<4 ;i++){
			iss.get(str, 9); 				// insert to 8 chars from de stream
			string s=string(str);			// transform into string
			bitset<8> binOctect(s);
			out <<binOctect.to_ulong();		// insert numeric octect to the out stream
			if(i<3){
				out<<".";	
			}
		}
		
		return out.str();	
	}
	

	
class Net 
{ 
    // Access specifier 
    public: 
	string description;
	bitset<32> address;				// IP address in binary form
	bitset<32> mask;			
	bitset<32> network; 
	bitset<32> broadcast;
	bitset<32> first;			// first Host
	bitset<32> last;			// last Host
	int capacity;				// host capacity
	
	
	Net(string IP, int n){
		description ="";
		//address made of: Network part and Host part
		address=binaryForm(IP);						// IP address to binary form
		mask= setMask(n);							// mask: Network part to 1 and Host part to 0
		network=address & mask; 					// network: host part to 0 (address AND mask) 
		broadcast=address |(~mask);					// broadcast: host part to 1 (network OR NOT mask)
		first= setAddress(network.to_ulong()+1);		// first Host: network address + 1
		last=setAddress(broadcast.to_ulong()-1);	// last Host: broadcast address -1			
		capacity= pow(2,32-n)-2;
	}
	

	
	string show (){
		stringstream out("");
		
		//string header="   address: \t  network: \t   mask: \t broadcast: \t first: \t last: \t\t capacity ";
		//out<<header<<endl;
		out<<endl;
		out<<"address: \t"<<numericForm(address)<<endl
		   <<"network: \t"<<numericForm(network)<<" /"<<mask.count()<<endl
		   <<"mask: \t\t"<<numericForm(mask)<<endl
		   <<"first: \t\t"<<numericForm(first)<<endl
		   <<"last: \t\t"<<numericForm(last)<<endl
		   <<"broadcast: \t"<<numericForm(broadcast)<<endl
		   <<"capacity: \t"<<capacity<<endl			;
		
		cout<<out.str();
		return out.str();	
	}


};

Net nextIP(Net previous, int users){
	int n= log2(users+1)+1;
	int num=previous.broadcast.to_ulong()+1;
	bitset<32> temp(num);
	string IP= numericForm(temp);
	Net prev(IP,32-n);
	return prev;
}

int main () {
	//ofstream myfile;
	//myfile.open ("report.txt");

	string IP= "192.168.10.107";								// network
	int firstUsers=4;
	int n= log2(firstUsers+1)+1;
	string description="";
	
	Net subnet(IP, 32-n);
	subnet.show();
	
	
	
	// myfile << mask[1]<<"Writing this to a file.\n";
	//myfile.close();
	
	
	
	cout<<endl<<endl<<"end.";
	return 0;
}
