---
layout: post
title:  "Fun with Python and Azure Devops"
date:   2023-01-28 19:00:00 PM
categories: Python, Azure
---

Recently at work we were running into an issue with Azure DevOps build. Azure Devops by default allows 10GB of space for running the build pipelines, however due to some issue we were constantly going over the 10GB limit and our builds were failing quite often.

There are couple of reasons why this issue happens.

1. Not doing nuget consolidation. When you have many projects in a solution and if you can using different versions of nuget in different projects it will cause your build size to increase, since build has to download about those different versions. 
2. Referening common projects which are too bloated in different sub projects. If your code is not structured properly and if you are referring to common projects which have huge nuget dependency it will cause your overall build size to increase.
3. Not using .props and .targets file in MSBuild. This is a feature provided by the msbuild and is a really good solution for nuget consolidation.

Couple of things you can do to help mitigate the issue.

1. When fetching the git repo, you can set the fetchdepth to 1, since you only care of the latest history. This will only pull down the repo with depth=1

```yaml
steps:
- checkout: self
  fetchDepth: 1
  clean: true
```

2. Delete some of the folders which are not needed.
3. Have some diagnostic scripts to view which folders/files are taking maximum space and then figure out ways to solve the problem around that.


I was skeptical about what was happening during the build and wrote a simple python script to dump out the Folders and Files which were taking max space. Python has very intutive and easy to use packages for this purpose and was really impressed with how quick and easy it is come with a script like such.

Python's os module has couple of ways to get the directory and file info.

1. os.scandir  
    os.scandir between the os.listdir and os.scandir and returns the DirEntry object where you can query if its a file/directory and also get stats about the direntry.
2. os.walk
    os.listdir just returns a list of string so its pretty fast but you need to call other apis to get meaningful data.
3. os.listdir
    os.walk is verbose and give lot of details but its performance is slowest of these methods.


Ended up writing a recursive function to measure the directory size and then figure out some folders which we thought we were deleting but actually were not getting deleted.

Here is the complete script.

```python
def get_directory_size(path='.', fileSizeMap={}, directorySizeMap={}):
    total = 0
    with os.scandir(path) as it:
        for entry in it:
            if entry.is_file():
                total += entry.stat().st_size
                fileSizeMap[entry.path] = entry.stat().st_size / 1048576
            elif entry.is_dir():
                s = get_directory_size(entry.path, fileSizeMap, directorySizeMap)
                total += s
                directorySizeMap[entry.path] = s / 1073741824
    return total

def delete_folder(key):
    for path in foldersToDelete[key]:
        size = get_folder_size(path) / 1048576
        shutil.rmtree(path)
        print(f"""{path} Folder and its content Deleted. Size={size:.2f} MB""")

def get_folder_size(path='.'):
    total = 0
    with os.scandir(path) as it:
        for dirEntry in it:
            if dirEntry.is_file():
                total += dirEntry.stat().st_size
            if dirEntry.is_dir():
                total += get_folder_size(dirEntry.path)
    return total

def dump_folder_file_by_size(path="D:\\a"):
    directorySizeMap = {}
    fileSizeMap = {}
    directorySizeMap[path] = get_directory_size(path, fileSizeMap, directorySizeMap) / 1073741824
    directorySizeMapBySize = sorted(directorySizeMap.items(), key=lambda x:x[1], reverse=True)

    print('*' * 100)
    print("Top 100 Directory by size in GB")
    for key, value in directorySizeMapBySize[:100]:
        print(f"""{key} {value:.2f}""", sep="\n", end="\n")

    print('*' * 100)
    print("Top 100 Files by size in MB")
    fileSizeMapBySize = sorted(fileSizeMap.items(), key=lambda x:x[1], reverse=True)
    for key, value in fileSizeMapBySize[:100]:
        print(f"""{key} {value:.2f}""", sep="\n", end="\n")
```

One of the joys of working with python is you can see the results very quickly and I really like that about python.

!Happy Learning and improving one day at a time!


