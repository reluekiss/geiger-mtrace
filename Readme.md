<video width="640" height="480" controls>
  <source src="./demonstration.mp4" type="video/mp4">
  Your browser does not support the video tag.
</video>
<br>

Malloc geiger counter using LD_PRELOAD to intercept malloc calls and [raylib](https://github.com/raysan5/raylib) for the audio backend. This project is inspired by [Malloc Geiger](https://github.com/laserallan/malloc_geiger) and [Alloc Geiger](https://github.com/cuviper/alloc_geiger?tab=readme-ov-file).

This uses ld's dlsym so is not cross platform, also you will need to point the Makefile to where you have the dynamic library for raylib located if it is not under /usr/local/lib/.
It is however very easy to compile yourself of get from their [releases page](https://github.com/raysan5/raylib/releases).

To use with any program run:
```bash
LD_PRELOAD=./libgeigermtrace.so <program>
```

Quick start
```bash
make
make run
```
