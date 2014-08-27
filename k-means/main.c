//
//  main.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum cluster_id {
    Adam,
    Bob,
    Charley,
    David,
    Edward,
    km_num_cluster_ids_
};


int distance_comparison_function(const void * a, const void * b)
{
    return (((km_point)a)->distance - ((km_point)b)->distance);
}


// 1. Read the data from file into N km_point structs
// 2. Compute the distance of each point from each of M cluster centres
// 3. Re-compute cluster centres
// 4. Repeat 2–3 until the total error is minimised
// 5. Write output points to file


void set_initial_cluster_centroids(km_pointlist pointlist)
{
    km_pointlist_update(pointlist, 0, Adam, -0.357, -0.253);
    km_pointlist_update(pointlist, 1, Bob, -0.055, 4.392);
    km_pointlist_update(pointlist, 2, Charley, 2.674, -0.001);
    km_pointlist_update(pointlist, 3, David, 1.044, -1.251);
    km_pointlist_update(pointlist, 4, Edward, -1.495, -0.090);
}

float euclidean_distance(km_point point1, km_point point2)
{
    return sqrtf(powf(point1->x - point2->x, 2) + powf(point1->y - point2->y, 2));
}

void classify_point(km_pointlist centroids, km_point point)
{
    assert(km_pointlist_num_points(centroids) == km_num_cluster_ids_);
    struct km_point_ distances[km_num_cluster_ids_];
    
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(centroids); ++index)
    {
        km_point centroid = km_pointlist_point_at_index(centroids, index);
        distances[index].distance = euclidean_distance(centroid, point);
        distances[index].id = centroid->id;
    }

    qsort(distances, km_num_cluster_ids_, sizeof(struct km_point_), distance_comparison_function);
    
    point->id = distances[0].id;
    point->distance = distances[0].distance;
}


// Return the total error metric
void classify_points(km_pointlist pointlist, km_pointlist centroids, double *error)
{
    *error = 0;
    
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        classify_point(centroids, point);
        printf("%d, %f, %f, %f\n", point->id, point->x, point->y, point->distance);
        *error += point->distance;
    }
}



int main(int argc, const char * argv[])
{

    km_textfile textfile = km_textfile_new();
    double error = 0.0;
    
    RETURN_ON_ERROR(km_textfile_init(textfile));
    RETURN_ON_ERROR(km_textfile_read(textfile, "input-2.csv"));
    
    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(textfile));
    km_pointlist centroids = km_pointlist_new(km_num_cluster_ids_);
    
    RETURN_ON_ERROR(km_pointlist_fill(pointlist, textfile));
    
    set_initial_cluster_centroids(centroids);
    classify_points(pointlist, centroids, &error);
    
    printf("total error: %f\n", error);
    
    km_pointlist_delete(pointlist);
    km_textfile_delete(textfile);
    
    return 0;
}
