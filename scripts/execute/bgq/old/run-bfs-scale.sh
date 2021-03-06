#! /bin/zsh

export  INPUT_BASEDIR=/projects/SSSPPg/yguo/mt-mrmpi/data
export OUTPUT_BASEDIR=/projects/SSSPPg/yguo/mt-mrmpi/data

function run_scale() {
    local N=$(echo "2^$1" | bc)
    local n_start=$2
    local n_end=$3
    local timeout=${4:-45}

    local input_dir_name=weakscale$1
    if [ $n_start -eq 1 ]; then
        input_dir_name="singlenode/s$1"
    fi

    for ((i = n_start; i <= n_end; i = i * 2)); do
        param=$(($N*$i))
        ./sub_jobs.sh basic bfs $input_dir_name 5 $i $i 512M 64M $timeout $param
        ./sub_jobs.sh cps bfs $input_dir_name 5 $i $i 512M 64M $timeout $param
        ./sub_jobs.sh kvhint bfs $input_dir_name 5 $i $i 512M 64M $timeout $param
        ./sub_jobs.sh cpskvhint bfs $input_dir_name 5 $i $i 512M 64M $timeout $param
    done
}

run_scale $1 $2 $3
