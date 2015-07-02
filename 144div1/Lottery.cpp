#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

const int maxCh = 100;
const int maxBl = 8;
class Lottery{
public:
  class Game{
  public:
    long long p;
    string name;
    Game(string str = ""): name(str){}
  };
  class Cmp{
  public:
    bool operator()(Game a, Game b){
      if(a.p != b.p) return a.p < b.p;
      else return a.name < b.name;
    }
  }myCmp;
  vector<string> sortByOdds(vector<string> &rules){
    vector<Game> gameList;
    /*f1[range][blanks]表示blanks个位置rang个选择下递增数列的个数
    f2[range][blanks]表示blanks个位置rang个选择下严格递增数列的个数*/
    vector<vector<long long>> f1(maxCh+1, vector<long long>(maxCh+1, 0));
    vector<vector<long long>> f2(maxCh+1, vector<long long>(maxCh+1, 0));
    /*初始化*/
    for(int i = 0; i <= maxCh; i++) f1[0][i] = f2[0][i] = 1;
    /*dp求解*/
    for(int i = 1; i <= maxBl; i++){
      for(int j = 1; j <= maxCh; j++){
        for(int k = 1; k <= j; k++){
          f1[i][j] += f1[i-1][k];
        }
        if(i == 1){
          for(int k = 1; k <= j; k++){
            f2[i][j] += f2[i-1][k];
          }
        }
        else{
          for(int k = 1; k < j; k++){
            f2[i][j] += f2[i-1][k];
          }
        }
      }
    }
    //数据读入
    for(auto a : rules){
      auto itr = a.find(':');
      Game g(string(a.begin(), a.begin()+itr));
      a.erase(a.begin(), a.begin()+itr+1);

      stringstream ss;
      int choices, blanks;
      string sorted, unique;
      ss << a;
      ss >> choices >> blanks >> sorted >> unique;
      if(sorted[0] == 'T' && unique[0] == 'T'){
        g.p = f2[blanks][choices];
      }
      else if(sorted[0] == 'T' && unique[0] == 'F'){
        g.p = f1[blanks][choices];
      }
      else if(sorted[0] == 'F' && unique[0] == 'T'){
        g.p = 1;
        for(int i = 0; i < blanks; i++){
          g.p *= choices-i;
        }
      }
      else{
        g.p = 1;
        while(blanks--) g.p *= choices;
      }
      gameList.push_back(g);
    }
    //按要求排序
    sort(gameList.begin(), gameList.end(), myCmp);
    vector<string> ret;
    for(auto e : gameList) ret.push_back(e.name);
    return ret;
  }
};