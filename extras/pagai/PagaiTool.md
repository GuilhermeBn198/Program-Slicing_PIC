# Pagai tool

## What is it?

PAGAI stands for Path Analysis for invariant Generation by Abstract Interpretation

## Installation

-   The code is freely available. You can clone the latest version of the source code:

    -   Via HTTPS:

        -   ```bash
            git clone https://gricad-gitlab.univ-grenoble-alpes.fr/pagai/pagai.git
            ```

    -   Via SSH:
        -   ```bash
            git clone git@gricad-gitlab.univ-grenoble-alpes.fr:pagai/pagai.git
            ```

-   After the cloning, install the dependencies:

    -   ```bash
        sudo apt-get install libmpfr-dev libgmp3-dev libboost-all-dev cmake cmake-gui curl
        ```
    -   run `default_build.sh` to install all PAGAI dependencies and then PAGAI itself.
        -   NOTE THAT -> Installation may take a while, since there are several external dependencies to compile (LLVM, Cudd, Apron, …).

-   If you want to change one of those options, use a custom build. See the documentation on [the original website](https://pagai.gricad-pages.univ-grenoble-alpes.fr/install.html)

-   To clean up the directory built by default_build.sh, run `default_clean.sh`
-   If all goes well, w
