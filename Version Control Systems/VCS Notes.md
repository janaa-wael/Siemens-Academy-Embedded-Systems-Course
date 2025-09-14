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

![image-20250914222325104](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914222325104.png)

----------

![image-20250914222900029](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914222900029.png)

 slide shows a typical output from the command `git log --oneline --graph --all`, which displays the project's history in a structured, visual way.

#### 1. Commit Hash

- **What it is:** The long string of numbers and letters (e.g., `8a2f398`, `4084ae0`). This is a **unique identifier** for each commit (snapshot), generated by a cryptographic hash function.
- **Purpose:** It's like a fingerprint for that specific change. You use it to reference, inspect, or revert to that exact commit.

#### 2. Commit Message

- **What it is:** The descriptive text next to the hash (e.g., `Added an index to aid performance`).
- **Purpose:** This is a **crucial** note explaining *what* was changed and *why*. Good commit messages act as a history book for the project.

#### 3. Branches and Tags (Pointers)

- **What they are:** The labels in parentheses `(...)` are **branch names** and **tags**. They are pointers that move to different commits.
- **How to read them:**
  - `(maptomonkey/db_index)`: This is a **branch** named `db_index` from a user `maptomonkey`. The commit `8a2f398` is the latest on this branch.
  - `(origin/stubs-are-not-numbers)`: The `origin/` prefix indicates this is the state of the branch on the **remote server** (e.g., GitHub).
  - `(richsage/talk-attend)`: A local branch by a user `richsage`.

#### 4. Graph Structure (The Asterisks `*` and Lines `|`)

- **What it shows:** The indentation and connecting lines show the **branching and merging structure** of the project's history.
- **How to read it:**
  - Lines that **branch out to the right** (like the list under `9818699`) show a series of commits made on a feature branch.
  - A line that **comes back to the main line** (like `09ldf9c Merge branch...`) shows a **merge commit**. This is when the work from a branch was integrated back into another branch (often `main`).

#### 5. Key Takeaway:

This history is not just a linear list. It's a **tree** that visually tells the story of how the project was built:

- Developers created branches to work on new features (`talk-attend`, `db_index`) without disrupting the main code.
- They made a series of commits (`+ 6043d5c`, `+ 505860c`, etc.) to build those features.
- When the features were complete, they were **merged** back into the main line of development (`09ldf9c Merge branch...`).

This structure allows developers to work on multiple things simultaneously and collaborate efficiently.

--------------

![image-20250914222935598](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914222935598.png)

#### Part 1: Viewing History (`git log` & `git checkout`)

| Command                | Purpose & Explanation                                        |
| :--------------------- | :----------------------------------------------------------- |
| `git log`              | **Show the commit history.** This displays the list of commits (snapshots) in reverse chronological order (newest first). It shows the **commit hash**, **author**, **date**, and the full **commit message** (subject + body). |
| `git checkout <id>`    | **Time travel to a past commit.** This moves your **HEAD** (your current point of view) to a specific commit. This puts you in **"detached HEAD state"**—you are looking at the project's past state but are not on a branch. Useful for inspecting old code. **To return:** run `git checkout main` (or your branch name). |
| `git checkout -f <id>` | **Forcefully discard changes and switch.** The `-f` (force) flag **discards any uncommitted changes** in your working directory before switching to the commit. **Use with caution!** You will lose any work you haven't committed. |

#### Part 2: Comparing Changes (`git diff`)

This command is your magnifying glass. It shows you the **line-by-line differences** between states.

| Command                              | Purpose & Explanation                                        |
| :----------------------------------- | :----------------------------------------------------------- |
| `git diff`                           | **What have I changed but not staged?** Compares your **Working Directory** (your current, unsaved files) against the **Staging Area**. It shows changes you've made that you haven't yet run `git add` on. |
| `git diff --staged` (or `--cached`)  | **What have I staged for the next commit?** Compares the **Staging Area** (what you've `add`ed) against the last commit (**HEAD**). This is the final review before you run `git commit`. |
| `git diff <commit_id>`               | **How does my current work differ from a past commit?** Compares your **Working Directory** against a specific past commit. Useful to see all progress since a known point. |
| `git diff <old_commit> <new_commit>` | **What changed between two points in history?** Compares any two commits directly. This is the best way to see what was included in a specific update or between two versions. Replace `<commit_id>` with the first 7+ characters of the hash. |

---

![image-20250914222944536](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914222944536.png)

![image-20250914230637424](C:\Users\hp\AppData\Roaming\Typora\typora-user-images\image-20250914230637424.png)