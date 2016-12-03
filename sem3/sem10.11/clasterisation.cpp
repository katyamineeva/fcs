#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


class DisjointSetUnion {
private:
    vector<int> parent_;
    vector<int> ranks_;

public:
    explicit DisjointSetUnion(size_t size)
        : parent_()
        , ranks_(size, 0)
    {
        parent_.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            parent_.push_back(i);
        }
    }

    int find(int node) {
        if (parent_[node] != node) {
            parent_[node] = find(parent_[node]);
        }
        return parent_[node];
    }

    void union_sets(int first, int second) {
        int first_root = find(first);
        int second_root = find(second);
        if (first_root == second_root) {
            return;
        }

        if (ranks_[first_root] < ranks_[second_root]) {
            parent_[first_root] = second_root;
        } else if (ranks_[first_root] > ranks_[second_root]) {
            parent_[second_root] = first_root;
        } else {
            parent_[second_root] = first_root;
            ++ranks_[first_root];
        }
    }
};


struct Edge {
    size_t from;
    size_t to;
    double weight;
};


// Map arbitrary labels to 0, ..., (n-1) labels
vector<size_t> RenumerateLabels(const vector<size_t>& rawLabels) {
    vector<int> rawToNew(rawLabels.size(), -1);
    size_t indexesUsed = 0;
    vector<size_t> newLabels(rawLabels.size());
    for (size_t i = 0; i < rawLabels.size(); ++i) {
        size_t oldLabel = rawLabels[i];
        if (rawToNew[oldLabel] == -1) {
            rawToNew[oldLabel] = indexesUsed;
            ++indexesUsed;
        }
        newLabels[i] = rawToNew[oldLabel];
    }
    return newLabels;
}


template <typename T, typename Dist>
vector<size_t> ClusterMST(const vector<T>& objects, Dist distance, size_t clusterCount) {
    for (auto it = objects.begin(); it != objects.end(); ++it) {

    }
    while () {

    }
}

template <typename T, typename Dist>
vector<size_t> ClusterMinDistToCenter(const vector<T>& objects,
                                      Dist distance,
                                      size_t clusterCount) {
    // Your implementation here
    // ...
}


struct Point2D {
    double x, y;
};


double EuclidianDistance(const Point2D& first, const Point2D& second) {
    return std::sqrt((first.x - second.x) * (first.x - second.x) +
                     (first.y - second.y) * (first.y - second.y));
}


vector<Point2D> Random2DClusters(const vector<Point2D>& centers,
                                 const vector<double>& xVariances,
                                 const vector<double>& yVariances,
                                 size_t pointsCount)
{
    auto baseGenerator = std::default_random_engine();
    auto generateCluster = std::uniform_int_distribution<size_t>(0, centers.size() - 1);
    auto generateDeviation = std::normal_distribution<double>();

    vector<Point2D> results;
    for (size_t i = 0; i < pointsCount; ++i) {
        size_t c = generateCluster(baseGenerator);
        double x = centers[c].x + generateDeviation(baseGenerator) * xVariances[c];
        double y = centers[c].y + generateDeviation(baseGenerator) * yVariances[c];
        results.push_back({x, y});
    }

    return results;
}


// Generate files for plotting in gnuplot
void GNUPlotClusters2D(const vector<Point2D>& points,
                       const vector<size_t>& labels,
                       size_t clustersCount,
                       const string& outFolder)
{
    std::ofstream scriptOut(outFolder + "/script.txt");
    scriptOut << "plot ";

    for (size_t cluster = 0; cluster < clustersCount; ++cluster) {
        string filename = std::to_string(cluster) + ".dat";
        std::ofstream fileOut(outFolder + "/" + filename);
        scriptOut << "\"" << filename << "\"" << " with points, ";

        for (size_t i = 0; i < points.size(); ++i) {
            if (labels[i] == cluster) {
                fileOut << points[i].x << "\t" << points[i].y << "\n";
            }
        }
    }
}


int main() {
    auto points = Random2DClusters(
        {{0, 0}, {1, 2}, {2, 1}},
        {0.3, 0.1, 0.3},
        {0.2, 0.1, 0.1},
        1000);

    vector<size_t> labels(points.size(), 0);
    GNUPlotClusters2D(points, labels, 1, "./plot_base");

    size_t clustersCount = 3;

    labels = ClusterMST(points, EuclidianDistance, clustersCount);
    GNUPlotClusters2D(points, labels, clustersCount, "./plot_mst");

    labels = ClusterMinDistToCenter(points, EuclidianDistance, clustersCount);
    GNUPlotClusters2D(points, labels, clustersCount, "./plot_mdc");


    return 0;
}
