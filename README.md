# janet-libcurl

A basic wrapper library for certain functions found in <curl/curl.h>. 

# Getting Started

Requires [Janet](https://www.github.com/janet-lang/janet) and [JPM](https://www.github.com/janet-lang/jpm).

1. Clone this repo (for e.g., with the GitHub CLI, `$ gh repo clone CFiggers/janet-libcurl`.)

2. Change directories into the cloned repo: `$ cd janet-libcurl`

3. Build the shared library by running `$ jpm build`.

4. To make `janet-libcurl` available as a Janet dependency anywhere on your system, run `$ jpm install` (on Ubuntu and similar systems, may required elevated permissions, e.g. `$ sudo jpm install`)

Now janet-libcurl can be imported at the Janet REPL or in a Janet source file using `(import janet-libcurl)`.

janet-libcurl provides a single function: `curl-easy`. Try it from the Janet REPL:

```bash
$ janet -l "./build/janet-libcurl"
repl:1:> (curl-easy "https://www.example.com")
```
