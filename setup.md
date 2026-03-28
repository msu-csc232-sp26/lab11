# ⚙️ Setup

Included in this repository is a script named [`setup.sh`](./setup.sh) that installs all the tools used by the GitHub actions that ultimately grade your assignment and that can be utilized by an IDE to help write code using modern styles and practices. This script is intended to run in a Debian distribution of Linux (e.g., Ubuntu). Our codespaces run Ubuntu, so it is advised you develop in a codespace.

To run this script (and it should be the first thing you do), simply open a terminal window and type:

```shell
sudo ./setup.sh
```

This script might take a minute or two to complete. You might also find a manual decision to make for configuring the
`openssh-server`.

```
Configuring openssh-server
--------------------------

A new version (/tmp/tmp.1tzvgwylD9) of configuration file /etc/ssh/sshd_config
is available, but the version installed currently has been locally modified.

  1. install the package maintainer's version
  2. keep the local version currently installed <-- choose this option
  3. show the differences between the versions
  4. show a side-by-side difference between the versions
  5. show a 3-way difference between available versions
  6. do a 3-way merge between available versions
  7. start a new shell to examine the situation
What do you want to do about modified configuration file sshd_config?
```

Depending on your terminal window and font sizes, you may not see all the options immediately (in which case you'll see `[More]` -- just hit the space bar until you see the prompt question). Select option **2** to `keep the local version currently installed`.

You'll see the following message when the script completes successfully:

```
All specified packages have been installed successfully.
```

and you'll be back at the command line prompt.

## Codespaces

If a Codespace is available for use (and this is your preferred method of development), open your newly created repository in a Codespace.

At this point, you can skip to [Creating a development branch](#creating-a-development-branch).

## Local Development

Depending upon the IDE of your choice, many of the following steps may be taken within your IDE. It is up to you to discover these tools (assuming they're available) and learn how to use them appropriately as desired. The following instructions are assumed to take place within a terminal window. Note: many IDEs provide a terminal window as well.

### Cloning your repository

The command you use to clone is slightly different depending upon whether you're using `git` via `https`, `ssh`, or using the GitHub Cli via `gh`.

If you're using the `https` protocol, your clone command is:

```shell
git clone https://github.com/msu-csc232-fa25/<repo-name>.git
```

If you're using the `ssh` protocol, your clone command is:

```shell
git clone git@github.com:msu-csc232-fa25/<repo-name>.git
```

Finally, if you're using the GitHub CLI (`gh`), your clone command is:

```shell
gh repo clone msu-csc232-fa25/<repo-name>
```

After cloning the repository, navigate into the newly cloned repository:

```shell
cd <repo-name>
```

### Creating a development branch

Next, create a branch named `develop`. Please note: The name of this branch **must** be as specified and will be, to the grading scripts, case-sensitive.

```shell
git checkout -b develop
```

Make sure you are on the `develop` branch before you get started. Make all your commits on the `develop` branch.

```shell
git branch
```

_You may have to type the `q` character to get back to the command line prompt after viewing the status. If this annoys you, it can be configured to not exemplify this behavior. Simply type the following in your terminal window:_

```shell
git config --global pager.branch false
```

### Manually formatting your files

Here's a linux command you can run from the root folder of your repositories terminal window to automatically reformat your files (if it can) in place:

```shell
find ./include ./src -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cpp' | xargs clang-format -i
```

* `find` generates a list of file names that match the file patterns
* `|` is the pipe symbol; it's "piping" the list of file names found by the previous command (`find`)
* `xargs` takes each of these file names piped into it, and supplies it as an argument to the
* `clang-format` command, which is executed in the interactive switch (`-i`) so as to make the changes in place

This is something you should get in the habit of doing to ensure you're getting full points on your style category of your assignments. This command _presumes_ you have run the [`setup.sh`](./setup.sh) script first, which installs the clang-format program. See [Setup](#-setup).
