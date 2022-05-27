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

template<class T, class distance>
class kmedoids {
private:
    using point = T;
    uint32_t k;
public:
    kmedoids(const uint32_t& k){
        this->k = k;
    }

    std::vector<uint32_t> cluster(const std::vector<point>& samples, distance f){
        assert((uint32_t) samples.size() > this->k);
        std::vector<point> medoids;
        std::vector<uint32_t> clusters(samples.size(), 0);
        std::map<uint32_t, bool> mp;
        std::default_random_engine generator;
        std::uniform_int_distribution<uint32_t> distribution(0, samples.size() - 1);
        std::vector<std::vector<int32_t>> distances;
        uint32_t min_cost = 0x3f3f3f3f;
        uint32_t total_cost = 0;

        for(uint32_t i = 0; i < this->k; i++){
            uint32_t idx = distribution(generator);
            while(mp[idx]){
                idx = distribution(generator);
            }
            
            metoids.emplace_back(samples[idx]);
            mp[idx] = true;

            distances.emplace_back({});

            for(int j = 0; j < samples.size(); j++){
                distances[i].emplace_back(0);
            }
        }

        for(size_t i = 0; i < samples.size(); i++){
            if (mp[i]) continue;

            uint32_t less_distance = 0x3f3f3f3f;
            uint32_t correct_cluster = 0;

            for(uint32_t j = 0; j < this->k; j++){
                distances[j] = distance(medoids[j], samples[i]);

                if (distances[j] < less_distance){
                    less_distance = distances[j];
                    correct_cluster = j;
                }
            }

            total_cost += less_distance;
            clusters[i] = correct_cluster;
        }

        while(total_cost < min_cost){
            min_cost = total_cost;

            for(uint32_t i = 0; i < this->k; i++){
                uint32_t old_cost = total_cost;
                total_cost = 0;

                for(size_t j = 0; j < samples.size(); j++){
                    if (mp[j]) continue;

                    swap(medoids[i], samples[j]);

                    for(size_t l = 0; l < samples.size(); l++){
                        if (mp[l]) continue;

                        uint32_t less_distance = 0x3f3f3f3f;
                        uint32_t correct_cluster = 0;

                        for(uint32_t z = 0; z < this->k; z++){
                            distances[z] = distance(medoids[z], samples[l]);

                            if (distances[z] < less_distance){
                                less_distance = distances[z];
                                correct_cluster = z;
                            }
                        }

                        total_cost += less_distance;
                        clusters[l] = correct_cluster;
                    }

                    if (total_cost > old_cost){
                        swap(medoids[i], samples[j]);
                    }
                }
            }
        }   

        return clusters;
    }
};

#endif