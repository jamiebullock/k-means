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
#include <string.h>

typedef enum cluster_id
{
    Adam,
    Bob,
    Charley,
    David,
    Edward,
    km_num_cluster_ids_
}
cluster_id;


int distance_comparison_function(const void * a, const void * b)
{
    return (((km_point)a)->distance - ((km_point)b)->distance);
}

void set_initial_cluster_centroids(km_pointlist pointlist)
{
    km_pointlist_update(pointlist, 0, Adam, -0.357, -0.253);
    km_pointlist_update(pointlist, 1, Bob, -0.055, 4.392);
    km_pointlist_update(pointlist, 2, Charley, 2.674, -0.001);
    km_pointlist_update(pointlist, 3, David, 1.044, -1.251);
    km_pointlist_update(pointlist, 4, Edward, -1.495, -0.090);
}

char *cluster_name_from_id(cluster_id id)
{
    switch (id) {
        case Adam:
            return "Adam";
        case Bob:
            return "Bob";
        case Charley:
            return "Charley";
        case David:
            return "David";
        case Edward:
            return "Edward";
        default:
            printf("error: unhandled cluster id: %d\n", id);
            abort();
    }
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
        *error += point->distance;
    }
}

void adjust_centroids(km_pointlist pointlist, km_pointlist centroids)
{
    uint64_t num_centroids = km_pointlist_num_points(centroids);
    uint32_t id_counts[num_centroids];

    assert(num_centroids == km_num_cluster_ids_);

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

km_error write_cluster_names(km_textfile outfile, km_pointlist pointlist)
{
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        char *cluster_name = cluster_name_from_id(point->id);
        RETURN_ON_ERROR(km_textfile_write_line(outfile, cluster_name, strlen(cluster_name) + 1));
    }
    return km_NoError;
}

int main(void)
{
    km_textfile csvfile = km_textfile_new();
    km_textfile outfile = km_textfile_new();
    double error = 0.0;
    double previous_error = 0.0;
    char line[128];

    printf("opening files...\n");
    RETURN_ON_ERROR(km_textfile_open(csvfile, "input-2.csv"));
    RETURN_ON_ERROR(km_textfile_open(outfile, "OUTPUT.TXT"));

    printf("filling point list...\n");
    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(csvfile));
    km_pointlist centroids = km_pointlist_new(km_num_cluster_ids_);

    RETURN_ON_ERROR(km_pointlist_fill(pointlist, csvfile));

    set_initial_cluster_centroids(centroids);

    printf("clustering...\n");
    do
    {
        previous_error = error;
        classify_points(pointlist, centroids, &error);
        adjust_centroids(pointlist, centroids);
        printf("error: %f\n", error);
    }
    while (error != previous_error);

    snprintf(line, 13, "error = %.3f", error);

    printf("writing output...\n");
    RETURN_ON_ERROR(km_textfile_write_line(outfile, line, 12));
    RETURN_ON_ERROR(write_cluster_names(outfile, pointlist));
    
    printf("cleaning up...\n");
    km_pointlist_delete(pointlist);
    km_pointlist_delete(centroids);
    km_textfile_delete(csvfile);
    km_textfile_delete(outfile);

    printf("done!\n");
    
    return 0;
}

