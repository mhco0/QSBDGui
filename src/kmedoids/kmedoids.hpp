/**
 * @file kmedoids.hpp
 * @brief QSBD kmedoids class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */


#ifndef K_MEDOIDS_DIALOG_H
#define K_MEDOIDS_DIALOG_H
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <random>

template<class T>
class kmedoids {
private:
    using point = T;
    using dmatrix = std::vector<std::vector<double>>;
    using compair_function = std::function<double(T, T)>;

    static dmatrix process_distance_matrix(const std::vector<point>& samples, compair_function f){
        dmatrix distances(samples.size(), std::vector<double>(samples.size(), 0.0));
        
        for(size_t i = 0; i < samples.size(); i++){
            for(size_t j = 0; j < samples.size(); j++){
                if(i == j) continue;

                distances[i][j] = (i < j) ? f(samples[i], samples[j]) : distances[j][i];
            }
        }

        return distances;
    }

    static void get_random_centroids(std::vector<int>& centroids, const int& pointsNumber, const int& k){
        assert(centroids.size() == k);
        std::uniform_int_distribution<int> dist(0, pointsNumber - 1);
        std::map<int, bool> mp;
        std::random_device gen;

        for(int i = 0; i < k; i++){
            int index = dist(gen);
            while(mp[index]){
                index = dist(gen);
            }
            mp[index] = true;

            centroids[i] = index;
        }
    }
public:
    static std::pair<std::vector<int>, std::vector<int>> cluster(const int& k, const int& steps, const std::vector<point>& samples, compair_function f, std::vector<int>& prev_cent = nullptr){
        if(k > samples.size()){
            std::vector<int> ret;

            for(int i = 0; i < k; i++){
                ret.emplace_back(i);
            }

            return std::make_pair(ret, ret);
        }
        
        dmatrix distances = kmedoids::process_distance_matrix(samples, f);
        std::vector<int> finalClusters(samples.size(), -1);
        std::vector<int> currentClusters(samples.size(), -1);
        std::vector<int> centroids(k, -1);
        double total_cost = std::numeric_limits<double>::max();
        int nSteps = 0; 

        if (prev_cent.size() == 0){
            kmedoids::get_random_centroids(centroids, samples.size(), k);

            for(size_t i = 0; i < k; i++){
                prev_cent.emplace_back(centroids[i]);
            }
        }else{
            assert(prev_cent.size() == centroids.size());
            for(size_t i = 0; i < k; i++){
                centroids[i] = prev_cent[i];
            }
        }

        do {
            double previus_cost = total_cost;
            total_cost = 0.0;

            for(size_t i = 0; i < samples.size(); i++){
                double smallDistance = std::numeric_limits<double>::max();
                for(size_t j = 0; j < centroids.size(); j++){
                    if (i == centroids[j]){
                        smallDistance = 0.0;
                        currentClusters[i] = j;
                        continue;
                    }

                    if (distances[i][centroids[j]] < smallDistance){
                        smallDistance = distances[i][centroids[j]];
                        currentClusters[i] = j;
                    }
                }

                total_cost += smallDistance;
            }

            qDebug() << nSteps << " " << total_cost << " " << previus_cost;

            if (total_cost < previus_cost){
                for(size_t i = 0; i < samples.size(); i++){
                    finalClusters[i] = currentClusters[i];
                }
            }else break;

            nSteps++;
        }while(nSteps < steps);

        return std::make_pair(finalClusters, centroids);
    }
};

#endif