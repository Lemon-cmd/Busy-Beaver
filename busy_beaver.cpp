#include <deque>
#include <algorithm>
#include <map>
#include <string> 
#include <iostream>

/* given an n-state Turing Machine with a two symbol alphabet {0, 1}
 * what is the maximum number of 1's that the machine can print on an
 * initially blank tape (filled with 0's) before halting? */

/* 
//Transition Table for 5 states BB. based on wikipedia 
static std::map <std::string, std::string> transitions {
	{"a0", "1rb"}, {"a1", "1lc"},
	{"b0", "1rc"}, {"b1", "1rb"},
	{"c0", "1rd"}, {"c1", "0le"},
	{"d0", "1la"}, {"d1", "1ld"},
	{"e0", "1rh"}, {"e1", "0la"}	
};
*/

//Transition Table for 6 states BB. based on wikipedia; this takes a very long time to finish....
static std::map <std::string, std::string> transitions {
	{"a0", "1rb"}, {"a1", "1le"},
	{"b0", "1rc"}, {"b1", "1rf"},
	{"c0", "1ld"}, {"c1", "0rb"},
	{"d0", "1re"}, {"d1", "0lc"},
	{"e0", "1la"}, {"e1", "0rd"},
	{"f0", "1lh"}, {"f1", "1rc"}	
};


int main()
{
	std::string S = "a", movement;
	int score = 0, step = 0, pos = 0;
	std::deque<std::string> symbols; symbols.emplace_back("0");
	
	while(S != "h")
	{
		movement = transitions[S + symbols[pos]];
		S = movement[2]; symbols[pos] = movement[0];

		if (movement[1] == 'r' && pos + 1 >= symbols.size()) {
			pos = pos + 1; symbols.emplace_back("0"); 
		}else if (movement[1] == 'l' && pos - 1 < 0) {
			symbols.emplace_front("0"); pos = 0;
		}else{
			pos = movement[1] == 'l' ? pos - 1 : pos + 1;
		}
		
		if (step % 1000000 == 0)
		   std::cout << "Current state: " << S << symbols[pos] << "\n";	
		//std::cout << "Step: " << step << " Movement: " << movement << " " << pos << " State: " << S << symbols[pos] << "\n";
		step += 1;
	}

	std::for_each(symbols.begin(), symbols.end(), [&score](auto &s) { score = s == "1" ? score + 1 : score; });
	std::cout << "Score: " << score << " Steps: " << step << "\n";
}
