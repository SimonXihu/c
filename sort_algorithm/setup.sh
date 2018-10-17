#!/bin/sh
sort_algorithm_path=`pwd`
echo $sort_algorithm_path
export LD_LIBRARY_PATH=$sort_algorithm_path:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
