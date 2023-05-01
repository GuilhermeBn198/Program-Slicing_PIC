# Frama-C Software Verification Tool Installation Tutorial (2023)

[Versão Pt-Br!](./translations/TutorialFramaCPTBR.md)

## **Installation:**

## Linux

### Simply follow the same procedure as the one done on Windows.

---

## Windows (WSL Ubuntu)

### 1. Open a terminal in your WSL Ubuntu.

### 2. Run the following command to update the package list:

```
	sudo apt-get update
```

### 3. Then, run the following command to install the required dependencies:

```
	sudo apt-get install -y m4 ocaml opam zlib1g-dev libsqlite3-dev libgmp-dev libgtk2.0-dev
```

### 4. Next, run the following commands to install the latest version of Frama-C:

```
	opam init --disable-sandboxing
	opam switch create 4.12.0
	eval $(opam env)
	opam update
	opam install frama-c
```

These commands initialize the OPAM package manager, configure a specific version of OCaml (4.12.0), update OPAM, and install Frama-C. <br><br>

### 5. When the installation is complete, you can test Frama-C with the following command:

```
	frama-c-gui
```

### This will launch the Frama-C graphical interface, where you can start working with the tool.

---

## Mac OS

### 1. Install Homebrew

-   Open a terminal on your macOS system and run the following command to install the Homebrew package manager:

```
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Install Required Dependencies

Run the following command to install the required dependencies:

```
	brew install opam ocaml-findlib gtk+ gtk-mac-integration sqlite3 gmp
```

### 3. Configure OPAM

Run the following commands to configure OPAM:

```
	opam init --disable-sandboxing
	opam switch create 4.12.0
	eval $(opam env)
	opam update
```

### 4. Install Frama-C

Run the following command to install Frama-C:

```
	opam install frama-c
```

### 5. Test Frama-C

When the installation is complete, you can test Frama-C with the following command:

```
	frama-c-gui
```

This will launch the Frama-C graphical interface and you can start working with the tool.

---

## to go back to the previous page: [Click me!](../README.md)
