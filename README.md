# build2 Packages for libigl Modules

[`libigl`](https://github.com/libigl/libigl) is a simple C++ geometry processing library separated into multiple modules that can be used either as header-only or as precompiled version. 

[![Official](https://img.shields.io/website/https/github.com/libigl/libigl.svg?down_message=offline&label=Official&style=for-the-badge&up_color=blue&up_message=online)](https://github.com/libigl/libigl)
[![build2](https://img.shields.io/website/https/github.com/build2-packaging/libigl.svg?down_message=offline&label=build2&style=for-the-badge&up_color=blue&up_message=online)](https://github.com/build2-packaging/libigl)

| Package | `cppget.org` | `queue.cppget.org`|
| :---    | :---         | :---              |
|`libigl-core` | [![cppget.org](https://img.shields.io/website/https/cppget.org/libigl-core.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/libigl-core) | [![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/libigl-core.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/libigl-core)|
|`libigl-opengl` | [![cppget.org](https://img.shields.io/website/https/cppget.org/libigl-opengl.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/libigl-opengl) | [![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/libigl-opengl.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/libigl-opengl)|
|`libigl-glfw` | [![cppget.org](https://img.shields.io/website/https/cppget.org/libigl-glfw.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/libigl-glfw) | [![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/libigl-glfw.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/libigl-glfw)|
|`libigl-imgui` | [![cppget.org](https://img.shields.io/website/https/cppget.org/libigl-imgui.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/libigl-imgui) | [![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/libigl-imgui.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/libigl-imgui)|
|`libigl-png` | [![cppget.org](https://img.shields.io/website/https/cppget.org/libigl-png.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/libigl-png) | [![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/libigl-png.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/libigl-png)|

## Usage
Currently, not all `libigl` packages can be found on `cppget.org`.
It is recommend to add this Git repository itself instead as a prerequisite to your `repositories.manifest` to be able to fetch the up-to-date packages of all provided libigl modules.

    :
    role: prerequisite
    location: https://github.com/build2-packaging/libigl.git

Otherwise, you will either have to add the stable or the alpha section of the `cppget.org` repository.

    :
    role: prerequisite
    location: https://pkg.cppget.org/1/alpha
    # trust: ...

Add the respective dependency in your project's `manifest` file to make the required packages available for import.

    depends: libigl-core ^2.5.0-
    depends: libigl-opengl ^2.5.0-
    depends: libigl-glfw ^2.5.0-
    depends: libigl-imgui ^2.5.0-
    depends: libigl-png ^2.5.0-

All the packages export only static libraries.
These can be imported by the following declarations in a `buildfile`.

    import igl = libigl-core%liba{igl-core}
    import igl = libigl-opengl%liba{igl-opengl}
    import igl = libigl-glfw%liba{igl-glfw}
    import igl = libigl-imgui%liba{igl-imgui}
    import igl = libigl-png%liba{igl-png}

Furthermore, every library supports immediate importation to access its metadata for querying whether it has been precompiled.

    import! [metadata, rule_hint=cxx.link] igl = libigl-core%liba{igl-core}
    precompiled = [bool] $($igl: libigl_core.precompiled)

## Configuration
### Precompilation

    config [bool] config.libigl_core.precompiled ?= true
    config [bool] config.libigl_opengl.precompiled
    config [bool] config.libigl_glfw.precompiled
    config [bool] config.libigl_imgui.precompiled
    config [bool] config.libigl_png.precompiled

`libigl` supports header-only and precompiled modes.
The default is to use the precompiled libraries as the header-only mode is only useful for small test projects and can get quite intensive for CPU and memory when compiling.
As of that, header-only mode should not be used for standard projects but only for small test builds.

Either all modules need to be used in header-only mode or all modules need to be precompiled.
Only `config.libigl_core.precompiled` from the `libigl-core` package decides this.
All other configuration variables are `undefined` on purpose.
As soon as specifying their value, the value will be traversed to dependent modules by dependency configuration negotiation.
With this approach only for one package the value needs to be specified.
If there are two specified inequal values, the negotiation will fail.

You should not state or require the precompilation or header-only mode in the `manifest` of your package as it is an implementation detail that every configuration should decide for itself.

## Issues and Notes
- Previous definite versions of libigl, fail to compile for strange reasons. So, the up-to-date main branch is used as an upstream reference, for now. To get around problems concerning versioning, we use alpha releases. `libigl` does not use alpha or beta releases. Esspecially, not for the upcoming version `2.5.0`. So, it seems to be a valid solution to use alpha versions for snapshots in this build2 packaging attempt.

### Unsupported Modules
- Currently unsupported `libigl` modules:
    + `copyleft/*`
    + `restricted/*`
    + `embree` (Embree is hard to build by yourself. Maybe we can rely on system installed versions?)
    + `predicates`
    + `spectra`
    + `xml` (probably easy to add)
- All Git submodules have been put into the `upstream` folder to provide a cleaner directory structure.
- In the upstream build, every dependency is loaded as an external project by CMake. We do not do that but need to keep track of their versions and commit references. Maybe add an entry to check that. Maybe we should add a general section on things to consider when trying to update the packages or release a new version?
- For easier inclusion of source files, several directory symlinks to `include/igl` are used.
- Unit tests are not provided for all modules of libigl. For such cases, only basic inclusion tests are used.
- For now, there is no stub package `libigl` that allows you to include all other modules at once by using `import igl = libigl%lib{igl}`. It is likely that it wouldn't be used that much.
- The generated `pkg-config` files for installation seem weird as preprocess options are missing and too many libraries are stated as link targets. Take a look into it, again.

### `core` Module
- For MSVC on Windows and for some source files, we need the `/bigobj` compile option. Currently, we apply it to all source files. This is probably overkill. Instead, we should figure out which of the source files need this option and adjust it in the precompiled static build and also the overall tests and tutorials.

- Build Times and Memory Usage: Intel `i7-7700K` with `8` jobs, `16 GiB` memory, Arch Linux with GCC `13.2.1` and the use of `-O3 -march=native`:
    + Header-Only Mode:
        * Building the Tests:
            - `~7.0 GiB`
            - `~3 min 50 s`
    + Precompiled Mode:
        * Building the Library:
            - `~5 GiB`
            - `~5 min 40 s`
        * Building the Tests:
            - `~3.2 GiB`
            - `~1 min 30 s`
- Build Times and Memory Usage: Intel `i9-13900K` with `32` jobs, `32 GiB` memory, Arch Linux with GCC `13.2.1` and the use of `-O3 -march=native`:
    + Header-Only Mode:
        * Building the Tests:
            - `~20 GiB`
            - `~50 s`
    + Precompiled Mode:
        * Building the Library:
            - `~13 GiB`
            - `~1 min 5 s`
        * Building the Tests:
            - `~12 GiB`
            - `~20 s`

### `opengl` and `glad` Module
- Currently, `libigl-opengl` is forced to use `libigl-glad` as OpenGL loader. For local workflows without installation, this is ok. We need to add the ability to change the loader library for global installation.
- `libigl-glad` should not be installed. It needs the KHR platform header. There should be a configuration to disable its use.

### `imgui` Module
- This module seems to be broken as even tutorials in header-only mode depending on it do not to work properly. In its precompiled version, it is not usable at all.
- Currently, ImGuizmo is not supported in the `libigl-imgui` package.
- Dear ImGui for `libigl-imgui` is compiled without `IMGUI_IMPL_OPENGL_LOADER_GLAD` and `IMGUI_DISABLE_OBSOLETE_FUNCTIONS` in contrast to the upstream build system. It does not seem to make a difference. See: `/upstream/libigl/cmake/recipes/external/imgui.cmake`
- `libigl-imgui` is not installable. The original module uses strange include paths for ImGui backends and its fonts. These paths are currently fixed by wrapper headers in the root of the package. But these headers should not be installed as they would pollute the global include folder.
    
### Tutorials
- As we currently do not support all modules, there are also tutorial entries that are not built by default as this would lead to compile errors. See: `libigl-tutorials/buildfile`
- The building of the tutorials in header-only mode is quite intensive and requires a lot of memory and time. The process will be aborted and probably fail when insufficient memory is encountered. Try to reduce the amount of jobs running by using something like `b -j 4`. Because of this, the tutorials will not be used for CI tests.
- Tutorials `104`, `701`, and `704` seem to not work correctly. Building these tutorials with the upstream CMake-based system works.

- Build Times and Memory Usage: Intel `i9-13900K` with `32` jobs, `32 GiB` memory, Arch Linux with GCC `13.2.1`, and the use of `-O3 -march=native`:
    + Header-Only Mode:
        * Not buildable as memory is insufficient for job count.
    + Precompiled:
        * `~8 GiB`
        * `~20 s`
- Build Times and Memory Usage: Intel `i9-13900K` with `8` jobs, `32 GiB` memory, Arch Linux with GCC `13.2.1`, and the use of `-O3 -march=native`:
    + Header-Only Mode:
        * `~16 GiB`
        * `~2 min 50 s`
    + Precompiled:
        * `~3 GiB`
        * `~20 s`

## Contributing
Thanks in advance for your help and contribution to keep this project up-to-date.
For now, please, file an issue on [GitHub](https://github.com/build2-packaging/libigl/issues) for everything that is not described below.

### Recommend Updating Version
Please, file an issue on [GitHub](https://github.com/build2-packaging/libigl/issues) with the new recommended version.

### Update Version by Pull Request
1. Fork the repository on [GitHub](https://github.com/build2-packaging/libigl) and clone it to your local machine.
2. Run `git submodule init` and `git submodule update` to get the current upstream directory.
3. Inside the `upstream/libigl` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged. Here, it is probably not a version but the newest commit from the master branch instead.
4. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
5. Update library version in `manifest` file if it has changed or add package update by using `+n` for the `n`-th update.
6. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
7. Run `bdep ci` and test for errors.
8. If everything works fine, make a pull request on GitHub and write down the `bdep ci` link to your CI tests.
9. After a successful pull request, we will run the appropriate commands to publish a new package version.

### Update Version Directly if You Have Permissions
1. Inside the `upstream/libigl` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged. Here, it is probably not a version but the newest commit from the master branch instead.
2. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
3. Update library version in `manifest` file if it has changed or add package update by using `+n` for the `n`-th update.
4. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
5. Run `bdep ci` and test for errors and warnings.
6. When successful, run `bdep release --tag --push` to push new tag version to repository.
7. Run `bdep publish` to publish the package to [cppget.org](https://cppget.org).
