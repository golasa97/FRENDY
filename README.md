
# FRENDY: Nuclear Data Processing Code
This is a fork of the JAEA nuclear processing code FRENDY. It's been modified to use CMAKE for compilation for parallel building and has been reorganized for better utilization of the c++ LSP.

## Dependencies
- **CMake**: Required for building the project.
- **GCC**: Default compiler (can be replaced with another compiler).
- **LAPACK**: Required for resonance reconstruction using R-matrix Limited.
- **Boost**: Required for testing.

Ensure all dependencies are installed before proceeding.

---

## Compilation Instructions

   ```bash
   cd FRENDY/frendy
   mkdir build && cd build
   cmake ../
   make -j<n> #Replace <n> with the number of processor cores
```
This produces a binary `frendy` in the `build/bin/` directory.

---

## Download
The FRENDY source code can be downloaded from the [JAEA website](https://rpg.jaea.go.jp/main/en/program_frendy/).

---

## Manual
For detailed instructions on using FRENDY, refer to the official manual:  
[https://doi.org/10.11484/jaea-data-code-2022-009](https://doi.org/10.11484/jaea-data-code-2022-009)

---

## Citation
If you use FRENDY in your research, please cite the following paper:

**K. Tada, A. Yamamoto, S. Kunieda, C. Konno, R. Kondo, T. Endo, G. Chiba, M. Ono, M. Tojo,**  
*"Development and verification of nuclear data processing code FRENDY version 2,"*  
*J. Nucl. Sci. Technol.* (2023).  
[https://www.tandfonline.com/doi/full/10.1080/00223131.2023.2278600](https://www.tandfonline.com/doi/full/10.1080/00223131.2023.2278600)
