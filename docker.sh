#!/bin/bash
set -xe

source_dir=$PWD
container=dsearch_builder_container
image=dsearch_builder

function docker_create {
    docker build -t $image .
    set +e
    docker container stop $container
    docker container rm $container
    set -e
    docker run -dit -v $source_dir:$source_dir --name $container $image
}

# $1 - build type
function docker_build {
    if ! docker inspect "$container" >/dev/null 2>&1; then
        docker_create
    fi
    user=`id -u`:`id -g`
    docker start $container
    build_type=Debug
    if [ "$1" != "" ] ; then
        build_type=$1
    fi 
    docker exec $container /bin/bash -c "cd $source_dir && $source_dir/build.sh $build_type"
}

# $1 - build type
# $2 - filter
function docker_test_run {
    user=`id -u`:`id -g`
    docker start $container
    build_type=Debug
    filter=".*"

    if [ "$1" != "" ] ; then
        build_type=$1
    fi 

    if [ "$2" != "" ] ; then
        filter=$2
    fi 

    docker exec $container /bin/bash -c "ctest --test-dir $source_dir/build_$build_type --verbose --output-on-failure -R '$filter'"
}

function docker_test_coverage {
    docker start $container
    docker exec $container /bin/bash -c "ctest --test-dir $source_dir/build_Debug -T test -T coverage"
    docker exec $container /bin/bash -c "cd $source_dir && $source_dir/coverage.sh"
}

function docker_bash {
    docker exec -it $container /bin/bash
}

docker_$1 $2 $3