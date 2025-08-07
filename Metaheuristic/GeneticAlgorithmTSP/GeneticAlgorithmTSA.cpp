#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <ctime>
#include "print.h"

using Matrix = std::vector<std::vector<int>>;
using Path = std::vector<int>;

struct Individual {
    Path path;
    int length = 0;
    static const int EMPTY = std::numeric_limits<int>::max();  

    void evaluate(const Matrix& distanceMtx) {
        length = 0;
        for (int i = 0; i + 1 < path.size(); ++i) {
            int distance = distanceMtx[path[i]][path[i + 1]];
            if (distance == 0) {
                length = EMPTY;
                return;
            }
            length += distance;
        }
        int cycleEnd = distanceMtx[path.back()][path[0]];
        if (cycleEnd == 0) {
            length = EMPTY;
            return;
        }
        length += cycleEnd;
    }

    bool operator<(const Individual& other) const {
        return length < other.length;
    }
};

std::random_device rd;
std::mt19937 rng(rd());

Path Crossover(const Path& firstParent, const Path& secondParent) {
    int n = firstParent.size();
    std::uniform_int_distribution<int> dist(0, n - 1);
    int leftBound = dist(rng),
        rightBound = dist(rng);
    if (leftBound > rightBound) {
        std::swap(leftBound, rightBound);
    }

    Path child(n, -1);
    std::vector<bool> used(n, false);

    for (int i = leftBound; i <= rightBound; ++i) {
        child[i] = firstParent[i];
        used[child[i]] = true;
    }

    int idx = (rightBound + 1) % n;
    for (int i = 0; i < n; ++i) {
        int city = secondParent[(rightBound + 1 + i) % n];
        if (!used[city]) {
            child[idx] = city;
            idx = (idx + 1) % n;
        }
    }
    return child;
}

void Mutate(Path& path) {
    std::uniform_int_distribution<int> dist(0, path.size() - 1);
    int i = dist(rng),
        j = dist(rng);
    std::swap(path[i], path[j]);
}

Individual Tournament(const std::vector<Individual>& population, int k = 3) {
    std::uniform_int_distribution<int> dist(0, population.size() - 1);
    Individual best = population[dist(rng)];
    for (int i = 1; i < k; ++i) {
        Individual candidate(population[dist(rng)]);
        if (candidate.length < best.length) {
            best = candidate;
        }
    }
    return best;
}

struct GeneticTSPConfig {
    int populationSize = 100;
    int generations = 500;
    int tournamentSize = 3;
    double mutationProbablity = 0.2;
};

Individual GeneticTSP(const Matrix& distanceMtx, const GeneticTSPConfig& config = {}) {
    int n = distanceMtx.size();
    std::vector<Individual> population;

    Path base(n);
    std::iota(base.begin(), base.end(), 0);

    for (int i = 0; i < config.populationSize;) {
        std::shuffle(base.begin(), base.end(), rng);
        Individual individual{base};
        individual.evaluate(distanceMtx);

        if (individual.length != std::numeric_limits<int>::max()) {
            population.push_back(individual);
            ++i;
        }
    }

    for (int gen = 0; gen < config.generations; ++gen) {
        std::vector<Individual> newPopulation;

        std::sort(population.begin(), population.end());
        newPopulation.push_back(population[0]);

        while (newPopulation.size() < config.populationSize) {
            Individual p1 = Tournament(population, config.tournamentSize);
            Individual p2 = Tournament(population, config.tournamentSize);
            Path childPath = Crossover(p1.path, p2.path);
            if (std::uniform_real_distribution<double>(0, 1)(rng) < config.mutationProbablity) {
                Mutate(childPath);
            }
            Individual child{childPath};
            child.evaluate(distanceMtx);
            newPopulation.push_back(child);
        }

        population = std::move(newPopulation);
    }

    return *std::min_element(population.begin(), population.end());
}


int main() {
    Matrix dist = {
		{ 0, 23,  0, 45, 12,  0, 67,  0, 89, 34},
		{23,  0, 17,  0,  0, 39,  0,  0,  0, 62},
		{ 0, 17,  0,  0, 28,  0,  0, 49,  0,  0},
		{45,  0,  0,  0, 16,  0, 38,  0,  0, 71},
		{12,  0, 28, 16,  0,  0,  0,  0, 52,  0},
		{ 0, 39,  0,  0,  0,  0, 27,  0,  0,  0},
		{67,  0,  0, 38,  0, 27,  0,  0, 19,  0},
		{ 0,  0, 49,  0,  0,  0,  0,  0, 14,  0},
		{89,  0,  0,  0, 52,  0, 19, 14,  0,  0},
		{34, 62,  0, 71,  0,  0,  0,  0,  0,  0},
	};

    Individual best = GeneticTSP(dist, {
        .populationSize = 1,
        .generations = 3,
    });
    std::cout << "Best path length: " << best.length << std::endl << "Path: ";
    tools::PrintArray(best.path, " -> ", " -> ");
    std::cout << best.path[0] << std::endl;
}