#!/bin/bash
set -xe

source_dir=$PWD
container=ubuntu_builder_container
image=ubuntu_builder

function docker_create {
    docker build -t $image .
    set +e
    docker container stop $container
    docker container rm $container
    set -e
    docker run -dit -v $source_dir:$source_dir --name $container $image
}

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

function docker_test_run {
    user=`id -u`:`id -g`
    docker start $container
    build_type=Debug
    if [ "$1" != "" ] ; then
        build_type=$1
    fi 
    docker exec $container /bin/bash -c "cd '$source_dir/build_$build_type' && ctest"
}

function docker_test_coverage {
    user=`id -u`:`id -g`
    docker start $container
    docker exec $container /bin/bash -c "cd $source_dir && $source_dir/coverage.sh"
}

function docker_bash {
    docker exec -it $container /bin/bash
}

docker_$1 $2 $3