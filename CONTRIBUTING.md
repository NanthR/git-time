# Contributing to git-time

Here are a the guidelines to follow

- [Setting up the project](#setting)
- [Setting up githooks](#githooks)
- [Additional dependencies for development](#add)

## <a name="setting"></a>Setting up the project
- Fork and clone the the repository and add this as remote upstream.
- Only work on the develop branch.
- Make sure to enable [githooks](#githooks) for proper formatting of code.
- Pull latest changes from upstream before pushing your code.
- Send a pull request to this repo for review and merging.

## <a name="githooks"></a>Setting up githooks

Run `git config core.hooksPath .githooks` once after cloning the repo.

---

**NOTE:**

Never push directly to this repo, i.e, upstream. Always push to your forked repo and send a pull request to the main repo.

---

## <a name="add"></a>Additional Dependencies
	- python
	- [clang-format](https://pypi.org/project/clang-format/)
	- [cmake-format](https://pypi.org/project/cmake-format/)
