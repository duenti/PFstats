# PFstats

PFstats is a set of programs and scripts devoted to analyze protein families using simple statistics. Its only mandatory input is a multiple sequence alignment in PFAM format, but availability of 3D structures can greatly improve the analysis.

Most of PFSTATS output is based on the calculation of conservation and correlation. In the sample alignment in the figure (right), there are variable levels of conservation – a strictly conserved tryptophan (W) in the first position, positions restricted to only two residue types (2, 5 and 7), and one position (3) which seems to be tolerant for very different residues. Also, every time there is an arginine (R) in position 5, there is also an aspartate (D) in position 2 – they seem to be correlated. Similarly, even though arginines are “common” in position 5, they are never present when there is a tyrosine (Y) in position 2 – there seems to be anti-correlation. Of course, there is no significance in such notions of correlation or anti-correlation unless this happens for a reasonable amount of sequences in a well sampled alignment. So, PFstats includes methods that filter alignments in order to ameliorate biased sampling (which is usually the case from alignments obtained automatically), and calculates correlation scores based on the odds of finding correlation by chance. Besides that, PFstats also includes methods for calculate residue conservation, coevolution analysis, automatic UniprotKb queries for residue-position annotation and many possible data visualization methods.

The software is still to be pubblished, but a complete description on the coevolution networks methodology used is available in the open-access article [Using Amino Acid Correlation and Community Detection Algorithms to Identify Functional Determinants in Protein Families.](http://www.plosone.org/article/info%3Adoi%2F10.1371%2Fjournal.pone.0027786)

## Getting Started

In order to run PFstats in a distinct operational system, the source code must be downloaded and compiled to a binary file. There is two ways to compile this program, the first involves download a bunch of small dependencies files through terminal, that can be hard to find in some systems or for people unfamiliar with the terminal. The second is easly, but involves download a whole IDE, so it might take longer to download and install. First of all, download (or clone) the PFstats source code at the GitHub page and extract it:

### Method 1 – Compiling through terminal

To compile through terminal, you will need to download the QT dependencies. For example, in a debian based system, it can be done by the following command:

```
sudo apt-get install qtbase5-dev qtbase5-dev-tools qt5-qmake libqt5webkit5-dev
```

To compile, go to the source code directory and run two more commands:

```
qmake -qt5
make -f Makefile
```

If everything works correctly, the binary file will be generated. Finnaly, put the binary in a same directory as the pflibs folder. Or set this path through the software through Options menu > Set Libraries Path.

### Method 2 – Compiling through QT Creator

Download QT Creator (Open source package) at https://www.qt.io/ide/. Make sure to install the 5.5 version.

Run QT creator and click in File > Open File or Project. Select the Pfstats.pro at the source code folder. Now the PFstats project may be loaded in the QT Creator. To compile it, change the compile mode from debug to release, the computer screen icon on the left, and press ctrl+r.

Finnaly, set up the visualization libraries (pflibs folder). You can either extract it to the PFstats binary folder or extract to a different folder and configure it in the PFstats window clicking in Option > Set Libraries Path.

## License

This project is licensed under the GPLV3 License.

## Contact

To report bugs and suggestions, please contact: nelifonseca@ufmg.br

More information can be found at http://www.biocomp.icb.ufmg.br/biocomp/software-and-databases/pfstats/