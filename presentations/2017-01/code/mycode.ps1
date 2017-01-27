break
#install git
# Configure global settings
git config --global user.name "Jay Ryan"
git config --global user.email jay.ryan@bankatfirst.com
ipmo posh-git

cd C:\

New-Item -Path c:\gitdemo -ItemType Directory

cd C:\gitdemo
gci
# initialize a repo
git init
git commit -am "[initial] empty commit" --allow-empty
git tag initial 40526ac -m "Tag initial commit"

git log --decorate --oneline --graph
git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
# These are useful - lets make aliases!
git config --global alias.ls 'log --graph --oneline --decorate'
git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
git ls
git lg

gci
gci -force
gci .git -force

new-item myproj.ps1 -ItemType File

git status
git add newproj.ps1
git status
git commit -m "my first commit"
git status
# removes unstaged changes
git checkout -- .

git reset --mixed #(default) --soft --hard

#Move HEAD back 1 commit
git checkout HEAD~1

git checkout 262e8a8 # your SHA will be different

# remotes

git remote add origin https://github.com/CincyPowerShell/gitdemo.git
git pull --rebase
git push -u origin master

# pull merge changes
git pull origin
#or
git fetch # updates the local version of the remote repo, not yours
git merge # crashes them together - hopefully this works
git rebase # sets your changes aside - adds the remote changes first - then applies yours on top



# Clean up
# git clean -fx