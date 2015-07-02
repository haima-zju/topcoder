#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

//模拟题
const int maxCh = 100;
const int maxBl = 8;
class BinaryCode{
public:
  vector<string> decode(string message){
    vector<string> ret;
    int pre, cur, next;

    string origin;
    for(int k = 0; k < 2; k++){
      origin = k+'0';
      pre = 0;
      cur = k;
      for(int i = 0; i < message.size(); i++){
        next = message[i]-'0'-pre-cur;
        if(i == message.size()-1){
          if(next == 0) ret.push_back(origin);
          else ret.push_back("NONE");
          break;
        }
        if(next == 0 || next == 1) origin.push_back(next+'0');
        else{
          ret.push_back("NONE");
          break;
        }
        pre = cur;
        cur = next;
      }
    }
    return ret;
  }
};