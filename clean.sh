#!/bin/bash
rm $(find | grep "\.o$")
rm $(find | grep "\.exe$")
rm $(find | grep "\.ilk$")
rm $(find | grep "\.pdb$")