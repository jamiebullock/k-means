//
//  km_local.c
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_local.h"
#include "km_pointlist.h"
#include "km_error.h"
#include "km_textfile.h"
#include "km_point.h"

#include <string.h>
#include <stdio.h>

void km_pointlist_set_initial_cluster_centroids(km_pointlist pointlist)
{
    km_pointlist_update(pointlist, 0, Adam, -0.357, -0.253);
    km_pointlist_update(pointlist, 1, Bob, -0.055, 4.392);
    km_pointlist_update(pointlist, 2, Charley, 2.674, -0.001);
    km_pointlist_update(pointlist, 3, David, 1.044, -1.251);
    km_pointlist_update(pointlist, 4, Edward, -1.495, -0.090);
}

char *km_cluster_name_from_id_(km_cluster_id id)
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

km_error km_textfile_write_cluster_names(km_textfile outfile, km_pointlist pointlist)
{
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        char *cluster_name = km_cluster_name_from_id_(point->id);
        RETURN_ON_ERROR(km_textfile_write_line(outfile, cluster_name, strlen(cluster_name) + 1));
    }
    return km_NoError;
}


