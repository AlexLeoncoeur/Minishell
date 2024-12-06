# Minishell 

Welcome to **Minishell**, a project from **42 School**! This repository is dedicated to creating a minimal Unix shell, helping you dive deep into the world of system programming and Unix internals.

---

## 📖 What is Minishell?  

Minishell is a simplified version of a Unix shell, like `bash` or `zsh`. You’ll implement essential shell features such as:  
- Parsing and executing commands.  
- Managing processes and signals.  
- Handling environment variables.  
- Implementing features like redirections (`>`, `<`) and pipes (`|`).
- Minishell is done with a partner. We learned to divide tasks, communicate effectively, and use tools like `git` to collaborate.  

---

## ✨ What can be learn?  

### 🔧 **System Calls**  
You’ll gain hands-on experience with system calls like:  
- `fork()`, `execve()`, `waitpid()`  
- `pipe()`, `dup2()`, `kill()`  

### 🗂️ **File Descriptors and I/O Redirection**  
Learn how to handle standard input/output and redirect streams effectively.  

### 🧠 **Process Management**  
Understand how parent and child processes interact and how to handle concurrent processes.  

### 🐛 **Debugging Skills**  
Build robust error handling and debugging skills while managing signals and memory leaks.  

### 🧹 **Memory Management**  
Become proficient in managing heap memory using tools like `valgrind` to ensure no memory leaks occur.  

---

## 🚀 How to Use Minishell  

### 🛠️ **Installation**  
1. Clone the repository:  
   ```bash  
   git clone https://github.com/yourusername/minishell.git  
   cd minishell  
   ```  
2. Compile the project:  
   ```bash  
   make  
   ```  

### 🏃 **Running Minishell**  
Start your shell by running the executable:  
```bash  
./minishell  
```  
---

## 📜 Project Requirements  

- **Mandatory Features:**  
  - Command execution with arguments.  
  - Environment variables and `$` expansion.  
  - Redirections (`<`, `>`).  
  - Pipes (`|`).  
  - Signal handling (`CTRL+C`, `CTRL+D`, `CTRL+\`).  

- **Bonus Features:**  
  - Advanced redirections (e.g., `<<`, `>>`).  
  - Command history and auto-completion.  

---

## 🐞 Known Issues  

Here are issues and limitations to be aware of when using or working on our Minishell:
  - To run executables you need to be in the executable's folder or use an absolute path. Relative paths haven´t been implemented.
