# Frenet-Serret-formulas
C code for implementation and visualization of Frenet–Serret apparatus

An excellent explanation can be found here;
https://en.wikipedia.org/wiki/Frenet%E2%80%93Serret_formulas

Main code file: frenet.c
gif maker file: tt_gif

Edit: the track/path of the particle can be added in line-8 of the file frenet.c (self-explanatory)
Comment: try to have as a recent version of Gnuplot as possible

Run: use the following command to compile-run-gif make;
gcc -o frenet frenet.c -lm; ./frenet ; gnuplot tt_gif
