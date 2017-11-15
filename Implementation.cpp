#include "Implementation.hpp"
#include <iostream>

using namespace std;
//////////////////// Nested Loop Joins ////////////////////

std::vector<std::string> getQualifyingBusinessesIDsVector(Businesses const& b, float latMin,
																													float latMax, float longMin,
																													float longMax) {
	// This function needs to find all businesses that have within the
	// specified latitude/longitude range and store their ids in the result vector
  std::vector<std::string> ids;
  for (int i = 0; i < b.ids.size(); i++){
    if (b.latitudes[i] <= latMax && b.latitudes[i] >= latMin){
      if (b.longitudes[i] <= longMax && b.longitudes[i] >= longMin){
	ids.push_back(b.ids[i]);
      }
    }
  }

  // std::cout << "function getQualifyingBusinessesIDsVector not implemented" << std::endl;
  // throw std::logic_error("unimplemented");

  return ids;
}

std::vector<unsigned long>
performNestedLoopJoinAndAggregation(Reviews const& r, std::vector<std::string> const& qualifyingBusinessesIDs) {
	// The second parameter of this function is the vector of qualifying
	// business ids you have created in the first function

	// This function needs to find all reviews that have business_ids in
	// the qualifyingBusinessesIDs vector and build a histogram over their stars
  	// The return value is that histogram

  std::vector<unsigned long> agg_stars(6);
  for (int i = 0; i < r.business_ids.size(); i++){
    for (int j = 0; j < qualifyingBusinessesIDs.size(); j++){
      if (r.business_ids[i] == qualifyingBusinessesIDs[j]){
	agg_stars[r.stars[i]]++;
      }
    }
  }

    return agg_stars;
      
  
	//std::cout << "function performNestedLoopJoinAndAggregation not implemented" << std::endl;
	//throw std::logic_error("unimplemented");
}

//////////////////// Hash Join ////////////////////

std::unordered_set<std::string> getQualifyingBusinessesIDs(Businesses const& b, float latMin,
																													 float latMax, float longMin,
																													 float longMax) {
	// This function needs to find all businesses that have within the
	// specified latitude/longitude range and store their ids in the result set

  std::unordered_set<std::string> ids;
  for (int i = 0; i < b.ids.size(); i++){
    if (b.latitudes[i] <= latMax && b.latitudes[i] >= latMin){
      if (b.longitudes[i] <= longMax && b.longitudes[i] >= longMin){
	ids.insert(b.ids[i]);
      }
    }
  }
  
  
  //std::cout << "function getQualifyingBusinessesIDs not implemented" << std::endl;
  //	throw std::logic_error("unimplemented");
  return ids; 
}

std::vector<unsigned long>
aggregateStarsOfQualifyingBusinesses(Reviews const& r,
																		 std::unordered_set<std::string> const& qualifyingBusinesses) {
	// The second parameter of this function is the set of qualifying
	// business ids you have created in the first function

	// This function needs to find all reviews that have business_ids in
	// the qualifyingBusinessesIDs vector and build a histogram over their stars
	// The return value is that histogram

  std::vector<unsigned long> agg_stars(6);
   for (int i = 0; i < r.business_ids.size(); i++){
     auto found = qualifyingBusinesses.find(r.business_ids[i]);
     // std::string probe_reviews = r.business_ids[i];
     if (found != qualifyingBusinesses.end()){
       agg_stars[r.stars[i]]++;
       // std:: cout << "sadsad " << *found << std::endl;
    }
  }
  
  return agg_stars; 
  //	std::cout << "function aggregateStarsOfQualifyingBusinesses not implemented" << std::endl;
  //	throw std::logic_error("unimplemented");
}
