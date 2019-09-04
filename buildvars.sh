# The Travis-CI auto build system tests the psp submodule by building it in the context of the
# cFS tree. The CFE_BRANCH environment variable is used by the auto-build system to specify
# which branch of the cFE tree will be used.
export CFS_BRANCH="task_3015"

# The auto build system makes a clone of the cFS tree in order to build the applications in
# order to build the applications. The following variable points to the get repository that
# is to be cloned.
export CFS_GITREPO="https://github.com/travis-r-wheatley/cFS.git"
