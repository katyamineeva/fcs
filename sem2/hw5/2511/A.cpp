#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <queue>

using std::vector;
using std::cout;
using std::ifstream;
using std::queue;
using std::pair;


const int NOT_INITIALISED = -2;
const int FIRST_COMPONENT_OF_EQUIVALENCE = -1;


void readData(vector<vector<vector<int>>>& reversedAutomat,
              vector<vector<int>>& graph,
              int& start,
              vector<bool>& isTerminal) {
    ifstream fin("input.txt");

    int numOfStates = 0;
    int sigmaSize = 0;

    fin >> numOfStates >> sigmaSize;

    vector<int> emptyVect = {};
    vector<vector<int>> pattern(sigmaSize, emptyVect);
    reversedAutomat.resize(numOfStates, pattern);
    graph.resize(numOfStates, {});
    isTerminal.resize(numOfStates, false);

    int nextState = 0;
    for (int curState = 0; curState < numOfStates; ++curState) {
        for (int symb = 0; symb < sigmaSize; ++symb) {
            fin >> nextState;
            reversedAutomat[nextState][symb].push_back(curState);
            graph[curState].push_back(nextState);
        }
    }

    int numOfTerminals = 0;
    int curTerminal = 0;

    fin >> start >> numOfTerminals;

    for (int i = 0; i < numOfTerminals; ++i) {
        fin >> curTerminal;
        isTerminal[curTerminal] = true;
    }
    fin.close();
}

void findReachable(const vector<vector<int>>& graph,
                   vector<bool>& used,
                   int curVertex) {
    used[curVertex] = true;
    for (int vertex : graph[curVertex]) {
        if (!used[vertex]) {
            findReachable(graph, used, vertex);
        }
    }
}

void makeEquivalenceTable(vector<vector<bool>>& marked,
               const vector<bool>& isTerminal,
               const vector<vector<vector<int>>>& reversedAutomat,
               int sigmaSize) {
    queue<pair<int, int>> myQueue;

    for (int i = 0; i < marked.size(); ++i) {
        for (int j = 0; j < marked.size(); ++j) {
            if (!marked[i][j] && (isTerminal[i] != isTerminal[j])) {
                marked[i][j] = true;
                marked[j][i] = true;
                myQueue.push({i, j});
            }
        }
    }

    int firstState = 0;
    int secondState = 0;

    while (!myQueue.empty()) {
        firstState = myQueue.front().first;
        secondState = myQueue.front().second;
        myQueue.pop();
        for (int symb = 0; symb < sigmaSize; ++symb) {
            for (int prevStateFirst : reversedAutomat[firstState][symb]) {
                for (int prevStateSecond : reversedAutomat[secondState][symb]) {
                    if (!marked[prevStateFirst][prevStateSecond]) {
                        marked[prevStateFirst][prevStateSecond] = true;
                        marked[prevStateSecond][prevStateFirst] = true;
                        myQueue.push({prevStateFirst, prevStateSecond});
                    }
                }
            }
        }
    }
}


void minimizeAutomat() {
    vector<vector<vector<int>>> reversedAutomat;
    vector<vector<int>> graph;
    int start = 0;
    vector<bool> isTerminal;
    readData(reversedAutomat, graph, start, isTerminal);

    vector<bool> isReachable(graph.size(), false);
    vector<vector<bool>> notEquivalent(graph.size(), isReachable);

    findReachable(graph, isReachable, start);

    int sigmaSize = reversedAutomat[0].size();
    makeEquivalenceTable(notEquivalent, isTerminal, reversedAutomat, sigmaSize);

    vector<int> componentOfEquivalence(graph.size(), NOT_INITIALISED);

    for (int i = 0; i < graph.size(); ++i) {
        if (!notEquivalent[0][i]) {
            componentOfEquivalence[i] = FIRST_COMPONENT_OF_EQUIVALENCE;
        }
    }

    int numOfComponents = 0;
    for (int stateFirst = 0; stateFirst < graph.size(); ++stateFirst) {
        if (!isReachable[stateFirst] || componentOfEquivalence[stateFirst] != NOT_INITIALISED) {
            continue;
        }
        ++numOfComponents;
        componentOfEquivalence[stateFirst] = numOfComponents;
        for (int stateSecond = stateFirst; stateSecond < graph.size(); ++stateSecond) {
            if (!notEquivalent[stateFirst][stateSecond]) {
                componentOfEquivalence[stateSecond] = componentOfEquivalence[stateFirst];
            }
        }
    }
    cout << numOfComponents + 1;
}

int main() {
    minimizeAutomat();
    return 0;
}

