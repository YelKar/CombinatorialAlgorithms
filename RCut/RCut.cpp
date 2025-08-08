#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include "print.h"
#include "RCut.h"

std::ostream& operator<<(std::ostream& os, const Point& point) {
	return os << "[" << point.id << ":" << point.pos.x << "," << point.pos.y << "]";
}

Cluster MakeCluster(const Point& center, double radius) {
	return {
		radius, 
		{center},
		std::vector<std::shared_ptr<Cluster>>{},
		center.id,
	};
}

void Clusterization(Cluster& cluster) {
	for (int i = 0; i < 10 - std::ceil(std::log2(cluster.radius)); i++) {
		std::cout << " ";
	}
	std::cout << "CLUSTER";
	if (cluster.radius <= 1) {
		std::cout << " LEAFS";
		for (const auto& point : cluster.points) {
			std::cout << " " << point;
			cluster.children.push_back(std::make_shared<Cluster>(MakeCluster(point, 0)));
		}
		std::cout << std::endl;
		return;
	}
	for (const auto& point : cluster.points) {
		std::cout << " " << point;
		bool found = false;
		for (const auto& child : cluster.children) {
			if (std::hypot(child->points[0].pos.x - point.pos.x, child->points[0].pos.y - point.pos.y) <= child->radius) {
				found = true;
				child->points.push_back(point);
				break;
			}
		}
		if (!found) {
			cluster.children.push_back(std::make_shared<Cluster>(MakeCluster(point, cluster.radius / 2)));
		}
	}
	std::cout << std::endl;
	for (const auto& child : cluster.children) {
		Clusterization(*child);
	}
}

double GetMetricDiameter(const MetricSpace& points) {
	double maxDistance = 0;
	for (int i = 0; i < points.size() - 1; ++i) {
		for (int j = i + 1; j < points.size(); ++j) {
			maxDistance = std::max(maxDistance, std::hypot(points[i].pos.x - points[j].pos.x, points[i].pos.y - points[j].pos.y));
		}
	}
	return maxDistance;
}

HSTTreeNode ClusterToTree(const Cluster& cluster) {
	if (cluster.children.size() == 0) {
		return {
			.id = cluster.id,
		};
	}
	HSTTreeNode node = {
		.distanceToChild = cluster.radius,
	};
	for (const auto& child : cluster.children) {
		node.children.push_back(std::make_shared<HSTTreeNode>(ClusterToTree(*child)));
	}
	return node;
}

HSTTreeNode RCut(const MetricSpace& points, double radiusCoefficient) {
	double metricDiameter = GetMetricDiameter(points);
	int radiusDegreeTop = std::ceil(std::log2(metricDiameter));
	std::cout << "D: " << metricDiameter << " d: " << radiusDegreeTop << std::endl;
	Cluster rootCluster{
		.radius = std::pow(2, radiusDegreeTop - 1) * radiusCoefficient,
		.points = points,
	};
	Clusterization(rootCluster);
	return ClusterToTree(rootCluster);
}

void PrintHSTTree(const HSTTreeNode& node, int maxRadius) {
	if (maxRadius == -1) {
		std::cout << "ROOT(" << node.distanceToChild << "):" << std::endl;
		maxRadius = node.distanceToChild;
	}
	for (const auto& child : node.children) {
		for (int i = 0; i < std::ceil(std::log2(maxRadius)) - std::ceil(std::log2(node.distanceToChild)) + 1; i++) {
			std::cout << " ";
		}
		if (child->id != -1) {
			std::cout << "Leaf: " << child->id << std::endl;
		} else  {
			std::cout << child->distanceToChild << ":" << std::endl;
			PrintHSTTree(*child, maxRadius);
		}
	}
}