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

using std::list;
using std::cout;

class Graph {
  public:
    using Vertex = size_t;
    using VertexSet = std::unordered_set<Vertex>;
    using AdjacencyList = std::unordered_map<Vertex, VertexSet>;

    void AddVertex(Vertex v) {
        adjacency_list_[v];
    }

    void AddEdge(Vertex u, Vertex v) {
        adjacency_list_[u].insert(v);
        adjacency_list_[v].insert(u);
    }

    const VertexSet& AdjacentVertices(Vertex v) const {
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

    const AdjacencyList& AsAdjacencyList() const {
        return adjacency_list_;
    }

  private:
    AdjacencyList adjacency_list_;
    static const VertexSet empty_set_;
};

const Graph::VertexSet Graph::empty_set_;

class VertexCover {
  public:
    explicit VertexCover(const Graph& graph)
        : graph_(graph), set_(graph.AllVertices()) {}

    Graph::VertexSet CandidatesToRemove() const {
        Graph::VertexSet candidates;
        for (const auto v : set_) {
            if (IsDeletable(v)) {
                candidates.insert(v);
            }
        }
        return candidates;
    }

    const Graph::VertexSet& CandidatesToAdd() const {
        return set_complement_;
    }

    void Add(Graph::Vertex v) {
        set_.insert(v);
        set_complement_.erase(v);
    }

    void Remove(Graph::Vertex v) {
        set_.erase(v);
        set_complement_.insert(v);
    }

    size_t Cost() const {
        return set_.size();
    }

    Graph::VertexSet::const_iterator find(Graph::Vertex v) const {
        return set_.find(v);
    }

    Graph::VertexSet::const_iterator begin() const {
        return set_.begin();
    }

    Graph::VertexSet::const_iterator end() const {
        return set_.end();
    }

    const Graph& GetGraph() const {
        return graph_;
    }

  private:
    bool IsDeletable(Graph::Vertex v) const {
        for (const auto u : graph_.AdjacentVertices(v)) {
            if (find(u) == end()) {
                return false;
            }
        }
        return true;
    }

    const Graph& graph_;
    Graph::VertexSet set_;
    Graph::VertexSet set_complement_;
};

void GraphEdges(std::ostream& out, const Graph::AdjacencyList& adjacency_list) {
    for (const auto& pair : adjacency_list) {
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

void GraphViz(std::ostream& out, const VertexCover& vertex_cover) {
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


// Use http://gnuplot.respawned.com/ to plot costs

class VertexCoverSolver {
  public:
    virtual VertexCover Solve(const Graph& graph) const = 0;
    virtual ~VertexCoverSolver() = default;
};

class GradientDescent final: public VertexCoverSolver {
    // TODO: insert implementation
};

class Metropolis final: public VertexCoverSolver {
    // TODO: insert implementation
};

Graph RandomGraph(size_t size, double edge_probability) {
    Graph graph;
    for (Graph::Vertex v = 1; v <= size; ++v) {
        graph.AddVertex(v);
    }
    for (Graph::Vertex v = 1; v <= size; ++v) {
        for (Graph::Vertex u = v + 1; u <= size; ++u) {
            if (double(rand()) / RAND_MAX <= edge_probability) {
                graph.AddEdge(v, u);
            }
        }
    }
    return graph;
}

Graph StarGraph(size_t size) {
    Graph graph;
    for (Graph::Vertex v = 2; v <= size; ++v) {
        graph.AddEdge(1, v);
    }
    return graph;
}

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

void TrySolver(const VertexCoverSolver& solver, const Graph& graph) {
    GraphViz(std::cout, graph);
    auto best_cost = std::numeric_limits<size_t>::max();
    size_t results = 0;
    for (int attempt = 1; attempt < 100; ++attempt) {

        const auto vertex_cover = solver.Solve(graph);
        auto cost = vertex_cover.Cost();
        if (cost < best_cost) {
            best_cost = cost;
            GraphViz(std::cout, vertex_cover);
            ++results;
        }
    }
    std::cout << "Results: " << results << std::endl;
}

int main(int argc, const char* argv[]) {
    std::cout << "Using rand seed: " << InitRandSeed(argc, argv) << "\n";
    const auto graph = RandomGraph(7, 0.5);
    list<int> l;
    l = {57, 2};

    l.insert(l.begin(), 42);

    for (auto n : l) {
        std::cout << n << '\n';
    }
    cout << l.front();

    return 0;
}
