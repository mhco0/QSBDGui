#include "model.h"

namespace qsbd {

	Model::Model(QObject* parent): QObject(parent), factory(nullptr), model(nullptr) {	
	}

	Model::~Model(){
		if(factory){
			delete factory;
		}

		if(model){
			delete model;
		}
	}

	void Model::turnToDiscrete(const aabb<double>& region, const int& depth){
		model_region = region;
		int discrete_bounds[4] = {map_coord(region.bounds().first.x(), region.bounds().first.x(), region.bounds().second.x(), depth),
		 						  map_coord(region.bounds().first.y(), region.bounds().first.y(), region.bounds().second.y(), depth),
		  						  map_coord(region.bounds().second.x(), region.bounds().first.x(), region.bounds().second.x(), depth),
		   						  map_coord(region.bounds().second.y(), region.bounds().first.y(), region.bounds().second.y(), depth)};

        aabb<int> bound_box(discrete_bounds[0], discrete_bounds[1], discrete_bounds[2], discrete_bounds[3]);

		model_discrete_region = bound_box;
	}

	int Model::getDepth() const {
		return model_depth;
	}

	void Model::initGk(const aabb<double>& region, const int& depth, bool only_leafs, double err){
		turnToDiscrete(region, depth);
		model_depth = depth;
		model_only_leafs = only_leafs;
		error = err;

		if(factory){
			delete factory;
		}

		if(model){
			delete model;
		}
		
		factory = new gk_factory<int>(error);

		model = new quantile_quadtree<int>(model_discrete_region, model_depth, factory, model_only_leafs);
	}

	void Model::initKll(const aabb<double>& region, const int& depth, bool only_leafs, double err){
		turnToDiscrete(region, depth);
		model_depth = depth;
		model_only_leafs = only_leafs;
		error = err;

		if(factory){
			delete factory;
		}

		if(model){
			delete model;
		}

		factory = new kll_factory<int>(error);

		model = new quantile_quadtree<int>(model_discrete_region, model_depth, factory, model_only_leafs);
	}

	void Model::initQDigest(const aabb<double>& region, const int& depth, bool only_leafs, double err, int univ){
		turnToDiscrete(region, depth);
		model_depth = depth;
		model_only_leafs = only_leafs;
		error = err;
		universe = univ;

		if(factory){
			delete factory;
		}

		if(model){
			delete model;
		}

		factory = new q_digest_factory(error, universe);

		model = new quantile_quadtree<int>(model_discrete_region, model_depth, factory, model_only_leafs);
	}

	void Model::initDcs(const aabb<double>& region, const int& depth, bool only_leafs, double err, int univ){
		turnToDiscrete(region, depth);
		model_depth = depth;
		model_only_leafs = only_leafs;
		error = err;
		universe = univ;

		if(factory){
			delete factory;
		}

		if(model){
			delete model;
		}

		factory = new dcs_factory(error, universe);

		model = new quantile_quadtree<int>(model_discrete_region, model_depth, factory, model_only_leafs);
	}

	void Model::onUpdate(const point<double>& pos, int value){
		if(model == nullptr) return;

		point<int> discrete_pos(map_coord(pos.x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
			map_coord(pos.y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));


		model->update(discrete_pos, value);
	}

	void Model::onUpdate(const point<double>& pos, int value, int weight){
		if(model == nullptr) return;
	
		point<int> discrete_pos(map_coord(pos.x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
			map_coord(pos.y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));

		model->update(discrete_pos, value, weight);
	}

	int Model::onQuery(const QRectF& region, int value){
		if(model == nullptr) return 0;

		aabb<int> discrete_region(map_coord(region.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
								  map_coord(region.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));

		//std::cout << discrete_region << std::endl;
		int rank = model->query(discrete_region, value); 

		emit requestReady(rank);

		return rank;
	}

	std::vector<int> Model::onMultiQuantile(const QRectF& region, const std::vector<double>& quants, const int& fromWhatQuery){
		aabb<int> discrete_region(map_coord(region.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
								  map_coord(region.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));
		
		//std::cout << discrete_region << std::endl;
		
		std::vector<int> ret = model->quantiles(discrete_region, quants);
		
		emit quantileReady(ret, fromWhatQuery);

		return ret;
	}

	std::vector<double> Model::onCdfQuery(const QRectF& region, const std::vector<int>& values){
		aabb<int> discrete_region(map_coord(region.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
								  map_coord(region.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));
		
		std::vector<double> ret = model->cdfs(discrete_region, values);

		emit cdfReady(ret);

		return ret;
	}

	std::vector<std::vector<double>> Model::onCdfsQueries(const std::vector<QRectF>& regions, const std::vector<int>& values){
		std::vector<std::vector<double>> cdfs;

		for(auto& region: regions){
			aabb<int> discrete_region(map_coord(region.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
								  map_coord(region.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
								  map_coord(region.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));
		
			//std::cout << discrete_region << std::endl;

			std::vector<double> ret = model->cdfs(discrete_region, values);

			std::cout << "In cdf query: " << std::endl;

			for(auto& it : ret){
				std::cout << it << " ";
			}
			std::cout << std::endl;

			cdfs.emplace_back(ret);
		}
		
		emit cdfsReady(cdfs);

		return cdfs;
	}

	std::vector<double> Model::onKsRequest(const std::vector<std::pair<QRectF, QRectF>>& regionPairs, const std::vector<int>& values){
		std::vector<double> ret;

		for(auto& regionPair : regionPairs){
			double max_distance_distributions = std::numeric_limits<double>::min();

			aabb<int> discrete_regionA(map_coord(regionPair.first.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
									map_coord(regionPair.first.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
									map_coord(regionPair.first.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
									map_coord(regionPair.first.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));

			aabb<int> discrete_regionB(map_coord(regionPair.second.bottomLeft().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
									map_coord(regionPair.second.topRight().y(),model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth), \
									map_coord(regionPair.second.topRight().x(), model_region.bounds().first.x(), model_region.bounds().second.x(), model_depth), \
									map_coord(regionPair.second.bottomLeft().y(), model_region.bounds().first.y(), model_region.bounds().second.y(), model_depth));

			
			std::vector<double> lhs = model->cdfs(discrete_regionA, values);
			std::vector<double> rhs = model->cdfs(discrete_regionB, values);

			for(size_t i = 0; i < lhs.size(); i++){
				double distribution_distance = fabs(lhs[i] - rhs[i]);
			
				max_distance_distributions = std::max(max_distance_distributions, distribution_distance);
			}
		
			ret.push_back(max_distance_distributions);
		}

		emit ksReady(ret);

		return ret;
	}

} // namespace qsbd
