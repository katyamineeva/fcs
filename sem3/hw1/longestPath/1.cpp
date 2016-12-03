#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <fstream>

using std::fstream;
using Vertex = size_t;
using VertexSet = std::unordered_set<Vertex>;
using AdjacencyList = std::unordered_map<Vertex, VertexSet>;
using std::list;
using std::cout;


const double T_MIN = 1;
const int NUMBER_OF_ATTEMPTS = 91;


class Graph {
  public:
    void AddVertex(Vertex v) {
        adjacency_list_[v];
    }

    void AddEdge(Vertex u, Vertex v) {
        adjacency_list_[u].insert(v);
        adjacency_list_[v].insert(u);
    }

    const VertexSet AdjacentVertices(Vertex v) const {
        const auto it = adjacency_list_.find(v);
        if (it != adjacency_list_.end()) {
            return it->second;
        } else {
            return empty_set_;
        }
    }

    VertexSet AllVertices() const {
        VertexSet vs;
        vs.reserve(adjacency_list_.size());
        for (const auto& pair : adjacency_list_) {
            const auto& vertex = pair.first;
            vs.insert(vertex);
        }
        return vs;
    }

    Vertex RandomVertex() const {
        double random_num_ = this->Size() / RAND_MAX * rand();
        auto it = adjacency_list_.begin();
        for (int i = 0; i < random_num_; ++i) {
            ++it;
        }
        return (*it).first;
    }


    const AdjacencyList& AsAdjacencyList() const {
        return adjacency_list_;
    }

    bool AreAdjacent(Vertex v, Vertex u) const {
        auto connectedWithU = adjacency_list_.find(u);
        if (connectedWithU == adjacency_list_.end()) {
            return false;
        }
        return ((connectedWithU->second).find(v) != (connectedWithU->second).end());
    }

    size_t Size() const {
        return adjacency_list_.size();
    }

  private:
    AdjacencyList adjacency_list_;
    static const VertexSet empty_set_;
};

Graph RandomGraph(size_t size, double edge_probability) {
    Graph graph;
    for (Vertex v = 1; v <= size; ++v) {
        graph.AddVertex(v);
    }
    for (Vertex v = 1; v <= size; ++v) {
        for (Vertex u = v + 1; u <= size; ++u) {
            if (double(rand()) / RAND_MAX <= edge_probability) {
                graph.AddEdge(v, u);
            }
        }
    }
    return graph;
}



class Path {
  public:
    Path(const Graph& graph):
        graph_(graph) {
            path_ = {graph.RandomVertex()};
            set_ = {*path_.begin()};
            set_complement_ = graph.AllVertices();
            set_complement_.erase(*path_.begin());
        };

    VertexSet CandidatesToRemove() const {
        VertexSet candidates;
        auto prevVertex = path_.begin();
        auto nextVertex = path_.begin();

        for (auto vertex = path_.begin(); vertex != path_.end(); ++vertex) {
            if (vertex == path_.begin()) {
                candidates.insert(*vertex);
            } else {
                prevVertex = vertex;
                --prevVertex;
                nextVertex = vertex;
                ++nextVertex;
                if (nextVertex == path_.end()) {
                    candidates.insert(*vertex);
                } else {
                    if (graph_.AreAdjacent(*prevVertex, *nextVertex)) {
                        candidates.insert(*vertex);
                    }
                }
            }
        }
        return candidates;
    }

    bool isSuitableCandidate(Vertex candidate) const {
        auto nextVertex = path_.begin();
        for (auto vertex = path_.begin(); vertex != path_.end(); ++vertex) {
            nextVertex = vertex;
            ++nextVertex;

            if (nextVertex == path_.end()) {
                return graph_.AreAdjacent(*vertex, candidate);
            } else {
                if (graph_.AreAdjacent(*vertex, candidate) && graph_.AreAdjacent(*nextVertex, candidate)) {
                    return true;
                }
            }
        }
        return false;
    }

    VertexSet CandidatesToAdd() const {
        VertexSet candidates;

        for (auto candidate = set_complement_.begin();
             candidate != set_complement_.end();
             ++candidate) {

            if (isSuitableCandidate(*candidate)) {
                candidates.insert(*candidate);
            }
        }
        return candidates;
    }

    void Add(Vertex v) {
        auto nextVertex = path_.begin();
        for (auto vertex = path_.begin();
            (vertex != path_.end()) && (*vertex != v);
            ++vertex) {
            nextVertex = vertex;
            ++nextVertex;
            if (nextVertex == path_.end()) {
                if (graph_.AreAdjacent(*vertex, v)) {
                    path_.push_back(v);
                } else {
                    throw std::exception();
                }
            } else {
                if (graph_.AreAdjacent(*vertex, v)
                    && graph_.AreAdjacent(*nextVertex, v)) {
                    path_.insert(nextVertex, v);
                }
            }
        }

        set_.insert(v);
        set_complement_.erase(v);
    }

    void Remove(Vertex v) {
        if (path_.size() > 1) {
            for (auto vertex = path_.begin(); vertex != path_.end(); ++vertex) {
                if (*vertex == v) {
                    path_.erase(vertex);
                }
            }
            set_.erase(v);
            set_complement_.insert(v);
        }
    }

    size_t Cost() const {
        return set_.size();
    }

    VertexSet::const_iterator find(Vertex v) const {
        return set_.find(v);
    }

    VertexSet::const_iterator begin() const {
        return set_.begin();
    }

    VertexSet::const_iterator end() const {
        return set_.end();
    }

    const Graph& GetGraph() const {
        return graph_;
    }



  private:
    const Graph& graph_;
    list<Vertex> path_;

    VertexSet set_;
    VertexSet set_complement_;
};




void GraphEdges(std::ostream& out, const AdjacencyList& adjency_list) {
    for (const auto& pair : adjency_list) {
        const auto& vertex = pair.first;
        const auto& neighbours = pair.second;
        for (const auto adj_vertex : neighbours) {
            out << "\t" << vertex << " -- " << adj_vertex << "\n";
        }
    }
}


// Use http://www.webgraphviz.com to take a look at the graph
void GraphViz(std::ostream& out, const Graph& graph) {
    out << "strict graph {\n";
    for (const auto& pair : graph.AsAdjacencyList()) {
        const auto& vertex = pair.first;
        out << "\t" << vertex << "\n";
    }
    GraphEdges(out, graph.AsAdjacencyList());
    out << "}\n";
}

void GraphViz(std::ostream& out, const Path& vertex_cover) {
    out << "strict graph {\n";
    for (const auto& pair : vertex_cover.GetGraph().AsAdjacencyList()) {
        const auto& vertex = pair.first;
        if (vertex_cover.find(vertex) != vertex_cover.end()) {
            out << "\t" <<  vertex << " [shape=doublecircle]\n";
        } else {
            out << "\t" << vertex << "\n";
        }
    }
    GraphEdges(out, vertex_cover.GetGraph().AsAdjacencyList());
    out << "}\n";
}


class LongestPathSolver {
  public:
    virtual Path Solve(const Graph& graph) const = 0;
    virtual ~LongestPathSolver() = default;
};

template<typename T>
void print(T v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
}


class GradientDescent final: public LongestPathSolver {
    Path Solve(const Graph& graph_) const {
        Path longest_path_(graph_);
        VertexSet candidates_to_add = longest_path_.CandidatesToAdd();
        double num = 0;
        auto v = candidates_to_add.begin();

        while (candidates_to_add.size() > 0) {
            num = candidates_to_add.size() / RAND_MAX * rand();

            v = candidates_to_add.begin();
            for (int i = 0; i < num; ++i) {
                ++v;
            }
            longest_path_.Add(*v);
            candidates_to_add = longest_path_.CandidatesToAdd();
        }
        return longest_path_;
    }
};


class Metropolis final: public LongestPathSolver {
    Path Solve(const Graph& graph_) const {
        double T = T_start;
        Path longest_path_(graph_);
        VertexSet candidates_to_add = longest_path_.CandidatesToAdd();
        VertexSet candidates_to_remove = longest_path_.CandidatesToRemove();
        double number_of_neighbours = candidates_to_add.size() + candidates_to_remove.size();
        double percentage_of_bad_neighbours = candidates_to_remove.size() / number_of_neighbours;
        double percentage_of_good_neighbours = 1 - percentage_of_bad_neighbours;

        int attempt = 0;
        double num = 0;
        double random_probability = 0;
        auto v = candidates_to_add.begin();

        while ((attempt < NUMBER_OF_ATTEMPTS) && (T > T_MIN) && (number_of_neighbours > 0)) {
            std::cout << attempt << std::endl;
            ++attempt;
            random_probability = rand() / RAND_MAX;
            if (log(random_probability) < log(percentage_of_good_neighbours)) {
                cout << "in ADD\n";
                random_probability = rand() / RAND_MAX;
                num = candidates_to_add.size() * random_probability;

                v = candidates_to_add.begin();
                for (int i = 0; i < num; ++i) {
                    ++v;
                }
                longest_path_.Add(*v);
            } else {
                cout << "in Remove\n";
                random_probability = rand() / RAND_MAX;
                cout << random_probability  << ' ' << (1 / k / T) << '\n';
                if (log(1 / random_probability) > (1 / k / T)) {
                    random_probability = rand() / RAND_MAX;
                    num = candidates_to_remove.size() * random_probability;
                    v = candidates_to_remove.begin();
                    for (int i = 0; i < num; ++i) {
                        ++v;
                    }
                    longest_path_.Remove(*v);
                }
            }

            candidates_to_add = longest_path_.CandidatesToAdd();
            candidates_to_remove = longest_path_.CandidatesToRemove();
            number_of_neighbours = candidates_to_add.size() + candidates_to_remove.size();
            percentage_of_bad_neighbours = candidates_to_remove.size() / number_of_neighbours;
            percentage_of_good_neighbours = 1 - percentage_of_bad_neighbours;

            if (annealing) {
                --T;
            }

        }
    return longest_path_;
    }

  public:
    Metropolis(double k_, double T_, bool annealing_) {
        annealing = annealing_;
        T_start = T_;
        k = k_;
    }

  private:
    bool annealing;
    double T_start;
    double k;

};




void TrySolver(const LongestPathSolver& solver, const Graph& graph) {
    fstream fout("output.txt", std::fstream::out);

    GraphViz(fout, graph);

    auto best_cost = 0;
    size_t results = 0;
    for (int attempt = 1; attempt < 100; ++attempt) {
        const auto path = solver.Solve(graph);
        auto cost = path.Cost();
        if (cost > best_cost) {
            best_cost = cost;
            GraphViz(fout, path);
            ++results;
        }
    }
    std::cout << "Best cost: " << best_cost << std::endl;

}




// --------------------------
int InitRandSeed(int argc, const char* argv[]) {
    int rand_seed;
    if (argc >= 2) {
        rand_seed = atoi(argv[1]);
    } else {
        rand_seed = time(nullptr);
    }
    srand(rand_seed);
    return rand_seed;
}
//---------------------------

int f() {
    return 5;
}

void ff(int (*func)() ) {
    cout << (*func)();
}


int main(int argc, const char* argv[]) {
    ff(f);
    return 0;
}





