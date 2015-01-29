# coding: utf-8

""" test reading/writing potentials to files """

from __future__ import division, print_function

__author__ = "adrn <adrn@astro.columbia.edu>"

# Standard library
import os, sys

# Third-party
import numpy as np
from astropy import log as logger
import astropy.units as u

# Project
from ..io import read, write
from ..builtin import IsochronePotential
from ...units import galactic

# TODO: config item to specify path to test data?
test_data_path = os.path.abspath(os.path.join(os.path.split(__file__)[0],
                                 "../../../test-data/"))

def test_read():
    f1 = os.path.join(test_data_path, 'potential', 'isochrone.yml')
    potential = read(f1)
    print(repr(potential))

def test_write():

    tmp_filename = "/tmp/potential.yml"

    # try a simple potential
    potential = IsochronePotential(m=1E11, b=0.76, units=galactic)

    with open(tmp_filename,'w') as f:
        write(potential, f)

    write(potential, tmp_filename)
