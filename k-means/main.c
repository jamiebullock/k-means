//
//  main.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_cluster.h"
#include "km_pointlist.h"
#include "km_textfile.h"
#include "km_local.h"

#include <stdio.h>

int main(void)
{
    km_textfile csvfile = km_textfile_new();
    km_textfile outfile = km_textfile_new();
    double error = 0.0;
    double previous_error = 0.0;
    char line[128];

    RETURN_ON_ERROR(km_textfile_open(csvfile, "input-2.csv"));
    RETURN_ON_ERROR(km_textfile_open(outfile, "OUTPUT.TXT"));

    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(csvfile));
    km_pointlist centroids = km_pointlist_new(km_num_cluster_ids_);

    RETURN_ON_ERROR(km_pointlist_fill(pointlist, csvfile));

    km_pointlist_set_initial_cluster_centroids(centroids);

    printf("clustering...\n");
    
    do
    {
        previous_error = error;
        km_pointlist_classify_points(pointlist, centroids, &error);
        km_pointlist_adjust_centroids(pointlist, centroids);
    }
    while (error != previous_error);

    printf("done!\n");
    
    snprintf(line, 13, "error = %.3f", error);

    RETURN_ON_ERROR(km_textfile_write_line(outfile, line, 12));
    RETURN_ON_ERROR(km_textfile_write_cluster_names(outfile, pointlist));
    
    km_pointlist_delete(pointlist);
    km_pointlist_delete(centroids);
    km_textfile_delete(csvfile);
    km_textfile_delete(outfile);
    
    return 0;
}

