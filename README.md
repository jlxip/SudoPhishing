# SudoPhishing

## Description
SudoPhishing is a pentesting tool for GNU/Linux systems. It modifies the call to `sudo` so that the user's password can be extracted and stored in a local file. This could be used as [part of another tool](https://github.com/jlxip/SudoPhishing-POC) in order to easily perform privilege escalation.

## Method
The program is based on the `-A` parameter of sudo, which, in a nutshell, executes a third party program to manage the user input.

The compiled binary is a dropper. Once executed, it will get the default shell, and modify its local profile (`~/.bashrc` for `bash`, `~/.zshrc` for `zsh`...). It will set the environment variable `SUDO_ASKPASS` to SudoPhishing (which will be dropped at `~/.config/.aux`) and create an alias from `sudo` to `sudo -A`.

This way, when the user opens a new terminal and runs `sudo`, everything will look as usual, but the password will be stored in plain text to `~/.config/._`.

## Compilation
In order to compile SudoPhishing, `TCC` must be installed on the system. As the executable will be a dropper, using `GCC` would end up giving a heavy binary. `python2` must be present as well. To compile the source, just run `make`.

## Copyleft
Copyright (C) 2019 jlxip

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
