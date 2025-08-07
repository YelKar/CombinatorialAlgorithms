#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include "print.h"

struct HSTTreeNode {
	double distanceToChild;
	std::vector<std::shared_ptr<HSTTreeNode>> children;
	int id = -1;
};

struct Point {
	int id;
	struct {
		double x;
		double y;
	} pos;
};

std::ostream& operator<<(std::ostream& os, const Point& point);

using MetricSpace = std::vector<Point>;

struct Cluster {
	double radius;
	MetricSpace points;
	std::vector<std::shared_ptr<Cluster>> children;
	int id = -1;
};

Cluster MakeCluster(const Point& center, double radius);
void Clusterization(Cluster& cluster);
double GetMetricDiameter(const MetricSpace& points);
HSTTreeNode ClusterToTree(const Cluster& cluster);
HSTTreeNode RCut(const MetricSpace& points, double radiusCoefficient = 1);
void PrintHSTTree(const HSTTreeNode& node, int maxRadius = -1);