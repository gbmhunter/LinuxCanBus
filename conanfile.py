from conans import ConanFile, CMake, tools
import os

class LinuxCanBus(ConanFile):
    name = "LinuxCanBus"
    version = "0.1"
    license = "MIT"
    url = ""
    description = ""
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"
    exports = "*"
    requires = "gtest/1.8.0@bincrafters/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="./")
        cmake.build()

        # Run the unit tests once the build is complete
        # (NOTE: unit tests and package tests are separate issues!)
        self.run('./bin/UnitTests')

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%sexample" % os.sep)

    def package(self):
        self.copy("*.hpp", dst="include", src="include") # All header files included in package
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["LinuxCanBus"]