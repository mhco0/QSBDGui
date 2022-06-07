/**
 * @file model.h
 * @brief QSBD Model class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 */

#ifndef QSBD_MODEL_H
#define QSBD_MODEL_H

#include <iostream>
#include <string>
#include <QObject>
#include <QRect>
#include <quantile_quadtree/quantile_quadtree.hpp>
#include <kll_factory/kll_factory.hpp>
#include <dcs_factory/dcs_factory.h>
#include <q_digest_factory/q_digest_factory.h>
#include <gk_factory/gk_factory.hpp>

namespace qsbd {

	/** @class Model
	* @brief A Class to represent a model in the MVC architecture
	* A model can represent anything, in this case we represent a quantile_quadtree,
	* This take the responsability of discretizates all values to the model, updates it and 
	*/
	class Model : public QObject {
		Q_OBJECT
	private:
		quantile_quadtree<int>* model;
		aabb<double> model_region;
		aabb<int> model_discrete_region;
		int model_depth;
		sketch_factory<int>* factory;
		bool model_only_leafs;
		double error;
		int universe;

		void turnToDiscrete(const aabb<double>& region, const int& depth);
	public:

		/**
		 * @brief The model constructor 
		 * @param parent The parent for this model
		*/
		explicit Model(QObject* parent = nullptr);
		
		/**
		 * @brief A destructor for the model
		*/
		~Model();

		/**
		 * @brief Returns the current depth in the model
		 * @return The current depth int the quadtree
		*/
		int getDepth() const;

	public slots:
		/**
		 * @brief Constructs or Restarts the Model using the gk sketch
		 * @param region The region that's used by the quantile quadtree
		 * @param depth The depth for the quantile quadtree
		 * @param only_leafs A boolean saying if the algorithm uses only sketchs on leafs or not
		 * @param err The error for the gk sketch
		*/
		void initGk(const aabb<double>& region, const int& depth, bool only_leafs, double err);

		/**
		 * @brief Constructs or Restarts the Model using the kll sketch
		 * @param region The region that's used by the quantile quadtree
		 * @param depth The depth for the quantile quadtree
		 * @param only_leafs A boolean saying if the algorithm uses only sketchs on leafs or not
		 * @param err The error for the kll sketch
		*/
		void initKll(const aabb<double>& region, const int& depth, bool only_leafs, double err);

		/**
		 * @brief Constructs or Restarts the Model using the q_digest sketch
		 * @param region The region that's used by the quantile quadtree
		 * @param depth The depth for the quantile quadtree
		 * @param only_leafs A boolean saying if the algorithm uses only sketchs on leafs or not
		 * @param err The error for the q_digest sketch
		 * @param univ The universe of values for the q_digest
		*/
		void initQDigest(const aabb<double>& region, const int& depth, bool only_leafs, double err, int univ);
		
		/**
		 * @brief Constructs or Restarts the Model using the dcs sketch
		 * @param region The region that's used by the quantile quadtree
		 * @param depth The depth for the quantile quadtree
		 * @param only_leafs A boolean saying if the algorithm uses only sketchs on leafs or not
		 * @param err The error for the dcs sketch
		 * @param univ The universe of values for the dcs
		*/
		void initDcs(const aabb<double>& region, const int& depth, bool only_leafs, double err, int univ);
		
		/**
		 * @brief Apply a update on the quadtree in this model.
		 * @param pos The coordenates for the point @p value
		 * @param value The value to be inserted
		*/
		void onUpdate(const point<double>& pos, int value);
		
		/**
		 * @brief Apply a update on the quadtree in this model.
		 * @param pos The coordenates for the point @p value
		 * @param value The value to be inserted
		 * @param weight The weight for the @p value
		*/
		void onUpdate(const point<double>& pos, int value, int weight);

		/**
		 * @brief Apply a rank query on the quadtree in this model.
		 * @param region The search region
		 * @param value The value queried
		 * @return The rank for the @p value
		*/
		int onQuery(const QRectF& region, int value);

		/**
		 * @brief Apply multiple quantile queries on the quadtree in this model.
		 * @param region The search region
		 * @param quants A vector of quantile to be queried, each quantile going from [0..1)
		 * @param fromWhatQuery The queryId where the request was made
		 * @return A vector with multiple elements one for each quantile
		*/
		std::vector<int> onMultiQuantile(const QRectF& region, const std::vector<double>& quants, const int& fromWhatQuery);

		/**
		 * @brief Apply a cdf queries on the quadtree in this model.
		 * @param region The search region
		 * @param values A vector with the values to query the cdf probability
		 * @return A vector with the probability for each element queried
		*/
		std::vector<double> onCdfQuery(const QRectF& region, const std::vector<int>& values);

		/**
		 * @brief Apply multiple cdfs queries on the quadtree in this model.
		 * @param regions The search regions
		 * @param values A vector with the values to query the cdf probability
		 * @return A vector for each probability searched
		*/
		std::vector<std::vector<double>> onCdfsQueries(const std::vector<QRectF>& regions, const std::vector<int>& values);

		/**
		 * @brief Apply multiples kolmogorov-smirnoff distance on each @p regionPairs
		 * @param regionPairs A vector with pairs of regions to be queried
		 * @param values A vector with the values to query the cdf probability
		 * @return A vector with the KS for each region pair queried
		*/
		std::vector<double> onKsRequest(const std::vector<std::pair<QRectF, QRectF>>& regionPairs, const std::vector<int>& values);
	signals:

		/**
		 * @brief A Qt signal that is emited when the Model::onQuery(const QRectF&, int) finish it's work.
		 * @param rank The processed rank is emitted
		*/
		void requestReady(const int& rank);

		/**
		 * @brief A Qt signal that is emited when the Model::onMultiQuantile(const QRectF&, const std::vector<double>&) finish it's work.
		 * @param quants A vector with multiple elements one for each quantile
		 * @param fromWhatQuery The queryId where the request was made
		*/
		void quantileReady(const std::vector<int>& quants, const int& fromWhatQuery);

		/**
		 * @brief A Qt signal that is emited when the Model::onCdfQuery(const QRectF&, const std::vector<int>&) finish it's work.
		 * @param cdf The processed cdf is emitted
		*/
		void cdfReady(const std::vector<double>& cdf);

		/**
		 * @brief A Qt signal that is emited when the Model::onCdfsQueries(const std::vector<QRectF>& regions, const std::vector<int>& values) finish it's work.
		 * @param cdfs The processed cdfs is emitted
		*/
		void cdfsReady(const std::vector<std::vector<double>>& cdfs);
		
		/**
		 * @brief A Qt signal that is emited when the Model::onKsRequest(const std::vector<std::pair<QRectF, QRectF>>&, const std::vector<int>&) finish it's work.
		 * @param rank The processed kss is emitted
		*/
		void ksReady(const std::vector<double>& kss);
	};

} // namespace qsbd

#endif // QSBD_MODEL_H
