//Junho Lee
//824002195
//CSCE 420
//Due: 03/07/2018
//hw2pr3.cpp

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Node {
public:
	bool isLast;
	bool make_false;
	char alp;
	bool value;
	
	vector<char> nodeVec;
	Node();
	Node(bool v, bool i, bool s, char l);
};

Node::Node() {
	alp = ' ';
	value = false;
	isLast = false;
	make_false = false;
}

Node::Node(bool val, bool iL, bool mf, char a) {
	value = val;
	isLast = iL;
	make_false = mf;
	alp = a;
}

int main(int argc, const char * argv[]) {
	
	ifstream infile;
	infile.open("input.txt");
	
	char last_alp;
	char temp[512];
	string s;
	
	map<char, Node> mapped_node;
	vector<char> alp_vec;
	
	cout << "input data: " << endl;
	
	bool checker = false;	
	
while(cin.getline(temp,512)) {
	getline(infile, s);
	string s = temp;
	char c = s.at(0);
		
	if( s.size() == 2 && isalpha(c) ) {
			
		if(mapped_node.find(c) == mapped_node.end()) {
			alp_vec.push_back(c);
			Node node(true, false, false, c);
			mapped_node[c] = node;
		}
			
		else {
				mapped_node.at(c).value = true;
			}
		}
		
		else if( s.size() == 3 && s[0] == ':' && s[2] == '.' ) {

		}
		
		else if(s.size() == 3 && c == '?') {
			c = s[1];
			
			if(mapped_node.find(c) == mapped_node.end()) {
				alp_vec.push_back(c);
				Node node(false, true, false, c);
				mapped_node[c] = node;
			}
			
			else {
				mapped_node.at(c).isLast = true;
			}
			last_alp = c;
		}
		
		else if(s.size() == 4 && c == ':') {
			c = s[2];
			if(mapped_node.find(c) == mapped_node.end()) {
				alp_vec.push_back(c);
				Node node(false, false, true, c);
				mapped_node[c] = node;
			}
			
			else {
				mapped_node.at(c).value = false;
				mapped_node.at(c).make_false = true;
			}			
		}
		
		else if(s.size() == 4 && isalpha(c)) {
			if(mapped_node.find(c) == mapped_node.end()) {
				Node node(true, false, true, c);
				alp_vec.push_back(c);
				mapped_node[c] = node;
				
			}
			
			else {
				mapped_node.at(c).value = true;
				mapped_node.at(c).make_false = false;
			}			
		}
		
		else {
			Node left(false, false, false, ' ');
			
			if(mapped_node.find(c) == mapped_node.end()) {
				alp_vec.push_back(c);
				left.value = false;
				left.isLast = false;
				left.make_false = false;
				left.alp = c;
				mapped_node[c] = left;
			}
			
			else {
				left = mapped_node.at(c);
			}
		s = s.substr(1, s.size());
			
			
			while(s.size() > 0) {
				c = s[0];
				if(isalpha(c)) {
					
			if(mapped_node.find(c) == mapped_node.end()) {
				alp_vec.push_back(c);
				left.nodeVec.push_back(c);
				Node node(false, false, false, c);
				mapped_node[c] = node;
			}
					
			else {
				left.nodeVec.push_back(c);
			}
		}
		s = s.substr(1, s.size());				
			}
			mapped_node.at(left.alp) = left;
		}
		cout << temp << endl;
	}

	do {
		if(mapped_node.at(last_alp).value) {
		cout << last_alp << " is true." << endl;
		return 0;
		}
		checker = false;
		
		for(int i = 0; i < alp_vec.size(); i++) {
		char c = alp_vec.at(i);
		Node node = mapped_node.at(c);
			
		if(node.value == false) {
		bool isEnd = false;
			
		for(int j = 0; j < node.nodeVec.size(); j++) {
		isEnd = true;
		char d = node.nodeVec.at(j);
		Node n2 = mapped_node.at(d);		
			if(n2.value == false) {
				isEnd = false;
				break;
			}
		}
		if(isEnd) {
		node.value = isEnd;
		mapped_node.at(c) = node;
		checker = true;
		}
		}
		}
	}while(checker);
	
	if(mapped_node.at(last_alp).make_false) {
		cout << last_alp << " is false." << endl;
		return 0;
	}
	
	if(mapped_node.at(last_alp).value) {
		cout << last_alp << " is true." << endl;
		return 0;
	}
	else {
		cout << last_alp << " is false." << endl;
		return 0;
	}
}