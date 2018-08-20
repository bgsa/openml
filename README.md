# OpenML
> Open Math Library is a cross-plataform math library for the new generation of computer graphic APIs, such as Vulkan, OpenGL-ES.


Main Features:

* Made with high legibility - clean code;
* Refactor friendly - covered by unit tests;
* Built with Microsoft Studio or VSCode or whatver tools with CMake support;
* Take advantage with C++11 features;

![](header.png)

## Installation

OS X & Linux:

```sh
mkdir build && cd build
cmake .. && build .
```

* Copy the header files and static/dynamic library to your IDE.

Windows:

* Copy the header files and static/dynamic library to your IDE.

## Usage example

auto transformationMatrix = worldMatrix * viewMatrix * projectionMatrix;
---
bool intersect = line.isOnTheLine(point);


## Meta

Bruno Gallego – [@Bruno_Gallego] – brunogsa@live.com

Distributed under the GNU license. See ``LICENSE`` for more information.

[https://github.com/bgsa/github-link](https://github.com/dbader/)


## Contributing

1. Fork it (<https://github.com/bgsa/openml/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki
