//
//  km_cluster.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_cluster.h"
#include "km_point.h"
#include "km_pointlist.h"
#include "km_local.h"
#include "km_error.h"
#include "km_textfile.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

float euclidean_distance_(km_point point1, km_point point2)
{
    return powf(point1->x - point2->x, 2) + powf(point1->y - point2->y, 2);
}

void classify_point_(km_pointlist centroids, km_point point)
{
    uint64_t num_centroids = km_pointlist_num_points(centroids);
    struct km_point_ distances[num_centroids];
    
    for (km_pointlist_index index = 0; index < num_centroids; ++index)
    {
        km_point centroid = km_pointlist_point_at_index(centroids, index);
        distances[index].distance = euclidean_distance_(centroid, point);
        distances[index].id = centroid->id;
    }
    
    float min_distance = FLT_MAX;
    km_pointlist_index min_index = 0;
    
    for (km_pointlist_index index = 0; index < num_centroids; ++index)
    {
        if (distances[index].distance < min_distance)
        {
            min_distance = distances[index].distance;
            min_index = index;
        }
    }
    
    point->id = distances[min_index].id;
    point->distance = min_distance;
}

// Return the total error metric as function parameter
void km_pointlist_classify_points(km_pointlist pointlist, km_pointlist centroids, double *error)
{
    *error = 0;
    
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        classify_point_(centroids, point);
        *error += point->distance;
    }
}

void km_pointlist_adjust_centroids(km_pointlist pointlist, km_pointlist centroids)
{
    uint64_t num_centroids = km_pointlist_num_points(centroids);
    uint32_t id_counts[num_centroids];
        
    // 1. zero centroid locations and id counts
    for (km_pointlist_index index = 0; index < num_centroids; ++index)
    {
        km_point centroid = km_pointlist_point_at_index(centroids, index);
        centroid->x = 0.f;
        centroid->y = 0.f;
        id_counts[index] = 0;
    }
    
    // 2. accumulate x, y point positions and id counts in cluster
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        km_point centroid = km_pointlist_point_with_id(centroids, point->id);
        
        centroid->x += point->x;
        centroid->y += point->y;
        id_counts[centroid->id]++;
    }
    
    // 3. divide by num points in cluster
    for (km_pointlist_index index = 0; index < num_centroids; ++index)
    {
        km_point centroid = km_pointlist_point_at_index(centroids, index);
        centroid->x /= id_counts[index];
        centroid->y /= id_counts[index];
    }
}






