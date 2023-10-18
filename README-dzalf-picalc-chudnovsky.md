
**Preparation**

_This guide was prepared using Ubuntu 22.04.2 LTS on WSL2 for Windows_

1. Clone this repository and enter the folder
`https://github.com/dzalf/picalc-chudnovsky.git`

2. Update and upgrade distribution
`sudo apt-get update && sudo apt-get upgrade -y`

2. [Optional] Install micro editor (better than Nano :wink:)
`sudo apt install micro`

**Installing prerequisites**

1. Install g++/gcc development libraries, cmake and pkg-config
`sudo apt install build-essential cmake pkg-config`

2. Install MPFR through the [Ubuntu Package](https://launchpad.net/ubuntu/+source/mpfrc%2B%2B):
`sudo apt install libmpfrc++-dev`

3. Install the [MPFR C++ header]()https://github.com/advanpix/mpreal_ (cloning the repo)
```
git clone https://github.com/advanpix/mpreal
```

4. Install [ncurses](https://en.wikipedia.org/wiki/Ncurses)
`sudo apt-get install libncurses5-dev libncursesw5-dev`

5. Install [tclap](https://launchpad.net/ubuntu/+source/tclap)
`sudo apt install libtclap-dev`

6. Install meson (includes ninja)
`sudo apt install meson`

**Compilation**

1. Compile with: `meson setup build`

If successful run `ninja -C build` otherwise install missing dependencies

**Running**

Enter the `build` directory and execute `./picalc-chudnovsky`

If some modifications are made, recompile with:

`meson build --reconfigure`


**Extras**

1. Upgrading gcc:

https://tutorialforlinux.com/2023/07/28/gcc-13-1-debian-bullseye-installation-step-by-step/2/

https://mirrorservice.org/sites/sourceware.org/pub/gcc/releases/gcc-13.2.0/

Modified `util.h` header file:

```cpp
	
	// util.h
	template <typename T, typename U> void print_percent(const T a, const U b) noexcept;
	
	// util.cpp
	template <typename T, typename U>
	void print_percent(const T a, const T b) noexcept
	{
		double rel = (double)a / (double)b;
		rel *= 100;
		if (rel == 0.0f)
			cout << "\r  0.0% " << std::flush;
		else if (rel == 100.0f)
			cout << "\r100.0% " << std::flush;
		else if (rel < 10.0f)
			cout << "\r  " << std::fixed << std::setprecision(1) << rel << "% " << std::flush;
		else
			cout << "\r " << std::fixed << std::setprecision(1) << rel << "% " << std::flush;
	}

```