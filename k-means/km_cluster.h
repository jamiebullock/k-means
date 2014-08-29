//
//  km.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef __k_means__km_cluster__
#define __k_means__km_cluster__

#include "km_pointlist.h"

// Return the total error metric as function parameter
void km_pointlist_classify_points(km_pointlist pointlist, km_pointlist centroids, double *error);
void km_pointlist_adjust_centroids(km_pointlist pointlist, km_pointlist centroids);

#endif /* defined(__k_means__km_cluster__) */
