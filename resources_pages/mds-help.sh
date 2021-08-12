# Detect which file browser string to use
if [[ "$(uname)" == 'Linux' ]]; then
    browser_cmd='xdg-open .'
elif [[ "$(uname)" == 'Darwin' ]]; then
    browser_cmd='open .    '
elif [[ "$OSTYPE" == 'msys' ]]; then
    browser_cmd='explorer .'
else
    echo "Operating system verison could not be detected." >> check-setup-mds.log
fi

# Use colors for headings for clarity
ORANGE='\033[0;33m'
NC='\033[0m' # No Color

# Help messages
help_preamble="
This help message shows a brief explanation
of the most important terminal commands we use in MDS.
It is meant to be complement the lecture notes
and be used as a reference when you forget a command.
Note that the words 'directory' and 'folder' are used interchangeably.
This also includes the aliases we have created in your bash configuration files
for commands that are very useful and that we want encourage you to use often.

All the commands are printed by default,
but you can specifiy a single section to show
by using the subcommands 'shell', 'git', 'conda', or 'alias'.
For example, if you only want to see the shell command help you would type:

mds-help shell
"

shell_help="
${ORANGE}# Shell commands${NC}

These are typed into your bash terminal prompt.

~                               Nickname for the home folder ($HOME)
.                               Nickname for the current folder
..                              Nickname for the parent folder
$browser_cmd                      Open the current folder in your file browser

man <COMMAND>                   Show the manual (help) of a command
history                         List all commands you have typed
pwd                             Print the name of the current (working) directory
clear                           Clear the terminal of all text

ls                              List the content of the current directory
ls <FOLDER>                     List the content of a specific directory
ls -a                           List hidden files
ls -l                           List additional information for each file
ls -lh                          Same as above, but with easier to interpret size info

cd <FOLDER>                     Navigate to a folder (one folder 'down')
cd <FOLDER>/<FOLDER>            Navigate two folders down
cd ..                           Navigate to the parent folder (one folder 'up')
cd ../..                        Navigate two folders up
cd -                            Navigate to the last visited directory (one folder 'back')

code <FILE_or_NEW_NAME>         Open an existing or new file in VS Code
mkdir <NEW_NAME>                Create a new directory
cp <FILE> <NEW_NAME>            Copy a file to a new location
cp -r <FOLDER> <NEW_NAME>       Copy a folder and all its content to a new location
mv <FILE_or_FOLDER> <NEW_NAME>  Move a file or folder to a new location
rm <FILE>                       Remove a file
rm -f <FILE>                    Remove a file without prompting for confirmation
rm -r <FOLDER>                  Remove a folder and all its content

cat                             Output the content of a file
head -<N>                       Output the first 'N' lines of a file
tail -<N>                       Output the last 'N' lines of a file

<COMMAND> > <FILE>              Redirect a commands output to a file
history > my-history.txt        Save your command history to a file
<COMMAND> | <COMMAND>           Redirect a commands output to another command
history | grep <PATTERN>        Search for a text pattern in your history
mds-help | grep remove          Search for all commands related to 'remove' in this help
"

git_help="
${ORANGE}# Git subcommands${NC}

These commands are typed after 'git' in the terminal.

log                        Show the log of commits
log -p                     Show the log of commits as well as the changes made
log --oneline              Show the commit messages only
status                     Show untracked and uncommited files

add <FILE>                 Add a file to the staging area
add -p                     Interactively go through all changes and select what to add, SUPER useful.
add --all                  Add all updated, new, and deleted files to the staging area.
add -u                     Only add updated and deleted files to the staging area.
add .                      Only add updated and new files to the staging area.

diff                       Show changes in unstaged files
diff --staged              Show changes in staged files
commit                     Commit all staged changes, optionally adding a message
commit -m <MESSAGE>        Commit all staged changes with a message

reset                      Reset all staged changes (careful when using with --hard)
reset -p                   Interactively choose which changes to reset
restore --staged <FILE>    Restore a specific staged change (care when using without --staged)
restore -s <SHA> <FILE>    Restore a file to a previous commit (sha).

clone <URL>                Clone an online git repository
pull                       Fetch and merge the latest changes from your online repository
pull origin main           Fetch from the remote called origin and merge into your main branch (the default)
push                       Upload changes to your online repository
push -u origin <BRANCH>    Upload changes to a specific branch in your online repository

switch <BRANCH>            Switch to another local branch
switch -c <NEW_NAME>       Create a new local branch
remote -v                  Show the URL of you remote repository
remote add upstream <URL>  Add a new remote repository

merge <BRANCH_or_COMMIT>   Join commit histories together (usually done as part of 'pull')
rebase <BRANCH_or_COMMIT>  Change your history to line up with the specified branch or commit
rebase -i HEAD~4           Reorder and/or drop the last four commits interactively
"


conda_help="
${ORANGE}# Conda subcommands${NC}

These commands are typed after 'conda' in the terminal.

list                              List all installed packages
list | grep <PATTERN>             Search for a text pattern among the installed packages

install <PACKAGE>                 Install one or multiple packages (separated by spaces)
install <PACKAGE>=1.1.0           Install a specific version of a package
remove <PACKAGE>                  Remove one or multiple packages
update <PACKAGE>                  Update one or multiple packages
update --all                      Update all packages
update -n base -c defaults conda  Update the base environment's conda to the latest in the default channel

create -n <NEW_NAME>              Create an environment
create -n <NEW_NAME> <PACKAGE>    Create an environment and install a package
create --file <FILE>              Create an environment from a file
activate <ENV>                    Activate an environment
deactivate                        Deactivate the current environment

env list                          List all environments
env remove -n <ENV>               Remove an environment
env export -f env.yaml            Export all installed packages to a file
env export -f env.yaml --from-history  Only export explicitly installed packages, not dependencies
"

alias_help="
${ORANGE}# MDS aliases${NC}

These aliases are shortcuts for commands we expect that you will be using often.

l      List files sorted by date via 'ls -lthAF'
jl     'jupyter lab'
gl     Improved 'git log --oneline' with dates
gl -N  Show 'N' lines instead of the default 10
gt     'git status'
gm     'git commit -m'
gap    'git add -p'
ca     'conda activate'
"

# Handle subcommands to only output single sections
if [[ $1 == 'shell' ]]; then
    echo -e "$shell_help"
elif [[ $1 == 'git' ]]; then
    echo -e "$git_help"
elif [[ $1 == 'conda' ]]; then
    echo -e "$conda_help"
elif [[ $1 == 'alias' ]]; then
    echo -e "$alias_help"
elif [[ $1 == '' ]]; then
    echo -e "$help_preamble"
    echo -e "$shell_help"
    echo -e "$git_help"
    echo -e "$conda_help"
    echo -e "$alias_help"
else
    echo "$1 is not recognized, either leave blank or specify 'shell', 'git', 'conda', or 'alias'."
fi
