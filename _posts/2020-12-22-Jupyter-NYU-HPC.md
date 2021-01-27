---
layout : post
title : Running Tensorflow in a Jupyter Notebook using Singularity and Slurm on NYU HPC
---

I have been trying to collect tasks I've had to do on the NYU HPC as a resource for others in the future. This post covers how to install Tensorflow onto the NYU HPC, and run an interactive session in Jupyter with Tensorflow, all using Singularity containers. 

I will refer to a jupyter notebook file and a slurm batch file in this section, you can find those the [__tensorflow_jupyter/__](https://github.com/ryanlstevens/nyu_hpc_helpers/tree/main/tensorflow_jupyter) folder. 

To run Tensorflow in a Jupyter notebook, we have to complete the following steps:

1. Setup Conda environment inside singularity container
2. Install python packages 
3. Create Jupyter slurm run script

All the code can be copied into the command line once you have ssh'ed into the NYU HPC. The NYU HPC team has a thorough [guide](https://devwikis.nyu.edu/display/NYUHPC/Logging+in+to+the+NYU+HPC+Clusters) for connecting to the HPC.

## Setup Conda Environment 

We copy an (overlay) container image with a set amount of RAM and Disk space (.ext3), this will be the environment tensorflow will run in. Overlays are nice because we can persist changes to our (.ext3) file, it gives us a kind of write access to these containers. 

We will then setup the conda environment inside the container, and finally a wrapper script we run when we reopen the container to point our environmental path to the conda environment.

A word of caution, we will be working with cuda version 10.1, this will require us to install an older version of tensorflow to get working.

```bash 

# Copy overlay container to current directory
cp -rp /scratch/work/public/overlay-fs-ext3/overlay-5GB-200K.ext3.gz .
gunzip overlay-5GB-200K.ext3.gz

# Setup conda environment inside container, running Ubuntu 18.04 with Cuda 10.1 
singularity exec --overlay overlay-5GB-200K.ext3 /scratch/work/public/singularity/cuda10.1-cudnn7-devel-ubuntu18.04.sif /bin/bash

# Install miniconda environment 
wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
sh Miniconda3-latest-Linux-x86_64.sh -b -p /ext3/miniconda3
export PATH=/ext3/miniconda3/bin:$PATH
conda update -n base conda -y

# Create wrapper script 
echo '''#!/bin/bash

source /ext3/miniconda3/etc/profile.d/conda.sh
export PATH=/ext3/miniconda3/bin:$PATH''' > /ext3/env.sh
``` 

## Install Python packages 

We will now relaunch the container and install our python packages. Note, one gotcha I ran into was I installed an incompatible version of Tensorflow. At the time of writing this script, CUDA 10.1 was the version I was using. This required me to install Tensorflow 2.3.0. To check which version of tensorflow is compatible with your cuda version, [click here](https://www.tensorflow.org/install/source#gpu). As a final cleanup step, we rename our overlay container to __tensorflow.2.3.0.ext3__.

```bash 
# Relaunch container 
singularity exec --overlay overlay-5GB-200K.ext3 /scratch/work/public/singularity/cuda10.1-cudnn7-devel-ubuntu18.04.sif /bin/bash
source /ext3/env.sh

# Now install python libraries 
pip install jupyter jupyterhub pandas matplotlib scipy 
pip install tensorflow==2.3.0

# Exit container 
exit 

# Rename container
mv overlay-5GB-200K.ext3 tensorflow.2.3.0.ext3
``` 

## Check that tensorflow install worked 

To check the installs worked, we run an interactive job with a gpu and then ask whether a gpu is available ``tf.test.is_gpu_available()``. If a GPU is available, this will return a true value.

```bash
# Run interactive slurm job 
srun -c2 --gres=gpu --mem='5gb' --pty /bin/bash

# Submit python command
singularity exec --nv --overlay tensorflow.2.3.0.ext3:ro \\ 
    /scratch/work/public/singularity/cuda10.1-cudnn7-devel-ubuntu18.04.sif \\ 
    bash -c 'source /ext3/env.sh; python -c "import tensorflow as tf; print(tf.test.is_gpu_available());"'
```

## Get jupyter working

The NYU HPC team provides many of these scripts already. The script to launch a batch job is available at [/tensorflow_jupyer/run-jupyter.sbatch](https://github.com/ryanlstevens/nyu_hpc_helpers/tree/main/tensorflow_jupyter/run-jupyter.sbatch). So long as you have followed everything the same, this script should work for you. One gotcha to watch out for is if you rename the (.ext3) file a different name, you will need to change it at the bottom of the sbatch script. 

We will simply submit our submit batch job.

```bash 
sbatch --output='run-jupyter.out' run-jupyter.sbatch
``` 

Once you have submitted this, you will need to inspect the output file to follow the instructions to connect to the jupyter notebook URL. Specifically, you will have to establish a connection to the port that the jupyter notebook is connected to, but the instructions are clear in the output file. To inspect the output file, you can run the print command.

```bash
cat run-jupyter.out
``` 

Once you have connected to the jupyter instance, you can run the two commands show in the [tensorflow_jupyter/jupyter_test_script.ipynb](https://github.com/ryanlstevens/nyu_hpc_helpers/tree/main/tensorflow_jupyter/jupyter_test_script.ipynb) file. 

