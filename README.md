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

The respective header-only and precompiled libraries can be imported by the following declarations in a `buildfile`.
Please note, precompiled versions are only exported as static libraries by the packages.

**`core` Module:**

    import igl_core = libigl-core%lib{igl-core}
    import igl_core_compiled = libigl-core%liba{igl-core-compiled}

**`opengl` Module:**

    import igl_opengl = libigl-opengl%lib{igl-opengl}
    import igl_opengl_compiled = libigl-opengl%liba{igl-opengl-compiled}

**`glfw` Module:**

    import igl_glfw = libigl-glfw%lib{igl-glfw}
    import igl_glfw_compiled = libigl-glfw%liba{igl-glfw-compiled}

**`imgui` Module:**

    import igl_imgui = libigl-imgui%lib{igl-imgui}
    import igl_imgui_compiled = libigl-imgui%liba{igl-imgui-compiled}

**`png` Module:**

    import igl_png = libigl-png%lib{igl-png}
    import igl_png_compiled = libigl-png%liba{igl-png-compiled}

## Configuration
There are no configuration options available.

## Issues and Notes
- Currently unsupported libigl modules:
    + `copyleft/*`
    + `restricted/*`
    + `embree` (Embree is hard to build by yourself. Maybe we can rely on system installed versions?)
    + `predicates`
    + `spectra`
    + `xml` (probably easy to add)
- Due to the unsupported modules, there are also unsupported tutorial entries. See: `/libigl-tutorials/buildfile`
- Currently, ImGuizmo is not supported in the `libigl-imgui` package.
- Dear ImGui for `libigl-imgui` is compiled without `IMGUI_IMPL_OPENGL_LOADER_GLAD` and `IMGUI_DISABLE_OBSOLETE_FUNCTIONS` in contrast to the upstream build system. It does not seem to make a difference. See: `/upstream/libigl/cmake/recipes/external/imgui.cmake`
- `libigl-imgui` is not installable. The original module uses strange include paths for ImGui backends and its fonts. These paths are currently fixed by wrapper headers in the root of the package. But these headers should not be installed as they would pollute the global include folder.
- For now, there is no stub package `libigl` that allows you to include all other modules at once by using `import igl = libigl%lib{igl}`. Maybe it would be useful?
- Currently, `libigl-glfw` is forced to use `libigl-glad` as OpenGL loader. For local workflows without installation, this is ok. We need to add the ability to change the loader library for global installation.
- `libigl-glad` should not be installed. It needs the KHR platform header. There should be a configuration to disable its use.
- To compile and run the tests and tutorials, a lot of memory and computing power is needed. The process will be aborted and probably fail when not enough memory is present.
- For MSVC on Windows, everything including libigl should be compiled with `/bigobj`.
- Tutorials `104`, `701`, and `704` seem to not work correctly. Building these tutorials with the upstream CMake-based system works.
- Unit tests are not provided for all modules of libigl. For such cases, only basic inclusion tests are used.
- All Git submodules have been put into the `upstream` folder to provide a cleaner directory structure.
- In the upstream build, every dependency is loaded as an external project by CMake. We do not do that but need to keep track of their versions and commit references. Maybe add an entry to check that. Maybe we should add a general section on things to consider when trying to update the packages or release a new version?
- For easier inclusion of source files, several directory symlinks to `include/igl` are used.
- For now and specifically for the upcoming version `2.5.0`, libigl does not use alpha or beta releases. So, it is ok to use alpha versions for snapshots in this build2 repository.
- Previous definite versions of libigl, fail to compile for strange reasons. So, the up-to-date main branch is used as a reference.
- Probably, all the buildfiles do not contain enough comments.

## Contributing
Thanks in advance for your help and contribution to keep this package up-to-date.
For now, please, file an issue on [GitHub](https://github.com/build2-packaging/libigl/issues) for everything that is not described below.

### Recommend Updating Version
Please, file an issue on [GitHub](https://github.com/build2-packaging/libigl/issues) with the new recommended version.

### Update Version by Pull Request
1. Fork the repository on [GitHub](https://github.com/build2-packaging/libigl) and clone it to your local machine.
2. Run `git submodule init` and `git submodule update` to get the current upstream directory.
3. Inside the `upstream` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged. Here, it is probably not a version but the newest commit from the master branch instead.
4. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
5. Update library version in `manifest` file if it has changed or add package update by using `+n` for the `n`-th update.
6. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
7. Run `bdep ci` and test for errors.
8. If everything works fine, make a pull request on GitHub and write down the `bdep ci` link to your CI tests.
9. After a successful pull request, we will run the appropriate commands to publish a new package version.

### Update Version Directly if You Have Permissions
1. Inside the `upstream` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged. Here, it is probably not a version but the newest commit from the master branch instead.
2. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
3. Update library version in `manifest` file if it has changed or add package update by using `+n` for the `n`-th update.
4. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
5. Run `bdep ci` and test for errors and warnings.
6. When successful, run `bdep release --tag --push` to push new tag version to repository.
7. Run `bdep publish` to publish the package to [cppget.org](https://cppget.org).
