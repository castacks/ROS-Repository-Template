#!/usr/bin/env python3
from catkin_pkg.python_setup import generate_distutils_setup
from distutils.core import setup

setup_args = generate_distutils_setup(
    scripts=["scripts/new_package_node.py"],
    packages=["new_package"],
    package_dir={"": "src"},
)

setup(**setup_args)
