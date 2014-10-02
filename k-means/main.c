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

int main(int argc, const char *argv[])
{
    km_textfile csvfile = km_textfile_new();
    km_textfile outfile = km_textfile_new();
    double error = 0.0;
    double previous_error = 0.0;
    char line[128];

    if (argc != 4)
    {
        fprintf(stderr, "usage: %s <num clusters> <infile.csv> <outfile.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint8_t num_clusters = atoi(argv[1]);
    const char *inpath = argv[2];
    const char *outpath = argv[3];

    fprintf(stdout, "Running %s with %d clusters...\n", argv[0]);
    
    RETURN_ON_ERROR(km_textfile_open(csvfile, inpath));
    RETURN_ON_ERROR(km_textfile_open(outfile, outpath));

    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(csvfile));
    km_pointlist centroids = km_pointlist_new(num_clusters);

    RETURN_ON_ERROR(km_pointlist_fill(pointlist, csvfile));

    km_pointlist_randomise(centroids);

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
    
    return EXIT_SUCCESS;
}

