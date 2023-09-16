import pkgs = {*/ -upstream/ -*-tests/ -*-tutorials/ -libigl-imgui/}
import tests = {*-tests/ *-tutorials/}
./: $pkgs
./: $tests: install = false
