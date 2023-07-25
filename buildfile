import pkgs = {*/ -upstream*/ -*-tests/}
import tests = {*-tests/}
./: $pkgs
./: $tests: install = false
