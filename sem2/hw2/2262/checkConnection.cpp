
bool areConnected(short start, short finish, vector<vector<short>>& graph) {
    vector<bool> used(graph.size(), false);
    stack<short> myStack;
    myStack.push(start);
    used[start] = true;
    short curVertex = 0;
    while (!myStack.empty()) {
        curVertex = myStack.top();
        myStack.pop();
        for (auto vertex : graph[curVertex]) {
            if (!used[vertex]) {
                if (vertex == finish) {
                    return true;
                }
                myStack.push(vertex);
                used[vertex] = true;
            }
        }
    }
    return false;
}




void makeConnectivityTable(vector<vector<bool>>& graph) {
    int cntVertex = graph.size();
    for (int i = cntVertex - 2; i >= 0; --i) {
        for (int j = i + 1; j < cntVertex; ++j) {
            if (graph[i][j]) {
                for (int k = 0; k < cntVertex; ++k) {
                    graph[i][k] = graph[i][k] || graph[j][k];
                }
            }
        }
    }
}


bool thereIsCycle(short start, vector<vector<short>>& graph) {
    vector<bool> used(graph.size(), false);
    stack<short> myStack;

    myStack.push(start);
    used[start] = true;
    short curVertex = start;

    while (!myStack.empty()) {
        curVertex = myStack.top();
        myStack.pop();

        for (auto vertex : graph[curVertex]) {
            if (vertex == start) {
                return true;
            }
            if (!used[vertex]) {
                myStack.push(vertex);
                used[vertex] = true;
            }
        }
    }
    return false;
}

