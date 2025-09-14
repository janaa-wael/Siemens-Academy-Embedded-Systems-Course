# Version Control Essentials

![image-20250914165024700](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914165024700.png)

- A Version Control System (VCS) is a software tool that helps track changes to files (usually source code, documents, or configurations) over time.

- Features:

  - **Tracks changes:** Every time you edit and save, the VCS records a new “version” of the file.
  - **History:** You can go back to any earlier version if something breaks.
  - **Collaboration:** Multiple people can work on the same project without overwriting each other’s work.
  - **Branching & merging:** Developers can create separate “branches” to test features, then merge them back into the main project.

  - **Backup & safety:** Since everything is stored in a repository, files are not lost easily.

  ### ![image-20250914165028501](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914165028501.png)

  - ## Repository

    - A **repository (repo)** is basically a **storage space** where your project and its history live.
    - A repository contains:
      - Your project files (code, documents, configs, images…).
      - The complete history of changes made to those files.
      - Metadata (commits, branches, contributors, etc.).
    - There are two kinds of repos:
      - **Local repository**: lives on your computer.
        - Created with `git init` or cloned from somewhere.
        - You work, commit changes, and keep a personal history.
      - **Remote repository**: lives on a server (like GitHub, GitLab, Bitbucket).
        - Used for backup & collaboration.
        - You “push” changes from local → remote, and “pull” changes from remote → local.

​	![image-20250914165851128](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914165851128.png)

- Two types of Version Control Systems:

  1- Centralized Version Control System

  - A **single central server** stores all files and history. (holds the codebase)
  - Developers check out files from the server and commit changes back.
  - Examples: **CVS**, **Subversion (SVN)**, **Perforce**.
  - **Advantages**: Everyone can see each other’s work easily, controlled access.
  - **Drawbacks**: If the central server goes down → no one can work or commit or access history. (Single Point of Failure)

  2- Distributed Version Control System

  - Every developer has a **full copy of the repository**, including history.

  - Better collaboration via branching and merging.

  - You can commit, branch, and work offline.

  - Later, you sync (push/pull) with a remote repo.

  - Examples: **Git**, **Mercurial**, **Bazaar**.

    **Advantages**:

    - No single point of failure.
    - Faster operations (local history).
    - Easier branching/merging.

![image-20250914180848613](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914180848613.png)

-----------------------------------------------

### Why companies keep using a legacy VCS:

1. **Existing Infrastructure**
   - They already have huge codebases and tooling built around the old VCS.
   - Migrating thousands of projects would be risky and expensive.
2. **Training & Culture**
   - Teams are already trained in the legacy system.
   - Switching means retraining everyone (time + cost).
3. **Integration with Other Systems**
   - Their build pipelines, CI/CD, issue trackers, and deployment tools may depend on that VCS.
   - Changing the VCS means rewriting automation scripts.
4. **Stability & Regulations**
   - In industries like automotive, aerospace, or banking, stability and audit trails matter more than “latest tech.”
   - If the system works reliably, they prefer not to change it.
5. **Cost of Migration**
   - Moving history from SVN/Perforce → Git is possible, but for very large repos, it’s painful.
   - Companies weigh: “Does the benefit of Git justify the cost of migration?”

-------------------------------------------

![image-20250914182044677](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914182044677.png)

- Git is a distributed version control system.

![image-20250914184122153](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914184122153.png)

### 1. **Working Directory (Workspace)**

- This is the folder on your computer where you edit files.
- Files here are just “normal files” until you tell Git to track changes.
- Example: You open `main.c`, edit it, save. At this point, Git only notices that it changed, but it’s not recorded yet.

### 2. **Staging Area (Index / Cache)**

- A “pre-commit” area where you put changes you want to save.

- You add files with:

  ```
  git add main.c
  ```

- This means: “I’m ready to include this change in my next snapshot (commit).”

- You can stage some files but not others — useful if you’re working on multiple things at once.

### 3. **Repository**

- Where Git actually stores **commits (snapshots of your project)** and all history.

- After staging, you run:

  ```
  git commit -m "message"
  ```

- This moves the changes from the staging area → into the **local repository**, permanently recorded.

----------------------------

![image-20250914191347664](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914191347664.png)

### Explanation of the Figure:

1. **Local (Disk) Side**
   - **Working Directory**:
      Where you create and modify files. These are the files on your computer.
     - When you run `git add`, changes move from the **Working Directory → Staging Area**.
   - **Staging Area (Index)**:
      A preparation space. Files added here are marked to be included in the next commit.
     - When you run `git commit`, the staged changes move from the **Staging Area → Local Git Repository**.
   - **Local Git Repository**:
      Stores the complete history of your project (commits, branches, tags).
     - From here, you can interact with the **Remote Git Repository**.

------

2. **Remote (Cloud) Side**

- **Remote Git Repository**:
   A copy of your repository stored on a server (e.g., GitHub, GitLab).
  - You use `git push` to send commits from local → remote.
  - You use `git fetch` to get updates from remote → local.

------

3. **Other Commands**

- **git checkout**: Moves changes from the repository to your working directory (e.g., switching branches or restoring files).
- **git merge**: Combines changes from one branch into another in your local repository.

###      4. Flow Summary:

1. Edit files in **Working Directory**.
2. Stage them with `git add` → goes to **Staging Area**.
3. Save snapshot with `git commit` → goes to **Local Git Repo**.
4. Share with team using `git push` → goes to **Remote Git Repo**.
5. Get updates from team using `git fetch` (or `git pull`) → brings changes from **Remote Git Repo → Local**.

------------------

- ## Git Commands

- ### Setup and Configuration

  ![image-20250914191334422](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914191334422.png)

  | Command                                 | Purpose & Explanation                                        |
  | :-------------------------------------- | :----------------------------------------------------------- |
  | `git init`                              | **Initialize a new repo.** Turns the current directory into a Git repository. Creates a hidden `.git` folder. |
  | `git init <dir>`                        | **Create & initialize.** Makes a new directory and initializes a Git repo inside it. |
  | `git config user.name/email`            | **Set identity (local).** Configures your name/email **for this specific repo only.** |
  | `git config --global user.name/email`   | **Set identity (global).** **Most common.** Sets your name/email for **all repos** on your computer. |
  | `git config core.editor`                | **Set text editor (local).** Chooses which editor Git uses for this repo (e.g., for writing commit messages). |
  | `git config --global core.editor`       | **Set text editor (global).** Sets your preferred editor for all Git repos on your machine. |
  | `git config --global credential.helper` | **Save credentials.** Caches your GitHub/username passwords so you don't have to enter them every time. |
  | `git help <command>`                    | **Get help.** Opens the official manual page for any Git command. |



- ### Staging & Committing

![image-20250914211305198](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914211305198.png)

| Command                  | Purpose & Explanation                                        |
| :----------------------- | :----------------------------------------------------------- |
| `git add <file>`         | **Stage a file.** Prepares a specific file to be saved in the next commit (snapshot). |
| `git add .`              | **Stage all changes.** Prepares **all** new and modified files in the current directory for the next commit. |
| `git reset <file>`       | **Unstage a file.** Removes a file from the staging area, but keeps your changes in the working directory. |
| `git commit`             | **Create a commit.** Opens your text editor to write a message for the new snapshot of all staged files. |
| `git commit -m "msg"`    | **Commit with a message.** Creates the snapshot immediately with the given message. **Always use a message!** |
| `git commit -a -m "msg"` | **Stage & commit tracked files.** A shortcut that stages all modified files that are already tracked **but ignores new, untracked files** and commits them. |