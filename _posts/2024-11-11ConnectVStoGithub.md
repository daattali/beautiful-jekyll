---
layout: post
title: "How to Link VS Code to GitHub: A Step-by-Step Guide"
date: 2024-11-11
author: "Ameen Abdelmutalab"
tags: [git, GitHub, version control, tutorial, VS Code, development]
image: "/assets/img/vscode-github.png"
---

# How to Link VS Code to GitHub: A Step-by-Step Guide

Connecting Visual Studio Code (VS Code) to GitHub is essential for developers looking to manage code, track changes, and collaborate effectively. This post covers everything you need to know to link VS Code to GitHub, including how to set up version control, commit changes, push code, ignore files, and manage branch names like `main` and `master`. 

Whether you’re new to Git or looking to streamline your workflow, this guide will walk you through every step.

---

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Setting Up Git in VS Code](#setting-up-git-in-vs-code)
3. [Creating a Repository on GitHub](#creating-a-repository-on-github)
4. [Initializing a Local Repository in VS Code](#initializing-a-local-repository-in-vs-code)
5. [Creating a `.gitignore` File](#creating-a-gitignore-file)
6. [Committing and Pushing Changes](#committing-and-pushing-changes)
7. [Managing Branches (`main` vs. `master`)](#managing-branches-main-vs-master)
8. [Additional Tips](#additional-tips)

---

## Prerequisites

Before you begin, make sure you have:
- **Git Installed**: Git must be installed on your machine. You can check by running `git --version` in the terminal. If not installed, download it from [git-scm.com](https://git-scm.com/).
- **GitHub Account**: Ensure you have a GitHub account. If not, create one at [github.com](https://github.com/).

You should also be familiar with basic Git concepts like repositories, commits, branches, and remotes.

---

## Setting Up Git in VS Code

VS Code integrates well with Git, making it easy to manage repositories. Here’s how to get started with Git in VS Code:

1. **Install Git** (if you haven’t already): Follow instructions from [git-scm.com](https://git-scm.com/) to install Git.
2. **Open VS Code** and go to `View > Command Palette` (or press `Ctrl+Shift+P`).
3. Type `Git: Enable` and select `Git: Enable in Workspace`. This enables Git features in your workspace.
4. **Check Git Status** in VS Code: You should now see a Source Control icon on the sidebar, which will indicate the Git status of your project.

---

## Creating a Repository on GitHub

1. **Go to GitHub** and log in.
2. **Create a New Repository**:
   - Click on the `+` icon in the upper-right corner and select **New repository**.
   - Enter a name for your repository (e.g., `my-project`).
   - Optionally, add a description.
   - Choose between making the repository **Public** or **Private**.
   - Do **not initialize** the repository with a README if you’re connecting from an existing project in VS Code.
   - Click **Create repository**.
3. **Copy the Repository URL**: Once the repository is created, GitHub will show you the URL (it should look like `https://github.com/username/my-project.git`). Copy this URL; you’ll need it to connect VS Code to GitHub.

---

## Initializing a Local Repository in VS Code

1. **Open Your Project Folder in VS Code**: Go to `File > Open Folder` and select the project folder you want to link to GitHub.
2. **Initialize Git**: Open the terminal in VS Code (`Ctrl+` ``) and run:
   ```bash
   git init

This will create a .git folder in your project directory, initializing it as a Git repository. 3. Link Local Repository to GitHub: Add GitHub as the remote origin by pasting the repository URL you copied earlier:

bash
Copy code
git remote add origin https://github.com/username/my-project.git
Check Connection: You can verify that the remote was added correctly by running:
bash
Copy code
git remote -v
Creating a .gitignore File
A .gitignore file specifies which files and directories Git should ignore, preventing sensitive or unnecessary files from being committed.

Create .gitignore: In your project’s root directory, create a file named .gitignore.

Add Files/Directories to Ignore:

To ignore the virtual environment folder, add venv/ or the name of your virtual environment folder.
To ignore system files and editor settings, add entries like .DS_Store, .vscode/, __pycache__/.
Example .gitignore:

plaintext
Copy code
# Ignore Python virtual environment
venv/

# Ignore Python cache files
__pycache__/
*.py[cod]

# Ignore editor settings
.vscode/

# Ignore system files
.DS_Store
Thumbs.db
Commit .gitignore:

bash
Copy code
git add .gitignore
git commit -m "Add .gitignore file"
Committing and Pushing Changes
Stage All Changes: Run the following command to add all changes to the staging area:
bash
Copy code
git add .
Commit Changes: Use a descriptive commit message to commit the changes:
bash
Copy code
git commit -m "Initial commit"
Push to GitHub: Push your code to GitHub using the main branch:
bash
Copy code
git push -u origin main
If you’re using master as the branch, replace main with master.
Managing Branches (main vs. master)
Branch Names in Git
Recent Git versions default to main as the default branch name instead of master. When working with older repositories or environments, you might encounter either name.

Check Your Branch: You can check your current branch by running:

bash
Copy code
git branch
Rename Branch (if needed):

If you want to rename the branch to main, you can run:
bash
Copy code
git branch -M main
Then push to GitHub:
bash
Copy code
git push -u origin main
Set Default Branch on GitHub: If you renamed your branch, go to your repository settings on GitHub, navigate to Branches, and set main as the default branch.

Additional Tips
Using VS Code’s Source Control Panel
VS Code’s Source Control panel makes it easy to manage Git without using the terminal. Here are some helpful features:

Staging Files: Click on the plus icon next to each file to stage changes, or click the "Stage All Changes" button.
Committing Changes: Enter a commit message in the text box and press Ctrl + Enter to commit.
Sync Changes: Once you’ve committed changes, you can push them by clicking on the cloud icon or "Sync Changes" button in the Source Control panel.
Using SSH for Authentication
GitHub has removed support for password-based authentication. To simplify authentication, consider setting up SSH keys:

Generate an SSH key by running:
bash
Copy code
ssh-keygen -t ed25519 -C "your_email@example.com"
Add the SSH key to GitHub by going to Settings > SSH and GPG keys and clicking New SSH key. Paste the contents of ~/.ssh/id_ed25519.pub (or your generated key).
Update your Git remote URL to use SSH:
bash
Copy code
git remote set-url origin git@github.com:username/my-project.git
Pulling Changes from GitHub
If you’re collaborating with others, regularly pull changes from GitHub to keep your local repository up-to-date:

bash
Copy code
git pull origin main
Replace main with master if applicable.

Common Commands Reference
Command	Description
git init	Initialize a new Git repository.
git add .	Stage all changes for commit.
git commit -m "message"	Commit changes with a message.
git remote add origin URL	Link local repo to GitHub repository.
git push -u origin main	Push code to GitHub on the main branch.
git branch -M main	Rename branch to main.
git pull origin main	Pull updates from GitHub’s main branch.
Conclusion
Linking VS Code to GitHub and managing repositories with Git is essential for any developer. By following this guide, you’ll be able to set up a repository, ignore unnecessary files, manage branches, and push changes to GitHub.
