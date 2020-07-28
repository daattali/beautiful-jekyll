#!/usr/bin/env bash
# Checks that the correct version of all system programs and R & Python packages
# which are needed for the start of the MDS program are correctly installed.

# 1. System programs
# Tries to run system programs and if successful greps their version string
# Currently marks both uninstalled and wrong verion number as MISSING
echo "" > check-setup-mds.log
echo "# MDS setup check 0.0.1" >> check-setup-mds.log
echo "" >> check-setup-mds.log
echo "## System programs" >> check-setup-mds.log
# The single equal sign syntax is what we have in the install instruction for conda,
# so I am using it below for Python packages so that we can just paste in the same
# syntax as for the conda installations instructions. I use the same single `=`
# for the system packages here for consistency
sys_progs=(python=3.* conda=4.* git=2.* docker=19.* R=4.* psql=12.* tlmgr=5.* latex=3.14.* rstudio=1.3.* code=1.4.*)
for sys_prog in ${sys_progs[@]}; do
    sys_prog_no_version=$(sed "s/=.*//" <<< "$sys_prog")
    regex_version=$(sed "s/.*=//" <<< "$sys_prog")
    # Check if command is executable
    if [ -x "$(command -v $sys_prog_no_version)" ]; then
        # Check if the version regex string matches the installed version
        if $(grep -iq "$regex_version" <<< "$(head -1 <<< $($sys_prog_no_version --version))"); then
            # Since programs like rstudio and vscode don't print the program name with `--version`,
            # we need one extra step before logging 
            installed_version=$(grep -io "$regex_version" <<< "$(head -1 <<< $($sys_prog_no_version --version))")
            echo "OK        "$sys_prog_no_version $installed_version >> check-setup-mds.log
            # Use `head` because `R --version` prints an essay...
            # echo "OK       " $(head -1 <<< "$($sys_prog_no_version --version)") >> check-setup-mds.log
        else  # If the version is wrong
            echo "MISSING   $sys_prog_no_version" >> check-setup-mds.log
        fi
    else  # If the executable does not exist
        echo "MISSING   $sys_prog_no_version" >> check-setup-mds.log
    fi
done

# 2. Python packages
# Greps the `conda list` output for correct version numbers
# Currently marks both uninstalled and wrong verion number as MISSING
echo "" >> check-setup-mds.log
echo "## Python packages" >> check-setup-mds.log
if ! [ -x "$(command -v conda)" ]; then  # Check that conda exists
    echo "Please install 'conda' to check Python package versions." >> check-setup-mds.log
    echo "If 'conda' is installed already, make sure to run 'conda init' if this was not chosen during the installation." >> check-setup-mds.log
    echo "In order to do this after the installation process, first run 'source <path to conda>/bin/activate' and then run 'conda init'." >> check-setup-mds.log
else
    py_pkgs=(jupyterlab=2.* numpy=1.* pandas=1.* flake8=3.* black=19.* nodejs=10.* jupytext=1.* jupyterlab-git)
    # installed_py_pkgs=$(pip freeze)
    installed_py_pkgs=$(conda list | tr -s " " "=" | cut -d "=" -f -2)
    for py_pkg in ${py_pkgs[@]}; do
        # py_pkg=$(sed "s/=/==/" <<< "$py_pkg")
        if $(grep -iq "$py_pkg" <<< $installed_py_pkgs); then
            echo "OK        $(grep -i "$py_pkg" <<< $installed_py_pkgs)" >> check-setup-mds.log
        else
            echo "MISSING   $py_pkg" >> check-setup-mds.log
        fi
    done
fi

# 3. R packages
# Format R package output similar to above for python and grep for correct version numbers
# Currently marks both uninstalled and wrong verion number as MISSING
echo "" >> check-setup-mds.log
echo "## R packages" >> check-setup-mds.log
if ! [ -x "$(command -v R)" ]; then  # Check that R exists
    echo "Please install 'R' to check R package versions." >> check-setup-mds.log
else
    r_pkgs=(cluster nlme tidyverse tinytex blogdown xaringan renv IRkernel tinytex)
    installed_r_pkgs=$(R -q -e "print(format(as.data.frame(installed.packages()[,c('Package', 'Version')]), justify='left'), row.names=FALSE)" | grep -v "^>" | tail -n +2 | sed 's/^ //;s/ *$//' | tr -s ' ' '=')
    for r_pkg in ${r_pkgs[@]}; do
        if $(grep -iq "$r_pkg" <<< $installed_r_pkgs); then
            echo "OK        $(grep -i "$r_pkg" <<< $installed_r_pkgs)" >> check-setup-mds.log
        else
            echo "MISSING   $r_pkg" >> check-setup-mds.log
        fi
    done
fi

# Ouput the saved file to stdout
cat check-setup-mds.log
