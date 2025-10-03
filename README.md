
# drinkDB

A cross-platform application for managing and exploring drink recipes.

---

## 🚀 Windows Compilation Instructions

```bash
git clone https://github.com/NikolaPeric286/drinkDB
cd drinkDB
git submodule update --init --recursive
cd build
cmake .. -G Ninja
ninja
```

---

## 🐧 Linux Compilation Instructions

Before running the program with GUI support, ensure that your display variables are set properly:

```bash
git clone https://github.com/NikolaPeric286/drinkDB
cd drinkDB
git submodule update --init --recursive
cd build
cmake ..
make 

export DISPLAY=$(grep -m1 nameserver /etc/resolv.conf | awk '{print $2}'):0
export LIBGL_ALWAYS_INDIRECT=1
```



---

## 📌 Notes

- This repository uses Git submodules. Make sure to include `--recursive` when cloning or run `git submodule update --init --recursive` after cloning.
- Linux users running in WSL2 may need to install an X server (like Xming or VcXsrv) to see the GUI.

---

## 🔧 Future Additions

This README will be updated as new features, dependencies, and platform-specific instructions are added.
