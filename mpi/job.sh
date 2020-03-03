#!/bin/bash
#SBATCH -n 4
#SBATCH -p skx-normal
#SBATCH -N 1
#SBATCH -t 00:10
module purge
module load TACC
srun ./a.out
