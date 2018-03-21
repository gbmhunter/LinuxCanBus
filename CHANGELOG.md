# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v1.1.2] - 2017-12-13

### Added
- '-f' flag to codecov bash script so that it considers the curated coverage.info file only.

## [v1.1.1] - 2017-12-13

### Changed
- Removed install of cpp-coveralls via pip from .travis.yml file.

## [v1.1.0] - 2017-11-29

### Added
- Basic code coverage functionality working correctly.
- Added info on code coverage support to README.

### Changed
- Moved the code coverage upload commands out of .travis.yml and into build.sh.
- Build script now filters out code coverage reports for the test folder (only src/ and include/ coverage information should be included).

## [v1.0.6] - 2017-11-29

### Added
- The start (untested) of code coverage support using www.codecov.io.

## [v1.0.5] - 2017-11-27

### Added
- Added info on Doxygen support to README, including link to example documentation on GitHub pages.

## [v1.0.4] - 2017-11-27

### Changed
- Moved `doc` folder to `docs` for GitHub pages support.

## [v1.0.3] - 2017-11-27

### Added
- Added support for Doxygen, including template `doxygen.conf` file.
- Added support for displaying documentation using GitHub pages.

## [v1.0.2] - 2017-11-27

### Added
- Added 'sudo: required' and 'dist: trusty' statements to the TravisCI config file.
- Added features section to the README.

## [v1.0.1] - 2017-11-27

### Added
- Installation instructions to the README.

### Fixed
- Removed old/incorrect information from README.
- Fixed incorrect URLs in CHANGELOG.md.

## [v1.0.0] - 2017-11-27

### Added
- Basic template source code.
- Basic template unit tests.
- This CHANGELOG.md file.

[Unreleased]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.1.2...HEAD
[v1.1.2]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.1.1...v1.1.2
[v1.1.1]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.1.0...v1.1.1
[v1.1.0]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.6...v1.1.0
[v1.0.6]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.5...v1.0.6
[v1.0.5]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.4...v1.0.5
[v1.0.4]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.3...v1.0.4
[v1.0.3]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.2...v1.0.3
[v1.0.2]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.1...v1.0.2
[v1.0.1]: https://github.com/mbedded-ninja/CppTemplate/compare/v1.0.0...v1.0.1