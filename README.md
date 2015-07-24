q2d
===

An editor for digital circuit schematics.
The focus lies on circuits build from configurable components such as LUTs or CMUXs.
It can evaluate if a given behaviour can be fulfilled by the designed circuit.

Current State
=============
Not dead, only asleep. 
Due to some questionable choices and lack of Qt-knowledge the current version has some design flaws.
A better design is in active development and a rewrite into **q2d 0.2** is scheduled for early 2016.

Features
========

* Support for user-generated components
* Automatically generated circuit symbols for components
  * Alternatively, custom symbols can be specified if desired

Releases
========

Currently the application is in the early *alpha* stage.
Releses are provided as source code only and can be found [here](https://github.com/fer-rum/q2d/releases) (incl. release notes).

Dependencies
============

Required to build and run:
* [*Qt*](http://doc.qt.io/qt-5/), version 5.4 ([Download](http://www.qt.io/download-open-source/))

*q2d* requires external tools to be able to solve the mapping of functions onto circuit designs:
* [*Quantor*](http://fmv.jku.at/quantor/) release 3.2 
* [*picosat*](http://fmv.jku.at/picosat/) release 960

Their source code must be put in the main q2d directory or the q2d.pro file must be adjusted to contain the correct paths.

Component descriptor files
==========================

These files describe components that can be used within the tool.
For those, who do not want to write these files by hand, a collection of pre-fabricated descriptor files can be found in the [q2d component repository](https://github.com/fer-rum/q2d-components).

Misc
====

Pronounced as きゅとで. At least for now.
