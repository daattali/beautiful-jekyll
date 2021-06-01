---
layout: page
title: For Users
---

To use DGtal in your own project, a very nice solution exists with *cmake*: here you have an example to build a DGtal *helloword*:

``` cmake
PROJECT(Helloworld)

### Required in DGtal
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

ADD_EXECUTABLE(helloworld helloworld)
TARGET_LINK_LIBRARIES(helloworld ${DGTAL_LIBRARIES})
```

See the [documentation][1] for details. DGtal is a free-software (Lesser Gnu Privacy License - LGPL) so you can freely use it and distribute it. However, if you use DGtal in your own project, we would be pleased to be kept in touch. If you want to refer to DGtal in your publications, please use the following bibtex entry:

``` bibtex
@Misc{DGtal,
  title = {DGtal: Digital Geometry tools and algorithms library},
  note = {\url{http://dgtal.org}}
}
```
## Projects/Publications using DGtal

*   ANR Grant [digitalSnow][2] (ANR-11-BS02-009) "Digital Geometry and Applied Mathematics for Snow Metamorphism"
*   Longuetaud, F.; Mothe, F.; Kerautret, B.; Krähenbühl, A.; Hory, L.; Leban, J. &amp; Debled-Rennesson, I. Automatic knot detection and measurements from X-ray CT images of wood: A review and validation of an improved algorithm on softwood samples.
*   Computers and Electronics in Agriculture, 2012, 85, 77-89
*   Kowalczyk, M. K.; Kerautret, B.; Naegel, B. &amp; Weber, J.,Revisiting Component Tree Based Segmentation Using Meaningful Photometric Informations. *Proc of International Conference ICCVG, Springer, 2012, 7594, 475-482*

 [1]: http://dgtal.org/doc/stable/moduleHowToUseDGtal.html
 [2]: http://liris.cnrs.fr/dsnow
