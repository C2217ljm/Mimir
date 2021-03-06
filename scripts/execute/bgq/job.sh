#! /bin/zsh -e

PPN=16
MIMIR_DEBUG=1

NODE=$1
EXE=$2
INDIR=$3
OUTDIR=$4
TMPDIR=$5
PREFIX=$6
NTIMES=$7
INBUFSIZE=$8
PAGESIZE=$9
PARAM=$10

# echo "node:" $NODE
# echo "program:" $EXE
# echo "input dir:" $INDIR
# echo "output dir:" $OUTDIR
# echo "temp dir:" $TMPDIR
# echo "prefix":$PREFIX
# echo "param:" $PARAM

export NPROC=$(($PPN*$NODE))
export OMP_NUM_THRADS=1

if [ $NPROC -et 16384 ]; then
    COMM_UNIT_SIZE=$((64*1024*1024/$NPROC))B
else
    COMM_UNIT_SIZE=$((64*1024*1024/$NPROC))B
fi

if [ ! -d "$OUTDIR" ]; then mkdir -p "$OUTDIR"; fi

for i in `seq 1 $NTIMES`; do
    echo "Run number" $i
    if [ ! -d "$TMPDIR" ]; then mkdir -p "$TMPDIR"; fi
    runjob --np $NPROC -p $PPN --block $COBALT_PARTNAME --verbose=INFO \
        --envs MIMIR_BUCKET_SIZE=17 \
        --envs MIMIR_IBUF_SIZE=$INBUFSIZE \
        --envs MIMIR_PAGE_SIZE=$PAGESIZE \
        --envs MIMIR_COMM_SIZE=$PAGESIZE \
        --envs MIMIR_COMM_UNIT_SIZE=$COMM_UNIT_SIZE \
        --envs MIMIR_DBG_ALL=$MIMIR_DEBUG \
        : ./$EXE $PARAM $INDIR "$PREFIX" $OUTDIR "$TMPDIR" $i
    rm -rf "$TMPDIR"
done

