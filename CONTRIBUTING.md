# How to contribute to DGtal

In this document, we describe how to contribute to
[DGtal](http://dgtal.org) library and its
[DGtalTools](http://dgtal.org/tools) and
[DGtalTools-contrib](http://dgtal.org/tools) projects.  Please keep in
mind that DGtal is an open-source initiative under LGPL license.

A first way to contribute to the library is to give us feedbacks and
comments using
[Github issue tracker](https://github.com/DGtal-team/DGtal/issues). Do
not hesitate to create an issue (feature request, bug report, issues
with the documentation...).

## Contribution reviewing process

We process contributions to the library using GitHub Pull-request
mechanism. If you want to contribute, you would have to:
* create an account on GitHub;
* clone [DGtal](https://github.com/DGtal-team/DGtal) main repository
  (or [DGtalTools](https://github.com/DGtal-team/DGtalTools),
[DGtalTools-contrib](https://github.com/DGtal-team/DGtalTools-contrib));
* create a branch for your contribution and push it to your DGtal
  clone;
* create a GitHub pull-request to ask for an inclusion.

Each pull-request must contain:
* a [doxygen](http://doxygen.org) documented source-code satisfying
  the coding style (see below);
* a unit test file testing the features in the contribution (written
  using [Catch](http://catch-lib.net), see for instance
  [this tutorial](http://dgtal.org/doc/stable/moduleCatch.html));
* a user-oriented documentation page describing the feature (using
  [doxygen](http://doxygen.org));
* an informative pull-request comment describing the contribution;
* a new entry in the project ```Changelog.md``` file.

Once the pull-request has been sent, a DGtal package manager will
review the code and may ask for edits before being merged to the DGtal
master branch. Note that we use [Travis](http://travis-ci.org) as
Continuous Integration platform. When creating a pull-request, several
builds are tested on several systems (linux, macos), compilers (gcc,
clang) and configurations (DGtal dependencies). On Microsoft Windows
platforms, we use [Appeveyor](http://www.appveyor.com) service to test
DGtal build.  Before being merged, a pull-request must pass all these
tests.

More information are described in the
[DGtal documentation](http://dgtal.org/doc/stable/moduleFAQGit.html).

## Code Structure

### Folders

DGtal features are organized into
[packages](http://dgtal.org/doc/stable/) and modules
(e.g. [Geometry Package modules](http://dgtal.org/doc/stable/packageGeometry.html)). The
source code folders follows this decomposition:
* ```src/DGtal/```: the main source code tree.
* Each package has its own subfolder. For instance
  ```src/DGtal/kernel``` for the Kernel Package.
* Each package also contains its documentation pages
  (e.g. ```src/DGtal/kernel/doc```).
* ```tests/``` contains all unit test files. This folder is also
  decomposted into package folders (e.g. ```tests/kernel/``` for unit
  tests of the Kernel package modules).
* ```examples/```examples source files (mostly used for documentation
  purposes).
* ```cmake```contains all [cmake](http://cmake.org) configuration
  scripts.

### Namespaces

All DGtal classes and functions are contained in a ```DGtal::``` C++
namespace. Additionally, sub-namespaces are used to gather specific
codes:
* ```DGtal::functions::``` contains all DGtal global functions.
* ```DGtal::functors::``` contains all DGtal C++ functors.
* ```DGtal::concepts::``` contains all DGtal concepts.
* ```DGtal::experimental::``` contains classes and features that have a "beta" status.
* ```DGtal::Z2i::``` and ```DGtal::Z3i::``` are user-oriented
  namespaces that contain predefined types for digital geometry in
  dimension 2 and 3 (respectivelly) using an arithmetical kernel based
  on ```DGtal::int32_t```.
* ```DGtal::deprecated::``` contains deprecated classes  and functions.
* ```DGtal::detail::``` contains some internal classes and funcitons.


## Coding style

We expect the source code to match with some coding style rules
described below. We strongly encourage the developers to consider
scripts and unit-test/class templates provided in the
[DGtalScripts](https://github.com/DGtal-team/DGtalScripts)
project. These scripts can be used to create templates of classes and
tools that satisfy the guideline.

### Documentation

All classes, types, methods and members must be documented using
[doxygen](http://doxygen.org) syntax. Please use
[DGtalScripts](https://github.com/DGtal-team/DGtalScripts) scripts to
create package and module documentation pages.

### Indent style

The DGtal indent style follow
[Allman Style](https://en.wikipedia.org/wiki/Indent_style#Allman_style)
for C/C++ code. Here you have an example:

```c++
template< typename TemplatedType>
class NewClass
{
  public:
    typedef TemplatedType Type;

    void aMethod(const int aParameter)
    {
      if ( myMember == aParameter )
      {
        something1();
        something2();
      }
      else
      {
        somethingelse1();
        somethingelse2();
      }
      finalthing();
    }

    unsigned int myMember;
};
```
### Naming rules

* Types/methods/variable/classes in ```CamelCase```: (e.g.
```BreadthFirstVisitor```, ```myImage```...)
* methods, functions or variables start with lowercase letter
* Types start with capital letters (
  e.g. ```DigitalSurface```,```Value```...)
* Concepts classes start with a "C" (e.g. ```CInteger```, ```CSpace```
  ...)
* Class members are prefixed by "my" (e.g.  myImage, myParameter)
* Method or function parameter are prefixed by "a". For instance:

``` c++ void superFunction(const Value & aParameter); ```

### Other rules

* All file must contain a proper LGPL/GPL header. See the source files for examples.
* Class member accessors/mutators
 * accessors are usually not prefixed by "get" is is name by the class member
 * if the accessor needs some computations, it is prefixed by "get"

      `Value parameter()` (if a `Value myParameter` exists)

      `Value getParameter()` (there is "computation")

 * Setter methods are prefixed by "set"

      `anImage.setValue (...)`


## Contributor license agreement

At this point, we do not have Contributor License Agreement. However,
contributors must agree with DGtal LGPL license and include the
appropriate license header in their own code.

Documentation are published under the
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0](http://creativecommons.org/licenses/by-nc-sa/4.0/)
International License.

If you want your package to be distributed under different
licenses. Please contact us (see below).

## Contacts

If you have any questions, do not hesitate to contact the developers
on the mailing-lists:
[dgtal-devel@lists.gforge.liris.cnrs.fr](mailto:dgtal-devel@lists.gforge.liris.cnrs.fr)
or [contacts@dgtal.org](mailto:contacts@dgtal.org).
