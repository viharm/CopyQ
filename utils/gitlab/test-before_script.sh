#!/bin/bash
set -ex

packages=(
    libkf5notifications5

    libqt5core5a
    libqt5gui5
    libqt5network5
    libqt5qml5
    libqt5waylandclient5
    libqt5widgets5
    libqt5svg5
    libqt5xml5
    libqt5test5

    libx11-6
    libxtst6
)

apt update

# Runtime libraries
apt -y install "${packages[@]}"
