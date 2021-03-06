#! /bin/zsh

if [ $# -lt 2 ]; then
    echo "./run-octree.sh <data size in MB> [n_node start] [n_node end]"
    exit 1
fi

export  INPUT_BASEDIR=$HOME/mcs/mimir/data
export OUTPUT_BASEDIR=$HOME/mcs/mimir/data

function run() {
    local N=$1
    local n_start=$2
    local n_end=$3
    if [ $n_end -lt $n_start ]; then
        n_end=$n_start
    fi
    local timeout=${4:-45}

    local input_dir_name="1S/weakscale$1"
    if [ $n_start -eq 1 ]; then
        input_dir_name="1S/singlenode/$1"
    fi

    for ((i = n_start; i <= n_end; i = i * 2)); do
        param="0.01"
        ./sub_jobs.sh basic       octree $input_dir_name 1 $i $i 512M 64M $timeout $param
        ./sub_jobs.sh cb          octree $input_dir_name 1 $i $i 512M 64M $timeout $param
#        ./sub_jobs.sh kvhint      octree $input_dir_name 1 $i $i 512M 64M $timeout $param
#        ./sub_jobs.sh cbkvhint    octree $input_dir_name 1 $i $i 512M 64M $timeout $param
    done
}

run $1 ${2:-1} ${3:-1}
