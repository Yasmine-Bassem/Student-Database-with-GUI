# 🚀 Student Database System | Modern GUI & Cache System in C++

A modern **Student Management System** built in **C++** using **GTK GUI** and **CSS** styling, as part of our Data Structures course project.

## 💻 Team Members
- Yasmine Bassem  
- Marwa Hamza  
- Yahia Mohamed  
- Youssef Samy  

---

## ✨ Key Features
- 🖥️ **GTK GUI** – Styled using CSS for a modern user experience  
- 🔗 **Linked List Implementation** – O(1) insertion/deletion, O(n) traversal  
- 💾 **CSV Cache System** – Persistent file storage and auto-load on startup  
- ✏️ **CRUD Operations** – Create, Read, Update, Delete with full input validation  
- 📊 **Grade Management** – Track and calculate subject grades  
- ✅ **Validation System** – Check for:
  - Duplicate student IDs
  - Alphabetic name formatting
  - Grade range (0–100)
- ❌ **Error Handling** – Clear messages for invalid actions  
- 🔧 **Modular Architecture** – UI, logic, and data layers separated  

---

## 📸 Screenshot

![1](https://github.com/user-attachments/assets/97c80a31-f1c8-4f4b-a137-f850b708fef4)

---

## 🧩 Requirements

To run this project, you need to install:
- GTK (via MSYS2)
- GCC Compiler
- Code::Blocks (or any C++ IDE)

---

## ⚙️ Setup Instructions (Windows)

### 1. Install MSYS2:
Download and install MSYS2 from [https://www.msys2.org](https://www.msys2.org)

### 2. Update packages:
```bash
pacman -Syu
pacman -Su
```

### 3. Install dependencies:
```bash
pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config
pacman -S mingw-w64-x86_64-atk
pacman -S mingw-w64-x86_64-gdk-pixbuf2
pacman -S mingw-w64-x86_64-harfbuzz
pacman -S mingw-w64-x86_64-pango
pacman -S mingw-w64-x86_64-cairo
```

### 4. Setup Code::Blocks:
- Go to **Settings > Compiler > Search Directories**
- Add paths for MSYS2 MinGW include and lib folders.
- In **Linker settings**, add required GTK libraries (no need to include full path).

---

## 🎥 Demo Video
📽️ [Click here to watch the demo](https://drive.google.com/file/d/1gCCE7H-yV13swy9MiS2jrgVZfMtohv6_/view?usp=drive_link)  

---

## 📁 How to Run

1. Open the project in Code::Blocks
2. Make sure all dependencies are correctly set (as above)
3. Build & Run the project


