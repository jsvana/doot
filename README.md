# doot

`doot` is Yet Another Dotfiles Manager(TM). Its novel feature is the automatic merging and updating of dotfiles with includes. This is useful for configuration systems that don't have an include mechanism.

## Usage

Dotfiles directory layout:

<dl>
  <dt>dotfiles/</dt>
  <dd>This includes all of your public-facing contents. Add any number of `.include path/in/private` directives. This should be synced to your repository.</dd>

  <dt>private/</dt>
  <dd>This includes all of your private included configs. This should be in your `.gitignore`.</dd>
</dl>

As an example, let's use `.ssh/config`:

    $ cat dotfiles/ssh/config
    Host awesome_host
      HostName cool.host.name
      Port 1337

    .include ssh/config.
    $ cat private/ssh/config
    Host super_secret_host
      HostName secret.host.name
      Port 12345
    $ doot dotfiles/ssh/config
    ...
    $ cat ~/.ssh/config
    Host awesome_host
      HostName cool.host.name
      Port 1337

    Host super_secret_host
      HostName secret.host.name
      Port 12345

To use the literal string `.include` in your configs, prefix it with `\` like so:

    \.include

## Motivation

Scowering documentation for all the different include mechanism for systems (and eventually finding that they don't exist) is really frustrating. Instead, I propose a [15th Standard](https://xkcd.com/927/) to solve the problem.

## Installation

Currently you'll need a compiler with C++1z support (I'm using G++ 6.2.1). This also only supports Linux.

    $ bfg9000 configure build
    $ cd build
    $ ninja
    $ ./doot --help

## License

[MIT](LICENSE)
