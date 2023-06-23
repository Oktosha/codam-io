# codam-io

## Overview

This project is a library written in C. It consists of input and output functions that can be used in rank2+ projects at [Codam](https://codam.nl/en) ([School 42](https://42.fr/en/homepage/)). The challenge is that high-level functions like `printf` are not permitted so we have to implement formatted output using only low-level calls like `write`.

The library is compliant with the school styleguide enforced by [norminnete](https://github.com/42School/norminette) (also a challenge).

## 🛠️ Usage

### Building

It should build on school computer with `make`. Run `make` in the root of this repo. The compiled library file will be `build/libcodamio.a`. You should include `codam_io.h` to get the function declarations. Add the `include` folder of this repo to the list of places you search for headers.

### Docs

All functions are documented in the header file `codam_io.h` in form of doxygen comments. VSCode picks up the docs automatically and shows them on hover (maybe you need some standard C++ extensions for this).

### Customization

You can change some behaviour through changing some macro defines. They are mostly about failfast behaviour (should the program fail on unsuccessful write?)

And, of course you can change the code or copy a part of the code to use in your project.

## 📃 Credits & Licence Notes

### Doom figlet font

I generated the section headers in `codam_io.h` on http://patorjk.com/software/taag/ using Doom font deloped by Frans P. de Vries in 1996 for [figlet app](http://www.figlet.org/) written in C by John Cowan. [Patrick Gillespie](http://patorjk.com/blog/about/), the author of the website, nicely retold the story behind ASCII-art fonts in the [about section](https://patorjk.com/software/taag/#p=about). You might want to follow the ASCII Arts links from there.

**License restrictions:** probably no restrictions

### Other things

I take for granted a lot of things I use. I'm not a lawyer to draw the line where the credit is due. Examples are: C language and its standard library, git, github, make, vscode, markdown, internet and computers. If you are a lawyer interested in creating templates that credit everything properly, I would love to participate in such project from the technical side (srsly, use contact data on my profile or the contact form (linked below) to start a conversation about it).

**License restrictions:** probably no restrictions

### My code

The repo was created by [Oktosha](https://github.com/Oktosha) and licensed under [unlicense](https://unlicense.org/) with the intent to allow you to do whatever you want with the code (no credit required) except for holding me liable.

**License restrictions:** no restrictions intended

### Overall licensing

As I stated my intent is to avoid imposing any restrictions. However, I couldn't find the proper ASCII-font license and I have a feeling that the proper way to use C is to include LGPL license with it. But anyway, licensing problems won't come from me.

**License restrictions:** probably no restrictions

## 📚 Further Reading

This project is a small peek into stuff I do at [Codam](https://codam.nl/en). You might be interested in other projects I did there. If so, go to my [codam-meta](https://github.com/Oktosha/codam-meta) repo with the actual info on my Codam projects (including group ones that aren't in my repos!).

I do some out-of-school coding, too. If you want the up-to-date info on my projects, got to my [github profile](https://github.com/Oktosha). At the moment of writing, I'm proud of the following:

+ [Advent of Code 2022 participation](https://github.com/Oktosha/aoc-2022): all stars gathered and I learned Kotlin!
+ [Raytracing in C++17 wrapped with Cython](https://github.com/Oktosha/ray-tracing): done in 2019 (hence the standard version choice) and it is mostly just another completion of [a very enjoyable tutorial](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley. The twist is that raytracing code is wrapped into a python module that can be used from Jupyter notebook. It was my first time wrapping C++ with Python and for me crossing the boundary between languages felt kinda magical. I guess that's why I'm so attached to this project even though no-one stars it (at the moment of writing)
+ The fact that I can still attest [my blue color](https://codeforces.com/profile/Dashk0) on Codeforeces

If you think we can collaborate, don't hesitate to contact me in some way listed on [my github profile page](https://github.com/Oktosha) or via [this form](https://forms.gle/GCa9ymrYwtTzgiCS8).

<p align="center">💜 💜 💜</p>
