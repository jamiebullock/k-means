//
//  km_local.h
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef __k_means__km_local__
#define __k_means__km_local__

#include "km_error.h"
#include "km_pointlist.h"
#include "km_textfile.h"

km_error km_textfile_write_cluster_names(km_textfile outfile, km_pointlist pointlist);

#endif /* defined(__k_means__km_local__) */
