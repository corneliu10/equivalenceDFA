#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#define maxStates 200
#define maxLetters 100
using namespace std;

class DFA {
public:
    int nrTransitions;
    int nrStates;
    int nrLetters;
    int nrFinalStates;
    int initialState;
    vector<int> states;
    map<int, bool> finalStates;
    vector<char> letters;
    char transitions[maxStates][maxLetters];
    
    void readData(char fileName[]) {
        int state,state1,state2;
        char letter;
        ifstream f(fileName);
        
        f>>nrStates;
        for(int i=0; i<nrStates; ++i) {
            f>>state;
            states.push_back(state);
        }
        
        f>>nrLetters;
        for(int i=0; i<nrLetters; ++i) {
            f>>letter;
            letters.push_back(letter);
        }
        
        f>>initialState;
        f>>nrFinalStates;
        for(int i=0; i<nrFinalStates; ++i) {
            f>>state;
            finalStates[state] = true;
        }
        
        f>>nrTransitions;
        for(int i=0; i<nrTransitions; ++i) {
            f>>state1>>letter>>letter>>state2;
            transitions[state1][letter - 'a'] = state2;
        }
    }
};

bool equivalenceDFA(DFA dfa1, DFA dfa2) {
    if(dfa1.finalStates[dfa1.initialState] !=
       dfa2.finalStates[dfa2.initialState] )
        return false;
    
    int st1Cur = dfa1.initialState;
    int st2Cur = dfa2.initialState;
    int st1Next, st2Next;
    
    queue<pair<int, int> > Q;
    map<pair<int, int>, bool> M;
    Q.push({st1Cur, st2Cur});
    M[{st1Cur, st2Cur}] = true;
    
    while(!Q.empty()) {
        for(int i=0; i<dfa1.nrLetters; ++i) {
            st1Next = dfa1.transitions[st1Cur][dfa1.letters[i] - 'a'];
            st2Next = dfa2.transitions[st2Cur][dfa2.letters[i] - 'a'];
            
            if(dfa1.finalStates[st1Next] !=
               dfa2.finalStates[st2Next] )
                return false;
            
            if(!M[{st1Next, st2Next}])
                Q.push({st1Next, st2Next});
        }
        
        st1Cur = Q.front().first;
        st2Cur = Q.front().second;
        Q.pop();
    }
    
    return true;
}

int main() {
    DFA dfa1, dfa2;
}
