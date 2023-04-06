# Tutorial de instalação da ferramenta de verificação de software Frama-C (2023)

## Instalação:
## Linux
### basta realizar o mesmo procedimento feito na operação do Windows.
---
## Windows(WSL Ubuntu)
   

### 1 - Abra um terminal no seu WSL Ubuntu.
### 2 - Execute o seguinte comando para atualizar a lista de pacotes:

```
sudo apt-get update
```

### 3 - Em seguida, execute o seguinte comando para instalar as dependências necessárias:

```
sudo apt-get install -y m4 ocaml opam zlib1g-dev libsqlite3-dev libgmp-dev libgtk2.0-dev
```

### 4 - Em seguida, execute o seguinte comando para instalar a versão mais recente do Frama-C:

```
opam init --disable-sandboxing
opam switch create 4.12.0
eval $(opam env)
opam update
opam install frama-c
```

#### Estes comandos inicializam o gerenciador de pacotes OPAM, configuram uma versão específica do OCaml (4.12.0), atualiza o OPAM, e em seguida, instala o Frama-C. <br><br>


### 5 - Quando a instalação estiver concluída, você pode testar o Frama-C com o seguinte comando:

```
frama-c-gui
```

### Isso iniciará a interface gráfica do Frama-C, onde você pode começar a trabalhar com a ferramenta.

---
## Mac OS
### 1. Instalar o Homebrew
Abra um terminal no seu sistema macOS e execute o seguinte comando para instalar o gerenciador de pacotes Homebrew:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Instalar as dependências necessárias
Execute o seguinte comando para instalar as dependências necessárias:

```
brew install opam ocaml-findlib gtk+ gtk-mac-integration sqlite3 gmp
```

### 3. Configurar o OPAM
Execute o seguinte comando para configurar o OPAM:

```
opam init --disable-sandboxing
opam switch create 4.12.0
eval $(opam env)
opam update
```

### 4. Instalar o Frama-C
Execute o seguinte comando para instalar o Frama-C:

```
opam install frama-c
```

### 5. Testar o Frama-C
Quando a instalação estiver concluída, você pode testar o Frama-C com o seguinte comando:

```
frama-c-gui
```

Isso iniciará a interface gráfica do Frama-C, onde você pode começar a trabalhar com a ferramenta. 
