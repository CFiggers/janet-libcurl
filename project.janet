(declare-project
  :name "janet-libcurl"
  :description "TODO: Write a cool description"
  :license "MIT"
  :dependencies [])

(declare-native 
  :name "janet-libcurl"
  :cflags ["-Wall" "-Wextra"]
  :lflags ["-pthread" "-lcurl"]
  :source ["janet_libcurl.c"])